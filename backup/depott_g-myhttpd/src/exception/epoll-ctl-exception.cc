#include "epoll-ctl-exception.hh"

/* Constructor */
EpollCtlException::EpollCtlException(int num, string const& msg) throw()
  : GlobalException(num, msg)
{}

/* Destructor */
EpollCtlException::~EpollCtlException() throw()
{}
