#pragma once

#include <exception>
#include <string>

using namespace std;

/* Global exception */
class GlobalException : public exception
{
  public:
    GlobalException(int num = 0, string const& msg = "Global exception")
                    throw();
    virtual ~GlobalException() throw();
    virtual const char* what() const throw();
    int get_num() throw();

  protected:
    int num_ = 0;
    string msg_ = "";
};
