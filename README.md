# Platinum

 - [English](README.md)
 - [简体中文](README_CN.md)

---

Platinum is a lightweight command-line toolkit developed in C++17 for the Windows platform. It offers practical features such as MD5 hashing, BMI calculation, random number generation, todo management, case conversion, UUID generation, and buzzer music playback. 

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


# Calculate BMI (height in cm, weight in kg)
platinum bmi 175 70


# Generate random numbers (default 0 to 100)
platinum random
platinum random --min 1 --max 100


# Todo Management
platinum todo add "Buy milk"
platinum todo list
platinum todo finish
platinum todo remove
platinum todo clear


# Case Conversion
platinum case upper "hello"
platinum case lower "WORLD"


# Generate UUID
platinum uuid


# Play buzzer music
platinum playsound
```


---


## Development Method 

### Environmental Requirements 

- **Operating System**: Windows (x64)  
- **Compiler**: C++17-compliant compiler (e.g., MinGW-w64 g++ or MSVC)  
- **Build Tool**: Make (optional, for Makefile-based builds) 

### Project Structure 

```
Platinum/
├── include/          # Header files  
│   ├── beep.hpp      # Beeper note definitions  
│   ├── bmi.hpp       # BMI calculation interface  
│   ├── case.hpp      # Case conversion interface  
│   ├── commands.hpp  # Command dispatch interface  
│   ├── cursor.hpp    # Terminal cursor control macros  
│   ├── md5.hpp       # MD5 hash interface  
│   ├── random.hpp    # Random number generation interface  
│   ├── todo.hpp      # Todo management interface  
│   ├── usage.hpp     # Help and version information  
│   └── uuid.hpp      # UUID generation interface  
├── src/              # Source files  
│   ├── beep.cpp      # Beep player entry point  
│   ├── bmi.cpp       # BMI calculation implementation  
│   ├── case.cpp      # Case conversion implementation  
│   ├── commands.cpp  # Command parsing and dispatch  
│   ├── md5.cpp       # MD5 algorithm implementation  
│   ├── random.cpp    # Random number generation implementation  
│   ├── todo.cpp      # Todo management implementation  
│   ├── usage.cpp     # Help and version output  
│   ├── uuid.cpp      # UUID generation implementation  
│   └── beep/         # Beep music data  
│       ├── base.cpp  # Basic note playback functions  
│       └── 0x00000001.cpp  # Track "Shang Chun Shan(上春山)"  
├── test/             # Test files (independent module tests)  
├── Platinum.cpp      # Main program entry  
├── Makefile          # Build script  
├── LICENSE           # MIT License  
└── README.md         # This file
```


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

And then use following commands to compile the project.

```bash
# Compilation
make

# Clean build artifacts
make clean
```


After compilation, `platinum.exe` will be generated in the project root directory. 

#### Manual Compilation 

If the Make tool is not available, you can directly call g++: 

```bash
g++ -std=c++17 -Iinclude     Platinum.cpp     src/commands.cpp src/md5.cpp src/bmi.cpp src/random.cpp     src/todo.cpp src/case.cpp src/uuid.cpp src/usage.cpp     src/beep.cpp src/beep/base.cpp src/beep/0x00000001.cpp     -o platinum.exe
```


### Development Guidelines 

- All functional modules are encapsulated under the `pt` namespace.  
- New commands must have their corresponding functions implemented in `commands.cpp` and registered with routing in `Platinum.cpp`.  
- Header files are all placed in the `include/` directory, while source files go into the `src/` directory.  
- Buzzer music data is stored in the `src/beep/` directory, named in the format `0xXXXXXXXX.cpp`. 

---


## License 

This project is open-source under the [MIT License](LICENSE). 

---


> Made by IceWars1o1.
