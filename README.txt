手写数字识别系统

基于 C++、Qt、OpenCV 与 Python/PyTorch 的课程小组项目。使用老师提供的 MNIST 手写数字 CNN 模型，在桌面画板中完成单数字识别，并扩展为多个数字的分割与顺序识别。

项目功能

- 在 Qt 画板中书写数字，支持调整笔宽、颜色、擦除和清空。
- 单数字识别：显示预测数字及前三个候选类别的模型输出概率。
- 多数字识别：根据外部轮廓提取数字区域，按横坐标从左到右排序，逐个识别并拼接结果。
- 输入预处理：裁剪笔迹区域、保持比例缩放、重心对齐到 28 × 28 画布，并进行灰度反转和归一化。
- 通过后台线程调用 Python 推理，识别期间保持界面响应。

我的贡献

黄宇旌在本小组项目中主要负责：

1. 加入重心对齐算法，改进手写输入的预处理。
2. 实现基于 OpenCV 外部轮廓的多数字分割，并接入逐个识别与结果拼接流程。
3. 完成相关算法功能的调试与完善。

CNN 模型由课程老师提供，界面等其他模块包含组员的工作。本仓库用于展示课程项目及个人负责的算法部分。

识别流程

画板输入 → 灰度化与阈值处理 → 外部轮廓及包围框提取 → 从左到右排序 → 单数字裁剪与重心对齐 → 28 × 28 归一化输入 → CNN 推理 → 结果显示。

预处理的归一化参数为 mean = 0.1307、std = 0.3081。predict.py 使用 torch.jit.load 读取 mnist.pt，在 CPU 上进行推理。

多数字分割主要适用于单行书写、各数字之间有间隔的输入。相互粘连的数字或断裂的笔画可能影响轮廓分割结果。单数字显示的候选概率反映模型输出，不等同于整个系统的准确率。

主要文件

文件：作用
CMakeLists.txt：CMake 构建配置与识别资源复制
widget.cpp / widget.h：识别流程、轮廓分割、重心对齐及后台任务
writelabel.cpp / writelabel.h：手写画板
*.ui：Qt 界面定义
predict.py：Python/PyTorch 模型推理
mnist.pt：老师提供的预训练模型
runtime.ini：推理使用的 Python 解释器路径

build/ 是本机构建目录，run/ 是本机部署的运行包，均可保留在本地并由 Git 忽略。运行包仍依赖可用的 Python/PyTorch 环境。

环境与运行

项目使用 C++17，CMake 最低版本为 3.16。随附的本机开发记录使用 Qt 6.11.1、MinGW 13.1 和 OpenCV 4.5.5；Python 环境需要安装 torch 与 numpy。CMake 配置也包含 Qt 5 分支，但随附记录未验证 Qt 5 构建。

1. 准备 Python 环境

在准备用于推理的 Python 环境中执行：

python -m pip install torch numpy
python -c "import sys; print(sys.executable)"

将打印出的解释器路径填入项目根目录的 runtime.ini。Windows 路径可使用正斜杠，例如：

[recognition]
python=D:/your-python-environment/Scripts/python.exe

上面的路径是示例，请换成实际路径。也可以通过环境变量 DIGIT_PYTHON 指定解释器；该变量优先于 runtime.ini。

2. 配置并构建 Qt 项目

1. 安装 Qt、CMake，以及与 Qt 所用编译器匹配的 OpenCV。
2. 在 Qt Creator 中打开项目根目录的 CMakeLists.txt。
3. 选择合适的 Qt/编译器套件。本项目原开发环境使用 MinGW，OpenCV 也应使用匹配的构建版本。
4. 将 CMake 配置项 OpenCV_DIR 设置为本机包含 OpenCVConfig.cmake 的目录。当前源码中的默认值指向原开发电脑的 D 盘目录，需要按实际安装位置调整。
5. 配置完成后构建并运行。构建配置会将 predict.py、mnist.pt、runtime.ini 复制到可执行程序目录。

修改根目录的 runtime.ini 后，请重新构建以同步到程序目录。使用已有本地 run/ 运行包时，应修改 run/runtime.ini，再启动 run/number3.exe。

仓库中的 configure_qt_build.ps1 和“用Qt打开正确版.cmd”是原开发电脑的辅助脚本，包含固定路径。换电脑时，建议直接在 Qt Creator 中打开 CMakeLists.txt 并配置本机环境。

3. 使用

在画板中书写单个数字，或从左到右书写有间隔的多个数字，点击“预测”。单数字模式显示候选结果，多数字模式显示拼接后的数字串。

测试记录与后续完善

随附的本机修复记录记载了对 7、17、2026 等输入的功能验证。系统准确率仍需要通过固定的手写样本集、明确的样本数量和统一测试流程进行评估。

后续计划补充演示截图、可复现的测试样本，以及重心对齐前后的对比结果。
