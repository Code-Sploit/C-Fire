// Include system libraries

#include <iostream>
#include <fstream>

// Include local libraries

#include "handler.h"
#include "auth.h"

// Namespaces

using namespace std;

string Handler::exec(string command) {
    char buffer[128];
    string result = "";

    // Open pipe to file
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "popen failed!";
    }

    // read till end of process:
    while (!feof(pipe)) {

        // use buffer to read and add to result
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
        }

    pclose(pipe);
    return result;
}

bool Handler::isNotPID(string pid) {
    if (pid.rfind("0", 0) == 0) {
        return false;
    }

    if (pid.rfind("1", 0) == 0) {
        return false;
    }
            
    if (pid.rfind("2", 0) == 0) {
        return false;
    }
            
    if (pid.rfind("3", 0) == 0) {
        return false;
    }
            
    if (pid.rfind("4", 0) == 0) {
        return false;
    }
            
    if (pid.rfind("5", 0) == 0) {
        return false;
    }
            
    if (pid.rfind("6", 0) == 0) {
        return false;
    }
            
    if (pid.rfind("7", 0) == 0) {
        return false;
    }
            
    if (pid.rfind("8", 0) == 0) {
        return false;
    }

    if (pid.rfind("9", 0) == 0) {
        return false;
    }

    return true;
}

void Handler::terminateConnection(string Conn) {
    vector <string> components;

    Handler H = Handler();

    string str;

    for (char x:Conn) {
        if (x == ';') {
            components.push_back(str);
        }

        if (x == ' ') {
            components.push_back(str);

            str.erase();
            } else {
            str = str + x;
        }
    }

    string pid = components[6].substr(0, components[6].find("/"));

    if (H.isNotPID(pid) == false) {
        string cmd = "kill -KILL " + pid;
        string logmsg = "Terminated connection {" + Conn + "} PID: " + pid;

        Log.log(logmsg, 0);

        exec(cmd);
    }
};

void Handler::handleFirewall() {
    Networking networking = Networking();
    Handler H = Handler();
    Auth auth = Auth();

    auth.parseRules();

    vector <string> NWData = networking.ParseNetworkingData();

    for (int i = 0; i < NWData.size(); i++) {
        bool hit;

        for (int j = 0; j < auth.BlockedIP.size(); j++) {
            vector <string> components;

            string receiver, sender, receiver_port, sender_port;
            string str;

            for (int i = 0; i < NWData.size(); i++) {
                cout << NWData[i] << endl;
            }

            for (char x:NWData[i]) {
                if (x == ' ') {
                    components.push_back(str);

                    //cout << str << endl;

                    str.erase();
                } else {
                    str = str + x;
                }
            }

            for (int i = 0; i < components.size(); i++) {
                receiver      = components[3];
                sender        = components[4];

                //cout << receiver << " | " << sender << endl;

                receiver_port = receiver.substr(receiver.find(":"), receiver.find(":") + 2);
                sender_port   = sender.substr(sender.find(":"), sender.find(":") + 2);
            }

            if (NWData[i].find(auth.BlockedIP[j].value) != string::npos) {
                if (sender == auth.BlockedIP[j].value) {
                    H.terminateConnection(auth.BlockedIP[j].value);
                }
            } else {
                hit = false;
            }
        }

        for (int j = 0; j < auth.BlockedPorts.size(); j++) {
            bool hit;

            if (NWData[i].find(auth.BlockedPorts[j].value) != string::npos) {
                vector <string> components;

                string receiver, sender, receiver_port, sender_port;
                string str;

                for (char x:NWData[i]) {
                    if (x == ' ') {
                        components.push_back(str);

                        //cout << str << endl;

                        str.erase();
                    } else {
                        str = str + x;
                    }
                }

                for (int i = 0; i < components.size(); i++) {
                    receiver      = components[3];
                    sender        = components[4];

                    receiver_port = receiver.substr(receiver.find(":"), receiver.find(":") + 1).erase(0, 1);
                    sender_port   = sender.substr(sender.find(":"), sender.find(":") + 1).erase(0, 1);
                }

                if (NWData[i].find("0.0.0.0") != string::npos) {
                    hit = false;
                } else {
                    if (NWData[i].find(":::") != string::npos) {
                        hit = false;
                    } else {
                        if (receiver_port == auth.BlockedPorts[j].value) {
                            H.terminateConnection(auth.BlockedPorts[j].value);
                        }
                    }
                }
            } else {
                hit = false;
            }
        }
    }
};