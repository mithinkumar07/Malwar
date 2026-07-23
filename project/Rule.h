#ifndef RULE_H
#define RULE_H

#include <string>
#include <vector>

enum class RuleType
{
    ASCII,
    HEX,
    REGEX
};

struct Rule
{
    RuleType type;
    std::string pattern;
};

struct MalwareDefinition
{
    std::string name;
    std::string description;
    std::vector<Rule> rules;
};

#endif
