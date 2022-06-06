//
// C ++ Fire
//


// Include system libraries

#include <iostream>

// Include local libraries

#include "handler.h"

// Namespaces

using namespace std;

int main(void) {
    Handler handler = Handler();

    while (true) {
        handler.handleFirewall();
    }

    return 0;
}