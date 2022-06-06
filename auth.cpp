// Include system libraries

#include <iostream>
#include <fstream>

// Include local libraries

#include "auth.h"

// Namespaces

using namespace std;

int Auth::parseRules() {
    ifstream ConfigF ("cppfire.conf");

    vector <string> ConfigLines;

    string line;

    if (ConfigF.is_open()) {
        while (getline(ConfigF, line)) {
            ConfigLines.push_back(line);
        }

        ConfigF.close();
    } else {
        return 1;
    }

    for (int i = 0; i < ConfigLines.size(); i++) {
        string cline = ConfigLines[i];

        bool rule;

        if (cline.rfind("!rule", 0) == 0) {
            rule = true;
        } else {
            rule = false;
        }

        if (rule == true) {
            vector <string> components;

            string str;

            for (char x:cline) {
                if (x == ';') {
                    components.push_back(str);
                }

                if (x == ' ') {
                    components.push_back(str);

                    //cout << str << endl;

                    str.erase();
                } else {
                    str = str + x;
                }
            }

            for (int i = 0; i < components.size(); i++) {
                string component = components[i];

                if (component.rfind("block", 0) == 0) {
                    string blockType = components[i + 1];
                    string blockDir  = components[i + 2];

                    if (blockType == "ip") {
                        RuleObj obj;

                        obj.value = components[i + 3];

                        if (blockDir == "out") {
                            obj.dir = "out";

                            BlockedIP.push_back(obj);
                        } else {
                            obj.dir = "in";

                            BlockedIP.push_back(obj);
                        }
                    }

                    if (blockType == "port") {
                        RuleObj obj;

                        obj.value = components[i + 3];

                        if (blockDir == "out") {
                            obj.dir = "out";

                            BlockedPorts.push_back(obj);
                        } else {
                            obj.dir = "in";

                            BlockedPorts.push_back(obj);
                        }
                    }
                }

                if (component.rfind("pass", 0) == 0) {
                    continue;
                }
            }
        }
    }

    return 0;
};