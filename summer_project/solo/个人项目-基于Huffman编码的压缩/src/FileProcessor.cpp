#include "FileProcessor.h"
#include "HuffmanTree.h"

#include <cstddef>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>


void FileProcessor::compress(const std::string& inputPath) {
    std::vector<int> freqs = calculateFrequencies(inputPath);

    HuffmanTree tree;
    tree.buildTree(freqs);

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
        if (freqs[i] > 0) {
            validFreqs.push_back({static_cast<unsigned char>(i), freqs[i]});
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
    std::string huff_title = title + ".huff";
    //the reason to use binary is same to below
    std::ofstream hufffile(huff_title, std::ios::binary);
    
    if (!hufffile) {
        std::cerr << "ERROR: fail to create the file" << huff_title << std::endl;
        return;
    }

    size_t uniqueCharCount = validFreqs.size();

    //first strore the header so that you know how to decompress the file

    hufffile.write(reinterpret_cast<const char*>(&uniqueCharCount), sizeof(uniqueCharCount));

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
    
}

void FileProcessor::decompress(const std::string &inputPath) {

}

void FileProcessor::adaptiveCompress(const std::string &inputPath) {

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