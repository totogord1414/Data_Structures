#ifndef HASHUTILS_H
#define HASHUTILS_H

#include <string>
#include <cstdint>

class HashUtils {
public:
    // 算法1：DJB2 哈希算法
    static uint64_t hash_djb2(const std::string& filepath);
    
    // 算法2：经典多项式哈希 (Polynomial Hash) - 带有手动取模
    static uint64_t hash_polynomial(const std::string& filepath);
};

#endif // HASHUTILS_H
