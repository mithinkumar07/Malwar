#include "RuleEngine.h"

#include <regex>

using namespace std;

bool RuleEngine::matchAscii(const string &data, const string &pattern)
{
    return data.find(pattern) != string::npos;
}

bool RuleEngine::matchHex(const string &data, const string &pattern)
{
    string hexStr = pattern;
    hexStr.erase(remove(hexStr.begin(), hexStr.end(), ' '), hexStr.end());
    hexStr.erase(remove(hexStr.begin(), hexStr.end(), '\t'), hexStr.end());

    if (hexStr.size() % 2 != 0)
        return false;

    string bytes;
    for (size_t i = 0; i < hexStr.size(); i += 2)
    {
        string byteStr = hexStr.substr(i, 2);
        char byte = (char)strtol(byteStr.c_str(), nullptr, 16);
        bytes.push_back(byte);
    }

    return data.find(bytes) != string::npos;
}

bool RuleEngine::matchRegex(const string &data, const string &pattern)
{
    try
    {
        regex re(pattern);
        return regex_search(data, re);
    }
    catch (...)
    {
        return false;
    }
}

bool RuleEngine::scan(const string &data, const MalwareDefinition &def)
{
    for (const auto &rule : def.rules)
    {
        bool matched = false;

        switch (rule.type)
        {
        case RuleType::ASCII:
            matched = matchAscii(data, rule.pattern);
            break;
        case RuleType::HEX:
            matched = matchHex(data, rule.pattern);
            break;
        case RuleType::REGEX:
            matched = matchRegex(data, rule.pattern);
            break;
        }

        if (!matched)
            return false;
    }

    return true;
}
