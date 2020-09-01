#include <iostream>
#include <string>
#include <vector>

#include "../header/io.h"
#include "../header/StringLib.h"

#define NO_NECESSARY_ARG_PROVIDED 0x1
#define MULTI_INPUT_FILES 0x2
#define NO_START_POINT_FOUND 0x4

using namespace std;

typedef unsigned long long int ulli;
typedef long long int lli;

class commandArgument {
private:
    enum Arg_Type {
        OPTION,
        SOURCE
    };
    Arg_Type type;
    string value;
public:
    commandArgument();
    commandArgument(const string content) {
        //Considered as OPTION
        if(content.at(0)=='-') {
            type = OPTION;
            value = content.substr(1,content.size()-1);
        }
        //Considered as INPUT_FILE
        else {
            type = SOURCE;
            value = content;
        }
    }
    string getValue() {
        return value;
    }
    int getType() {
        return type;
    }
};

int main(int argc, char *args[]) {
    //Load, check argument
    vector<commandArgument> argument_set;
    int input_location=-1;
    for(int i=1; i<argc; i++) {
        argument_set.push_back(commandArgument(args[i]));
        if(argument_set.back().getType()==1) {
            if(input_location != -1) {
                cout << "ERROR " << MULTI_INPUT_FILES << ": Multi input files is not allowed. Specify only one file.";
                return MULTI_INPUT_FILES;
            }
            input_location = i;
        }
    }

    if(input_location==-1) {
        cout << "ERROR " << NO_NECESSARY_ARG_PROVIDED << ": No input file given\n";
        return NO_NECESSARY_ARG_PROVIDED;
    }

    vector<string> line;
    try {
        string codePre = readFile(args[input_location]);
        string code = toLowerCase(codePre);
        if(code.back()!='\n') code+="\n";
        int lastRead=0, len=1;
        for(unsigned long int i=0; i<code.size(); i++) {
            if(code.at(i) == '\n') {
                line.push_back(code.substr(lastRead,len-1));
                len=0;
                lastRead = i+1;
            }
            len++;
        }
    } catch(const int errCode) {
        switch (errCode) {
        case FILE_NOT_FOUND:
            cout << "ERROR " << FILE_NOT_FOUND << ": Input file \"" << args[input_location] << "\" is not found";
            break;
        default:
            cout << "Unknown exception code: " << errCode;
            break;
        }
        return errCode;
    }

    try {
        //Find start point, code before start annotation will be ignored.
        int startAddr=-1;
        vector<string> preProcess;
        for(unsigned long long int i=0; i<line.size(); i++) {
            if(isContain(line.at(i), START_ANNOTATION)) {
                startAddr=i;
            }
        }
        if(startAddr==-1) {
            throw NO_START_POINT_FOUND;
        }
        for(size_t i=startAddr+1; i<line.size(); i++) {
            try {
                string ln = line[i];
                string instruction = getInstruction(ln);
                
            } catch(const int errCode) {
                switch (errCode)
                {
                case NO_INSTRUCTION_FOUND:
                    cout << "ERROR " << NO_INSTRUCTION_FOUND << ": " << "No instruction found at line " << i+1 << endl;
                    break;
                default:
                    cout << "Unknown exception code: " << errCode;
                    break;
                }
            }
        }
    } catch(const int errCode) {
        switch (errCode) {
        case NO_START_POINT_FOUND:
            cout << "ERROR " << NO_START_POINT_FOUND << ": No start point found. Use \"start from here\" to define start point.";
            break;
        default:
            cout << "Unknown exception code: " << errCode;
            break;
        }
        return errCode;
    }
}
