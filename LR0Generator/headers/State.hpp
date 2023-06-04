#ifndef State_hpp
#define State_hpp

#include <string>
#include <vector>

#include "Rule.hpp"

using namespace std;

class State {
    public:
        State();
        State(int number);
        ~State();

        void addRule(Rule rule);
        void addClosure(string element);
        void addTransition(string element, int state);
        bool isClosed(string element);
        bool isEqual(State& otherState);
        bool reduce();

        int reduce_rule;
        int depth;
        int number;
        vector<Rule> rules;
        vector<string> closed;
        vector<pair<string, int>> transitions;

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
            for(auto transition : state.transitions)
            {
                   os << "(" << transition.first << "," << transition.second << ")" << endl;
            }
            return os;
        }
};

#endif
