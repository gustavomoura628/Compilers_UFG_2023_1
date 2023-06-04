#ifndef LR0Generator_hpp
#define LR0Generator_hpp

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <assert.h>

#include "Rule.hpp"
#include "State.hpp"

using namespace std;

class LR0Generator {
    public:
        LR0Generator();
        ~LR0Generator();
        LR0Generator(string path_to_grammar);

        int nextAvailableID;
        void read_grammar_file(string path_to_grammar);
        void print_rules();
        void close_rule(State& state);
        void add_new_states(int state_number);
        int find_equal_state(State state);

        vector<Rule> rules;
        vector<State> states;

        friend ostream& operator<<(ostream& os, const LR0Generator& lr0generator);
};
#endif
