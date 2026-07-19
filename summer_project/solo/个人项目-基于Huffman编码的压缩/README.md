## 运行环境
* **操作系统**: Windows (推荐使用 PowerShell 或 Git Bash), Linux, macOS
* **编译器**: 支持 C++17 的编译器 (如 GCC 7+, Clang 5+, MSVC 19.14+)
* **构建工具**: CMake (最低版本 3.10)

## 编译方法
本项目使用 CMake 进行构建。在项目根目录下运行以下命令：

```bash
# 1. 生成构建配置（输出到 build 文件夹）
cmake -B build

# 2. 编译可执行文件
cmake --build build
```
编译成功后，可执行文件 `Huffman.exe` (Windows) 或 `Huffman` (Linux/Mac) 将生成在 `build/` 目录下。

## 使用说明与命令示例

### 1. 单文件压缩 (`-c`)
将指定文件压缩，生成 `.huff` 压缩包、频率表和自动解压验证文件。
```bash
./build/Huffman.exe -c test_suite/hamlet.txt
```
**期望输出**:
* `test_suite/hamlet.huff` (压缩后的文件)
* `test_suite/hamlet_freq.txt` (字符频率表)
* `test_suite/hamlet_unzip.txt` (验证用的解压文件)
* 控制台输出哈希校验通过的信息。

### 2. 独立解压 (`-x`)
解压已有的 `.huff` 文件。
```bash
./build/Huffman.exe -x test_suite/hamlet.huff
```
**期望输出**:
* `test_suite/hamlet_unzip.txt` (恢复出的原始文件)

### 3. 自适应流式压缩 (`-a`)
```bash
./build/Huffman.exe -a test_suite/adaptive_data
```
**期望输出**:
* 对于目录下的每个文件（如 `1.txt`），生成:
  * `1_adp.huff` (基于累加频率树的压缩文件)
  * `1_freq.txt` (包含累加频率的频率表)
  * `1_unzip.txt` (解压验证文件)
* 控制台同样会输出每个文件的哈希校验结果。
