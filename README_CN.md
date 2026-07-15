<div align="center">

<!-- 动态标题区 -->
<img src="https://img.shields.io/badge/Windows-x64-0078D6?logo=windows&logoColor=white" alt="Platform">
<img src="https://img.shields.io/badge/C++-17-00599C?logo=c%2B%2B&logoColor=white" alt="C++17">
<img src="https://img.shields.io/badge/License-MIT-green.svg" alt="License">
<img src="https://img.shields.io/github/v/release/IceWars1o1/Platinum?include_prereleases&color=brightgreen" alt="Release">

<!-- 项目 Logo / 名称 -->
<h1><img src="resource/icon.png" alt="Pt Platinum"><br> Platinum
</h1>


<p><strong>Windows 轻量命令行工具</strong></p>
<p>MD5 · BMI · 随机数 · 待办 · 字母转换 · UUID</p>

<!-- 快速安装按钮 -->
<a href="https://github.com/IceWars1o1/Platinum/releases">
  <img src="https://img.shields.io/badge/立即下载-2ea44f?style=for-the-badge" alt="Download">
</a>
&nbsp;
<a href="#start">
  <img src="https://img.shields.io/badge/快速开始-0366d6?style=for-the-badge" alt="Get Started">
</a>

</div>


 - [English](README.md)
 - [简体中文](README_CN.md)

---
<div id="start"></div>

Platinum 是一个使用 C++17 开发的 Windows 平台轻量级命令行工具包。它提供了 MD5 哈希计算、随机数生成、待办事项管理、时间格式化输出以及UUID 生成等实用功能。


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


# 生成随机数（默认范围 0 到 100）
platinum random
platinum random --min 1 --max 100


# 待办事项管理
platinum todo add "购买牛奶"
platinum todo list
platinum todo finish
platinum todo remove
platinum todo clear


# 生成 UUID
platinum uuid
```


---


## 开发方式

### 环境要求

- **操作系统**：Windows (x64)
- **编译器**：支持 C++17 的编译器（例如 MinGW-w64 g++ 或 MSVC）
- **构建工具**：Make（可选，用于基于 Makefile 的构建）

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
       $(BUILD)/random.o $(BUILD)/todo.o $(BUILD)/case.o $(BUILD)/uuid.o \
       $(BUILD)/usage.o

RES_OBJ = $(BUILD)/app_res.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) $(RES_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD)/%.o: $(SRC)/%.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/Platinum.o: Platinum.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(RES_OBJ): resource/app.rc resource/icon.ico | $(BUILD)
	windres -O coff -i $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD) $(TARGET)

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

如果 Make 工具不可用，可以直接调用 g++。


### 开发规范

- 所有功能模块均封装在 `pt` 命名空间下。
- 新增命令需在 `commands.cpp` 中实现对应函数，并在 `Platinum.cpp` 中注册路由。
- 头文件统一放置在 `include/` 目录下，源文件放置在 `src/` 目录下。

---


## 许可证

本项目基于 [MIT 许可证](LICENSE) 开源。


---


> 由 IceWars1o1 制作。