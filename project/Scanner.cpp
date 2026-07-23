#include "Scanner.h"
#include "RuleParser.h"
#include "RuleEngine.h"

#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

// Read target file in binary mode
string Scanner::readFile(const string &filename)
{
    ifstream file(filename, ios::binary);

    if (!file)
    {
        cerr << "Error: Cannot open file " << filename << endl;
        return "";
    }

    return string((istreambuf_iterator<char>(file)),
                  istreambuf_iterator<char>());
}

// Load all .rule files recursively
vector<MalwareDefinition> Scanner::loadRules(const string &folder)
{
    vector<MalwareDefinition> definitions;

    for (const auto &entry : fs::recursive_directory_iterator(folder))
    {
        if (entry.is_regular_file() &&
            entry.path().extension() == ".rule")
        {
            MalwareDefinition rule =
                RuleParser::parseRuleFile(entry.path().string());

            if (!rule.name.empty())
                definitions.push_back(rule);
        }
    }

    return definitions;
}

// Scan the target file
void Scanner::scanFile(const string &filename,
                       const vector<MalwareDefinition> &rules)
{
    string data = readFile(filename);

    if (data.empty())
    {
        cout << "Unable to read target file." << endl;
        return;
    }

    bool detected = false;

    cout << "\nScanning file...\n\n";

    for (const auto &malware : rules)
    {
        if (RuleEngine::scan(data, malware))
        {
            detected = true;

            cout << "=====================================\n";
            cout << "Malware Detected\n";
            cout << "Name        : " << malware.name << endl;
            cout << "Description : " << malware.description << endl;
            cout << "=====================================\n\n";
        }
    }

    if (!detected)
    {
        cout << "No malware detected.\n";
    }
}
