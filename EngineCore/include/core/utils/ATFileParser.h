//
// Created by Gerry on 2021-05-09.
//

#ifndef CPPMC_ATFILEPARSER_H
#define CPPMC_ATFILEPARSER_H

#include <string>
#include <functional>
#include <unordered_map>
#include <vector>
#include <sstream>
namespace Ziti {
    class ATFileReader;
    typedef std::function<void(ATFileReader*,std::string&,std::string&)> AttrListener;
    class ATFileReader {
    public:
        ATFileReader(const std::string& file);
        void addAttrListener(const std::string& attrName, AttrListener listener);
        void read();
        std::stringstream& filecontents();
    private:
        std::string _path;
        std::stringstream _contents;
        std::unordered_map<std::string, std::vector<AttrListener>> _listeners;
    };
}
#endif //CPPMC_ATFILEPARSER_H
