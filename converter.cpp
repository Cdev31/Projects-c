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
        string line = "";
        short numLines = 0;
        short numParameters =0;
        string allContentInLine = "";

        ifstream file(_archiveName);

        while( getline( file, line, '\n') ){
            allContentInLine = allContentInLine + " " +  line;
        }

        ofstream onCreateTemporalFile("temporal.txt");

        onCreateTemporalFile << allContentInLine;

        onCreateTemporalFile.close();

        ifstream onReadTemporalFile("temporal.txt");

        while( getline( onReadTemporalFile , line, ',' ) ){

           short position = 0;
           size_t finalPosition = line.find_last_not_of(" ");
           numParameters =1;
           while( true ){

              size_t isNotEmptySpaceIndex = line.find_first_not_of(" ", position);

              size_t firstPosicionIndex = line.find(":", isNotEmptySpaceIndex );

              size_t finalPositionWord = line.find(" ", isNotEmptySpaceIndex );

              
              if( finalPositionWord != string::npos ){
                JsonFormat newJson;

                newJson.key = line.substr( isNotEmptySpaceIndex, firstPosicionIndex - isNotEmptySpaceIndex);
                newJson.value = line.substr( firstPosicionIndex + 1 , finalPositionWord - firstPosicionIndex );

                objectJson.push_back(newJson);

                position = finalPositionWord;
              } 
              else {
                JsonFormat newJson;
                newJson.key = line.substr( isNotEmptySpaceIndex, firstPosicionIndex - isNotEmptySpaceIndex);
                newJson.value = line.substr( firstPosicionIndex + 1 , finalPosition - firstPosicionIndex);

                objectJson.push_back(newJson);
                position = 0;
                break;
              }
              numParameters++;
           }
           numLines++;
        }

        createJsonArchive( objectJson, _archiveName, numLines, numParameters );

        remove("temporal.txt");
    }  

    void createJsonArchive( vector<JsonFormat> data, string filename, short size, short parameters ){
        cout << parameters<< endl;
        cout << size << endl;
        //Evaluar la extension del archivo(TASK)
        ofstream newJsonFile(filename + ".json");

        newJsonFile << "[\n";
        for( short i =0; size > i; i++ ){
            newJsonFile << "\t{\n";
            for( short j =0; parameters > j;j++ ){
                string lineData =  
                "\t\t\"" + data[j].key + "\"" 
                 + ":" + "\"" 
                 + data[j].value + "\"" + (( 2 > j )? ",\n": "\n" );
                 newJsonFile << lineData;
            }
            newJsonFile << (( size -1 > i ) ? "\t},\n": "\t}");
        }
        newJsonFile << "]";
    }

    bool isOpened( ifstream* file ){

        if( !file->is_open() ){
            cerr << "No se pudo abrir el archivo\n";
            return false;
        }

        return true;
    }

};
