cmake_minimum_required(VERSION 3.17)
project(JLang)

set(CMAKE_CXX_STANDARD 17)

# add_compile_definitions(_DEBUG)

add_executable(
        JLang
        src/main.cpp
        src/lexer/Token.cpp
        src/lexer/Token.h
        src/lexer/Lexer.cpp
        src/lexer/Lexer.h
        src/lexer/IntConstToken.cpp
        src/lexer/IntConstToken.h
        src/lexer/BoolConstToken.cpp
        src/lexer/BoolConstToken.h
        src/lexer/RealConstToken.cpp
        src/lexer/RealConstToken.h
        src/lexer/IdentifierToken.cpp
        src/lexer/IdentifierToken.h
        src/logger.h
        src/logger.cpp
        src/utils.h
        src/utils.cpp
        src/parser/Parser.cpp
        src/parser/Parser.h
        src/parser/tree/TreeNode.h
        src/parser/tree/Tree.h
        src/parser/exceptions/SyntaxError.cpp
        src/parser/exceptions/SyntaxError.h
        src/rpn_interpreter/RPNInterpreter.cpp
        src/rpn_interpreter/RPNInterpreter.h
        src/rpn_interpreter/exceptions/RunTimeError.cpp
        src/rpn_interpreter/exceptions/RunTimeError.h
        src/rpn_interpreter/VariableType.h
        src/lexer/JUMPToken.cpp src/lexer/JUMPToken.h
        src/lexer/JFToken.cpp
        src/lexer/JFToken.h
        src/lexer/exceptions/LexerError.cpp
        src/lexer/exceptions/LexerError.h
)