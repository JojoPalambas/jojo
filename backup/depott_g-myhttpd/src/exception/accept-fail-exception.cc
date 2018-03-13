#include "accept-fail-exception.hh"

/* Constructor */
AcceptFailException::AcceptFailException(int num, string const& msg) throw()
  : GlobalException(num, msg)
{}

/* Destructor */
AcceptFailException::~AcceptFailException() throw()
{}
