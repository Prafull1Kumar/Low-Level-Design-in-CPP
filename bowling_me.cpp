#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

class Player{

    public:
    static const int max_roll=23;
    Player(string);
    string getName();
    int getScore();
    void roll(int);
    bool isCanPlay();
    // int x=max_roll;

    private:
    string name;
    int score;
    int rolls[23];
    int firstRoll;
    int frameIndex;
    bool canPlay;
    int currentRoll;
    bool isStrike();
    bool isSpare();
    void update();
};
class GameSession{
    private:
    vector<Player> players;
    int alley;
    int id;
    int getUniqueId();

    public:
    GameSession();
    void setPlayer(vector<Player>);
    void setAlley(int);
    int getAlley();
    int getId();
    bool declareWinner();
    void makeRoll(Player,int);
};

class Game{
    private:
    unordered_map<int,GameSession> gamesessions; 
    public:
    static vector<int> allies;
    int createSession(vector<Player> );
    void declarewinner(int);
    void roll(int,Player,int);
    static void makeActive(int);
};
vector<int> Game::allies={1,2,3,4};
int Game::createSession(vector<Player> players){
    if(Game::allies.size()==0){
        cout<<"Their is no empty allies"<<"\n";
        return 0;
    }
    GameSession g;
    g.setPlayer(players);
    g.setAlley(Game::allies[allies.size()-1]);
    Game::allies.pop_back();
    gamesessions[g.getId()]=g;
    return g.getId();
}
void Game::makeActive(int alley){
    Game::allies.push_back(alley);
}
void Game::declarewinner(int alley){
    bool winner=gamesessions[alley].declareWinner();
    if(!winner){
        cout<<"No winner yet"<<"\n";
    }
}
void Game::roll(int alley,Player p,int pins){
    gamesessions[alley].makeRoll(p,pins);
}
GameSession::GameSession(){
    this->id=getUniqueId();
    this->alley=-1;
    this->players.clear();
}
void GameSession::setPlayer(vector<Player> p){
    this->players=p;
}
void GameSession::setAlley(int a){
    this->alley=a;
}
int GameSession::getId(){
    return this->id;
}
int GameSession::getAlley(){
    return this->alley;
}
void GameSession::makeRoll(Player p,int pins){
    for(int i=0;i<players.size();i++){
        if(players[i].getName()==p.getName()){
            players[i].roll(pins);
        }
    }
}
int GameSession::getUniqueId(){
    static int sessionid=0;
    sessionid++;
    return sessionid;
}
bool GameSession::declareWinner(){
    int maxi=0;
    string name="";
    for(int i=0;i<players.size();i++){
        if(players[i].isCanPlay()){
            cout<<"There is still a chance left"<<"\n";
            return false;
        }
        if(maxi<players[i].getScore()){
            maxi=players[i].getScore();
            name=players[i].getName();
        }
    }
    cout<<"Player "<<name<<" is a winner with a score of "<<maxi<<" point"<<"\n";
    Game::makeActive(this->alley);
    return true;
}
Player::Player(string name){
    this->name=name;
    this->canPlay=true;
    this->currentRoll=0;
    this->firstRoll=true;
    this->frameIndex=0;
}

string Player::getName(){
    return this->name;
}
int Player::getScore(){
    return this->score;
}

bool Player::isCanPlay(){
    return this->canPlay;
}
bool Player::isStrike()
{
	return this->firstRoll == true && rolls[frameIndex] == 10;
}

bool Player::isSpare()
{
	return rolls[frameIndex] + rolls[frameIndex + 1] == 10;
}

void Player::roll(int pins){
    if(this->canPlay==false){
        return ;
    }
    rolls[currentRoll++]=pins;
    // return 
    update();
}
void Player::update(){
    if(isStrike()){
        score+=20;
        rolls[currentRoll++]=0;
        frameIndex+=2;
        if(frameIndex>=max_roll){
            this->canPlay=false;
        }
    }
    else{
        if(frameIndex>=max_roll-1){
            score+=rolls[currentRoll];
            this->canPlay=false;
        }
        else if(firstRoll){
            firstRoll=false;
        }
        else{
            if(isSpare()){
                score+=5;
            }
            score+=rolls[frameIndex]+rolls[frameIndex+1];
            frameIndex+=2;
            firstRoll=true;
            if(frameIndex>=max_roll-3){
                this->canPlay=false;

            }
        }
    }
}
int main(){
    Player p1("Thor");
    Player p2("Loki");
    Player p3("Hela");
    Player p4("Odin");

    vector<Player> vec;
    vec.push_back(p1);
    vec.push_back(p2);
    vec.push_back(p3);
    vec.push_back(p4);

    Game g;
    int index = g.createSession(vec);

    vector<int> s1;
    vector<int> s2;
    vector<int> s3;
    vector<int> s4;
    int score;
    for(int i=0; i<20; ++i)
    {
    	score = abs(rand()%10);
    	s1.push_back(score);
        g.roll(index, p1, score);
    	score = abs(rand()%10);
    	s2.push_back(score);
        g.roll(index, p2, score);
    	score = abs(rand()%10);
    	s3.push_back(score);
        g.roll(index, p3, score);
    	score = abs(rand()%10);
    	s4.push_back(score);
        g.roll(index, p4, score);
    }
    cout << "Player 1: ";
    for(int i: s1)
    	cout << i << " ";
    cout << "\n";

    cout << "Player 2: ";
    for(int i: s2)
    	cout << i << " ";
    cout << "\n";

    cout << "Player 3: ";
    for(int i: s3)
    	cout << i << " ";
    cout << "\n";

    cout << "Player 4: ";
    for(int i: s4)
    	cout << i << " ";
    cout << "\n";


    g.createSession(vec);
    g.createSession(vec);
    g.createSession(vec);
    g.declarewinner(index);
    g.createSession(vec);
    return 0;
}