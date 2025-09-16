#include<iostream>
#include<vector>
#include<string>
#include <numeric>
#include<unordered_map>
#include<map>
#include<algorithm>
#include <cmath>
#include<list>
#include<unordered_set>
using namespace std;
enum Split {EQUAL,EXACT,PERCENT};
class User{
    string id;
    string name;
    double totalExpense;
    unordered_map<User*,double> expenseSheet;
    // unordered_map<date,vector<string>> monthlySummary;
    string getUniqueId(){
        static int userId=0;
        userId++;
        return "user"+to_string(userId);
    }
    public:
    User(string name){
        this->name=name;
        this->id=getUniqueId();
        this->totalExpense=0;
        this->expenseSheet.clear();
    }
    
    string getName(){
        return this->name;
    }
    string getUserId(){
        return this->id;
    }
    void addToUserExpenseSheet(User* user,double amount){
        /*
        if(amount>0 && user->getUserId()!=id){
            string summary="You will pay "+to_string(amount)+"to "+user->getName();
            expenseSheet[currentmonth].push_back(summary);
        }
        */
        this->totalExpense+=amount;
        if(expenseSheet.find(user)!=expenseSheet.end()){
            expenseSheet[user]+=amount;
            return ;
        }
        expenseSheet[user]=amount;
        return ;
    }
    void printTotalExpense(){
        if(totalExpense>0){
            cout<<"Overall, you need to pay this "<<totalExpense<<"\n";
        }
        else if(totalExpense<0){
            cout<<"Overall, you will get paid "<<-totalExpense<<"\n";
        }
        else cout<<"Overall nobody will pay you or you will pay anybody"<<"\n";
    }
    void userExpenseSheet(){
        // else 
        for(auto it:expenseSheet){
            if(it.second>0){
                cout<<"You need to pay "<<it.second<<" amount to "<<it.first->getName()<<"\n";
            }
            else if(it.second<0){
                cout<<"You will get paid "<<-it.second<<" amount from "<<it.first->getName()<<"\n";
            }
        }
    }
};
class Expense{
    string id;
    string decription;
    Split split;
    User* creditor;
    int totalAmount;
    vector<User*> friends;
    vector<double> exactAmount;
    vector<double> percent;
    string getUniqueId(){
        static int expenseId=0;
        expenseId++;
        return "expense"+to_string(expenseId);
    }
    public:
    Expense(string decrip,Split split,User* user,vector<User*> users,int totalAmt){
        this->creditor=user;
        this->decription=decrip;
        this->split=split;
        this->friends=users;
        this->id=getUniqueId();
        this->totalAmount=totalAmt;
    }
    vector<User*> getFriends(){
        return this->friends;
    }
    User* getCreditor(){
        return this->creditor;
    }
    Split getSplit(){
        return split;
    }
    void setExactDistribution(vector<double> exact){
        this->exactAmount=exact;
    }
    vector<double> getExactDistribution(){
        return this->exactAmount;
    }
    void setPercentDistribution(vector<double> percent){
        this->percent=percent;
    }
    vector<double> getPercentDistribution(){
        return this->percent;
    }
    int getTotalAmount(){
        return this->totalAmount;
    }
};
class Group{
    unordered_map<string,User*> users;
    string groupName;
    string id;
    vector<User*> userList;
    int totalGroupSpending;
    map<User*,int> totalyouPaid;
    map<User*,int> totalyourShare;
    string getUniqueId(){
        static int groupId=0;
        groupId++;
        return "group"+to_string(groupId);
    }
    public:
    Group(string name){
        this->totalGroupSpending=0;
        this->groupName=name;
        this->id=getUniqueId();
    }
    int getTotalGroupSpending(){
        return this->totalGroupSpending;
    }
    int getTotalYouPaid(User* user){
        return totalyouPaid[user];
    }
    int getTotalyourShare(User* user){
        return totalyourShare[user];
    }
    void registerUser(User* user){
        // cout<<user->getUserId()<<"\n";
        // string ID=user->getUserId();
        // cout<<ID<<"\n";
        // this->users.insert(ID);
        // usersList[user]="hkh";
        if(users.find(user->getUserId())==users.end()){
            userList.push_back(user);
            totalyouPaid[user]=0;
            totalyourShare[user]=0;
            users[user->getUserId()]=user;
            return ;
        }
        return ;
    }
    vector<User*> getUsers(){
        
        return this->userList;
    }
    bool verifyUser(User* cred,vector<User*> friends){
        bool exist=true;
        for(int i=0;i<friends.size();i++){
            if(friends[i]->getUserId()==cred->getUserId()){
                exist=false;
            }
        }
        if(exist){
            friends.push_back(cred);
        }
        for(int i=0;i<friends.size();i++){
            if(users.find(friends[i]->getUserId())==users.end()){
                return false;
            }
        }
        return true;
    }
    vector<double> divideEqually(int totalAmt,int n){
        vector<double> amt;
        for(int i=0;i<n;i++){
            double part=totalAmt/(n-i);
            amt.push_back(part);
            totalAmt-=part;
        }
        return amt;
    }

    bool addExpense(Expense* exp){
        if(verifyUser(exp->getCreditor(),exp->getFriends())==false){
            cout<<"One of the user is not registered"<<"\n";
            return false;
        }   
        int totalamt=exp->getTotalAmount();
        totalGroupSpending+=totalamt;
        vector<User*> friends=exp->getFriends();
        User* creditor=exp->getCreditor();
        totalyouPaid[creditor]+=totalamt;
        totalyourShare[creditor]+=totalamt;
        vector<double> amtPerhead;
        
        if(exp->getSplit()==Split::EQUAL){
            
            amtPerhead=divideEqually(totalamt,friends.size());
            for(int i=0;i<friends.size();i++){
                if(creditor->getUserId()!=friends[i]->getUserId()){
                    totalyourShare[creditor]-=amtPerhead[i];
                    totalyourShare[friends[i]]+=amtPerhead[i];
                }
                friends[i]->addToUserExpenseSheet(creditor,amtPerhead[i]);
                creditor->addToUserExpenseSheet(friends[i],-amtPerhead[i]);
            }
        }
        else if(exp->getSplit()==Split::EXACT){
            amtPerhead=exp->getExactDistribution();
            
            if(totalamt!=accumulate(amtPerhead.begin(), amtPerhead.end(), 0)){
                cout<<"Sum of exact value's is not equal to totalAmount"<<"\n";
                return false;
            }
            if(friends.size()!=amtPerhead.size()){
                cout<<"Something is wrong"<<"\n";
                return false;
            }
            for(int i=0;i<friends.size();i++){
                if(creditor->getUserId()!=friends[i]->getUserId()){
                    totalyourShare[creditor]-=amtPerhead[i];
                    totalyourShare[friends[i]]+=amtPerhead[i];
                }
                friends[i]->addToUserExpenseSheet(creditor,amtPerhead[i]);
                creditor->addToUserExpenseSheet(friends[i],-amtPerhead[i]);
            }
        }
        else if(exp->getSplit()==Split::PERCENT){
            amtPerhead=exp->getPercentDistribution();
            if(100!=accumulate(amtPerhead.begin(), amtPerhead.end(), 0)){
                cout<<"Sum of total percentage is not equal to 100"<<"\n";
                return false;
            }
            if(friends.size()!=amtPerhead.size()){
                cout<<"Something is wrong"<<"\n";
                return false;
            }
            for(int i=0;i<friends.size();i++){
                double val=(amtPerhead[i]*totalamt)/100;
                if(creditor->getUserId()!=friends[i]->getUserId()){
                    totalyourShare[creditor]-=val;
                    totalyourShare[friends[i]]+=val;
                }
                friends[i]->addToUserExpenseSheet(creditor,val);
                creditor->addToUserExpenseSheet(friends[i],-val);
            }
        }
        return true;
    }
    pair<double,double> findminmax(vector<double> amt){
        double minindex;
        double maxindex;
        double max_value=INT_MIN;
        double min_value=INT_MAX;
        for(int i=0;i<amt.size();i++){
            if(max_value<amt[i]){
                max_value=amt[i];
                maxindex=i;
            }
            if(min_value>amt[i]){
                min_value=amt[i];
                minindex=i;
            }
        }
        return {minindex,maxindex};
    }
    void simplifyExpenses(){
        vector<double> amounts;
        // for(auto it:)
        auto itTotal=totalyouPaid.begin();
        auto itPaid=totalyourShare.begin();
        vector<string> UserName;
        for(;itTotal!=totalyouPaid.end();itTotal++,itPaid++){
            cout<<itTotal->first->getName()<<" "<<itTotal->second-itPaid->second<<"\n";
            amounts.push_back(itTotal->second-itPaid->second);
            UserName.push_back(itTotal->first->getName());
        }
        pair<double, double> min_max = findminmax(amounts);
        while(amounts[min_max.first]!=0 || amounts[min_max.second]!=0){
            int min_index = min_max.first;
            int max_index = min_max.second;

            int min_amount = min(-amounts[min_index], amounts[max_index]);

            amounts[min_index] += min_amount;
            amounts[max_index] -= min_amount;

            cout << UserName[min_index] << " pays the amount " << min_amount << " to " << UserName[max_index] << "\n";

            min_max = findminmax(amounts);
        }
    }
    void printBalanceForAllUsers(){
        for(int i=0;i<userList.size();i++){
            cout<<userList[i]->getName()<<": ";
            userList[i]->printTotalExpense();
        }
    }
    string getName(){
        return this->groupName;
    }
};
class SplitWise{
    vector<Group*> groups;
    unordered_set<Group*> grouplist;
    User* user;
    public:
    SplitWise(User* user){
        this->user=user;
    }
    void addGroup(Group* grp){
        grouplist.insert(grp);
        groups.push_back(grp);
    }
    User* getUser(){
        return this->user;
    }
    void addExpenseInGroup(Group* grp,Expense* exp){
        if(grouplist.find(grp)==grouplist.end()){
            cout<<"Sorry but doesn't not have this group"<<"\n";
            return ;
        }
        grp->addExpense(exp);
    }
    void simplifyaGroupExpenses(Group* grp){
        grp->simplifyExpenses();
    }
    void groupSummary(){
        for(int i=0;i<groups.size();i++){
            cout<<groups[i]->getName()<<"\n";
            cout<<"TOTAL GROUP SPENDING"<<"\n";
            cout<<"INR "<<groups[i]->getTotalGroupSpending()<<"\n";
            cout<<"TOTAL YOU PAID"<<"\n";
            cout<<"INR "<<groups[i]->getTotalYouPaid(this->user)<<"\n";
            cout<<"TOTAL YOUR SHARE"<<"\n";
            cout<<"INR "<<groups[i]->getTotalyourShare(this->user)<<"\n";
            cout<<"\n";
        }
    }
};
int main(){
    string s1 = "User1";
    string s2 = "User2";
    string s3 = "User3";
    string s4 = "User4";
    User* u1=new User(s1);
    User* u2=new User(s2);
    User* u3=new User(s3);
    User* u4=new User(s4);

    vector<User*> users1;
    users1.push_back(u1);
    users1.push_back(u2);
    users1.push_back(u3);
    users1.push_back(u4);

    Group* g1=new Group("Sikkim Trip");
    SplitWise* sp=new SplitWise(u1);
    sp->addGroup(g1);
    
    g1->registerUser(u1);
    g1->registerUser(u2);
    g1->registerUser(u3);
    g1->registerUser(u4);

    Expense* expense=new Expense("Dinner", Split::EQUAL,u1, users1, 2000);
    // g1->addExpense(expense);
    sp->addExpenseInGroup(g1,expense);

    vector<User*> users2;
    users2.push_back(u2);
    users2.push_back(u3);

    Expense* expense2=new Expense("Hotels", Split::EXACT,u1, users2, 1400);
    sp->addExpenseInGroup(g1,expense2);

    vector<double> db = {500, 900};
    expense2->setExactDistribution(db);
    sp->addExpenseInGroup(g1,expense2);

    vector<double> db2 = { 40,20,20,20 };
    vector<User*> users3 = { u1, u2, u3, u4 };

    Expense* expense3=new Expense("Cab",Split::PERCENT,u4 , users3, 1200);
    expense3->setPercentDistribution(db2);
    sp->addExpenseInGroup(g1,expense3);


    // User* u5=new User("User5");

    // Group* g2=new Group("Meghalaya Trip");
    // sp->addGroup(g2);
    // Expense* expense4=new Expense("Dinner", Split::EQUAL,u3, {u1,u2,u3,u5}, 6000);
    // g2->registerUser(u1);
    // g2->registerUser(u2);
    // g2->registerUser(u3);
    // g2->registerUser(u5);
    
    // sp->addExpenseInGroup(g2,expense4);

    // Expense* expense5=new Expense("Lunch",Split::EXACT,u5,{u1,u2,u3,u5},10000);
    // vector<double> db3={3000,4000,2000,1000};
    // expense5->setExactDistribution(db3);

    // SplitWise* sp2=new SplitWise(u5);
    // sp2->addGroup(g2);
    // sp2->addExpenseInGroup(g2,expense5);

    cout<<"\n";
    cout<<sp->getUser()->getName()<<" Overall total Summary:-"<<"\n";
    sp->getUser()->printTotalExpense();
    
    cout<<"\n";
    cout<<sp->getUser()->getName()<<" Account Summary"<<"\n";
    sp->getUser()->userExpenseSheet();

    cout<<"\n";
    cout<<sp->getUser()->getName()<<" Group Summary"<<"\n";
    sp->groupSummary();

    cout<<"\n";
    cout<<"Simplify group expense"<<"\n";
    sp->simplifyaGroupExpenses(g1);


    // cout<<"\n";
    // cout<<sp2->getUser()->getName()<<" Overall total Summary:-"<<"\n";
    // sp2->getUser()->printTotalExpense();

    // cout<<"\n";
    // cout<<sp2->getUser()->getName()<<" Account Summary"<<"\n";
    // sp2->getUser()->userExpenseSheet();

    // cout<<"\n";
    // cout<<sp2->getUser()->getName()<<" Group Summary"<<"\n";
    // sp2->groupSummary();

    return 0;
}