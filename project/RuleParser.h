#ifndef RULEPARSER_H
#define RULEPARSER_H

#include "Rule.h"
#include <string>

class RuleParser
{
public:
    static MalwareDefinition parseRuleFile(const std::string &filename);

private:
    static std::string extractQuoted(const std::string &line);
    static std::string trim(const std::string &str);
};

#endif
