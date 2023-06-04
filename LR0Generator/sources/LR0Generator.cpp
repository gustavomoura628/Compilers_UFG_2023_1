#include <iostream>
#include "LR0Generator.hpp"

Rule::Rule()
{
}
Rule::~Rule()
{
}
Rule::Rule(int _number, string _left, string _right)
{
    number = _number;
    left = _left;
    right = _right;
}
string Rule::getDotElement()
{
    int dot = right.find(".");
    if(dot == -1) return "";
    string after_dot = right.substr(dot+1);
    int space = after_dot.find(" ");
    string before_space = after_dot.substr(0,space);
    return before_space;
}

Rule Rule::addDot()
{
    if(getDotElement() != "") return Rule(number,left,right);

    string dot = ".";
    return Rule(number, left, dot.append(right));
}

Rule Rule::nextDot()
{

    int dot = right.find(".");
    int space = right.substr(dot).find(" "); 
    if(space == -1) space = right.size()-1;
    else space += dot;
    string left_of_dot = right.substr(0,dot);
    string word_of_dot = right.substr(dot+1,space+1-(dot+1));//This imposes a restriction where the string cannot have more than one space
    string right_of_dot = right.substr(space+1);
    string newRight = left_of_dot.append(word_of_dot).append(".").append(right_of_dot);

    return Rule(number,left,newRight);
}
bool Rule::isEqual(Rule otherRule)
{
    if(number != otherRule.number) return false;
    if(right.find(".") != otherRule.right.find(".")) return false;
    return true;
}
bool Rule::isReduction()
{
    return getDotElement() == "";
}

State::State()
{
}
State::State(int _number)
{
    number = _number;
    reduce_rule = -1;
}

State::~State()
{
}
void State::addRule(Rule rule)
{
    rules.push_back(rule);
    if(rule.isReduction())
    {
        reduce_rule = rule.number;
    }
}
void State::addClosure(string element)
{
    closed.push_back(element);
}
void State::addTransition(string element, int state)
{
     transitions.push_back(make_pair(element, state));

}
bool State::isClosed(string element)
{
    for(auto closed_element : closed)
    {
        if(closed_element == element) return true;
    }
    return false;
}
bool State::isEqual(State& otherState)
{
    if(otherState.rules.size() != rules.size()) return false;
    for(auto otherRule : otherState.rules)
    {
        bool found = false;
        for(auto rule : rules)
        {
            if(rule.isEqual(otherRule))
            {
                found = true;
                break;
            }
        }
        if(found == false) return false;
    }
    return true;
}
bool State::reduce()
{
    return reduce_rule > -1;
}

LR0Generator::LR0Generator()
{
}
LR0Generator::~LR0Generator()
{
}
LR0Generator::LR0Generator(string path_to_grammar)
{
    read_grammar_file(path_to_grammar);

    State initial_state(0);
    initial_state.addRule(rules.front().addDot());
    close_rule(initial_state);
    initial_state.depth = 0;
    states.push_back(initial_state);
    nextAvailableID = 1;

    for(int i=0; i<states.size(); i++)
    {
        //cout << "PROCESSING STATE " << i << endl;
        //cout << states[i];
        add_new_states(i);
        //cout << "FINISHED STATE " << i << endl;
    }
}
int LR0Generator::find_equal_state(State state)
{
    for(int i=0; i< states.size(); i++)
    {
        if(states[i].isEqual(state)) return i;
    }
    return -1;
}
void LR0Generator::add_new_states(int state_number)
{
    //cout << "Trying to add new states from " << states[state_number].number << endl;
    //cout << states[state_number] << endl;
    for(auto element : states[state_number].closed)
    {
        //cout << "Adding new states from " << states[state_number].number << " to " << element << endl;
        State new_state(-1);
        for(auto rule : states[state_number].rules)
        {
            if(rule.getDotElement() == element)
            {
                //cout << rule.getDotElement() << " == " << element << endl;
                //cout << "adding " << rule.nextDot() << endl;
                new_state.addRule(rule.nextDot());
            }
        }
        close_rule(new_state);
        int already_exists = find_equal_state(new_state);
        if(already_exists != -1)
        {
            //cout << "State already exists\n";
            states[state_number].addTransition(element,already_exists);
        }
        else
        {
            new_state.number = nextAvailableID;
            nextAvailableID++;
            //cout << "Adding new state " << new_state.number << endl;
            //cout << new_state << endl;
            states[state_number].addTransition(element,new_state.number);
            new_state.depth = states[state_number].depth + 1;
            states.push_back(new_state);
        }
    }
    //cout << "Finished State " << states[state_number].number << endl;
}
void LR0Generator::read_grammar_file(string path_to_grammar)
{
    ifstream file(path_to_grammar);
    assert(file.is_open());
    int number;
    string left, arrow, right;
    while( file >> number >> left >> arrow)
    {
        file.ignore();
        if(!getline(file,right))break;
        rules.push_back(Rule(number,left,right));
    }
    file.close();
}
void LR0Generator::close_rule(State& state)
{
    //cout << "Closing state " << state.number << endl;
    for(int i = 0; i < state.rules.size(); i++)
    {
        Rule & rule = state.rules[i];
        //cout << "Analyzing rule " << rule << endl;
        string dot = rule.getDotElement();
        //cout << "dot = " << dot;
        if(dot == "") continue;
        if(state.isClosed(dot))
        {
            //cout << dot << " is already closed\n";
            continue;
        }
        for(auto scan_rule : rules)
        {
            if(dot == scan_rule.left)
            {
                state.addRule(scan_rule.addDot());
            }
        }
        state.addClosure(dot);
        //cout << "adding " << dot << " closure\n";
    }
    //cout << "Closed state " << state.number << endl;
}
void LR0Generator::print_rules()
{
    cout << "RULES:\n";
    for(auto rule : rules)
    {
        cout << rule << endl;
    }
}
