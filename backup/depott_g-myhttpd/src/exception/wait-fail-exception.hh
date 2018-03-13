#include "global-exception.hh"

/* Wait failed exception, inherits from GlobalException */
class WaitFailException : public GlobalException
{
  public:
    WaitFailException(int num = 2, string const& msg = "Wait failed")
                      throw();
    ~WaitFailException() throw();
};
