//
// Created by jsz on 11/16/21.
//

#include "Config_reader.h"
#include <istream>
#include <cstdio>
#include "Utility/utility.h"
#include "Utility/exceptions.h"
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
    if (this->document["cameraMatrix"].IsArray()) {
        const  rapidjson::Value &cameraMatrix = this->document["cameraMatrix"];
        vector<double> temp;
        for (rapidjson::SizeType i = 0; i < cameraMatrix.Size(); i++) {
            temp.push_back(cameraMatrix[i].GetDouble());
        }
        RT_utility::cameraMatrix_= cv::Mat(3, 3, cv::DataType<double>::type);
        memcpy(RT_utility::cameraMatrix_.data,temp.data(),temp.size()*sizeof(double));
    }

    if (this->document["distCoeffs"].IsArray()) {
        const  rapidjson::Value &distCoeffs = this->document["distCoeffs"];
        vector<double> temp;
        for (rapidjson::SizeType i = 0; i < distCoeffs.Size(); i++) {
            temp.push_back(distCoeffs[i].GetDouble());
        }
        RT_utility::distCoeffs_= cv::Mat(1, 5, cv::DataType<double>::type);
        memcpy(RT_utility::distCoeffs_.data,temp.data(),temp.size()*sizeof(double));
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



