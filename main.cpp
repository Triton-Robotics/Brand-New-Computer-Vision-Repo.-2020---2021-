#include <iostream>
#include "Config/include/rapidjson/document.h"

using namespace rapidjson;
Document document;
int main() {
    std::cout << "Hello, World!" << std::endl;
    const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
    document.Parse(json);
    assert(document.IsObject());
    assert(document.HasMember("hello"));
    assert(document["hello"].IsString());
    printf("hello = %s\n", document["hello"].GetString());

    assert(document["i"].IsNumber());
    assert(document["pi"].IsDouble());
    printf("pi = %g\n", document["pi"].GetDouble());
    return 0;
}

