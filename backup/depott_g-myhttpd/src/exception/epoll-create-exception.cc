#include "epoll-create-exception.hh"

/* Constructor */
EpollCreateException::EpollCreateException(int num, string const& msg) throw()
  : GlobalException(num, msg)
{}

/* Destructor */
EpollCreateException::~EpollCreateException() throw()
{}
