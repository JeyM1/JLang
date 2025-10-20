# JLang - A Custom Programming Language

A custom programming language implementation written in C++17, featuring a complete lexer, parser, and Reverse Polish Notation (RPN) interpreter.

## Features

- **Variable Declarations & Assignments** - Declare and manage variables with type support
- **Arithmetic & Logical Expressions** - Perform mathematical and boolean operations
- **Control Structures** - if statements, for loops, and do-while loops
- **Input/Output Operations** - Interactive I/O with users
- **Type System** - Support for integers, reals, and booleans
- **Error Handling** - Syntax error detection and runtime error reporting

## Architecture

JLang follows a classic three-stage compiler architecture:

### 1. Lexer
Tokenizes input code by classifying characters into categories (letters, digits, operators, etc.).

### 2. Parser
Analyzes the token stream and builds a syntax tree using recursive descent parsing.

### 3. RPN Interpreter
Executes the parsed code using a stack-based Reverse Polish Notation approach.

## Build & Installation

### Prerequisites
- C++17 compatible compiler
- CMake 3.17 or higher

### Building

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Usage

Create a `test.jlang` file with your JLang code and run the compiled executable:

```bash
./jlang
```

The program will read and execute the code from `test.jlang`.

## Project Structure

```
src/
├── lexer/              # Lexical analysis components
│   ├── Lexer.h/cpp
│   ├── Token.h/cpp
│   └── Token type implementations
├── parser/             # Syntax parsing & tree construction
│   ├── Parser.h/cpp
│   ├── tree/           # Syntax tree structures
│   └── exceptions/     # Parser error handling
├── rpn_interpreter/    # RPN-based execution engine
│   ├── RPNInterpreter.h/cpp
│   ├── VariableType.h
│   └── exceptions/     # Runtime error handling
├── main.cpp            # Entry point
├── utils.h/cpp         # Utility functions
└── logger.h/cpp        # Logging utilities
```

## Key Components

| Component | Purpose |
|-----------|---------|
| **Lexer** | Converts raw source code into tokens |
| **Parser** | Converts tokens into an abstract syntax tree (AST) |
| **Interpreter** | Executes the AST using RPN evaluation |

## Language Execution Flow

1. **Lexical Analysis** - Source code is tokenized
2. **Syntax Parsing** - Tokens are organized into an AST and converted to RPN
3. **RPN Interpretation** - Stack-based execution of RPN instructions

## License

This project is provided as-is for educational and development purposes.

---

**Built with C++17 • CMake • Custom Language Design**