#include "RuleParser.h"

#include <fstream>
#include <iostream>

using namespace std;

string RuleParser::trim(const string &str)
{
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == string::npos)
        return "";

    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

string RuleParser::extractQuoted(const string &line)
{
    size_t first = line.find('"');
    if (first == string::npos)
        return "";

    size_t second = line.find('"', first + 1);
    if (second == string::npos)
        return "";

    return line.substr(first + 1, second - first - 1);
}

MalwareDefinition RuleParser::parseRuleFile(const string &filename)
{
    MalwareDefinition def;
    ifstream file(filename);

    if (!file)
    {
        cerr << "Error: Cannot open rule file " << filename << endl;
        return def;
    }

    string line;
    while (getline(file, line))
    {
        line = trim(line);

        if (line.empty())
            continue;

        if (line.rfind("Name=", 0) == 0)
        {
            def.name = trim(line.substr(5));
        }
        else if (line.rfind("Description=", 0) == 0)
        {
            def.description = trim(line.substr(12));
        }
        else if (line.rfind("ASCII(", 0) == 0)
        {
            def.rules.push_back({RuleType::ASCII, extractQuoted(line)});
        }
        else if (line.rfind("HEX(", 0) == 0)
        {
            def.rules.push_back({RuleType::HEX, extractQuoted(line)});
        }
        else if (line.rfind("REGEX(", 0) == 0)
        {
            def.rules.push_back({RuleType::REGEX, extractQuoted(line)});
        }
    }

    return def;
}
