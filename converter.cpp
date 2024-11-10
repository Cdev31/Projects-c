#include "metadata.h"

class Converter {
    private:
        string _archiveName = "";
        FileType _fileType;

    public:
        Converter( string archiveName, FileType fileType): 
        _archiveName( archiveName), _fileType( fileType ){};

    void convertTextToJson( ){

        vector<JsonFormat> objectJson;

        string line ="";
        string allContent = "";
        ifstream file(_archiveName);

        ofstream temporalArchive("temporal.txt");

        isOpened( &file );

        while( getline( file, line, '\n') ){
            allContent = allContent + " " + line;
        }

        temporalArchive << allContent;
        temporalArchive.close();

        ifstream writeTemporalArchive("temporal.txt");

        while( getline( writeTemporalArchive, line , ',') ){

            size_t position = 0;
            string word = "";

            while( ( position = line.find_first_not_of(" ", position) ) != string::npos ){
                size_t nextSpace = line.find(" ", position);

                if( nextSpace != string::npos ){
                    
                    size_t delimiter = line.find(":");
                    JsonFormat newJson;
                    
                    newJson.key = line.substr( position, delimiter );
                    newJson.value = line.substr( delimiter, nextSpace - 1 );

                    objectJson.push_back( newJson );
                    position = nextSpace + 1;
                }
                else{
                    break;
                }
            }
        }

        for( short i =0; objectJson.size() > i; i++ ){
            cout << (string)objectJson[i].key << ":";
            
            visit([](auto&& arg){
                cout << arg;
            }, objectJson[i].value);
            
            cout << endl;
        }

    }  

    bool isOpened( ifstream* file ){

        if( !file->is_open() ){
            cerr << "No se pudo abrir el archivo\n";
            return false;
        }

        return true;
    }

};
