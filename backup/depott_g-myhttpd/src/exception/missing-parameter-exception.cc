#include "missing-parameter-exception.hh"

/* Constructor */
MissingParameterException::MissingParameterException(int num,
                                                     string const& msg)
                                                     throw()
  : GlobalException(num, msg)
{}

/* Destructor */
MissingParameterException::~MissingParameterException() throw()
{}
