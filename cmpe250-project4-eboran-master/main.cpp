#include <stack>
#include <list>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iterator>
#include <queue>

using namespace std;
typedef pair<int,int> ii;
struct edge{
    edge(int x,int y,int z){
        loc = make_pair(x,y);
        weight = z;
    }
    ii loc;
    int weight;
    bool operator<(const edge& x) const
    {
        return weight > x.weight;
    }

};

priority_queue<edge> Q;

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(cont));
}
int dt[1000000];
int allNum;
int N,M;
list <ii> *adjList;
bool inMst[1000000] = {false};

int sondeneme[1000000]={0};

int prim(int start,int end){
    int ff = start;
    inMst[start] = true;
    if(start%M!=0){
        edge esol(start,start-1,abs(dt[start]-dt[start-1]));
        Q.push(esol);
    }
    if((start+1)%M!=0){
        edge esag(start,start+1,abs(dt[start]-dt[start+1]));
        Q.push(esag);
    }
    if((start-M)>=0){
        edge eyuk(start,start-M,abs(dt[start]-dt[start-M]));
        Q.push(eyuk);
    }
    if((start+M+1)<=allNum){
        edge easag(start,start+M,abs(dt[start]-dt[start+M]));
        Q.push(easag);
    }
    sondeneme[ff]=0;
    int to,from;
    while(!Q.empty()){
        edge e = Q.top();
        Q.pop();
        to = e.loc.second;
        from = e.loc.first;
        //int dd = abs(dt[from]-dt[tt]);
        //if()
        //cout << e.loc.first << " "<<e.loc.second<<endl;
        if(!inMst[to]){
            //int abss = abs(dt[to]-dt[from]);
            if(e.weight >= sondeneme[from]){
                sondeneme[to] = e.weight;
                //cout << sondeneme[to]<<endl;
            }else{
                sondeneme[to] = sondeneme[from];
            }
            if(to==end)
                break;
            inMst[to] = true;
            //res+=e.weight;
            //adjList[from].push_back(make_pair(to,e.weight));
            //adjList[to].push_back(make_pair(from,e.weight));

            if(to%M!=0 && !inMst[to-1]){
                edge esol(to,to-1,abs(dt[to]-dt[to-1]));
                Q.push(esol);
            }
            if((to+1)%M!=0&& !inMst[to+1]){
                edge esag(to,to+1,abs(dt[to]-dt[to+1]));
                Q.push(esag);
            }
            if((to-M)>=0&& !inMst[to-M]){
                edge eyuk(to,to-M,abs(dt[to]-dt[to-M]));
                Q.push(eyuk);
            }
            if((to+M+1)<=allNum&& !inMst[to+M]){
                edge easag(to,to+M,abs(dt[to]-dt[to+M]));
                Q.push(easag);
            }
        }
    }
    cout <<" result : " <<sondeneme[end]<<endl;
    return sondeneme[end];
}

//stack <int> Stack;
//bool src[1000000]={false};
//queue <int>q;
//int uzak[1000000];
/*
int BFS(int s,int aranan)
{
    list<int> queue;
    src[s] = true;
    uzak[s]=0;
    queue.push_back(s);

    list<ii>::iterator i;
    //int xxx=-1;
    while(!queue.empty())
    {
        s = queue.front();
        //cout << s << " ";
        queue.pop_front();

        if(s==aranan)
            break;
        for (i = adjList[s].begin(); i != adjList[s].end(); ++i) {
            //cout <<"in for loop "<<endl;
            if (!src[(*i).first]) {
                int dist= abs(dt[s]-dt[(*i).first]);
                //cout << "dist: "<<dist<<endl;
                if(dist>uzak[s]){
                    //cout << " adasda";
                    uzak[(*i).first] = dist;
                }else{
                    uzak[(*i).first] = uzak[s];
                }
                src[(*i).first] = true;
                queue.push_back((*i).first);
            }
        }
    }
    cout << "ans "<<uzak[aranan]<<endl;
    return uzak[aranan];
}
*/
int main(int argc, char* argv[]) {
    clock_t tStart = clock();

    if (argc != 3) {
        cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    ofstream myfile;
    myfile.open(argv[2]);
    string line;
    getline(infile, line);
    vector<string> words;
    split1(line, words);
    N = stoi(words[0]);
    M = stoi(words[1]);
    allNum = N*M;
    adjList = new list<ii>[N*M];
    int c= 0; //  Input Time taken: 12.68s
    for (int i = 0; i < N; i++) {
        getline(infile, line);
        vector<string> words;
        split1(line, words);
        for (int j = 0; j < M; j++) {
            dt[c] = stoi(words[j]);
            c++;
        }
    }
    getline(infile, line);
    int query = stoi(line);
    //cout << query;
    getline(infile, line);
    vector<string> words2;
    split1(line, words2);

    int a, b, t, z, k, l;
    a = stoi(words2[1]);
    b = stoi(words2[0]);
    k = ((b-1)*M) + (a-1);
    t = stoi(words2[3]);
    z = stoi(words2[2]);
    l = ((z-1)*M) + (t-1);

    myfile << prim(k,l);
//    myfile << BFS(k,l);
    //int xxxxx = 0;
/*
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cout << sondeneme[xxxxx]<< " ";
            xxxxx++;
        }
        cout <<endl;
        //if((M-1)%i)
          //  cout <<endl;
    }*/
    infile.close();
    myfile.close();
    //printf("\n Input Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}

