
#pragma once
#define MAX_EVENTS 10

#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <thread>
#include <mutex>
#include <condition_variable>

#include "../socket/socket.hh"
#include <sys/epoll.h>

  class Server
  {

  public:
    // TODO new constructor that take file as arg
    Server(std::string config);

    Server(std::string name, std::string port,
           std::string ip, std::string root_dir,
           bool log = false,
            std::string log_file = "");
    ~Server();

    void set_up_server();

    void set_up_epoll();
    void wait();

  public:
    const std::string &getName_() const;

    const std::string &getPort_() const;

    const std::string &getIp_() const;

    const std::string &getRoot_dir_() const;

    Socket getServ_sockt_() const;

    void setW8_loop(bool w8_loop);

  private:
    std::string name_;
    std::string port_;
    std::string ip_;
    std::string root_dir_;
    std::string log_file_;
  public:
    const std::string &getLog_file_() const;

    void setLog_file_(const std::string &log_file_);

  private:

    struct epoll_event ev;
    struct epoll_event events[MAX_EVENTS];
    int nfds;
    int epollfd;
    int n;

    bool log_;
  public:
    bool isLog_() const;
    void set_mutex(std::mutex* mut);

  private:
    Socket serv_sockt_;

    bool w8_loop;
    std::mutex* mut_;
  };
