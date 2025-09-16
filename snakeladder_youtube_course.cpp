#include<iostream>
#include<cstdlib>
#include<unordered_map>
#include<queue>
using namespace std;
class Dice{

    int numberofDice;
    public:
    Dice(int n){
        this->numberofDice=n;
    }
    int throughtDice(){
        return (rand()%(6*numberofDice-numberofDice+1))+numberofDice;
    }
};

class Player{
    public:
    string name;
    Player(string name){
        this->name=name;
    }
};
class GameBoard{
    queue<pair<Player*,int>> playerchance;
    Dice dice;
    unordered_map<int,int> Jumper;
    int boardSize;
    public:
    GameBoard(int d,unordered_map<int,int> j,int b,queue<pair<Player*,int>> q):dice(d){
        this->boardSize=b;
        // this->dice=d;
        this->Jumper=j;
        this->playerchance=q;
    }
    void startGame(){
        while(playerchance.size()>1){
            pair<Player*,int> p=playerchance.front();
            playerchance.pop();
            Player* currentPlayer=p.first;
            int currentPosition=p.second;
            int newPosition=currentPosition+dice.throughtDice();
            cout<<"Dice value: "<<newPosition-currentPosition<<", ";
            if(newPosition==boardSize){
                cout<<currentPlayer->name<<" win the game"<<"\n";
                continue;
            }
            else{
                if(Jumper.find(newPosition)!=Jumper.end()){
                    if(newPosition>Jumper[newPosition]){
                        newPosition=Jumper[newPosition];
                        cout<<currentPlayer->name<<" is bitten by a snake"<<"\n";
                    }
                    else{
                        newPosition=Jumper[newPosition];
                        cout<<currentPlayer->name<<" is climbing a ladder"<<"\n";
                    }
                }
                if(newPosition>boardSize){
                    newPosition=currentPosition;
                }
                cout<<currentPlayer->name<<" current position is "<<newPosition<<"\n";
                playerchance.push({currentPlayer,newPosition});
            }
        }
    }
};
int main(){
    // Dice d=new Dice(2);
    Player* p1=new Player("Ravi");
    Player* p2=new Player("Rahul");
    Player* p3=new Player("Ram");
    queue<pair<Player*,int>> q;
    q.push({p1,0});
    q.push({p2,0});
    q.push({p3,0});
    int n=100;
    unordered_map<int,int> mp;
    mp[56]=45; 
    mp[5]=78;
    mp[58]=8;
    mp[9]=45;
    mp[76]=80;
    mp[90]=23;
    mp[24]=3;
    mp[83]=42;
    mp[97]=77;
    mp[39]=66;
    mp[55]=74;
    GameBoard* g=new GameBoard(2,mp,n,q);
    g->startGame();
    return 0;
}