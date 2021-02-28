#include "Graph.h"
int min(int a, int b) {
    return a < b ? a : b;
}
Graph::Graph(int V) {
    this->V=V;
    ix=new int[V]; // ix
    low=new int[V]; // low
    onStack = new bool[V]; //
    adj= new list<int>[V]; //adj

    root=new int[V]; // root

    dgr = new int[V]; // ind
    Stack = new stack<int>(); // Stack
}

void Graph::edge(int V, int W) {
    adj[V].push_back(W);
}

void Graph::helper(int v) {
    static int time=0;
    ix[v]=time;
    low[v]=time;
    time++;
    Stack->push(v);
    onStack[v]=true;
    list<int>::iterator i;
    for(i=adj[v].begin(); i!=adj[v].end(); i++){
        int w = *i;
        if(ix[w]==-1){
            helper(w);
            low[v]=min(low[v],low[w]);
        }
        else if(onStack[w]){
            low[v]=min(low[v],ix[w]);
        }
    }
    int w=0;
    if(low[v]==ix[v]) {
        while (Stack->top() != v) {
            w = (int) Stack->top();
            Stack->pop();
            root[w]=v;
            onStack[w] = false;
        }
        w = (int) Stack->top();
        Stack->pop();
        root[w]=v;
        onStack[w] = false;
    }
}
void Graph::scc() {
    for (int i = 0; i < V; i++) {
        ix[i] = -1;
        low[i] = -1;
        onStack[i]= false;
        dgr[i]=0;
    }
    for (int i = 0; i < V; i++) {
        if (ix[i] == -1) {
            helper(i);
        }
    }
//    find();
}
