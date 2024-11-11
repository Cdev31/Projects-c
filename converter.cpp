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
          
           while( true ){
    
              size_t isNotEmptySpaceIndex = line.find_first_not_of(" ", position);

              size_t firstPosicionIndex = line.find(":", isNotEmptySpaceIndex );

              size_t finalPositionWord = line.find(" ", firstPosicionIndex );

              if( finalPositionWord - 1 != finalPosition ){
                JsonFormat newJson;

                newJson.key = line.substr( isNotEmptySpaceIndex, firstPosicionIndex - 1);
                newJson.value = line.substr( firstPosicionIndex + 1, finalPositionWord -1 );

                objectJson.push_back(newJson);

                position = finalPositionWord;
              } 
              else {
                break;
              }
           }
        }
        //  for( short i =0; objectJson.size()> i; i++ ){
        //     cout << objectJson[i].key << endl;
        //  }


    }  

    bool isOpened( ifstream* file ){

        if( !file->is_open() ){
            cerr << "No se pudo abrir el archivo\n";
            return false;
        }

        return true;
    }

};
