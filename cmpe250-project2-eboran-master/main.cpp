#include "event.h"
#include <vector>
//#include "time.h"
#include <fstream>



struct compare{
    bool operator()(event& e1, event& e2)
    {
        //      cout <<"in comparator"<<endl;
        if(e1.event_time != e2.event_time)
        {
            return e1.event_time > e2.event_time;
        }else{
            if(e1.type == e2.type){
                return e1.p.getArr()>e2.p.getArr();
            }else{
                return e1.type<e2.type;
            }
        }
    }
};


struct compare2{
    bool operator()(passenger& p1, passenger& p2){
        //      cout <<"in comparator"<<endl;
        if(p1.depTime != p2.depTime)
            return p1.depTime > p2.depTime;
        else
            return p1.getArr() > p2.getArr();
    }
};

priority_queue <passenger,vector<passenger>,compare2> PLQ;
priority_queue <passenger,vector<passenger>,compare2> PSQ;

queue <passenger> LQ;
queue <passenger> SQ;

int Lmax,Smax,Lcount,Scount;
int world_time;

template<typename A> void print_queue(A pq){
    while (!pq.empty())
    {
        // cout<<"Event time: ";
        // cout <<pq.top().event_time<<endl;
        pq.pop();
    }
}


void popFromLQ( pair <int,priority_queue <event,vector<event>,compare>>&start,queue<passenger> &LQ,int &Lcount,
               priority_queue <passenger,vector<passenger>,compare2> &PLQ,type &tt) {
    passenger pass;
    //cout<<"id: "<< pass.id<< " popFromLQ world time: "<<world_time<<endl;

    if(tt.c1 == 0){
        pass = LQ.front();
        LQ.pop();
        // cout<<"id: "<< pass.id<<" addToLug world time: "<<world_time<<endl<<" size LQ: "<< LQ.size()<<endl;
    }else{
        pass = PLQ.top();
        PLQ.pop();
        //cout<<"id: "<< pass.id<<" addToLug world time: "<<world_time<<endl<<" size LQ: "<< PLQ.size()<<endl;
    }
    int o = world_time+pass.LT;
    event n(o,3,pass);
    start.second.push(n);
    Lcount++;
}

void popFromSQ( pair <int,priority_queue <event,vector<event>,compare>>&start,queue<passenger> &SQ,int &Scount,
               priority_queue <passenger,vector<passenger>,compare2> &PSQ,type &tt) {
    passenger pass;
    if(tt.c1 == 0){
        pass = SQ.front();
        SQ.pop();
        // cout<<" size SQ: "<< SQ.size()<<endl;
    }else{
        pass = PSQ.top();
        PSQ.pop();
        // cout<<" size PSQ: "<< PSQ.size()<<endl;
    }
    int o = world_time+pass.ST;
    event n(o,6,pass);
    start.second.push(n);
    Scount++;
    //cout<<"id: "<< pass.id<<" popFromSQ vip: "<<pass.vip<< " Smax: " << Smax<< " Scount "<< Scount<<endl;

}

void popFromSeq(passenger p,pair <int,priority_queue <event,vector<event>,compare>>&start,queue<passenger> &LQ,queue<passenger> &SQ,int &Scount,
        priority_queue <passenger,vector<passenger>,compare2> &PSQ,type &tt,int &c) {
    //cout <<"id: "<<p.id<<" popFromSeq "<< "vip: "<< p.vip<< " Smax: "<< Smax<< " Scount: "<< Scount<<endl;
    //if(!(p.getVip() && tt.c2 == 1)){
    Scount--;
    //cout << "Scount: "<<Scount<<endl;
    if(p.vip=='V' && tt.c2==1)
        Scount++;
    //}
    start.first += world_time - p.arrTime;
    if(world_time>p.depTime)
        c++;
    if (tt.c1 == 0) {
        //cout <<"Smax: "<<Smax<<" "<<"Scount: "<<Scount<<" SQ: "<< SQ.size()<<endl;
        if(!(tt.c2 == 1 && p.vip == 'V')) {
            if (!SQ.empty()) {
                popFromSQ(start, SQ, Scount, PSQ, tt);
            }
        }
    } else {
        //cout <<"Smax: "<<Smax<<" "<<"Scount: "<<Scount<<" SQ: "<< PSQ.size()<<endl;
        if(!(tt.c2 == 1 && p.vip == 'V')) {
            if (!PSQ.empty()) {
                //cout<<"sdad"<<endl;
                popFromSQ(start, SQ, Scount, PSQ, tt);
            }
        }
    }

    //if(p.vip != 'V'|| tt.c2 != 1){
    //}
    //cout<<"end of popfromseq"<<endl;
}
/*
void addToSeq(passenger p,pair <int,priority_queue <event,vector<event>,compare>>&start,queue<passenger> &LQ,queue<passenger> &SQ,int &Scount,
        priority_queue <passenger,vector<passenger>,compare2> &PSQ,type &tt){
    //cout<<"id: "<< p.id<<" addToSeq world time: "<<world_time<< endl;
    //cout <<"Smax: "<<Smax<<" "<<"Scount"<<Scount<<" SQ: "<< SQ.size()<<endl;
    if(Smax == Scount) {
        if (tt.c1 == 0) {
            SQ.push(p);
  //          cout<<"add to SQ, size: "<<SQ.size()<<endl;
        } else {
            PSQ.push(p);
            //cout<<"add to PSQ, size: "<<PSQ.size()<<endl;
        }
        //cout<<"add to SQ, size: "<<SQ.size()<<endl;
    }else{
        Scount++;
        //cout << Scount<< " ";
        int o = world_time + p.ST;
        event n(o,6,p);//pop from seq
        start.second.push(n);
    }
}
*/

void addToSeq(passenger p,pair <int,priority_queue <event,vector<event>,compare>>&start,queue<passenger> &LQ,queue<passenger> &SQ,int &Scount,
        priority_queue <passenger,vector<passenger>,compare2> &PSQ,type &tt){
    //cout<<"vip: "<< p.vip<<" id: "<< p.id<<" addToSeq world time: "<<world_time<< endl;
    //cout <<"Smax: "<<Smax<<" "<<"Scount: "<<Scount<<" SQ: "<< SQ.size()<<endl;
    if(tt.c2 == 1 && p.vip == 'V'){
        event n(world_time,6,p);//pop from seq
        start.second.push(n);
        //Scount++;
    }else{
        if(Smax == Scount) {
            if (tt.c1 == 0) {
                SQ.push(p);
      //          cout<<"add to SQ, size: "<<SQ.size()<<endl;
            } else {
                PSQ.push(p);
                //cout<<"add to PSQ, size: "<<PSQ.size()<<endl;
            }
            //cout<<"add to SQ, size: "<<SQ.size()<<endl;
        }else{
            Scount++;
            int o = world_time + p.ST;
            event n(o,6,p);//pop from seq
            start.second.push(n);
        }
    }
    //cout <<"id: "<<p.id<<" addtoSeq "<<"vip: "<<p.vip<<" Smax: "<<Smax<<" "<<"Scount: "<<Scount<<" SQ: "<< SQ.size()<<endl;
}



void popFromLug(passenger p,pair <int,priority_queue <event,vector<event>,compare>>&start
,queue<passenger> &LQ,queue<passenger> &SQ,int &Lcount,
        priority_queue <passenger,vector<passenger>,compare2> &PLQ,type &tt) {
    //cout<<"id: "<< p.id<< " popFromLug  world time: "<<world_time<<endl;
    Lcount--;
    //cout<<"Lcount in popFromLug: "<<Lcount<<endl;

    addToSeq(p,start,LQ,SQ,Scount,PSQ,tt);
    if(tt.c1 == 0 && !LQ.empty()){
        popFromLQ(start,LQ,Lcount,PLQ,tt);
    }else if(tt.c1 == 1 && !PLQ.empty()) {
        popFromLQ(start,LQ,Lcount,PLQ,tt);
    }
}


/*
void popFromLug(passenger p,pair <int,priority_queue <event,vector<event>,compare>>&start
,queue<passenger> &LQ,queue<passenger> &SQ,int &Lcount,
        priority_queue <passenger,vector<passenger>,compare2> &PLQ,type &tt) {
    //cout<<"id: "<< p.id<< " popFromLug  world time: "<<world_time<<endl;
    Lcount--;
    //cout<<"Lcount in popFromLug: "<<Lcount<<endl;
    if(tt.c2==1 && p.vip=='V'){
        event n(world_time,6,p);//pop from seq
        start.second.push(n);
    }else{
        addToSeq(p,start,LQ,SQ,Scount,PSQ,tt);
    }

    if(tt.c1 == 0 && !LQ.empty()){
        popFromLQ(start,LQ,Lcount,PLQ,tt);
    }else if(tt.c1 == 1 && !PLQ.empty()) {
        popFromLQ(start,LQ,Lcount,PLQ,tt);
    }
}
*/
void addToLug(passenger p, pair <int,priority_queue <event,vector<event>,compare>>&start
        ,queue<passenger>&LQ,queue<passenger> &SQ,int &Lcount,
              priority_queue <passenger,vector<passenger>,compare2> &PLQ,type tt) {
    //cout<<"id: "<< p.id<<" addToLug world time: "<<world_time<<endl;
    if(tt.c3==1 && p.lug=='N'){
        addToSeq(p,start,LQ,SQ,Scount,PSQ,tt);
    }else{
        if(Lmax == Lcount) {
            if (tt.c1 == 0) {
                LQ.push(p);
                //cout << "add to LQ, size: " << LQ.size() << endl;
            } else {
                PLQ.push(p);
                //cout << "add to PLQ, size: " << PLQ.size() << endl;
            }
            //cout<<"add to SQ, size: "<<SQ.size()<<endl;
            //   LQ.push(p);
        }else{
            Lcount++;
            //      cout <<"Lcount: "<<Lcount<<endl;
            int x = world_time + p.LT;
            event n(x,3,p);
            start.second.push(n);
            //print_queue(allEvents);
        }
    }

}

void make(event e,pair <int,priority_queue <event,vector<event>,compare>>&start,int &world_time,int &Lcount, type &tt,int &c,int &Scount) {
    world_time = e.event_time;
//    cout<<"world time in make: "<< world_time <<endl;
    if(e.type == 1){
        addToLug(e.p,start,LQ,SQ,Lcount,PLQ,tt);
    }else if(e.type == 3){
        popFromLug(e.p,start,LQ,SQ,Lcount,PLQ, tt);
    }else if(e.type == 6){
        popFromSeq(e.p,start,LQ,SQ,Scount,PSQ,tt,c);
    }
}

int main(int argc, char* argv[]) {

    string line;
    ifstream infile(argv[1]);

    priority_queue <event,vector<event>,compare> allEvents;

    //clock_t tStart = clock();
    int N,L,S;
    infile>>N;
    infile>>L;
    infile>>S;
    int x,y,t,z;
    char a,b;
    Lmax = L;
    Smax = S;
    Lcount= 0 ;
    Scount= 0 ;

    for(int i=1;i<=N;i++){
        infile>>x;
        infile>>y;
        infile>>z;
        infile>>t;
        infile>>a;
        infile>>b;
        passenger p(x,y,z,t,a,b,i);
        event e(x,1,p);
        allEvents.push(e);
    };
    infile.close();
    priority_queue <event,vector<event>,compare> s = allEvents;

    int sum= 0;
    pair <int,priority_queue <event,vector<event>,compare>>start;
    int c = 0;
    start.first = sum;
    start.second = allEvents;
    vector<float> avgs;
    ofstream myfile;
    myfile.open (argv[2]);
    

    for(int i = 0;i<2;i++){
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++){
                type tt(k,j,i);
                while(!start.second.empty()){
                    event n = start.second.top();
                    start.second.pop();
                    make(n,start,world_time,Lcount,tt,c,Scount);
                }
                myfile<<float(start.first) / N<<" "<<c<<endl;
                start.first = 0;
                start.second = allEvents;
                c= 0;
                Lcount= 0 ;
                Scount= 0 ;
            }
        }
    }
    myfile.close();

    //printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);



    return 0;
}


