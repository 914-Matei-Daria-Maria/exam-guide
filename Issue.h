#pragma once

#include <string>
#include <iostream>

class Issue
{
private:
    std::string description;
    bool status;
    std::string reporter;
    std::string solver;

public:
    Issue(const std::string &description, bool status, std::string reporter, std::string solver);

    friend std::ostream& operator<<(std::ostream& stream, Issue& i);

    std::string toString();
    std::string getDescription() { return this->description; }
    [[nodiscard]] bool getStatus() const { return this->status; }
    std::string getSolver() { return this->solver; }
    void setSolver(std::string& value) { this->solver = value; }
    void solveIssue() { this->status = false; }
};