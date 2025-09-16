#include<iostream>
#include<vector>
#include <cstring>
using namespace std;

class Player{
    private:
    string name;
    int score;
    public:
    Player(string);
    string getName();
    void setScore(int);
    int getScore();
};

class SnakeLadder{
    public:
    SnakeLadder();
    void setPlayer(vector<Player>);
    void setSnakeandLadder(vector<pair<int,int>>, vector<pair<int,int>>);
    bool playerChance(Player,int);
    void playerScore();
    static const int win=36;
    private:
    vector<Player> players;
    int snakes[win];
    int ladders[win];
};

Player::Player(string name){
    this->name=name;
    this->score=0;
}
int Player::getScore(){
    return this->score;
}
void Player::setScore(int score){
    this->score=score;
}
string Player::getName(){
    return this->name;
}
SnakeLadder::SnakeLadder(){
    // this->win=36;
    // snakes(win,0);
    // ladders(win,0);
    memset(snakes, 0, sizeof snakes);
    memset(ladders, 0, sizeof ladders);
    for(int i=0;i<win;i++){
        snakes[i]=i;
    }
    for(int i=0;i<win;i++){
        ladders[i]=i;
    }
}
void SnakeLadder::setPlayer(vector<Player> p){
    this->players=p;
}
void SnakeLadder::setSnakeandLadder(vector<pair<int,int>> s,vector<pair<int,int>> l){
    // this->snakes=s;
    // this->ladder=l;
    for(int i=0;i<s.size();i++){
        snakes[s[i].first]=s[i].second;
    }
    for(int i=0;i<l.size();i++){
        snakes[l[i].first]=l[i].second;
    }
}
bool SnakeLadder::playerChance(Player player,int score){
    for(int i=0;i<players.size();i++){
        if(players[i].getName()==player.getName()){
            int nextscore=players[i].getScore()+score;
            if(nextscore==win){
                players[i].setScore(nextscore);
                return true;
            }
            else if(nextscore>win){
                return false;
            }
            nextscore=snakes[nextscore];
            nextscore=ladders[nextscore];
            players[i].setScore(nextscore);
            break;
        }
    }
    // cout<<nextscore<<"\n";
    // player.setScore(nextscore);
    
    return false;
}
void SnakeLadder::playerScore(){
    for(int i=0;i<players.size();i++){
        cout<<"(Player: "<<players[i].getName()<<" ,Score: "<<players[i].getScore()<<"), ";
    }
    cout<<"\n";
}
int main(){

    Player p1("Ankit");
    Player p2("Rohit");
    Player p3("Pant");
    Player p4("Virat");
    vector<Player> p={p1,p2,p3,p4};
    vector<pair<int,int>> snakes;
    snakes.push_back({16,5});
    snakes.push_back({26,7});
    snakes.push_back({33,19});
    snakes.push_back({35,15});
    vector<pair<int,int>> ladders;
    ladders.push_back({3,14});
    ladders.push_back({11,21});
    ladders.push_back({27,32});
    SnakeLadder game;
    game.setSnakeandLadder(snakes,ladders);
    game.setPlayer(p);
    bool flag=true;
    int j=0;
    while(j<=20 && flag){
        for(int i=0;i<p.size();i++){
            int score = abs(rand()%6)+1;
            if(game.playerChance(p[i],score)){
                cout<<p[i].getName()<<" is a winner"<<"\n";
                flag=false;
                break;
            }
        }
        game.playerScore();
        j++;
    }

    return 0;
}