#include "CLI.h"
#include "FileProcessor.h"

#include <iostream>

void CLI::parseAndRun(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "ERROR: no enough arguments" << std::endl;
        return;
    }

    std::string mode = argv[1];
    std::string path = argv[2];

    if (mode == "-c")  {
        FileProcessor::compress(path);
    } else if (mode == "-x") {
        FileProcessor::decompress(path);
    } else if (mode == "-a") {
        FileProcessor::adaptiveCompress(path);
    } else {
        std::cerr << "ERROR: unknown mode" << std::endl;
    }
}