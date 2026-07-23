#include <iostream>
#include "Scanner.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "=====================================\n";
        cout << " Malware Scanner\n";
        cout << "=====================================\n\n";
        cout << "Usage:\n";
        cout << "scanner <target_file> <rules_folder>\n";
        return 1;
    }

    string targetFile = argv[1];
    string rulesFolder = argv[2];

    cout << "Loading malware definitions...\n";

    vector<MalwareDefinition> rules =
        Scanner::loadRules(rulesFolder);

    cout << "Loaded " << rules.size()
         << " malware definition(s).\n";

    Scanner::scanFile(targetFile, rules);

    return 0;
}
