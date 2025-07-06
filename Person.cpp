#include "Person.h"

int Person::totalPersons = 0;

Person::Person(const std::string& name)
    : name(name)
{
    ++totalPersons;
}

Person::~Person()
{
    --totalPersons;
}

const std::string& Person::getName() const
{
    return name;
}

int Person::getTotalPersons()
{
    return totalPersons;
}
