#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Customer{

    string name;
    int parkinglot_id;
    public:
    Customer(string);
    string getName();
    int getParkingLotId();
    void setParkingLotId(int);
};
class ParkingLot{
    int id;
    int rate=100;
    bool isfree;
    public:
    ParkingLot();
    int getUniqueId();
    
    int getId();
    void assignParkingLot();
    void emptyParkingLot();
    bool getStatus();
};
class Booking{
    vector<ParkingLot> parkinglots;
    queue<Customer> customerqueue;
    public:
    Booking(vector<ParkingLot>);
    void bookParking(Customer&);
    void exist(Customer);
};
Customer::Customer(string name){
    this->name=name;
}
string Customer::getName(){
    return this->name;
}
int Customer::getParkingLotId(){
    return this->parkinglot_id;
}
void Customer::setParkingLotId(int id){
    this->parkinglot_id=id;
    return ;
}
ParkingLot::ParkingLot(){
    this->isfree=true;
    this->id=getUniqueId();
}
int ParkingLot::getId(){
    return this->id;
}
int ParkingLot::getUniqueId(){
    static int parkingid=0;
    parkingid++;
    return parkingid;
}
void ParkingLot::assignParkingLot(){
    this->isfree=false;
    return;
}
void ParkingLot::emptyParkingLot(){
    this->isfree=true;
}
bool ParkingLot::getStatus(){
    return this->isfree;
}
Booking::Booking(vector<ParkingLot> parkings){
    this->parkinglots=parkings;
}
void Booking::bookParking(Customer &cur){
    for(int i=0;i<parkinglots.size();i++){
        if(parkinglots[i].getStatus()){
            cur.setParkingLotId(parkinglots[i].getId());
            parkinglots[i].assignParkingLot();
            cout<<cur.getName()<<" has parked his car in parking lot "<<parkinglots[i].getId()<<"\n";
            return ;
        }
    }
    cout<<"No parking lots empty"<<"\n";
    cout<<"Will assign you when it will be free"<<"\n";
    this->customerqueue.push(cur);
}
void Booking::exist(Customer cur){
    for(int i=0;i<parkinglots.size();i++){
        if(parkinglots[i].getId()==cur.getParkingLotId()){
            parkinglots[i].emptyParkingLot();
            break;
        }
    }
    if(!customerqueue.empty()){
        cout<<"Parking lot is empty"<<"\n";
        // cout<<customerqueue.front().getName()<<" "
        bookParking(customerqueue.front());
        customerqueue.pop();
    }
    return ;
}
int main(){
    Customer c1("Myur");
    Customer c2("krishna");
    Customer c3("batista");
    Customer c4("Farista");
    ParkingLot p1;
    ParkingLot p2;
    ParkingLot p3;
    vector<ParkingLot> ps={p1,p2,p3};
    Booking b1(ps);
    b1.bookParking(c1);
    b1.bookParking(c2);
    b1.bookParking(c3);
    b1.bookParking(c4);
    b1.exist(c1);
    return 0;
}