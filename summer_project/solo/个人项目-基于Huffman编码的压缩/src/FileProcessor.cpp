#include "FileProcessor.h"
#include "HuffmanTree.h"
#include "HashUtils.h"

#include <cstddef>
#include <ios>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <filesystem>

void FileProcessor::coreCompress(const std::string& inputPath, const std::vector<int>& freqToUse, 
bool isAdaptive) {
    
    HuffmanTree tree;
    tree.buildTree(freqToUse);

    std::vector<std::string> codes = tree.getCodes();

    size_t pos = inputPath.find(".");
    std::string title = inputPath.substr(0, pos);
    

    // this part makes the freq file
    struct CharFreq {
        unsigned char bytes;// use the unsigned char instead of int because it's easier to understand
        int freq;
    };

    std::vector<CharFreq> validFreqs;
    for (int i = 0; i < 256; i++) {
        if (freqToUse[i] > 0) {
            validFreqs.push_back({static_cast<unsigned char>(i), freqToUse[i]});
        }
    }

    std::sort(validFreqs.begin(), validFreqs.end(), [](const CharFreq& a, const CharFreq& b) {
        if (a.freq == b.freq) {
            return a.bytes < b.bytes;
        }
        return a.freq > b.freq;
    });

    std::string freq_title = title + "_freq.txt";
    std::ofstream freqfile(freq_title);
    
    if (!freqfile) {
        std::cerr << "ERROR: fail to create the file" << freq_title << std::endl;
        return;
    }
    
    for (const auto& item : validFreqs) {
        char displaychar = std::isprint(item.bytes) ? item.bytes : '.';
        freqfile << static_cast<int>(item.bytes) << " " << displaychar << " " << item.freq << "\n";
    }




    //this part makes the huf file
    std::string huff_title;
    if (isAdaptive) {
        huff_title = title + "_adp.huff";
    } else {
        huff_title = title + ".huff";
    }
    //the reason to use binary is same to below
    std::ofstream hufffile(huff_title, std::ios::binary);
    
    if (!hufffile) {
        std::cerr << "ERROR: fail to create the file" << huff_title << std::endl;
        return;
    }

    size_t uniqueCharCount = validFreqs.size();

    //first strore the header so that you know how to decompress the file

    hufffile.write(reinterpret_cast<const char*>(&uniqueCharCount), sizeof(uniqueCharCount));

    //这个是AI写的，我原来的写法貌似因为mingw的问题出错了
    // 用 ifstream 来获取文件大小，避开 MinGW 下 std::filesystem 对中文路径(UTF-8)的编码转换报错
    std::ifstream sizeCheck(inputPath, std::ios::binary | std::ios::ate);
    size_t actualFileSize = sizeCheck.tellg();
    sizeCheck.close();
    hufffile.write(reinterpret_cast<const char*>(&actualFileSize), sizeof(actualFileSize));

    for (const auto& item: validFreqs) {
        hufffile.write(reinterpret_cast<const char*>(&item.bytes), sizeof(item.bytes));
        hufffile.write(reinterpret_cast<const char*>(&item.freq), sizeof(item.freq));
    }

    //then read the original file again to conpress it
    std::ifstream inFile(inputPath, std::ios::binary); 
    std::vector<char> inBuffer(1024);

    if (!inFile) {
        std::cerr << "ERROR: fail to open the file: " << inputPath << std::endl;
    }
    
    unsigned char currentByte = 0;
    int bitCount = 0;

    while (inFile) {
        inFile.read(inBuffer.data(), inBuffer.size());
        std::streamsize bytesRead = inFile.gcount();

        for (std::streamsize i = 0; i < bytesRead; i++) {
            unsigned char c = static_cast<unsigned char>(inBuffer[i]);
            std::string code = codes[c];
            for (char bit : code) {
                currentByte = currentByte << 1;

                if (bit == '1') {
                    currentByte = currentByte | 1;
                }

                bitCount++;

                if (bitCount == 8) {
                    hufffile.write(reinterpret_cast<const char*>(&currentByte), 1);
                    currentByte = 0;
                    bitCount = 0;
                }
            }
        }
    }

    if (bitCount > 0) {
        currentByte = currentByte << (8 - bitCount);
        hufffile.write(reinterpret_cast<const char*>(&currentByte), 1);
    }


    //have to close the huffile here so that the remaining data in the buffer will get into the panel
    hufffile.close();

    //decompress the compressed file

    decompress(huff_title);

    // Custom Hash Validation
    std::string unzip_title = title + "_unzip.txt";
    
    std::cout << "\n--- Hash Validation for " << inputPath << " ---" << std::endl;
    
    uint64_t djb2_orig = HashUtils::hash_djb2(inputPath);
    uint64_t djb2_unzip = HashUtils::hash_djb2(unzip_title);
    std::cout << "[DJB2 Hash] Original: " << djb2_orig << " | Unzipped: " << djb2_unzip;
    if (djb2_orig == djb2_unzip) std::cout << " (MATCH!)" << std::endl;
    else std::cout << " (MISMATCH!)" << std::endl;

    uint64_t poly_orig = HashUtils::hash_polynomial(inputPath);
    uint64_t poly_unzip = HashUtils::hash_polynomial(unzip_title);
    std::cout << "[Poly Hash] Original: " << poly_orig << " | Unzipped: " << poly_unzip;
    if (poly_orig == poly_unzip) std::cout << " (MATCH!)" << std::endl;
    else std::cout << " (MISMATCH!)" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
}





void FileProcessor::compress(const std::string& inputPath) {
    std::vector<int> freqs = calculateFrequencies(inputPath);

    coreCompress(inputPath, freqs, false);
    
}








void FileProcessor::decompress(const std::string &inputPath) {
    if (inputPath.find(".huff") == std::string::npos) {
        std::cerr << "ERROR: only .huff file can be decompressed" <<std::endl;
        return;
    }

    std::ifstream inFile(inputPath, std::ios::binary);
    if (!inFile) {
        std::cerr << "ERROR: fail to open the file: " << inputPath << std::endl;
        return;
    }

    size_t uniqueCharCount = 0;

    inFile.read(reinterpret_cast<char*>(&uniqueCharCount), sizeof(uniqueCharCount));

    size_t totalOriginalBits = 0;
    inFile.read(reinterpret_cast<char*>(&totalOriginalBits), sizeof(totalOriginalBits));

    std::vector<int> freqs(256, 0);


    for (size_t i = 0; i < uniqueCharCount; i++) {
        unsigned char byteVal;
        int freq;
        inFile.read(reinterpret_cast<char *>(&byteVal), sizeof(byteVal));
        inFile.read(reinterpret_cast<char *>(&freq), sizeof(freq));

        freqs[byteVal] = freq;
    }

    HuffmanTree tree;
    tree.buildTree(freqs);
    HuffmanNode* root = tree.getRoot();

    std::string unzip_title;
    if (inputPath.find("_adp.huff") != std::string::npos) {
        size_t pos = inputPath.find("_adp.huff");
        unzip_title = inputPath.substr(0, pos) + "_unzip.txt";
    } else {
        size_t pos = inputPath.find(".huff");
        unzip_title = inputPath.substr(0, pos) + "_unzip.txt";
    }

    std::ofstream outFile(unzip_title, std::ios::binary);
    if (!outFile) {
        std::cerr << "ERROR: fail to create the file: " << unzip_title << std::endl;
    }

    HuffmanNode* currentNode = root;
    std::vector<char> buffer(1024);

    while (inFile && totalOriginalBits > 0) {
        inFile.read(buffer.data(), buffer.size());
        std::streamsize bytesRead = inFile.gcount();

        for (std::streamsize i = 0; i < bytesRead; i++) {
            unsigned char currentByte = static_cast<unsigned char>(buffer[i]);

            for (int bitIndex = 7; bitIndex >= 0; bitIndex--) {
                bool isOne = (currentByte >> bitIndex) & 1;
                if (isOne) {
                    currentNode = currentNode->right;
                } else {
                    currentNode = currentNode->left;
                }

                if (currentNode->left == nullptr && currentNode->right == nullptr) {
                    outFile.write(reinterpret_cast<char *>(&currentNode->data), sizeof(currentNode->data));
                    currentNode = root;
                    totalOriginalBits--;
                    //so that the reamin 0s won't be caluclated
                    if (!totalOriginalBits) {
                        break;
                    }
                }
            }
        }
    }

}








void FileProcessor::adaptiveCompress(const std::string &inputDir) {
    std::vector<std::string> txtFiles;

    for (const auto& entry : std::filesystem::directory_iterator(inputDir)) {
        // makes sure that it is a txt file rather than a folder or other types of file
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::string filePath = entry.path().string();

            if (filePath.find("_unzip") == std::string::npos && filePath.find("_freq") == std::string::npos) {
                txtFiles.push_back(filePath);
            }
        }
    }

    std::sort(txtFiles.begin(), txtFiles.end());

    std::vector<int> accumulateFreqs(256, 0);

    for (const std::string& filePath: txtFiles) {
        std::vector<int> localFreqs = calculateFrequencies(filePath);
        
        for (int i = 0; i < 256; i++) {
            accumulateFreqs[i] += localFreqs[i];
        }

        coreCompress(filePath, accumulateFreqs, true);
    }

}








std::vector<int> FileProcessor::calculateFrequencies(const std::string& inputPath) {

    std::vector<int> count(256, 0);
    //this means the pure binary mode,in case the data is ruined by the os, "\n\r"
    std::ifstream file(inputPath, std::ios::binary);

    if (!file) {
        std::cerr  << "ERROR: fail to open the file";
        return count;
    }

    std::vector<char> buffer(1024);

    while (file) {
        file.read(buffer.data(), buffer.size());

        std::streamsize byteRead = file.gcount();

        for (std::streamsize i = 0; i < byteRead; i++) {
            //have to cast or some words may be recognized as negative ones

            unsigned char byte = static_cast<unsigned char>(buffer[i]);

            count[byte]++;
        }
    }

    return count;
}