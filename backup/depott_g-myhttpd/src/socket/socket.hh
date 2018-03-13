#pragma once

#include <string>
#include <sys/socket.h>
#include <netdb.h>

class Socket
{
public:
  Socket(int sockfd_);

  int sock_accept();
  void sock_receive();
  void sock_send();
  bool sock_bind(std::string);
  bool sock_listen();
  void set_non_blocking();

  int getSockfd_() const;

private:
  int sockfd_;
  int status_;
  struct addrinfo hints_;
  struct addrinfo *servinfo_;  // will point to the results
  struct addrinfo *p_;

};

