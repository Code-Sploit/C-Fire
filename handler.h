// Include system libraries

#include <iostream>
#include <fstream>

// Include local libraries

#include "logger.h"
#include "networking.h"

// Namespaces

using namespace std;

class Handler {
    public:
        Logger Log = Logger();

        string exec(string command);

        bool isNotPID(string pid);

        void terminateConnection(string Conn);
        void handleFirewall();

        int parseRules();
};