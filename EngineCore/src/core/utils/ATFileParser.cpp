//
// Created by Gerry on 2021-05-09.
//
#include <core/utils/ATFileParser.h>
#include <fstream>
Ziti::ATFileReader::ATFileReader(const std::string &file) : _path(file) {
}

void Ziti::ATFileReader::addAttrListener(const std::string &attrName, AttrListener listener) {
    if(_listeners.find(attrName) != _listeners.end())
        _listeners[attrName] = {};

    _listeners[attrName].push_back(listener);
}

void Ziti::ATFileReader::read() {
    std::ifstream infile(_path);
    printf("HERE NOW! \n");
    if(!infile.is_open()) {
        printf("not found!");
        return;
    }

    std::string line;
    int prevTokenEnd = 0;
    bool lastLineHadToken = false;
    int size = 0;
    while(std::getline(infile,line)) {
        if(lastLineHadToken) {
            prevTokenEnd = size;
            lastLineHadToken = false;
        }
        if(line.rfind("//#",0) == 0) {
            unsigned int pos;
            pos=line.find(' ',0);
            std::string value = line.substr(pos+1);
            std::string token = line.substr(3,pos-3);
            if(_listeners.find(token) != _listeners.end()) {
                auto &listeners = _listeners[token];
                for(auto& listener : listeners) {
                    std::string contents = _contents.str();
                    contents = contents.substr(prevTokenEnd);
                    listener(this, value,contents);
                }
            }
            lastLineHadToken = true;
        }
        size += line.length()+1;
        _contents << line;
        _contents << '\n';
    }
}

std::stringstream& Ziti::ATFileReader::filecontents() {
    return _contents;
}
