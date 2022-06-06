// Include system libraries

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

// Namespaces

using namespace std;

// Some structs for data storing

struct NWType {
    vector <string> Data;

    int length = 0;
};

class Networking {
    private:
        string oldNWData;
        
        vector <string> oldTempData;

        string exec(string command);

        string getAllNetworkConnections(void);
        NWType splitString(string Data, string delimiter);
    
    public:
        vector <string> ParseNetworkingData();
};