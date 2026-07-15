<div align="center">

<!-- 动态标题区 -->
<img src="https://img.shields.io/badge/Windows-x64-0078D6?logo=windows&logoColor=white" alt="Platform">
<img src="https://img.shields.io/badge/C++-17-00599C?logo=c%2B%2B&logoColor=white" alt="C++17">
<img src="https://img.shields.io/badge/License-MIT-green.svg" alt="License">
<img src="https://img.shields.io/github/v/release/IceWars1o1/Platinum?include_prereleases&color=brightgreen" alt="Release">

<!-- 项目 Logo / 名称 -->
<h1><img src="resource/icon.png" alt="Pt Platinum"><br> Platinum
</h1>


<p><strong>Lightweight command-line toolkit for Windows</strong></p>
<p>MD5 · BMI · Random · Todo · Case Conversion · UUID</p>

<!-- 快速安装按钮 -->
<a href="https://github.com/IceWars1o1/Platinum/releases">
  <img src="https://img.shields.io/badge/Download-2ea44f?style=for-the-badge" alt="Download">
</a>
&nbsp;
<a href="#start">
  <img src="https://img.shields.io/badge/Get Started-0366d6?style=for-the-badge" alt="Get Started">
</a>

</div>

 - [English](README.md)
 - [简体中文](README_CN.md)

---
<div id="start"></div>
Platinum is a lightweight command-line toolkit developed in C++17 for the Windows platform. It offers practical features such as MD5 hashing, random number generation, todo management, time output, and UUID generation.

---


## Usage Instructions 

### 1. Obtain via Release 

Go to the [GitHub Releases](https://github.com/IceWars1o1/Platinum/releases) page, download the latest version of `platinum.exe`, and place it in any directory (recommended to add it to the system PATH). 

### 2. Running from the Command Line 

Open the terminal (CMD or PowerShell) and enter the following command: 

```bash
# View Help
platinum -h
platinum --help


# View Version
platinum -v
platinum --version


# Calculate MD5 Hash
platinum md5 "Hello World"


# Generate random numbers (default 0 to 100)
platinum random
platinum random --min 1 --max 100


# Todo Management
platinum todo add "Buy milk"
platinum todo list
platinum todo finish
platinum todo remove
platinum todo clear


# Generate UUID
platinum uuid
```


---


## Development Method 

### Environmental Requirements 

- **Operating System**: Windows (x64)  
- **Compiler**: C++17-compliant compiler (e.g., MinGW-w64 g++ or MSVC)  
- **Build Tool**: Make (optional, for Makefile-based builds) 

### Build Steps 

#### Using Makefile (Recommended) 

```bash
# Clone repository
git clone https://github.com/IceWars1o1/Platinum.git
cd Platinum
```

Then create a `Makefile` file in the root directory and type in the following content.

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

And then use following commands to compile the project.

```bash
# Compilation
make

# Clean build artifacts
make clean
```


After compilation, `platinum.exe` will be generated in the project root directory. 

#### Manual Compilation 

If the Make tool is not available, you can directly call g++.


### Development Guidelines 

- All functional modules are encapsulated under the `pt` namespace.  
- New commands must have their corresponding functions implemented in `commands.cpp` and registered with routing in `Platinum.cpp`.  
- Header files are all placed in the `include/` directory, while source files go into the `src/` directory.  

---


## License 

This project is open-source under the [MIT License](LICENSE). 

---


> Made by IceWars1o1.
