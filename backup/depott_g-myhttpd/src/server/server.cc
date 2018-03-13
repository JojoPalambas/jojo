#include <cstring>
#include <string>
#include "server.hh"
#include <unistd.h>
#include <cstdlib>
#include <sys/epoll.h>

#include "../response/http_response.hh"
#include "../host/host.hh"
#include "../exception/global-exception.hh"
#include "../exception/epoll-create-exception.hh"
#include "../exception/epoll-ctl-exception.hh"
#include "../exception/wait-fail-exception.hh"
#include "../exception/add-fail-exception.hh"
#include "../exception/accept-fail-exception.hh"

Server::Server(std::string name, std::string port, std::string ip,
               std::string root_dir, bool log, std::string log_file)
  : name_(name), port_(port), ip_(ip), root_dir_(root_dir)
    , log_file_(log_file)
  , log_(log)
    ,serv_sockt_(-1)
{
  w8_loop = true;
}

  Server::~Server()
  {
    // FIXME implement this to avoid leaks
  }

// bind the server to a socket TODO check error code
  void Server::set_up_server()
  {

    if (!serv_sockt_.sock_bind(getPort_())) // then no binding succeded
    {
      std::cerr << "binding failed";
      exit(1);
    }
    if (!serv_sockt_.sock_listen())
    {
      std::cerr << "listening failed";
      exit(1);
    }
  }



void Server::set_up_epoll()
{ // TODO implement proper exeption
  serv_sockt_.set_non_blocking();
  epollfd = epoll_create1(0);
  if (epollfd == - 1) {
    throw *new EpollCreateException;
  }
  ev.events = EPOLLIN;
  ev.data.fd = serv_sockt_.getSockfd_();
  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, serv_sockt_.getSockfd_(), &ev) == - 1) {
    throw *new EpollCtlException;
  }
}

void Server::wait()
{
  Socket conn_sock(- 1);
  nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
    if (nfds == -1) {
      throw *new WaitFailException;
    }

    for (n = 0; n < nfds; ++n) {
      if (events[n].data.fd == serv_sockt_.getSockfd_()) {
        conn_sock = serv_sockt_.sock_accept();
        if (conn_sock.getSockfd_() == -1) {
          throw *new AcceptFailException;
        }
        conn_sock.set_non_blocking();
        ev.events = EPOLLIN | EPOLLRDHUP | EPOLLOUT;
        ev.data.fd = conn_sock.getSockfd_();
        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock.getSockfd_(),
          &ev) == -1) {
          throw *new AddFailException;
        }
      }
      else if (events[n].events & EPOLLRDHUP){
        close(events[n].data.fd);
      }
      else if (events[n].events & EPOLLIN){
        Http_response r(events[n].data.fd, name_, root_dir_);
        r.msg_recieve();
        if (log_)
        Host::addLog(log_file_,name_,r.get_ver()
                     ,r.get_meth(),r.get_resrc(), mut_);
        r.msg_respond();
      }
    }

}

const std::string &Server::getName_() const
  {
    return name_;
  }

  const std::string &Server::getPort_() const
  {
    return port_;
  }

  const std::string &Server::getIp_() const
  {
    return ip_;
  }

  const std::string &Server::getRoot_dir_() const
  {
    return root_dir_;
  }

  Socket Server::getServ_sockt_() const
  {
    return serv_sockt_;
  }

void Server::setW8_loop(bool w8_loop)
{
  Server::w8_loop = w8_loop;
}

bool Server::isLog_() const
{
  return log_;
}

const std::string &Server::getLog_file_() const
{
  return log_file_;
}

void Server::setLog_file_(const std::string &log_file_)
{
  Server::log_file_ = log_file_;
}

void Server::set_mutex(std::mutex* mut)
{
  mut_ = mut;
}
