#pragma once
#include <string>
#include <iostream>

class User
{
private:
    std::string name;
    std::string type;

public:
    User() = default;

    User(std::string name, std::string type);

    std::string getName() { return this->name; }
    std::string getType() { return this->type; }
};