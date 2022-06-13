#include <QApplication>
#include <QPushButton>
#include "Repo/UsersRepo.h"
#include "Repo/IssuesRepo.h"
#include "Service/Service.h"
#include "GUI/GUI.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IssuesRepo::testAdd();
    IssuesRepo::testUpdate();

    std::string filename =  "../Files/users.txt";
    UsersRepo usersRepo(filename);
    filename = "../Files/issues.txt";
    IssuesRepo issuesRepo(filename);
    Service service(usersRepo, issuesRepo);

    std::vector<User> users = service.getUsers();
    for (auto user : users)
    {
        auto window = new GUI(service, user);
        window->show();
    }

    return QApplication::exec();
}
