#include <fstream>
#include <string>
#include "../header/io.h"

using namespace std;

string readFile(string path) {
    ifstream reader = ifstream(path);
    if(!reader) {
        throw FILE_NOT_FOUND;
        return NULL;
    }
    string source;
    getline(reader, source, '\0');
    reader.close();
    return source;
}
