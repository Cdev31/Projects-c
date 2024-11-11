#include <iostream>
#include "converter.cpp"

using namespace std;

int main(){
    Converter converter( "./archives/text.txt", TEXT );
    converter.convertTextToJson();

    // string text = "l ls";

    // size_t position = text.find(" ");

    // cout << position << endl;

    // cout << "other " << text.compare(position, 2, " ") << endl;

}