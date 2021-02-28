#include "SurveyClass.h"

SurveyClass::SurveyClass() {
    members = new LinkedList;
}

SurveyClass::SurveyClass(const SurveyClass &other) {
    this->members = new LinkedList(*(other.members));
}

void SurveyClass::handleNewRecord(string _name, float _amount) {
    members->updateNode(_name,_amount);
}
SurveyClass::~SurveyClass() {
    //cout<<"destructor surveyclass"<<endl;
    delete members;
}

SurveyClass::SurveyClass(SurveyClass&& other) {
    //cout<<"move constructor for surveyclass"<<endl;
    this->members = move(other.members);
    other.members = NULL;
}

SurveyClass& SurveyClass::operator=(SurveyClass &&list) {
    //cout<<"move assign for surveyclass"<<endl;
    delete this->members;
    this->members = move(list.members);
    list.members = NULL;
    return *this;
}

float SurveyClass::calculateMaximumExpense(){
    Node *tmp = members->head;
    float max = tmp->amount;
    tmp = tmp->next;
    for(int i=1;i<members->length;i++){
        if(max<tmp->amount){
            max = tmp->amount;
        }
        tmp = tmp->next;
    }
    float res = int(max*100);
    res /= 100;
    
    //cout <<"max: "<<max<<endl;
    return res;
}
float SurveyClass::calculateMinimumExpense(){
    Node *tmp = members->head;
    float min = tmp->amount;
    tmp = tmp->next;
    for(int i=1;i<members->length;i++){
        if(min>tmp->amount){
            min = tmp->amount;
        }
        tmp = tmp->next;
    }
    //cout <<"min: "<<min<<endl;
    float res = int(min*100);
    res /= 100;
    return res;
}
float SurveyClass::calculateAverageExpense(){
    Node *tmp = members->head;
    float avg = tmp->amount;
    tmp = tmp->next;
    for(int i=1;i<members->length;i++){
        avg += tmp->amount;
        tmp = tmp->next;
    }
    //cout <<"avg: "<<avg<<endl;
    float res = int((avg/members->length)*100);
    res /= 100;
    return res;
}



SurveyClass& SurveyClass::operator=(const SurveyClass &list) {
    delete this->members;
    this->members = new LinkedList(*(list.members));
    return *this;
}
