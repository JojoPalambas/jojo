#include "global-exception.hh"

/* Epoll Create exception, inherits from GlobalException */
class EpollCreateException : public GlobalException
{
  public:
    EpollCreateException(int num = 1, string const& msg = "epoll_create1")
                         throw();
    ~EpollCreateException() throw();
};
