#include "global-exception.hh"

/* Missing parameter exception, inherits from GlobalException */
class MissingParameterException : public GlobalException
{
  public:
    MissingParameterException(int num = 3,
           string const& msg = "A mandatory parameter is missing in conf file")
           throw();
    ~MissingParameterException() throw();
};
