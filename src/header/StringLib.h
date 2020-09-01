#ifndef STRINGLIB_H
    #define STRINGLIB_H
    #include <string>

    #define START_ANNOTATION "start from here"
    #define FINISH_ANNOTATION "that's it"
    #define IMPORT_ANNOTATION "import"
    #define CASE_GAP 'a'-'A'

    #define NO_INSTRUCTION_FOUND 0x5

    using namespace std;

    bool isContain(string text, string pattern);
    string toLowerCase(string plainText);
    string getInstruction(string line);
#endif
