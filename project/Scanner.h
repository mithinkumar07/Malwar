#ifndef SCANNER_H
#define SCANNER_H

#include "Rule.h"
#include <string>
#include <vector>

class Scanner
{
public:
    // Read the target file in binary mode
    static std::string readFile(const std::string &filename);

    // Load all .rule files recursively
    static std::vector<MalwareDefinition> loadRules(const std::string &folder);

    // Scan the target file
    static void scanFile(const std::string &filename,
                         const std::vector<MalwareDefinition> &rules);
};

#endif
