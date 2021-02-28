

#include<iostream>
#include <list>
#include <stack>
#include <vector>
using namespace std;

class Graph{
public:
    int V;
    list<int> *adj;
    //list<int> *scc;

    //vector<int> sccId;
    Graph(int V);
    void edge(int V, int W);
    void helper(int v);
    //void crackPiggy();
    void scc();
    int *ix;
    int *low;
    bool *onStack;
    int *root;
    int *dgr;
    stack<int> *Stack;
};
