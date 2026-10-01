手写数字识别系统：最终报告版

最终工程位置
C:\Users\35452\Desktop\DigitRecnition
构建目录：C:\Users\35452\Desktop\DigitRecnition\build\Debug
直接运行：C:\Users\35452\Desktop\DigitRecnition\run\number3.exe

Qt Creator 使用
1. 完全关闭旧的 Qt Creator 窗口。
2. 双击 DigitRecnition 内的“用Qt打开正确版.cmd”。
   脚本会打开实体英文源码目录，并将构建目录设置到本工程的 build/Debug。
3. 使用 Desktop (x86-windows-msys-pe-64bit) 套件，已绑定 Qt 6.11.1 与 MinGW 13.1。
4. 配置完成后按 Ctrl+B 编译，Ctrl+R 运行。

报告一致性
Python 输出原 HTML，Qt 保留原解析和显示；Worker/QThread、OpenCV 多数字分割、
质心对齐、28×28 预处理、0.1307/0.3081 归一化、Top-3 与模型保持报告原版。
原 16 个文件仅 CMakeLists.txt、widget.cpp、predict.py 保留路径、依赖、中文目录兼容改动。
新增 runtime.ini 和打开脚本用于本机环境设置。
已验证实际识别 7、17、2026；不以样本测试代替报告准确率实验。

本机依赖
Qt：D:\Qt\6.11.1\mingw_64
MinGW：C:\Qt\Tools\mingw1310_64\bin
CMake：C:\Qt\Tools\CMake_64\bin\cmake.exe
OpenCV：D:\OpenCV-MinGW-Build-OpenCV-4.5.5-x64
Python：D:\pytorch_env\Scripts\python.exe（torch、numpy）
修改 Python 路径可调整 runtime.ini，DIGIT_PYTHON 可覆盖该设置。

2026-10-01 旧版本清理
按用户“删除错误版本、只留最终版本”的要求，旧桌面工程、旧目录链接、旧构建缓存、
原版备份、历史修复草稿及原源码压缩包均已删除；回收站中四个已核实的错误工程也已清理。
当前构建目录已整合到最终工程内部，Debug 完整编译通过。
清理前后核对最终源码、模型、可执行程序和配置文件哈希，内容一致。
