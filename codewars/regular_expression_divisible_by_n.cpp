#include <string>
#include <vector>
#include <iostream>
using namespace std;

void printautomata( const vector<vector<string>>& automaton){
  cout<<" i will print out the automato here"<<endl;
  for(int a = 0; a < automaton.size(); a++){
    auto x = automaton[a];
    cout<<"for "<<a<<endl;
    for(int i =0; i < x.size();i++){
      if(x[i]!="") cout<< "takes in "<<x[i]<<" to reach "<<i<<"        ";
    }
    cout<<endl;
  }
}
void createAutomaton(int n, vector<vector<string>> &automaton){
    // a 2d matrix would be better for look up and as well for mutation
    // for a number n, the number of states in the automaton would be exactly n (from 0 to n-1) where i in ith state represents the remainder upon dividing it with N
    automaton.resize(n, vector<string>(n, ""));
    // for every such automaton the 0th state the initial state is also the accepting state

    for(int state = 0; state< n; state++){
        int _x = state*2;
        int f0 = _x%n;
        int f1 = (_x+1)%n;
        automaton[state][f0] = "0";
        if(automaton[state][f1] == "") automaton[state][f1] = "1";
        else automaton[state][f1] = "(" + automaton[state][f1] + "|1)";
    }
//     printautomata(automaton);
    // automaton[i][j] is the string that is the transition variable from state i to state j, if there is no direct transition it would be empty
    return;
}

string generateRegularExpression(vector<vector<string>> &automaton){
    // we will remove the states one by one untill there is only one state left (for this example the accepting and initial state is same, that's why 1 otherwise we need two (2) states)
    int number_of_states = automaton.size();
    for(int s = number_of_states-1; s>=1; s--){
        vector<int> coming_from;
        // get the states that has an outward edge towards state i
        // why u < s  (states where i >s would have been deleted already)
        for(int u = 0; u < s; u++){
            if(automaton[u][s] != ""){
                // state u has an outward edge towards state s that we want to remove
                coming_from.push_back(u);
            }
        }

        for(int v = 0; v < s; v++){
            if(automaton[s][v] != ""){
                // if state s has an outward edge towards state v
                for(auto u: coming_from){
                    // for every incoming edge in state s, combine the expression to get from state u to state v
                    string expression = automaton[u][s];
                    if(automaton[s][s] != "") expression += "(" + automaton[s][s] + ")*";
                    expression += automaton[s][v];
                    if(automaton[u][v]!=""){
                        expression = "(" + expression + "|" + automaton[u][v] + ")";
                    }
                    automaton[u][v] = expression;
                }
            }
        }
    }
    return "(" + automaton[0][0] + ")*";
}

string regex_divisible_by(int n)
{
//     cout<<"the input n is "<< n<<endl;
    vector<vector<string>> automaton;
    createAutomaton(n, automaton);
    auto x = generateRegularExpression(automaton);
//     cout<<"after generate the automate is "<<endl;
//   printautomata(automaton);
    cout<<"the answer is"<<x<<endl;
  return x;
}
