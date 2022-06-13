#include "User.h"
#include <utility>


User::User(std::string name, std::string type) : name(std::move(name)), type(std::move(type))
{}

