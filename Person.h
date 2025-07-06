#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
public:
    explicit Person(const std::string& name);
    virtual ~Person();

    void show() const { displayInfo(); }

    virtual void displayInfo() const = 0;
    virtual Person* clone() const = 0;

    const std::string& getName() const;
    static int getTotalPersons();

private:
    std::string name;
    static int totalPersons;
};

#endif // PERSON_H
