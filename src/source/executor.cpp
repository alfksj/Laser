#include <string>
#include "../header/executor.h"
#include "../header/StringLib.h"
#include "../header/exceptions.h"

using namespace std;

pair<int,string> execute(string instruction, string command) {
    //Check instruction
    if(instruction.compare(FINISH_ANNOTATION)==0) {
        return pair<int,string>(EXIT, command);
    }
    throw UNKNOWN_INSTRUCTION_EXCEPTION;
    return make_pair(0,"0");
}