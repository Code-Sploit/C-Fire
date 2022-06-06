// Include system libraries

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>

#include "networking.h"

// Namespaces

using namespace std;

// Config JSON reader

void NWConfigReader() {
    ifstream file("cppfire.json");

    Json::Value ConfigData;
    Json::Reader Reader;
    Json::FastWriter Writer;

    Reader.parse(file, ConfigData);

    Json::Value Rules = ConfigData["RULES"];

    for (int i = 0; i < Rules.size(); i++) {
        bool conf = false;
        bool rule = false;

        string RuleType;// = ConfigData["RULES"];

        try {
            RuleType = Writer.write(Rules["CONF"]);

            conf = true;
            rule = false;
        } catch (int) {
            rule = false;
            conf = false;
        }

        try {
            RuleType = Writer.write(Rules["RULE"]);

            conf = false;
            rule = true;
        } catch (int) {
            rule = false;
            conf = false;
        }

        cout << RuleType << endl;
    }

    //cout << Rules << endl;
};

// Some structs for data storing

string Networking::exec(string command) {
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

string Networking::getAllNetworkConnections(void) {
    string NWData = exec("netstat -anp | grep -v unix");

    return NWData;
};

NWType Networking::splitString(string Data, string delimiter) {
    NWType Temp;

    size_t pos = 0;
    string token;

    regex reg(R"(\s+)");

    int count = 0;

    while ((pos = Data.find(delimiter)) != string::npos) {
        token = Data.substr(0, pos);
        Temp.Data.push_back(regex_replace(token, reg, " "));
        Data.erase(0, pos + delimiter.length());

        count = count + 1;
    }

    Temp.length = count;

    return Temp;
};

vector <string> Networking::ParseNetworkingData() {
    // Get network data from private function
    string NWData = getAllNetworkConnections();

    if (NWData == oldNWData) {
        return oldTempData;
    }

    // Erase useless text from first line
    NWData.erase(0, NWData.find("\n") + 1);

    // Split $NWData into array

    string Delimitor = "\n";

    NWType Temp = splitString(NWData, Delimitor);

    // Create arrays for different protocols

    vector <string> ICMPnw, UDPnw, TCPnw, UOnw;

    // Filter protocols in arrays

    for (int i = 0; i < Temp.length; i++) {
        
        if (Temp.Data[i].rfind("udp", 0) == 0) {
            UDPnw.push_back(Temp.Data[i]);
        }
        
        if (Temp.Data[i].rfind("tcp", 0) == 0) {
            TCPnw.push_back(Temp.Data[i]);
        }
        
        if (Temp.Data[i].rfind("icmp", 0) == 0) {
            ICMPnw.push_back(Temp.Data[i]);
        }
    }

    //for (int i = 0; i < Temp.length; i++) {
    //    if (CF.usingIP6 == false) {
    //        if (Temp.Data[i].rfind("tcp6", 0) == 0) {
    //            Temp.Data.erase(Temp.Data.begin() + i);
    //        }
    //    }
    //}

    //NWConfigReader();

    oldTempData = Temp.Data;

    return Temp.Data;
}
