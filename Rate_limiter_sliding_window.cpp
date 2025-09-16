#include<iostream>
#include<queue>
#include<unordered_map>
#include <stdio.h>
#include <time.h>
using namespace std;
static int curr_time=0;
class SlidingWindowRateLimiter{
    
    queue<time_t> request;
    int window;
    public:
    SlidingWindowRateLimiter(int window){
        this->window=window;
        curr_time++;
    }
    bool getAccess(){
        time_t curr_time;
        curr_time = time (NULL);
        while(!request.empty() && curr_time-5>request.front()){
            request.pop();
        }
        if(request.size()<window){
            request.push(curr_time);
            cout<<"Access is Provided"<<"\n";
            return true;
        }
        cout<<"You are above your daily limit"<<"\n";
        return false;
    }
};
class User{

    string name;
    int id;
    public:
    User(string name){
        this->name;
        this->id=getUniqueId();
    }
    int getUniqueId(){
        static int userId=0;
        return userId;
    }
    int getId(){
        return this->id;
    }
};
class Bucket{
    unordered_map<User*,SlidingWindowRateLimiter*> bucket;
    public:
    Bucket(){};
    void addUserUser(User* u){
        bucket[u]=new SlidingWindowRateLimiter(3);
    }
    void passwordChange(User* u){
        if(bucket[u]->getAccess()){
            cout<<"Password Chnage"<<"\n";
            return ;
        }
        cout<<"Limit Exceed"<<"\n";
        return ;
    }
};
int main(){
    Bucket* b=new Bucket();
    User* u=new User("Ram");

    b->addUserUser(u);

    b->passwordChange(u);
    long long n=1000000000;
    while(n>0){
        n--;
    }
    b->passwordChange(u);
    n=1000000;
    while(n>0){
        n--;
    }
    b->passwordChange(u);
    n=10000000000;
    while(n>0){
        n--;
    }
    b->passwordChange(u);

    return 0;
}