#include "HashUtils.h"
#include <fstream>
#include <iostream>

//udr uint64_t instead of long long beacause this can avoid the negative number
// DJB2 Hash
uint64_t HashUtils::hash_djb2(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        std::cerr << "ERROR: Cannot open file for hashing: " << filepath << std::endl;
        return 0;
    }

    uint64_t hash = 5381;
    char buffer[4096];
    while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
        std::streamsize bytes = file.gcount();
        for (std::streamsize i = 0; i < bytes; ++i) {
            hash = ((hash << 5) + hash) + static_cast<unsigned char>(buffer[i]); // hash * 33 + c
        }
    }
    return hash;
}

uint64_t HashUtils::hash_polynomial(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        std::cerr << "ERROR: Cannot open file for hashing: " << filepath << std::endl;
        return 0;
    }

    const uint64_t P = 131;
    const uint64_t MOD = 1000000007; 

    uint64_t hash = 0;
    char buffer[4096];
    while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
        std::streamsize bytes = file.gcount();
        for (std::streamsize i = 0; i < bytes; ++i) {

            hash = (hash * P + static_cast<unsigned char>(buffer[i])) % MOD;
        }
    }
    return hash;
}
