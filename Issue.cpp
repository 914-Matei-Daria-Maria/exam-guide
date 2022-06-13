#include "Issue.h"

Issue::Issue(const std::string &description, bool status, std::string reporter, std::string solver)
        : description(description), status(status), reporter(reporter), solver(solver)
{}

std::ostream &operator<<(std::ostream &stream, Issue &i)
{
    std::string s;
    if (i.status)
        s = "open";
    else
        s = "closed";
    stream << i.description << ',' << s << ',' << i.reporter << ',' << i.solver;
    return stream;
}

std::string Issue::toString()
{
    std::string s;
    if (this->status)
        s = "open";
    else
        s = "closed";
    return this->description + ", " + s + ", " + this->reporter + ", " + this->solver;
}
