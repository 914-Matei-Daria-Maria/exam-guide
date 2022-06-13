#include <fstream>
#include <cassert>
#include "IssuesRepo.h"

IssuesRepo::IssuesRepo(std::string& filename)
{
    this->filename = filename;
    this->readFromFile();
}

void IssuesRepo::readFromFile()
{
    std::ifstream file(this->filename);

    std::string description, reporter, solver, status;
    bool s;
    while(file)
    {
        std::getline(file, description, ',');
        if (description.empty())
            break;
        std::getline(file, status, ',');
        std::getline(file, reporter, ',');
        std::getline(file, solver, '\n');
        if (status == "open")
            s = true;
        else
            s = false;
        Issue newIssue(description, s, reporter, solver);
        this->issues.push_back(newIssue);
    }

    file.close();
}

void IssuesRepo::writeToFile()
{
    std::ofstream file(this->filename);

    for (auto issue : this->issues)
    {
        file << issue << '\n';
    }

    file.close();
}

void IssuesRepo::addIssue(Issue &i)
{
    this->issues.push_back(i);
    this->writeToFile(); //write to file can also be done just once in the destructor
}

void IssuesRepo::removeIssue(int pos)
{
    this->issues.erase(this->issues.begin() + pos);
    this->writeToFile();
}

int IssuesRepo::getPos(Issue &is)
{
    for (int i = 0; i < this->issues.size(); i++)
        if (issues[i].getDescription() == is.getDescription())
            return i;
    return -1;
}

void IssuesRepo::updateIssue(int pos, std::string& solver)
{
    this->issues[pos].setSolver(solver);
    this->issues[pos].solveIssue();
    this->writeToFile();
}

void IssuesRepo::testAdd()
{
    std::string filename = "../Files/test_issues.txt";
    IssuesRepo repo(filename);
    int size = repo.getIssues().size();
    Issue i1("issue1", false, "Moldovan", "Popescu");
    Issue i2("issue2", true, "Moldovan", "not-solved");
    repo.addIssue(i1);
    repo.addIssue(i2);
    assert(repo.getOnPos(size).getDescription() == i1.getDescription());
    assert(repo.getOnPos(size + 1).getDescription() == i2.getDescription());
    assert(repo.getIssues().size() == size + 2);
}

void IssuesRepo::testUpdate()
{
    std::string filename = "../Files/test_issues.txt";
    IssuesRepo repo(filename);
    int size = repo.getIssues().size();
    Issue i1("issue1", true, "Moldovan", "not-solved");
    repo.addIssue(i1);
    assert(repo.getOnPos(size).getStatus() == true);
    assert(repo.getOnPos(size).getSolver() == "not-solved");
    std::string solver = "Popescu";
    repo.updateIssue(size, solver);
    assert(repo.getOnPos(size).getStatus() == false);
    assert(repo.getOnPos(size).getSolver() == "Popescu");
}


