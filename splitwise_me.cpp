#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class User{
    private:
    string name;
    int id;
    int moneyin;
    int moneyout;
    int amtpaid;
    public:
    User(string);
    int getId();
    string getName();
    int getUniqueId();
    void setAmtPaid(int);
    int getAmtPaid();
    void setMoneyIn(int);
    void setMoneyOut(int);
    int getMoneyIn();
    int getMoneyOut();
};
class Group{
    private:
    string name;
    vector<User> users;
    unordered_map<int,vector<User>> m;
    int totalAmt;
    public:
    Group(vector<User>,string);
    void equal(User,int);
    void exact(User);
    void percentage(User);
    void userStatus(User);
    int getTotalAmt();
    void setTotalAmt();
};
class Splitwise{
    private:
    vector<Group> groups;
    public:
    void getGroupStatus(Group);
    void setGroup(Group);
};
int User::getId(){
    return this->id;
}
int User::getUniqueId(){
    static int userid=0;
    userid++;
    return userid;
}
User::User(string name){
    this->name=name;
    this->id=getUniqueId();
    this->amtpaid=0;
    this->moneyin=0;
    this->moneyout=0;
}
string User::getName(){
    return this->name;
}
void User::setAmtPaid(int Tamt){
    amtpaid+=Tamt;
}
void User::setMoneyIn(int amt){
    this->moneyin=amt;
}
void User::setMoneyOut(int amt){
    this->moneyout=amt;
}
int User::getMoneyIn(){
    return this->moneyin;
}
int User::getMoneyOut(){
    return this->moneyout;
}
int User::getAmtPaid(){
    return this->amtpaid;
}
Group::Group(vector<User> users,string name){
    this->name=name;
    this->users=users;
    this->totalAmt=0;
    for(int i=0;i<users.size();i++){
        vector<User> temp=users;
        temp.erase(temp.begin()+i);
        m[users[i].getId()]=temp;
    }
}
void Group::equal(User u,int amt){
    totalAmt+=amt;
    int equalamt=amt/users.size();
    for(int i=0;i<users.size();i++){
        if(users[i].getId()!=u.getId()){
            for(int j=0;j<m[users[i].getId()].size();j++){
                if(m[users[i].getId()][j].getId()==u.getId()){
                    m[users[i].getId()][j].setAmtPaid(-equalamt);
                }
            }
        }
        else{
            for(int j=0;j<m[u.getId()].size();j++){
                m[u.getId()][j].setAmtPaid(equalamt);
            }
        }
    }
}
void Group::userStatus(User u){
    cout<<u.getName()<<" Status: "<<"\n";
    for(User user:m[u.getId()]){
        if(user.getAmtPaid()>0){
            cout<<user.getName()<<" owes you "<<user.getAmtPaid()<<"\n";
        }else{
            cout<<"You owes "<<user.getName()<<" "<<-user.getAmtPaid()<<"\n";
        }
    }
}
int Group::getTotalAmt(){
    return this->totalAmt;
}
int main(){
    User A("A");
    User B("B");
    User C("C");
    User D("D");
    vector<User> users={A,B,C,D};
    Group g(users,"Sikkem");
    g.equal(A,400);
    g.equal(B,600);
    g.equal(C,1000);
    g.equal(D,200);
    g.userStatus(A);
    g.userStatus(B);
    g.userStatus(C);
    g.userStatus(D);
    return 0;
}
