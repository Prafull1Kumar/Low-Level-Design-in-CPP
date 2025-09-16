#include<iostream>
#include<vector>
using namespace std;
class Meeting;
typedef vector<Meeting> Calendar;
class Room
{
    
private:
    string name;
    Calendar calendar;
public:
    Room(string name){
      this->name=name;   
    }
    bool isavailable(int, int);
    string& get_name(){
        return this->name;
    }
    
};
class Meeting
{
    // public:
    // int start;
    // int end;
    // Room room;
    // Meeting(int start,int end, Room r): room(r){
    //     this->end=end;
    //     this->start=start;
    // }
    // public:
    // int get_start(){
    //     return start;
    // }
    // int get_end(){
    //     return end;
    // }
    public:
	Meeting(int, int, Room);
	int getEnd() const;
	int getStart() const;

    private:
	int start, end;
	Room room;

};
class Schedular
{
    public:
    vector<Room> rooms;
    Schedular(vector<Room> r){
        this->rooms=r;
    }
public:
    string book(int start,int end){
        for(int i=0;i<rooms.size();i++){
            bool flag=rooms[i].isavailable(start,end);
            if(flag){
                return rooms[i].get_name();
            }
        }
        return "No room available";
    }
};

// Room::Room(string name)
// {
// 	this->name = name;
// }

// bool Room::isavailable(int start, int end)
// {
// 	for(Meeting m: calendar)
// 	{
// 		if(m.getStart() < end && start < m.getEnd())
// 			return false;
// 	}

// 	Meeting meeting(start, end, *this);
// 	calendar.push_back(meeting);

// 	return true;
// }

// const string& Room::get_name() const {
// 	return name;
// }
bool Room::isavailable(int start,int end){
    // for(Meeting m:calender){
    //     if(m.get_start()<end && m.get_end()>start){
    //         return false;
    //     }
    // }
    // Meeting meeting(start,end,*this);
    // calender.push_back(meeting);
    // return true;
    for(Meeting m: calendar)
    {
        if(m.getStart() < end && start < m.getEnd())
            return false;
    }

    Meeting meeting(start, end, *this);
    calendar.push_back(meeting);

    return true;
}

Meeting::Meeting(int start, int end, Room room): room(room)
{
	this->start = start;
	this->end = end;
}

int Meeting::getEnd() const {
	return end;
}

int Meeting::getStart() const {
	return start;
}
int main(){
    vector<Room> r;
    Room r1("B1");
    Room r2("B2");
    Room r3("B3");
    r.push_back(r1);
    r.push_back(r2);
    r.push_back(r3);
    Schedular s(r);
    cout<<s.book(1,2)<<"\n";
    return 0;
}