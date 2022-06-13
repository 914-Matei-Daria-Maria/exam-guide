#pragma once

#include "../Repo/UsersRepo.h"
#include "../Repo/IssuesRepo.h"

class Service: public Subject
{
private:
    UsersRepo usersRepo;
    IssuesRepo issuesRepo;

public:
    Service(UsersRepo usersRepo, IssuesRepo issuesRepo);
    std::vector<User> getUsers() { return this->usersRepo.getUsers(); }
    std::vector<Issue> getIssues() { return this->issuesRepo.getIssues(); }
    std::vector<Issue> getIssuesSorted();
    void addIssue(std::string& issueDesc, std::string& reporterName);
    void removeIssue(int index);
    int getIssuePos(Issue &issue) { return this->issuesRepo.getPos(issue); };
    void updateIssue(int index, std::string& solverName);
};