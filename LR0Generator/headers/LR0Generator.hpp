#ifndef LR0Generator_hpp
#define LR0Generator_hpp

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <assert.h>

using namespace std;



class Rule {
    public:
        int number;
        string left;
        string right;

        Rule();
        ~Rule();
        Rule(int number, string left, string right);
        string getDotElement();
        Rule addDot();
        Rule nextDot();
        bool isEqual(Rule otherRule);
        bool isReduction();

        friend ostream& operator<<(ostream& os, const Rule & rule)
        {
            return os << "(" << rule.number << ") " << rule.left << " -> " << rule.right;
        }
};

class State {
    public:
        State();
        State(int number);
        ~State();

        void addRule(Rule rule);
        void addClosure(string Element);
        void addTransition(string Element, int state);
        bool isClosed(string Element);
        bool isEqual(State& otherState);
        bool reduce();

        int reduce_rule;
        int depth;
        int number;
        vector<Rule> rules;
        vector<string> closed;
        vector<string> transitions_order; //TODO????? maybe its fine already?
        map<string, int> transitions;

        friend ostream& operator<<(ostream& os, const State & state)
        {
            os << "State " << state.number << endl;
            os << "Depth " << state.depth << endl;
            os << "Rules: " << endl;
            for(auto rule : state.rules)
            {
                os << rule << endl;
            }
            os << "Closures: " << endl;
            for(auto closed : state.closed)
            {
                os << closed << endl;
            }
            os << "Transitions: " << endl;
            //ORDER BY INSERTION
            for(string element : state.transitions_order)
            {
                int next_state = state.transitions.at(element);
                       os << "(" << element << "," << next_state << ")" << endl;
            }
            //ORDER BY VALUE
            //int max_transition = 0;
            //for(auto transition : state.transitions)
            //{
            //    if(transition.second > max_transition) max_transition = transition.second;
            //}
            //for(int i=0; i<max_transition; i++)//Disgusting hack to get the correct order (map ordered by value)
            //{
            //    for(auto transition : state.transitions)
            //    {
            //        if(transition.second == i)
            //        {
            //            os << "(" << transition.first << "," << transition.second << ")" << endl;
            //        }
            //    }
            //}
            return os;
        }
};

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

        friend ostream& operator<<(ostream& os, const LR0Generator & lr0generator)
        {
            os << "States:\n";
            for(auto state : lr0generator.states)
            {
                os << state << endl;
            }
            return os;
        }
};
#endif
