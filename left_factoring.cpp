#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Function to split a string based on a delimiter
vector<string> split(const string &str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        // Remove leading and trailing whitespaces from token
        token.erase(remove(token.begin(), token.end(), ' '), token.end());
        tokens.push_back(token);
    }
    return tokens;
}

// Function to find the common prefix between two strings
string findCommonPrefix(const string &s1, const string &s2) {
    cout << "Comparing rules: '" << s1 << "' and '" << s2 << "'" << endl;
    string prefix;
    int minLength = min(s1.length(), s2.length());

    for (int i = 0; i < minLength; i++) {
        if (s1[i] == s2[i]) {
            prefix += s1[i];
        } else {
            break;
        }
    }
    cout << "Common prefix found: '" << prefix << "'" << endl;
    return prefix;
}

int main() {
    int n;
    cout << "Enter the number of productions: ";
    cin >> n;
    cin.ignore();

    vector<string> nonTerminals(n);
    vector<string> productions(n);

    cout << "Enter the productions (e.g., S -> iets | ietses | a):" << endl;
    for (int i = 0; i < n; ++i) {
        getline(cin, productions[i]);
        // Remove spaces and extract the non-terminal
        productions[i].erase(remove(productions[i].begin(), productions[i].end(), ' '), productions[i].end());
        nonTerminals[i] = productions[i].substr(0, productions[i].find("->"));
    }

    cout << "\nNon-terminal symbols:\n";
    for (const string &nt : nonTerminals) {
        cout << nt << " ";
    }
    cout << "\n\nProduction rules:\n";
    for (int i = 0; i < n; ++i) {
        cout << nonTerminals[i] << " -> " << productions[i].substr(productions[i].find("->") + 2) << endl;
    }

    cout << "\nFactored grammar:\n";

    for (int i = 0; i < n; ++i) {
        string nonTerminal = nonTerminals[i];
        string production = productions[i].substr(productions[i].find("->") + 2);

        cout << "\nProcessing non-terminal " << nonTerminal << " with production rules: ";
        vector<string> rules = split(production, '|');
        for (const string &rule : rules) {
            cout << rule << " ";
        }
        cout << endl;

        vector<string> alpha, beta;
        vector<string> tempRules = rules;

        while (tempRules.size() > 1) {
            vector<string> currentPrefixes;
            vector<string> remainingRules;
            string commonPrefix = "";

            for (size_t j = 0; j < tempRules.size(); ++j) {
                for (size_t k = j + 1; k < tempRules.size(); ++k) {
                    string prefix = findCommonPrefix(tempRules[j], tempRules[k]);
                    if (!prefix.empty()) {
                        currentPrefixes.push_back(prefix);
                        break;
                    }
                }
            }

            if (!currentPrefixes.empty()) {
                commonPrefix = currentPrefixes.front(); // Take the first common prefix

                cout << "Common prefix for " << nonTerminal << ": " << commonPrefix << endl;

                for (string rule : tempRules) {
                    if (rule.substr(0, commonPrefix.size()) == commonPrefix) {
                        string suffix = rule.substr(commonPrefix.size());
                        suffix.empty() ? alpha.push_back("ε") : alpha.push_back(suffix);
                    } else {
                        remainingRules.push_back(rule);
                    }
                }

                // Print the factored production
                cout << nonTerminal << " -> " << commonPrefix << nonTerminal << "'" << (remainingRules.empty() ? "" : " | ");
                for (size_t j = 0; j < remainingRules.size(); ++j) {
                    cout << remainingRules[j];
                    if (j != remainingRules.size() - 1) cout << " | ";
                }
                cout << endl;

                // Print the new non-terminal production
                cout << nonTerminal << "' -> ";
                for (size_t j = 0; j < alpha.size(); ++j) {
                    cout << alpha[j];
                    if (j != alpha.size() - 1) cout << " | ";
                }
                cout << endl;

                // Update rules for further processing
                tempRules = remainingRules;
                alpha.clear();
                remainingRules.clear();

                // If all rules have been processed, break the loop
                if (tempRules.size() <= 1) break;
            } else {
                cout << "No common prefix found for " << nonTerminal << endl;
                cout << nonTerminal << " -> " << production << endl;
                break;
            }
        }

        // If only one production is left and no factoring was done
        // if (tempRules.size() == 1) {
        //     //cout << "Only one production for " << nonTerminal << "; no common prefix search needed." << endl;
        //     cout << nonTerminal << " -> " << tempRules[0] << endl;
        // }
    }

    return 0;
}
