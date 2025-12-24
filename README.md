# FireGuard: YOLOv8 Fire Detection System (C++ & CUDA)

基于 YOLOv8 和 OpenCV CUDA 加速的实时火灾预警系统。

## 🌟 项目亮点
- **高性能推理**：利用 RTX 4060 GPU 加速，FPS 可达 100+。
- **工业级逻辑**：采用连续帧确认机制，有效降低误报率。
- **智能预警**：检测到火情后自动触发系统声音报警，并保存截图至 `logs` 文件夹。
- **工程化结构**：解耦了检测器（Detector）与业务逻辑，易于维护和扩展。

## 🛠️ 环境要求
- Windows 10/11
- Visual Studio 2022
- OpenCV 4.10.0 (with CUDA modules)
- CUDA Toolkit 11.8 & cuDNN 9.x
- NVIDIA GeForce RTX 4060 (或其它支持 CUDA 的显卡)

## 📂 项目结构
- `src/`: 核心源代码
- `include/`: 头文件
- `models/`: 存放导出的 `best.onnx` 模型
- `data/`: 测试视频素材
- `logs/`: 报警截图自动保存位置

## 🔨 编译步骤
1. 克隆项目
2. 在 CMakeLists.txt 中修改你的 OpenCV 和 CUDA 路径
3. 执行以下命令：
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build . --config Release
   ```