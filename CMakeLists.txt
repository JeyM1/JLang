cmake_minimum_required(VERSION 3.17)
project(JLang)

set(CMAKE_CXX_STANDARD 17)

add_executable(JLang src/main.cpp src/lexer/Token.cpp src/lexer/Token.h src/lexer/Lexer.cpp src/lexer/Lexer.h src/lexer/IntConstToken.cpp src/lexer/IntConstToken.h src/lexer/BoolConstToken.cpp src/lexer/BoolConstToken.h src/lexer/RealConstToken.cpp src/lexer/RealConstToken.h)