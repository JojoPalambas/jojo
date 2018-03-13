#include "global-exception.hh"

/* Accept failed exception, inherits from GlobalException */
class AcceptFailException : public GlobalException
{
  public:
    AcceptFailException(int num = 2,
                      string const& msg = "Accept failed")
                      throw();
    ~AcceptFailException() throw();
};
