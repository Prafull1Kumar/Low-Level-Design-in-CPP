#include<iostream>
#include<vector>
#include<queue>
using namespace std;
/*
Medium article: https://medium.com/@mithoonkumar/design-call-centre-ood-9f5d3baff82a

*/
class Employee{
    string designnation;
    bool free;
    string name;
    Employee(string,string);
    string getname();
    bool isbusy();
    void callEnd();
    void onCall();
};
class Call{
    Employee empoyee;
    Customer customer;
    Call(Customer ,Employee );
};
class CallManegar{
    // priority_queue<Employee> q;
    vector<vector<Employee>> list;
    vector<Call> calllog;
    queue<Customer> callqueue;
    // CallManeger(){};
    setEmployee(vector<Employee>,vector<Employee>,Employee);
    void callAssign(Customer);
    void callEnded(string Employee);
    void callAssigned(Employee,Customer);

};
class Customer{
    string name;
    Customer(string);
};
Customer::Customer(){
    this->name=name;
}
Employee::Employee(string designation,string name){
    this->designnation=designation;
    this->free=true;
    this->name=name;
}
string Employee::getname(){
    return this->name;
}
void Employee::onCall(){
    this->free=false;
}
bool Employee::isbusy(){
    return this->free;
}
void Employee::callEnd(){
    this->free=true;
}
Call::Call(Customer cus,Employee emp){
    this->customer=cus;
    this->empoyee=emp
}
void CallManegar::setEmployee(vector<Employee> fresher,vector<Employee> lead,Employee Maneger){
    list.push_back(fresher);
    list.push_back(lead);
    list.push_back({Maneger});
}
void CallManegar::callAssigned(Employee &emp,Customer cur){
    calllog.push_back(new Call(cur,emp));
    emp.onCall();
    return ;
}
void CallManegar::callAssign(Customer cur){

    for(int i=0;i<3;i++){
        for(int j=0;j<list[i].size();j++){
            if(list[i][j].isbusy()){
                CallManegar::callAssigned(list[i][j],cur);
                
                return ;
            }
        }
    }
    cout<<"Please Stay in Line"<<"\n";
    callqueue.push(cur);
    return ;
}
void CallManegar::callEnded(Employee emp){
    for(int i=0;i<3;i++){
        for(int j=0;j<list[i].size();j++){
            if(list[i][j].getname()==emp.getname()){
                list[i][j].callEnd();
                if(!callqueue.empty()){
                    CallManegar::callAssigned(list[i][j],callqueue.front());
                    callqueue.pop();
                }
                return ;
            }
        }
    }
}
int main(){
    Employee e1("fresher","E1");
    Employee e2("fresher","E2");
    Employee e3("fresher","E3");
    Employee e4("lead","E4");
    Employee e5("lead","E5");
    Employee e6("lead","E6");
    Employee e7("maneger","E7");
    vector<Employee> fresher={e1,e2,e3};
    vector<Employee> lead={e4,e5,e6};
    CallManegar Cm;
    Cm.setEmployee(fresher,lead,e7);
    Customer c1("C1");
    Cm.callAssign(c1);
    Customer c2("C2");
    Cm.callAssign(c1);
    Customer c3("C3");
    Cm.callAssign(c1);
    Customer c4("C4");
    Cm.callAssign(c1);
    Customer c5("C5");
    Cm.callAssign(c1);
    Customer c6("C6");
    Cm.callAssign(c1);
    Customer c7("C7");
    Cm.callAssign(c1);
    Customer c8("C8");
    Cm.callAssign(c1);
    return 0;
}