#include "Service.h"

Service::Service(UsersRepo usersRepo, IssuesRepo issuesRepo) : usersRepo(usersRepo), issuesRepo(issuesRepo)
{}

std::vector<Issue> Service::getIssuesSorted()
{
    std::vector<Issue> issues = this->getIssues();

    for (int i = 0; i < issues.size() - 1; i++)
    {
        for (int j = i+1; j < issues.size(); j++)
        {
            if ((!issues[i].getStatus() && issues[j].getStatus()) ||
                (issues[i].getStatus() == issues[j].getStatus() && issues[i].getDescription() > issues[j].getDescription()))
            {
                Issue aux = issues[i];
                issues[i] = issues[j];
                issues[j] = aux;
            }
        }
    }

    return issues;
}

void Service::addIssue(std::string& issueDesc, std::string& reporterName)
{
    if (issueDesc.empty())
        throw std::runtime_error("Description is empty.");

    std::vector<Issue> issues = this->getIssues();
    for (auto issue : issues)
    {
        if (issue.getDescription() == issueDesc)
            throw std::runtime_error("Issue with same description already exists.");
    }

    Issue issue(issueDesc, false, reporterName, "no-solver");
    this->issuesRepo.addIssue(issue);
    this->notify();
}

void Service::removeIssue(int index)
{
    if (this->issuesRepo.getOnPos(index).getStatus())
        throw std::runtime_error("Issue is still open and it cannot be removed.");

    this->issuesRepo.removeIssue(index);
    this->notify();
}

void Service::updateIssue(int index, std::string& solverName)
{
    this->issuesRepo.updateIssue(index, solverName);
    this->notify();
}
