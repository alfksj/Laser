#include <iostream>
#include <string>
#include <vector>

#include "../header/io.h"
#include "../header/StringLib.h"
#include "../header/executor.h"
#include "../header/exceptions.h"

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
                cout << "ERROR " << MULTI_INPUT_FILES << ": Multi input files is not allowed. Specify only one file." << endl;
                return MULTI_INPUT_FILES;
            }
            input_location = i;
        }
    }

    if(input_location==-1) {
        cout << "ERROR " << NO_NECESSARY_ARG_PROVIDED << ": No input file given\n" << endl;
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
            cout << "ERROR " << FILE_NOT_FOUND << ": Input file \"" << args[input_location] << "\" was not found" << endl;
            break;
        default:
            cout << "Unknown exception code: " << errCode << endl;
            break;
        }
        return errCode;
    }

    try {
        //Find start point, code before start annotation will be ignored.
        int startAddr=-1;
        vector<string> preProcess;
        for(unsigned long long int i=0; i<line.size(); i++) {
            if(line.at(i)[0]=='#') continue;
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
                //comment
                if(ln[0]=='#') continue;
                pair<string,string> parsedLine = getInstruction(ln);
                string instruction = parsedLine.first, command = parsedLine.second;
                pair<int,string> ret = execute(instruction, command);
                if(ret.first==0) cout << "ERROR: Abnormal reply from code runner: " << ret.second << endl;
                else if(ret.first==EXIT) return 0;
            } catch(const int errCode) {
                switch (errCode)
                {
                case NO_INSTRUCTION_FOUND:
                    cout << "ERROR " << NO_INSTRUCTION_FOUND << ": " << "No instruction found at line " << i+1 << endl;
                    break;
                case UNKNOWN_INSTRUCTION_EXCEPTION:
                    cout << "ERROR " << UNKNOWN_INSTRUCTION_EXCEPTION << ": " << "Unknown instrcution at line " << i+1 << endl;
                    break;
                default:
                    cout << "Unknown exception code: " << errCode << endl;
                    break;
                }
            }
        }
    } catch(const int errCode) {
        switch (errCode) {
        case NO_START_POINT_FOUND:
            cout << "ERROR " << NO_START_POINT_FOUND << ": No start point found. Use \"start\" to define start point." << endl;
            break;
        default:
            cout << "Unknown exception code: " << errCode << endl;
            break;
        }
        return errCode;
    }
    cout << "WARNING " << NO_EXIT_COMMAND << ": No exit command found. Please use \"end\" to define end point of the program." << endl;
    return 1;
}
