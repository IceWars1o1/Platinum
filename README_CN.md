# Platinum


Platinum 是一个使用 C++17 开发的 Windows 平台轻量级命令行工具包。它提供了 MD5 哈希计算、BMI 计算、随机数生成、待办事项管理、大小写转换、UUID 生成以及蜂鸣器音乐播放等实用功能。


---


## 使用说明

### 1. 通过 Release 获取

前往 [GitHub Releases](https://github.com/IceWars1o1/Platinum/releases) 页面，下载最新版本的 `platinum.exe`，将其放置到任意目录（建议添加到系统 PATH 中）。

### 2. 命令行运行

打开终端（CMD 或 PowerShell），输入以下命令：

```bash
# 查看帮助
platinum -h
platinum --help


# 查看版本
platinum -v
platinum --version


# 计算 MD5 哈希
platinum md5 "Hello World"


# 计算 BMI（身高单位为厘米，体重单位为千克）
platinum bmi 175 70


# 生成随机数（默认范围 0 到 100）
platinum random
platinum random --min 1 --max 100


# 待办事项管理
platinum todo add "购买牛奶"
platinum todo list
platinum todo finish
platinum todo remove
platinum todo clear


# 大小写转换
platinum case upper "hello"
platinum case lower "WORLD"


# 生成 UUID
platinum uuid


# 播放蜂鸣器音乐
platinum playsound
```


---


## 开发方式

### 环境要求

- **操作系统**：Windows (x64)
- **编译器**：支持 C++17 的编译器（例如 MinGW-w64 g++ 或 MSVC）
- **构建工具**：Make（可选，用于基于 Makefile 的构建）

### 项目结构

```
Platinum/
├── include/          # 头文件
│   ├── beep.hpp      # 蜂鸣器音符定义
│   ├── bmi.hpp       # BMI 计算接口
│   ├── case.hpp      # 大小写转换接口
│   ├── commands.hpp  # 命令分发接口
│   ├── cursor.hpp    # 终端光标控制宏
│   ├── md5.hpp       # MD5 哈希接口
│   ├── random.hpp    # 随机数生成接口
│   ├── todo.hpp      # 待办事项管理接口
│   ├── usage.hpp     # 帮助与版本信息
│   └── uuid.hpp      # UUID 生成接口
├── src/              # 源文件
│   ├── beep.cpp      # 蜂鸣器播放器入口
│   ├── bmi.cpp       # BMI 计算实现
│   ├── case.cpp      # 大小写转换实现
│   ├── commands.cpp  # 命令解析与分发
│   ├── md5.cpp       # MD5 算法实现
│   ├── random.cpp    # 随机数生成实现
│   ├── todo.cpp      # 待办事项管理实现
│   ├── usage.cpp     # 帮助与版本输出
│   ├── uuid.cpp      # UUID 生成实现
│   └── beep/         # 蜂鸣器音乐数据
│       ├── base.cpp  # 基础音符播放函数
│       └── 0x00000001.cpp  # 曲目《上春山》
├── test/             # 测试文件（独立模块测试）
├── Platinum.cpp      # 主程序入口
├── Makefile          # 构建脚本
├── LICENSE           # MIT 许可证
└── README.md         # 本文件
```


### 构建步骤

#### 使用 Makefile（推荐）

```bash
# 克隆仓库
git clone https://github.com/IceWars1o1/Platinum.git
cd Platinum
```

然后在根目录下创建 `Makefile` 文件，并输入以下内容。

```makefile
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude
BUILD = build
SRC = src
TARGET = platinum.exe

OBJS = $(BUILD)/Platinum.o $(BUILD)/commands.o $(BUILD)/md5.o $(BUILD)/bmi.o \
       $(BUILD)/random.o $(BUILD)/todo.o $(BUILD)/case.o $(BUILD)/uuid.o $(BUILD)/usage.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD)/%.o: $(SRC)/%.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/Platinum.o: Platinum.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD) $(TARGET)

.PHONY: all clean

```

然后使用以下命令编译项目。

```bash
# 编译
make

# 清理构建产物
make clean
```


编译完成后，`platinum.exe` 将生成在项目根目录下。

#### 手动编译

如果 Make 工具不可用，可以直接调用 g++：

```bash
g++ -std=c++17 -Iinclude     Platinum.cpp     src/commands.cpp src/md5.cpp src/bmi.cpp src/random.cpp     src/todo.cpp src/case.cpp src/uuid.cpp src/usage.cpp     src/beep.cpp src/beep/base.cpp src/beep/0x00000001.cpp     -o platinum.exe
```


### 开发规范

- 所有功能模块均封装在 `pt` 命名空间下。
- 新增命令需在 `commands.cpp` 中实现对应函数，并在 `Platinum.cpp` 中注册路由。
- 头文件统一放置在 `include/` 目录下，源文件放置在 `src/` 目录下。
- 蜂鸣器音乐数据存储在 `src/beep/` 目录中，文件命名格式为 `0xXXXXXXXX.cpp`。


---


## 许可证

本项目基于 [MIT 许可证](LICENSE) 开源。


---


> 由 IceWars1o1 制作。