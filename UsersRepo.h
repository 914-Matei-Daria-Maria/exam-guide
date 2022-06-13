#pragma once

#include <vector>
#include "../Domain/User.h"

class UsersRepo
{
private:
    std::vector<User> users;
    std::string filename;

public:
    explicit UsersRepo(std::string& filename);

    void readFromFile();
    void addUser(User& u);
    std::vector<User> getUsers() { return this->users; }
    ~UsersRepo() = default;
};