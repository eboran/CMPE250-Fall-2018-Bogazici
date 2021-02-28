#include <sstream>
#include <fstream>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <unordered_map>


using namespace std;

typedef long long int LL;


LL mod = 1000000007;
string input;
LL sonuc[1000];

string alphabet = " abcdefghijklmnopqrstuvwxyz";
unordered_map <char,int> alp_map;

LL H[1000][1000];


LL HashWord(string &s){
    int l = s.length();
    LL r = alp_map[s[0]];
    for(int i = 1 ; i<l;i++){
        r *= 26;
        r += alp_map[s[i]];
        r = r%mod;
    }
    return r;
}

LL HashSearch(int i , int j){
    if(i==j) {
        H[i][i] = alp_map[input[i]];
        return H[i][i];
    } // base case
    if (H[i][j-1] == 0){
        H[i][j-1] = HashSearch(i,j-1)%mod;
    }
    if (H[j][j] == 0){
        H[j][j] = HashSearch(j,j)%mod;
    }
    H[i][j] = (H[i][j-1]*26 + H[j][j])%mod;
    return H[i][j];
}
bool edge[1000][1000];

void Search(LL &h,int &l){
    for(int i=0,j = l-1 ; i<input.length()-j;i++ ){
        if(H[i][j+i] == 0 ){
            H[i][i+j] = HashSearch(i,i+j)%mod;
        }
        if(H[i][i+j] == h){
            edge[i][i+j] = true;
        }
    }
}


LL run(){
    int len = input.length()-1;
    for(int i = len ; i>-1 ; i--){
        int j = len;
        for( ; j>=i; j--){
            if(edge[i][j]){
                if(j == len){
                    sonuc[i] = (sonuc[i] + 1)%mod;
                }else{
                    sonuc[i] = (sonuc[i] + sonuc[j+1])%mod;
                }
            }
        }
    }
    return sonuc[0];
}


int main(int argc, char* argv[]){


    ifstream infile(argv[1]);
    ofstream myfile;
    myfile.open(argv[2]);

    infile >>input;

    int N;
    infile >> N;
    for(int i= 0;i<1000;i++){
        sonuc[i] = 0;
    }
    for(int i = 0;i<N; i++){
        for(int j = 0;j<N;j++){
            H[i][j] = 0;
            edge[i][j] = false;
        }
    }


    for(int i=1;i<27;i++)   {
        char s = alphabet[i];
        alp_map[s] = i;
    }


    for(int i=0;i<N;i++){
        string new_;
        infile >> new_;
        LL k = HashWord(new_);
        int ll = new_.length();
        Search(k,ll);
    }

    LL res = run();

    cout << "res: "<< res%mod<<endl;

    myfile << res%mod;

    infile.close();
    myfile.close();


    return 0;
}


