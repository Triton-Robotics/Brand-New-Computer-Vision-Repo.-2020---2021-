//
// Created by jsz on 11/16/21.
//

#ifndef RM_EXCEPTIONS_H
#define RM_EXCEPTIONS_H

#include <iostream>
#include <exception>

struct Config_exceptions: public std::exception {

    const char* what() const throw()
    {
        return "config Reader error!";
    }
} configExceptions;


#endif //RM_EXCEPTIONS_H
