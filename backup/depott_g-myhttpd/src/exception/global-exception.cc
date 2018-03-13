#include "global-exception.hh"

/* Constructor */
GlobalException::GlobalException(int num, std::string const& msg) throw()
  : num_(num)
  , msg_(msg)
{}

/* Destructor */
GlobalException::~GlobalException()
{}

/* what method: return the exception message*/
const char* GlobalException::what() const throw()
{
  return msg_.c_str();
}

/* get_num method: return the exception num */
int GlobalException::get_num() throw()
{
  return num_;
}
