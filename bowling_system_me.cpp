#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

class Player
{
    private:
    string name;
    int score;
    vector<int> rolls;
    public:
    Player(string);
    void set_score(int);
    int get_score();
    string get_name();
    // void bowl(int);
    // bool istrike(int);
    // bool spare(int);
    
};
class GameSession
{
    private:
    int alley;
    vector<Player> players;
    int id;
    int chance=0;
    public:
    GameSession();
    GameSession(vector<Player>,int);
    // void set_chances(int);    
    void declarewinner();
    int getuniqueId();
    int get_id();
    void rollchange(Player ,int );
};
class Game{
    private:
    unordered_map<int,GameSession> m;
    vector<int> allies;

    public:
    Game(vector<int>);
    GameSession createSession(vector<Player>);
};


Player::Player(string name)
{
    this->name=name;
}
int Player::get_score(){
    return this->score;
}
void Player::set_score(int s){
    score+=s;
    rolls.push_back(s);
}
string Player::get_name(){
    return this->name;
}

Game::Game(vector<int> a){
    this->allies=a;
}
GameSession Game::createSession(vector<Player> p){
    for(int i=0;i<allies.size();i++){
        if(m.find(allies[i])==m.end()){
            GameSession g(p,allies[i]);
            m[allies[i]]=g;
            cout<<"Alley "<<allies[i]<<" is assign to game session "<<g.get_id()<<"\n";
            return g;
        }
    }
    cout<<"No alley is empty"<<"\n";
    GameSession gs;
    return gs;
}
GameSession::GameSession(vector<Player> ps,int a){
    this->players=ps;
    this->alley=a;
    this->id=getuniqueId();
    this->chance=ps.size();
}
GameSession::GameSession(){
    this->id=getuniqueId();
}
// void GameSession::set_chances(int cnt){
//     this->chance=cnt;
// }
int GameSession::get_id(){
    return this->id;
}
void GameSession::rollchange(Player p,int v){
        chance--;
        for(int i=0;i<players.size();i++){
            if(players[i].get_name()==p.get_name()){
                players[i].set_score(v);
            }
        }
        // cout<<players[chance%players.size()]<<" chance is now"<<"\n";
        if(chance==0){
            declarewinner();
        }
    }
int GameSession::getuniqueId(){
    static int i=0;
    i++;
    return i;
}
void GameSession::declarewinner(){
    string ans="";
    int maxi=0;
    for(int i=0;i<players.size();i++){
        if(maxi<players[i].get_score()){
            maxi=players[i].get_score();
            ans=players[i].get_name();
        }
    }
    cout<<ans<<" is the winner of GameSession "<<this->id<<"\n";
}
int main(){
    Player p1("Rahul");
    Player p2("Ravi");
    Player p3("Ramesh");
    vector<Player> p={p1,p2,p3};
    vector<int> a={1,2,3};
    Game g(a);
    GameSession gs=g.createSession(p);
    gs.rollchange(p1,2);
    gs.rollchange(p2,3);
    gs.rollchange(p3,5);
    return 0;
}