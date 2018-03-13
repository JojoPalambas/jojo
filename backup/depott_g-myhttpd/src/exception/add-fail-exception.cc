#include "add-fail-exception.hh"

/* Constructor */
AddFailException::AddFailException(int num, string const& msg) throw()
  : GlobalException(num, msg)
{}

/* Destructor */
AddFailException::~AddFailException() throw()
{}
