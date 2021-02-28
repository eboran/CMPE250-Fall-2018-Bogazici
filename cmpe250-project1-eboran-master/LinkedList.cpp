#include "LinkedList.h"


LinkedList::LinkedList(){
//    cout<<"LinkedList constructor"<<endl;
    length = 0;
}

void LinkedList::pushTail(string _name, float _amount) {
    Node *tmp = new Node(_name,_amount);
    if(length != 0){
        tail->next = tmp;
    }else{
        head = tmp;
    }
    tail = tmp;
    length++;
}

LinkedList::LinkedList(LinkedList&& list){
    //cout<<"LinkedList move constructor"<<endl;
    //delete head;
    length = move(list.length);
    //head = new Node("s",1);
    head = new Node(move(*(list.head)));
    Node *t = head;
    //cout<<t->next->next->name<<endl;
    while(t->next){t = t->next;}
    tail=t;
    list.head = NULL;
    list.tail = NULL;
    list.length = 0;
}

LinkedList& LinkedList::operator=( LinkedList &&list) {
    //cout<<"move assignment for linkedlist"<<endl;
    //delete head;
    length = move(list.length);
    *head = move(*(list.head));
    Node *t = head;
    //cout<<t->next->next->name<<endl;
    while(t->next){t = t->next;}
    tail=t;
    list.head = NULL;
    list.tail = NULL;
    list.length = 0;
    return *this;
}

void LinkedList::updateNode(string _name, float _amount) {
    Node *tmp= head;
    bool done = false;
    while(tmp){
        if(tmp->name == _name){
            //cout <<"in if"<<endl;
            tmp->amount=_amount;
            done = true;
            break;
        }
        tmp=tmp->next;
    }
    if(!done){
        pushTail(_name,_amount);
    }
}

LinkedList::~LinkedList() {
    //cout<<"linkedList destructor"<<endl;
    delete head;
}

LinkedList& LinkedList::operator=(const LinkedList &list) {
    //cout<<"copy assignment executed for linkedlist"<<endl;
    length = list.length;
    *head = *(list.head);
    Node *tmp = head;
    while(tmp->next)
        tmp=tmp->next;
    tail = tmp;
    return *this;
}

LinkedList::LinkedList(const LinkedList &list) {
    //cout <<"linkedList copy constructor"<<endl;
    length = list.length;
    if(list.head){
        head = new Node(*(list.head));
    }
    Node *tmp=head;
    while(tmp->next)
        tmp = tmp->next;
    tail = tmp;
}


