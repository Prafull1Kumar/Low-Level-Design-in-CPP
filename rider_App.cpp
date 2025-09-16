
// #include <bits/stdc++.h>
#include<iostream>
#include<vector>
using namespace std;
enum Ridestatus {completed,not_started,ongoing,withdraw};
class Person{
    public:
    string name;
    int age;
    public:
    void get_user(){
        cout<<"Name: "<<this->name<<", Age:"<<this->age<<"\n";
    }
};
class Ride{
    public:
    int id;
    int origin;
    int destination;
    int no_seat;
    int perkmprice=20;
    Ridestatus status;
    public:
    void set_perkm_price(int price){
        this->perkmprice=price;
    }
    void set_Ride(int id,int origin,int destination,int no_seat,Ridestatus status){
        this->id=id;
        this->origin=origin;
        this->destination=destination;
        this->no_seat=no_seat;
        this->status=status;
    }
    // int price=((this->destination)-(this->origin))*(this->perkmprice)*(this->no_seat);
    float calculatefare(bool vip){
        // cout<<(vip?0.75:1)<<" "<<((this->destination)-(this->origin))*(this->perkmprice)*(this->no_seat)*(vip?0.75:1)<<"\n";
        if(this->no_seat==1){
            return ((this->destination)-(this->origin))*(this->perkmprice)*(this->no_seat)*(vip?0.75:1);
        }
        return ((this->destination)-(this->origin))*(this->perkmprice)*(this->no_seat)*(vip?0.50:0.75);
    }
    void set_status(Ridestatus status){
        this->status=status;
    }
    
    void get_id(){
        cout<<"id: "<<this->id<<"\n";
    }
    void get_origin(){
        cout<<"Origin: "<<this->origin<<"\n";
    }
    void get_destination(){
        cout<<"Destination: "<<this->destination<<"\n";
    }
    void get_no_seat(){
        cout<<"No. of seats booked: "<<this->no_seat<<"\n";
    }
    void get_status(){
        cout<<"Status: "<<this->status<<"\n";
    }
    void get_current_ride(){
        get_id();
        get_origin();
        get_destination();
        get_no_seat();
        get_status();
    }
};
class Rider:private Person,private Ride{
    public:
    vector<Ride> All_Ride;
    Ride current_Ride;
    public:
    Rider(string name,int age){
        this->name=name;
        this->age=age;
    }
    void get_rider_details(){
        get_user();
    }
    void get_all_rides(){
        cout<<"Rider History:-"<<"\n";
        for(int i=0;i<All_Ride.size();i++){
            All_Ride[i].get_current_ride();
            cout<<"..."<<"\n";
        }
    }
    void createRide(int id,int origin,int destination,int no_seat){
        if(origin>=destination){
           cout<<"input value of Origin and End are not correctly confidgured"; 
        }
        current_Ride.set_Ride(id,origin,destination,no_seat,Ridestatus::not_started);
    }
    void updateRide(int id,int origin,int destination,int no_seat){
        if(current_Ride.status==Ridestatus::completed){
            cout<<"This ride is completed"<<"\n";
        }
        if(current_Ride.status==Ridestatus::withdraw){
            cout<<"This ride is withdrawn"<<"\n";
        }
        
        current_Ride.set_Ride(id,origin,destination,no_seat,current_Ride.status);
        
    }
    float closeRide(){
        if(current_Ride.status==Ridestatus::withdraw){
            cout<<"Ride is already withdrawn"<<"\n";
            return 0.0;
        }
        All_Ride.push_back(current_Ride);
        // cout<<All_Ride.size()<<"\n";
        return current_Ride.calculatefare(All_Ride.size()>=10);
    }
    void withdraw(){
        current_Ride.set_status(Ridestatus::withdraw);
        All_Ride.push_back(current_Ride);
    }
    void getRide_status(){
        current_Ride.get_current_ride();
    }
};

class Driver:private Person,public Ride{
    public:
    Ride current_Ride;
    public:
    Driver(string name,int age){
        this->name=name;
        this->age=age;
    }
    void start_ride(){
        set_status(Ridestatus::ongoing);
    }
};
int main(){
    cout<<"HEllo Ride app"<<"\n";
    Rider R1("Rohan",12);
    R1.get_rider_details();
    R1.createRide(1,100,300,2);
    R1.withdraw();
    cout<<R1.closeRide()<<"\n";

    R1.createRide(2,200,700,2);
    cout<<R1.closeRide()<<"\n";

    R1.createRide(3,50,300,3);
    cout<<R1.closeRide()<<"\n";
    R1.get_all_rides();
    return 0;
}