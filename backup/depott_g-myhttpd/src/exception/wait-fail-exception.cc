#include "wait-fail-exception.hh"

/* Constructor */
WaitFailException::WaitFailException(int num, string const& msg) throw()
  : GlobalException(num, msg)
{}

/* Destructor */
WaitFailException::~WaitFailException() throw()
{}
