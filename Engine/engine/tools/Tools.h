//
// Created by Gerry on 2020-08-10.
//

#ifndef CPPMC_TOOLS_H
#define CPPMC_TOOLS_H

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <core/Logger.h>
#include <vector>
#include "glm/glm.hpp"
namespace VoxEng {

    struct ParsedShader {
        std::string vertex, fragment;
        std::vector<std::string> in;
    };

    /*
		template<class T,class C, class U, class V>
		class MapWrapper
		{
		private:
		    std::unordered_map<T, C, U, V> map;
		};
	*/

    static unsigned int getTime()
    {
        return (unsigned int)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }

    static bool loadShaders(const char* path, ParsedShader* out) {
        char* vertexStart = "#shaderbegin vertex";
        char* end = "#shaderend";
        char* fragmentStart = "#shaderbegin fragment";
        int state = 0;
        std::stringstream inStream;
        std::ifstream file;
        std::string line;
        file.open(path);
        if(file.fail())
            return false;
        while(std::getline(file, line)) {
            if(state == 0 && line == vertexStart) {
                state = 1;
                inStream.str(std::string());
            } else if(state == 0 && line == fragmentStart) {
                state = 2;
                inStream.str(std::string());
            }else if(state != 0 && line == end) {
                switch (state) {
                    case 1: out->vertex = inStream.str(); break;
                    case 2: out->fragment = inStream.str(); break;
                }
                state = 0;
            } else {
                inStream << line << '\n';
                if(state == 1 && line.rfind("in",0) == 0) {
                    int pos = line.size()-1;
                    while(line[pos] != ' ' && pos > 0) pos--;
                    auto inVar = line.substr(pos+1);
                    inVar.pop_back();
                    out->in.push_back(inVar);
                }
            }
        }

        file.close();
        return true;
    }

    struct IVec2KeyFuncs
    {
        size_t operator()(const glm::ivec2& k)const
        {
            return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
        }

        bool operator()(const glm::ivec2& a, const glm::ivec2& b)const
        {
            return a.x == b.x && a.y == b.y;
        }
    };

}
#endif //CPPMC_TOOLS_H
