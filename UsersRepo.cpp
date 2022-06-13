#include <fstream>
#include "UsersRepo.h"

UsersRepo::UsersRepo(std::string &filename)
{
    this->filename = filename;
    this->readFromFile();
}

void UsersRepo::addUser(User &u)
{
    this->users.push_back(u);
}

void UsersRepo::readFromFile()
{
    std::ifstream file(this->filename);

    std::string name, type;
    while(file)
    {
        std::getline(file, name, ',');
        if (name.empty())
            break;
        std::getline(file, type, '\n');
        User newUser(name, type);
        this->users.push_back(newUser);
    }

    file.close();
}
