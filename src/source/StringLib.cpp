#include <string>
#include <iostream>
#include "../header/StringLib.h"
#include "../header/exceptions.h"

using namespace std;

int ret3[3] = {0,0,0};
int ret4[4] = {0,0,0,0};
int* getPi(string pattern) {
    if(pattern.compare(START_ANNOTATION)==0) {
        return ret4;
    }
    else if(pattern.compare(FINISH_ANNOTATION)==0) {
        return ret3;
    }
    //TODO: Implement getPiAlgorithm
    return NULL;
}

//Implementation of KMP algoritm
bool isContain(string text, string pattern) {
    int txt_l = text.size(), ptn_l = pattern.size(), j=0;
    int* pi_array = getPi(pattern);
    for(int i=0; i<txt_l; i++) {
        while(text.at(i)!=pattern.at(j)) {
            if(j==0) {
                break;
            }
            j=pi_array[j-1];
        }
        if(text.at(i)==pattern.at(j)) {
            j++;
            if(ptn_l==j) return 1;
        }
    }
    return 0;
}

string toLowerCase(string plainText) {
    string ret = "";
    size_t codeSize =  plainText.size();
    for(size_t i=0; i<codeSize; i++) {
        if('A'<=plainText[i] && plainText[i]<='Z') {
            ret+=(plainText[i]+CASE_GAP);
        }
        else ret+=plainText[i];
    }
    return ret;
}

pair<string,string> getInstruction(string line) {
    for(size_t i=0; i<line.size(); i++) {
        if(line[i]==' ') return make_pair(line.substr(0,i), line.substr(i+1,line.size()));
    }
    return make_pair(line,"");
}
