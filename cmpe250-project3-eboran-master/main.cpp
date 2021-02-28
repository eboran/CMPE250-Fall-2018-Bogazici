#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include "Graph.h"
//#include <time.h>

using namespace std;


int main(int argc,char* argv[]) {
    ios_base::sync_with_stdio(false);

    ifstream infile(argv[1]);
    ofstream outfile;
    outfile.open(argv[2]);


    int data;
    infile>> data;

    Graph g(data);


    for (int i = 0; i < data; i++) {
      
        int key;
        infile>>key;
        int w;
        for (int j = 1; j <= key; j++) {
            infile>>w;
            if (i != w - 1) {
                g.edge(i, w - 1);
            }
        }
    }

    g.scc();

    int count = 0;
    for (int u = 0; u < g.V; ++u) {
        list<int>::iterator it;
        for(it=g.adj[u].begin(); it!=g.adj[u].end(); it++) {
            int v = *it;
            int v_ = g.root[v];
            g.dgr[v_]++;
        }
    }
    for (int i = 0; i < g.V; ++i) {
        if (g.root[i] ==i && g.dgr[i]==0 ) {
            count++;
        }
    }

    outfile <<count <<" ";
    int c = 0; 
    for (int i = 0; i < g.V; ++i) {
        if (g.root[i] ==i && g.dgr[i]==0 ) {
            outfile<<i+1<<" ";
        }
    }

    outfile.close();


    return 0;
}
