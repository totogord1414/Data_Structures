#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <string>
#include <vector>

class FileProcessor {

public:

    static void compress(const std::string& inputPath);

    static void decompress(const std::string& inputPath);
    //the entry to adaptive compression
    static void adaptiveCompress(const std::string& inputPath);

private:

    static std::vector<int> calculateFrequencies(const std::string& inputPath);

    static void coreCompress(const std::string& inputPath, const std::vector<int>& freqToUse, 
    bool isAdaptive);

};



#endif