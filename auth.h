// Include system libraries

#include <iostream>
#include <fstream>
#include <vector>

// Namespaces

//#include "networking.h"

using namespace std;

struct RuleObj {
    string dir;
    string value;
};

class Auth {
    public:
        vector <RuleObj> BlockedIP, BlockedPorts;

        int parseRules();
};