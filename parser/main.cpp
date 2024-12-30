
#include "parser.h"

int main(int argc, char** argv)
{    auto base_grammar =argv[1];
    //cout <<"\n\n input n\n\n\n";

     auto input = FileToString(argv[2]);

     /*cout <<"\n\n\n\n\n";
     cout << input;
     cout <<"\n\n\n\n\n";
*/
   cout <<parseInput(base_grammar,input.c_str());

}