#include "global-exception.hh"

/* Epoll Ctl exception, inherits from GlobalException */
class EpollCtlException : public GlobalException
{
  public:
    EpollCtlException(int num = 1,
                      string const& msg = "epoll_ctl: serv_sockt_")
                      throw();
    ~EpollCtlException() throw();
};
