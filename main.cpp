#include <iostream>
#include <Config/Config_reader.h>
#include "Utility/utility.h"

int main() {
    Config_reader* configReader = new Config_reader();

    configReader->parse();

    delete configReader;
    return 0;
}

