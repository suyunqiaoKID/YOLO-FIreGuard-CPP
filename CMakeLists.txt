# 1. 声明 CMake 最低版本要求 
cmake_minimum_required(VERSION 3.10)

# 2. 项目名称
project(YOLO-FireGuard-CPP LANGUAGES CXX)

set(CUDA_TOOLKIT_ROOT_DIR "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.8")
set(CUDA_SDK_ROOT_DIR "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.8")

set(CMAKE_PREFIX_PATH "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.8;${CMAKE_PREFIX_PATH}")

set(CUDA_BIN_PATH "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.8/bin")
set(CUDA_LIB_PATH "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.8/lib/x64")

# 3. 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenCV_DIR "C:\\new_OpenCV\\opencv\\build_cuda\\install\\x64\\vc17\\lib")

# 4. 寻找 OpenCV 库
find_package(OpenCV REQUIRED)

# 5. 指定头文件目录
include_directories(include)
include_directories(${OpenCV_INCLUDE_DIRS})

# 6. 指定源文件
set(SOURCE_FILES 
    src/main.cpp 
    src/Detector.cpp
)

# 7. 生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# 8. 链接 OpenCV 库
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})