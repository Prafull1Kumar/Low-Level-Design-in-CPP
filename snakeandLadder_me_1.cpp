#include<iostream>
#include<vector>
#include<set>
using namespace std;
/*
Requiments:
1. Number of Dice can change
2. Number of Player can change
3. Board Size can change
4. Snakes and Ladders can be added dynamically

Class

Board
Position
Dice
Player
Jumper(Snake/Ladder)
Game
*/
class Position{
    public:
    int val;
    Position(int val){
        this->val=val;
    }
    void add(Position* pos){
        this->val+=pos->val;
    }
};
class Player{
    public:
    string name;
    int id;
    Position* currentPosition;
    Player(string name, int id){
        this->name=name;
        this->id=id;
    }
    void move(Position* newPosition){
        this->currentPosition=newPosition;
    }
    int getCurrentPosition(){
        return currentPosition->val;
    }
};
class Dice{
    public:
    int roll(){
        return rand()%6+1;
    }
};
class Jumper{
    public:
    Position* start;
    Position* end;
    Jumper(Position* st,Position* ed){
        this->start=st;
        this->end=ed;
    }
};
class Board{
    public:
    int size;
    vector<Jumper*> snakes;
    vector<Jumper*> ladders;
    Board(int size,vector<Jumper*> snakes,vector<Jumper*> ladders){
        this->size=size;
        this->snakes=snakes;
        this->ladders=ladders;
    }

};
class Game{
    public:
    Board* board;
    vector<Player*> players;
    vector<Dice*> dices;
    int numberOfSnakes=5;
    int numberOfLadders=5;
    Game(Board* board,vector<Player*> players,vector<Dice*> dices){
        this->board=board;
        this->players=players;
        this->dices=dices;
        initializeBoard();
    }
    void initializeBoard(){
        set<pair<Position*,Position*>> occupiedPositions;
        while(board->snakes.size()<this->numberOfSnakes){
            int start=rand()%(board->size);
            int end=rand()%(board->size);
            if(start<end) continue;
            Position* st=new Position(start);
            Position* ed=new Position(end);
            occupiedPositions.insert({ed,st});
            board->snakes.push_back(new Jumper(st,ed));
        }
        while(board->ladders.size()<this->numberOfLadders){
            int start=rand()%(board->size);
            int end=rand()%(board->size);
            if(start>end) continue;
            Position* st=new Position(start);
            Position* ed=new Position(end);
            if(occupiedPositions.count({st,ed})) continue;
            board->ladders.push_back(new Jumper(st,ed));
        }
    }
    void startGame(){
        bool gameWon=false;
        int n=players.size();
        int index=0;
        while(!gameWon){
            Player* currentPlayer=players[index%n];
            cout<<currentPlayer->name<<" "<<currentPlayer->getCurrentPosition()<<"\n";
            int moveBy=currentPlayer->currentPosition->val;
            for(Dice* dice:dices){
                moveBy+=dice->roll();
            }
            Position* newPosition=new Position(moveBy);
            if(newPosition->val>board->size){
                index++;
                continue;
            }
            currentPlayer->move(newPosition);
            if(newPosition->val==board->size){
                cout<<"Player "<<currentPlayer->name<<" has won the game!"<<"\n";
                gameWon=true;
            }
            for(Jumper* snake:board->snakes){
                if(snake->start->val==currentPlayer->getCurrentPosition()){
                    currentPlayer->move(snake->end);
                    cout<<"Player "<<currentPlayer->name<<" got bitten by name snake and move to "<<snake->end->val<<"\n";
                    break;
                }
            }
            for(Jumper* ladder:board->ladders){
                if(ladder->start->val==currentPlayer->getCurrentPosition()){
                    currentPlayer->move(ladder->end);
                    cout<<"Player "<<currentPlayer->name<<" got ladder and move to "<<ladder->end->val<<"\n";
                    break;
                }
            }
            index++;
        }
    }

};
int main(){
    Player* p1=new Player("Player1",1);
    p1->move(new Position(0));
    Player* p2=new Player("Player2",2);
    p2->move(new Position(0));
    Player* p3=new Player("Player3",3);
    p3->move(new Position(0));
    vector<Player*> players={p1,p2,p3};
    Dice* d1=new Dice();
    vector<Dice*> dices={d1};
    Board* board=new Board(100,{},{}); // Empty snakes and ladders, will be initialized in Game
    Game* game=new Game(board,players,dices);
    game->startGame();
    cout<<"Design Snake and Ladder Game in C++"<<"\n";
    return 0;
}