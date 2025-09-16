#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Player{
    string name;
    char symbol;
    public:
    Player(string name,char c){
        this->name=name;
        this->symbol=c;
    }
    string getName(){
        return this->name;
    }
    char getSymbol(){
        return this->symbol;
    }
};
class Board{
    int board_size;
    queue<Player*> chance;
    vector<vector<char>> playBoard;
    public:
    Board(int n,Player* p1, Player* p2){
        this->board_size=n;
        chance.push(p1);
        chance.push(p2);
        this->playBoard.resize(n,vector<char>(n,'.'));
    }
    int getInputValue(){
        int pos=-1;
        while(pos>(board_size*board_size) || pos<0){
            cout<<"Type your value: ";
            cin>>pos;
        }
        return pos;
    }
    bool win(int x,int y){
        char sym=playBoard[x][y];
        string winstring="";
        for(int i=0;i<board_size;i++){
            winstring+=sym;
        }
        string row="";
        string column="";
        string diagonal="";
        string reversediagonal="";
        for(int i=0;i<board_size;i++){
            row+=playBoard[x][i];
            column+=playBoard[i][y];
            diagonal+=playBoard[i][i];
            reversediagonal+=playBoard[i][board_size-1-i];
        }
        if(winstring==row || winstring==column || winstring==diagonal || winstring==reversediagonal){
            return true;
        }
        return false;
    }
    void startPlay(){
        cout<<"Value shoukd be in between 0 and"<<board_size*board_size-1<<"\n";
        int cnt=0;
        for(int i=board_size-1;i>=0;i--){
            for(int j=0;j<board_size;j++){
                cout<<board_size*i+j<<" ";
            }
            cout<<"\n";
        }
        while(true){
            Player* p=chance.front();
            chance.pop();
            cout<<"This is "<<p->getName()<<" chance"<<"\n";
            int val=getInputValue();
            int x=val/board_size;
            int y=val%board_size;
            playBoard[x][y]=p->getSymbol();
            for(int i=board_size-1;i>=0;i--){
                for(int j=0;j<board_size;j++){
                    cout<<playBoard[i][j]<<" ";
                }
                cout<<"\n";
            }
            cnt++;
            int winflag=win(x,y);
            if(winflag){
                cout<<"Player "<<p->getName()<<" has win the match"<<"\n";
                break;
            }
            if(cnt>=board_size*board_size){
                cout<<"The match is draw"<<"\n";
                break;
            }
            chance.push(p);
        }
    }
};
int main(){
    Player* p1=new Player("Ram",'O');
    Player* p2=new Player("Sham",'X');
    Board* b=new Board(3,p1,p2);
    b->startPlay();
    return 0;
}