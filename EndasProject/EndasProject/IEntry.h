#ifndef ENTRY_INTERFACE_H
#define ENTRY_INTERFACE_H

#include <string>
using namespace std;
#include <iostream>


class IEntry
{
public:
    virtual void setLock(const bool &) = 0;
    virtual bool getLock() = 0;
    virtual string getDirection() = 0;
};

#endif // ENTRY_INTERFACE_H
