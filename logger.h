#include <iostream>

using namespace std;

class Logger {
    public:
        void log(string message, int logCode) {
            string logCodes[] = {"[T]", "[L]"};

            cout << logCodes[logCode] << " : " << message << endl;
        }
};