#ifndef EXCEPTION
#define EXCEPTION
#include <exception>
#include <iostream>

class Exception : public std::exception{
public:
    std::string message;

    Exception(std::string msg): message(msg){}
    Exception(const char* c): message(c){}
    Exception(char * c): message(c){}

    virtual const char* what() const throw(){ return message.c_str(); }
    virtual ~Exception() throw (){}
};

#endif // EXCEPTION