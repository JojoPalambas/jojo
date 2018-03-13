 #include "global-exception.hh"

/* Add failed exception, inherits from GlobalException */
class AddFailException : public GlobalException
{
  public:
    AddFailException(int num = 2,
                        string const& msg = "Add failed")
                        throw();
    ~AddFailException() throw();
};
