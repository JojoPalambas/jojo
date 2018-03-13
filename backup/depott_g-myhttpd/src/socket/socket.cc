//
// Created by silentshad on 14/02/18.
//

#include "socket.hh"
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <cstdio>
#include <fcntl.h>


int Socket::getSockfd_() const
{
  return sockfd_;
}

Socket::Socket(int sockfd_) : sockfd_(sockfd_)
{
  memset(&hints_, 0, sizeof hints_); // make sure the struct is empty
  (hints_).ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
  (hints_).ai_socktype = SOCK_STREAM; // TCP stream sockets
  (hints_).ai_flags = AI_PASSIVE;     // fill in my IP for me
}

bool Socket::sock_bind(std::string port)
{
  int yes = 1;
  if ((status_ = getaddrinfo(NULL, port.c_str(), &hints_, &servinfo_)) != 0) {
    std::cerr << "getaddrinfo error: %s\n" << gai_strerror(status_);
    exit(1);
  }

  for (p_ = servinfo_; p_ != NULL; p_ = p_->ai_next) {
    if ((sockfd_ = socket(p_->ai_family, p_->ai_socktype, p_->ai_protocol)) == - 1) {
      continue;
    }

    if (setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == - 1) {
      std::cerr << "setsockopt failed";
      freeaddrinfo(servinfo_);
      exit(1);
    }

    if (bind(sockfd_, p_->ai_addr, p_->ai_addrlen) == - 1) {
      continue;
    }
    break;
  }
  if (sockfd_ == -1)
  {
    freeaddrinfo(servinfo_); // all done with this structure
    return false;
  }

  return true;
}

bool Socket::sock_listen()
{
 if (listen(sockfd_, 10) == -1) {
   perror("\nlisten\n");
  return false;
 }
return true;
}

void Socket::set_non_blocking()
{
  fcntl(sockfd_, F_SETFL, O_NONBLOCK);
}

int Socket::sock_accept()
{
  struct sockaddr their_addr;
  socklen_t addr_size = sizeof(their_addr);
  return accept(sockfd_, &their_addr, &addr_size);
}
