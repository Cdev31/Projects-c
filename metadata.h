#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <variant>

using namespace std;


struct JsonFormat
{
    string key;
    variant< int, string > value;
};


enum FileType{
    TEXT,
    JSON,
    CSV
};


namespace fs = std::filesystem;


inline bool createArchiveDirectory(){
    string path = "./archives";

    if( fs::exists( path ) && fs::is_directory( path ) ) return true;
    
    return ( fs::create_directory( path ) ) ? true : false;

}