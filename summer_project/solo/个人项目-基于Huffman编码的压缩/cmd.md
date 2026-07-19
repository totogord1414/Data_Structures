# 快捷测试命令 (PowerShell 专用)

以下命令已为你配置好了纯正的 Windows PowerShell 执行路径 (`.\build\Huffman.exe`)。
请确保在项目根目录（也就是包含 `build`、`test_suite` 的文件夹）下的 PowerShell 终端中依次粘贴运行。

### 1. 测试基础压缩解压与优先队列
```powershell
.\build\Huffman.exe -c test_suite\hamlet.txt
```
*(运行后控制台应打印出哈希匹配结果)*

### 2. 验证解压后文件是否完全一致
```powershell
fc.exe /b test_suite\hamlet.txt test_suite\hamlet_unzip.txt
```
*(如果控制台输出 `FC: 找不到差异`，说明 100% 一致！)*

### 3. 测试中文大文件 (16MB 与 21MB)
```powershell
.\build\Huffman.exe -c test_suite\斗破苍穹.txt
.\build\Huffman.exe -c test_suite\完美世界.txt
```
*(这步可能需要跑一小会儿，耐心等待哈希匹配输出)*

### 4. 测试自适应流式压缩
```powershell
.\build\Huffman.exe -a test_suite\adaptive_data\
```
*(会自动处理里面的 1.txt, 2.txt, 3.txt)*

### 5. 一次性批量验证所有大文件和流式文件
```powershell
fc.exe /b test_suite\斗破苍穹.txt test_suite\斗破苍穹_unzip.txt
fc.exe /b test_suite\完美世界.txt test_suite\完美世界_unzip.txt
fc.exe /b test_suite\adaptive_data\1.txt test_suite\adaptive_data\1_unzip.txt
fc.exe /b test_suite\adaptive_data\2.txt test_suite\adaptive_data\2_unzip.txt
fc.exe /b test_suite\adaptive_data\3.txt test_suite\adaptive_data\3_unzip.txt
```
*(同样，只要提示 `FC: 找不到差异`，就说明所有文件都完美无损地解压回来了！)*
