#ifndef ENTRY_INTERFACE_H
#define ENTRY_INTERFACE_H

#include <string>
using namespace std;
#include <iostream>


class entry_interface
{
public:
    //virtual ~entry_interface() = 0;

    virtual void setLock(bool key) = 0;
    virtual bool getLock() = 0;
};

#endif // ENTRY_INTERFACE_H
