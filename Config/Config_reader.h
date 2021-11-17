//
// Created by jsz on 11/16/21.
//

#ifndef RM_CONFIG_READER_H
#define RM_CONFIG_READER_H
#include "include/rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <string>
#include <iostream>
class Config_reader {
private:
    char* file_name = "../config.json";
    rapidjson::Document document;
    rapidjson::FileReadStream readConfigFile();
public:
    Config_reader();
    ~Config_reader();


    void parse();
};



#endif //RM_CONFIG_READER_H
