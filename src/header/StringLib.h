#ifndef STRINGLIB_H
    #define STRINGLIB_H
    #include <string>

    #define START_ANNOTATION "start"
    #define FINISH_ANNOTATION "end"
    #define IMPORT_ANNOTATION "import"
    #define CASE_GAP 'a'-'A'

    using namespace std;

    bool isContain(string text, string pattern);
    string toLowerCase(string plainText);
    pair<string,string> getInstruction(string line);
#endif
