
#include "peglib.h"

#include <string>
#include <fstream>
#include <streambuf>

#include <chrono>

#include <iostream>
#include <sstream>
#include <chrono>
#include <string>

using namespace std;

#ifndef STAND_ALONE
#include <emscripten/emscripten.h>
#endif
// run as ./test grammar input




#include "peglib.h"

#include <string>
#include <fstream>
#include <streambuf>

#include <chrono>

#include <iostream>
#include <sstream>
#include <chrono>
#include <string>

using namespace std;

// run as ./test grammar input

std::string FileToString(std::string file_name) {
    std::ifstream str(file_name);
    std::string txt((std::istreambuf_iterator<char>(str)),
                     std::istreambuf_iterator<char>());
    return txt;
}

std::string combineVector(const std::vector<std::string>& vec) {
    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        oss << vec[i];
        if (i < vec.size() - 1) {
            oss << ", "; // Add separator
        }
    }
    return oss.str();
}


// Function to parse input and simulate parser operations
#ifndef STAND_ALONE
extern "C" EMSCRIPTEN_KEEPALIVE
#endif
const char * parseInput(const char* grammar_filename, const char* input) {
    vector<string> vs;

    string base_grammar(FileToString(grammar_filename));
    string input_text(input);
    //cout <<"*******************************\n\n\n\n ";
    //cout << base_grammar;
    //cout <<"*******************************\n\n\n\n ";
    auto start_parser_construct = chrono::system_clock::now();
    peg::parser p(base_grammar);
    p.enable_packrat_parsing();
    p.enable_ast();
    auto end_parser_construct = chrono::system_clock::now();

    auto construct_ms
            = chrono::duration_cast<chrono::nanoseconds>(
                  end_parser_construct - start_parser_construct)
                  .count();

    if(!(bool)p) {
        printf("parser construction error\n");
        return "parser construction error\n";
    }
    printf("PEG load base grammar %lld\n", construct_ms);
     // enable error logging just in case
    p.set_logger([&](size_t line, size_t col, const string& msg) {
            #define BUFFER_SIZE 1024
            static char output_buffer[BUFFER_SIZE];
          snprintf(output_buffer, BUFFER_SIZE, "Error on line %zu:%zu -> %s\n", line, col, msg.c_str());
          vs.push_back(output_buffer);
    });

    
    auto start_parser_execute = chrono::system_clock::now();

   p.parse(input_text);
  auto end_parser_execute = chrono::system_clock::now();

  auto parse_ms
          = chrono::duration_cast<chrono::nanoseconds>(
                end_parser_execute - start_parser_execute)
                .count() ;

  // Print the result
  printf("PEG parsing time %lld\n", parse_ms);

   static std::string combinedResult = combineVector(vs);

    return combinedResult.c_str(); // Return the combined string

    
}

#ifndef STAND_ALONE
extern "C" EMSCRIPTEN_KEEPALIVE
#endif
long long wordcount(char * filename) {

    string base_grammar(FileToString(filename));

    std::string str(base_grammar);
    std::istringstream stream(str);
    std::vector<std::string> words;
    std::string word;

    while (stream >> word) {
        words.push_back(word);
    }

    return words.size();
}
