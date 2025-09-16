#include<iostream>
#include<vector> 
#include<unordered_map>
enum Split {EQUAL,EXACT,PERCENT};
class User{
    private:
    int id;
    string name;
    double totalExpenseSoFar;
    vector<pair<User,double>> userExpenseSheet;
    int getuniqueId();
    
    public:
    User(string);
    string getName();
    int getId();
    int getTotalExpenseSoFar();
    void setTotalExpenseSoFar();
    vector<pair<User,double>> getUserExpenseSheet();
    bool operator==(User user);
    void printTotalBalance();

};
class Expense{
    private:
    int id;
    string description;
    Split split;
    vector<double> exactDistibution;
    vector<double> percentDistribution;
    User creditor;
    vector<User> defaulters;
    double exactTotalAmount;
    int getUniqueId();
    public:
    Expense(User,Split,vector<User>);
    int getId();
    void setDescription();
    int getDescription();
    void setExactDistribution(vector<double>);
    vector<double> getExactDistribution();
    void setpercentDistribution(vector<double>);
    vector<double> getpercentDistribution();
    Split getSplit();
    User getCreditor();
    vector<User> getDefaulters();
    int getexactTotalAmount();

};
class Splitwise{
    private:
    list<User> users;
    unordered_map<int,User> UserIdMap;
    public:
    

};
using namespace std;
int main(){
    return 0;
}