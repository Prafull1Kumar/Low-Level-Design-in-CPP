#include<iostream>
#include<unordered_map>
#include<vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
enum SlotType {TWOWHEELER,SEDAN,SUV};
class ParkSlot{
    bool isavailable;
    SlotType type;
    string name;
    public:
    ParkSlot(string name,SlotType t){
        this->isavailable=true;
        this->name=name;
        this->type=t;
    }
    bool getavailability(){
        return this->isavailable;
    }
    void setavailable(){
        this->isavailable=true;
    }
    void setTaken(){
        this->isavailable=false;
    }
    string getName(){
        // cout<<this->name<<"\n";
        return this->name;
    }
};
class ParkFloor{
    unordered_map<SlotType,vector<ParkSlot*>> mp;
    public:
    ParkFloor(unordered_map<SlotType,vector<ParkSlot*>> m){
        this->mp=m;
    }
    ParkSlot* findAvailableSlot(SlotType type){
        for(int i=0;i<mp[type].size();i++){
            if(mp[type][i]->getavailability()){
                mp[type][i]->setTaken();
                return mp[type][i];
            }
        }
        cout<<"No parking slot is available for this CarType"<<"\n";
        return NULL;
    }
};
class Ticket{
    int start_time;
    int end_time;
    void setStart_time(int time){
        this->start_time=time;
    }
    void setEnd_time(int time){
        this->end_time=time;
    }
    void calculateCharge(){
        cout<<(this->end_time-this->start_time)*10<<"\n";
    }
};
class Car{
    string noPlat;
    SlotType carType;
    ParkSlot* slot;
    Ticket* ticket;
    public:
    Car(string no,SlotType t){
        this->noPlat=no;
        this->carType=t;
        this->ticket=new Ticket();
    }
    SlotType getType(){
        return carType;
    }
    void setParkingSlot(ParkSlot* ps){
        this->slot=ps;
    }
    void setTicket(int start_time){
        this->ticket->setStart_time(start_time);
    }
    void calculateCharges(int end_time){
        slot->setavailable();
        this->ticket->setEnd_time(end_time);
        this->ticket->calculateCharge();
    }
    void getParkingSlot(){
        if(this->slot==NULL){
            cout<<"Your car Type slot is full"<<"\n";
            return ;
        }
        cout<<slot->getName()<<"\n";
        return ;
    }

};
class ParkingLot{
    string name;
    vector<ParkFloor*> floors;
    public:
    ParkingLot(vector<ParkFloor*> fls,string name){
        this->floors=fls;
        this->name=name;
    }
    Car* assignParkingLot(Car* c){
        ParkSlot* slot;
        // cout<<"I am here"<<"\n";
        for(int i=0;i<floors.size();i++){
            slot=floors[i]->findAvailableSlot(c->getType());
            if(slot){
                cout<<"SLot is available"<<"\n";
                c->setParkingSlot(slot);
                c->setTicket(8);
                return c;
            }
        }
        // cout<<"No slot"<<"\n";
        return c;
    }
    void removeCar(Car* c){
        c->calculateCharges();
    }
};


int main(){
    ParkSlot* slot1=new ParkSlot("TW1",SlotType::TWOWHEELER);
    ParkSlot* slot2=new ParkSlot("TW2",SlotType::TWOWHEELER);
    ParkSlot* slot3=new ParkSlot("TW3",SlotType::TWOWHEELER);
    ParkSlot* slot4=new ParkSlot("SE1",SlotType::SEDAN);
    ParkSlot* slot5=new ParkSlot("SE2",SlotType::SEDAN);
    ParkSlot* slot6=new ParkSlot("SE3",SlotType::SEDAN);
    ParkSlot* slot7=new ParkSlot("SUV1",SlotType::SUV);
    ParkSlot* slot8=new ParkSlot("SUV2",SlotType::SUV);
    ParkSlot* slot9=new ParkSlot("SUV3",SlotType::SUV);
    unordered_map<SlotType,vector<ParkSlot*>> mp;
    mp[SlotType::TWOWHEELER]={slot1,slot2,slot3};
    mp[SlotType::SEDAN]={slot4,slot5,slot6};
    mp[SlotType::SUV]={slot7,slot8,slot9};
    ParkFloor* first_floor=new ParkFloor(mp);
    vector<ParkFloor*> floor;
    floor.push_back(first_floor);
    ParkingLot* p1=new ParkingLot(floor,"Bhagwan Nagar");
    Car* c1=new Car("MH42:4569",SlotType::TWOWHEELER);
    Car* c2=new Car("MH42:1990",SlotType::TWOWHEELER);
    Car* c3=new Car("MH42:5908",SlotType::TWOWHEELER);
    Car* c4=new Car("MH42:6899",SlotType::SEDAN);
    Car* c5=new Car("MH42:7803",SlotType::SEDAN);
    Car* c6=new Car("MH42:2345",SlotType::SEDAN);
    Car* c7=new Car("MH42:3897",SlotType::SUV);
    Car* c8=new Car("MH42:9000",SlotType::SUV);
    Car* c9=new Car("MH42:8790",SlotType::SUV);
    Car* c10=new Car("MH42:7896",SlotType::TWOWHEELER);
    p1->assignParkingLot(c1)->getParkingSlot();
    p1->assignParkingLot(c2)->getParkingSlot();
    // p1->assignParkingLot(c1)->getParkingSlot();
    // p1->assignParkingLot(c2)->getParkingSlot();
    p1->assignParkingLot(c3)->getParkingSlot();
    p1->assignParkingLot(c4)->getParkingSlot();
    p1->assignParkingLot(c5)->getParkingSlot();
    p1->assignParkingLot(c6)->getParkingSlot();
    p1->assignParkingLot(c7)->getParkingSlot();
    p1->assignParkingLot(c8)->getParkingSlot();
    p1->assignParkingLot(c9)->getParkingSlot();
    p1->assignParkingLot(c10)->getParkingSlot();
    // cout<<c1->getParkingSlot()<<"\n";
    time_t my_time = time(NULL);
  
    // ctime() used to give the present time
    auto startit=ctime(&my_time);
    cout<<startit<<"\n";
    // system("PAUSE");
    
    auto endit=ctime(&my_time);
    cout<<endit<<"\n";
    return 0;
}