//
// Created by jsz on 11/16/21.
//

#include "Config_reader.h"
#include <istream>
#include <cstdio>
#include "Utility/exceptions.h"
#include "Utility/utility.h"
using namespace std;

Config_reader::Config_reader() {
    cout << "config reader initializing....." << endl;
    try {
        this->parse();
    } catch (configExceptions &e){

        cout << e.what() << '\n';
        exit(1);
    }
    if (this->document["DEBUG_MODE"].IsBool())
    {
        RT_utility::DEBUG_ = this->document["DEBUG_MODE"].GetBool();
        cout << RT_utility::DEBUG_  << endl;
    }
    //TODO: add more value in the future.

    cout << "config reader finished....." << endl;
}
rapidjson::FileReadStream Config_reader::readConfigFile() {
    char readBuffer[1024*10];
    FILE* fp = fopen(this->file_name,"r");
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    fclose(fp);
    return  is;
}

void Config_reader::parse() {
        rapidjson::FileReadStream is = this->readConfigFile();
        this->document.ParseStream(is);

}

Config_reader::~Config_reader() {

}



