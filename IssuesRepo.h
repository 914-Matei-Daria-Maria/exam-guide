#pragma once

#include <vector>
#include "../Domain/Issue.h"
#include "../Observer/Observer.h"

class IssuesRepo
{
private:
    std::vector<Issue> issues;
    std::string filename;

public:
    explicit IssuesRepo(std::string& filename);

    void readFromFile();
    void writeToFile();
    void addIssue(Issue &i);
    std::vector<Issue> getIssues() { return this->issues; }
    Issue getOnPos(int pos) { return this->issues[pos]; }
    void removeIssue(int pos);
    int getPos(Issue& i);
    void updateIssue(int pos, std::string& solver);

    ~IssuesRepo() = default;

    static void testAdd();
    static void testUpdate();
};