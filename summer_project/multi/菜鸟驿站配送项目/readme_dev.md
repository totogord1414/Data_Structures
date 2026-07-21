
## 🛠️ 编译与构建说明

本项目使用跨平台的 **CMake** 作为构建系统。请确保你的电脑上已经安装了 CMake 以及支持 C++17 标准的编译器（如 GCC/MinGW）。

### 1. 生成构建配置
在项目根目录下，打开终端（PowerShell 或 CMD），运行以下命令来初始化 build 目录：
```powershell
cmake -B build -S .
```

### 2. 编译可执行文件
接着，运行以下命令进行编译：
```powershell
cmake --build build
```
编译成功后，可执行文件 `CainiaoDeliverySystem.exe` 会生成在 `build/` 目录下。

---

## 🚀 运行与测试

在终端中输入以下命令即可运行完整的 T1 到 T6 测试集：
```powershell
.\build\CainiaoDeliverySystem.exe
```

程序运行后，终端将依次打印出各个任务（最短路径、双车协同、各贪心策略对比）的详细成本输出与超时统计。

---

## 📊 动画可视化面板 (Web Visualization)

为了最直观地展示 T3/T5 中的车辆路径规划过程，本项目自带了一个极其轻量的纯前端数据大屏，**不需要配置任何本地服务器或 Node.js 环境**。

**如何体验：**
1. 首先执行一次上面的 C++ 核心程序 `.\build\CainiaoDeliverySystem.exe`。
2. 程序运行完毕后，会在项目根目录自动吐出一个轨迹数据文件 `trace.js`。
3. 在左侧的文件管理器中，找到项目根目录下的 **`visualization.html`**，**直接双击**用 Chrome 或 Edge 等现代浏览器打开。
4. 你将在浏览器中看到一个极具科技感的深色仪表盘，带有小车移动的平滑动画。你可以在页面上点击 `Play / Pause` 或 `Reset` 来控制播放进度，也可以在 HTML 文件中自由修改 `speed` 参数来改变车速。
