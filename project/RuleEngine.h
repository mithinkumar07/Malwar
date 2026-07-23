#ifndef RULEENGINE_H
#define RULEENGINE_H

#include "Rule.h"
#include <string>

class RuleEngine
{
public:
    static bool scan(const std::string &data,
                     const MalwareDefinition &def);

private:
    static bool matchAscii(const std::string &data,
                           const std::string &pattern);
    static bool matchHex(const std::string &data,
                         const std::string &pattern);
    static bool matchRegex(const std::string &data,
                           const std::string &pattern);
};

#endif
