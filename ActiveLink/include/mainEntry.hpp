#include <string>
#include <iostream>

#include "lexer.h"
#include "parser.h"
#include "runtime.h"
#include "help.h"
#include "repl_core.h"

Runtime runtime;

// ---------------- Block detection ----------------
bool isBlockStart(const std::string& line) {
    size_t start = line.find_first_not_of(" \t");
    if (start == std::string::npos) return false;

    std::string s = line.substr(start);
    size_t end = s.find_last_not_of(" \t");
    if (end != std::string::npos)
        s = s.substr(0, end + 1);

    return (
        s.rfind("if",0)==0 ||
        s.rfind("while",0)==0 ||
        s.rfind("for",0)==0 ||
        s.rfind("func",0)==0 ||
        s.rfind("app",0)==0 ||
        s.rfind("window",0)==0 ||
        s.rfind("elif",0)==0 ||
        s.rfind("else",0)==0 ||
        (!s.empty() && (s.back()=='{' || s.back()=='['))
    );
}

// ---------------- CORE RUN FUNCTION ----------------
std::string run(const std::string& source, bool isDebug) {
    try {
        Lexer lexer(source);
        auto tokens = lexer.tokenize();

        Parser parser(tokens);
        auto program = parser.parse();

        if (isDebug) {
            std::cout << "\n--- DEBUG AST ---\n";
            program->print();
            std::cout << "-----------------\n";
        }

        runtime.execute(std::move(program));

        return "OK";

    } catch (const std::exception& e) {
        return std::string("Error: ") + e.what();
    }
}