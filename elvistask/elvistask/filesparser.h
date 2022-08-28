#pragma once
#include <string>
#include <iostream>
#include <filesystem>
#include<future>
#include <vector>
#include <fstream>
#include <string_view>
#include <sstream>
#include <memory>
#include <utility>

namespace Parser{

using InputFile = std::pair<std::ifstream, std::string>;

class FilesParser {
public:
    FilesParser(const std::string& catalogpath, const std::string& pathtowrite);

    void SingleThreadParse();
    void MultiThreadParse();

private:
    void FileParse(const std::shared_ptr<InputFile> inpdata);
    std::shared_ptr<std::ofstream> outputfile;
    std::vector<std::future<void>> tasks;
    std::vector<std::shared_ptr<InputFile>> inputfiles;
};

}