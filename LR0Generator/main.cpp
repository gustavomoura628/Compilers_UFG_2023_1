#include <iostream>
#include <string>
#include "LR0Generator.hpp"
#include "XMLGenerator.hpp"

using namespace std;

int main(int argc, char *argv[])
{

    //string path_to_grammar = argv[1];
    //LR0Generator gen(path_to_grammar);
    //gen.print();
    //Rule r(1,"E'", "E");
    //cout << r.addDot() << endl;
    //State state(0);
    //state.addRule(r);
    //state.addClosure("P");
    //state.addTransition("+", 1);
    //cout << state << endl;

    string path_to_grammar = argv[1];
    LR0Generator gen(path_to_grammar);

    //gen.print_rules();
    //cout << gen << endl;
    //return 0;

    XMLGenerator xml(gen);
    xml.print_header();
    xml.recursive_draw(xml.lr0generator.states[0],0,0,false, -1, 0);
    xml.print_footer();
    return 0;
}
