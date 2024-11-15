#include <iostream>
#include "converter.cpp"

using namespace std;

int main(){
    Converter converter( "./archives/text.txt", TEXT );
    converter.convertTextToJson();

   

}