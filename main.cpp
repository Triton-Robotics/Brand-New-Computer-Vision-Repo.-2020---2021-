#include <iostream>
#include <Config/Config_reader.h>
#include "Utility/utility.h"

int main() {
    Config_reader* configReader = new Config_reader();

    configReader->parse();
    std::cout << RT_utility::cameraMatrix_ <<std::endl;
    std::cout << RT_utility::distCoeffs_ << std::endl;
    delete configReader;
    return 0;
}

