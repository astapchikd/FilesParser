#include "filesparser.h"

using namespace std;

namespace Parser {
    
    FilesParser::FilesParser(const string& catalogpath, const string& pathtowrite) : outputfile(make_shared<ofstream>(pathtowrite)) {  
        for (const auto& entry : filesystem::directory_iterator(catalogpath)) {
            if ( entry.is_regular_file() ) {
                if (auto f = ifstream(entry); f) {
                    inputfiles.push_back(make_shared<InputFile>(move(f), entry.path().filename().string()));
                }
                else {
                    throw runtime_error("File" + entry.path().filename().string() + "not opened!");
                }
            }
            
           
        }

    }

    void FilesParser::FileParse(const shared_ptr<InputFile> inpdata) {
        std::string strparse;
        std::string tmp;
        stringstream ss;
        ss << inpdata->second << '\n';
        std::getline(inpdata->first, strparse);
        while (std::getline(inpdata->first, tmp)) {
            std::string_view s = strparse;
            while (true) {
                size_t delim = s.find(tmp);
                ss << s.substr(0, delim) << '\n';
                if (delim == s.npos) {
                    break;
                }
                else {
                    s.remove_prefix(delim + 1);
                }

            }
        }
        *outputfile << ss.str();

    }
    void FilesParser::SingleThreadParse() {
        for (auto& file : inputfiles) {
            FileParse(file);
        }
    }
    void FilesParser::MultiThreadParse() {
        for (auto& file : inputfiles) {
            tasks.push_back(async(std::launch::async, [=]() {
                FileParse(file);
                }
            ));
        }
    }
}