#include<iostream>
#include<vector>
using namespace std;
class Country{
    private:
    string name;
    int totalrevenue=0;
    public:
    Country(string);
    void updateRevenue(int);
    void status();
};
class State{
    private:
    string name;
    int totalrevenue=0;
    public:
    State(string);
    void updateRevenue(int);
    void status();
};
class City{
    private:
    string name;
    int totalrevenue=0;
    public:
    City(string);
    void updateRevenue(int);
    void status();
};
class Beverage{
    private:
    string name;
    int price;
    public:
    Beverage(string,int);
    int getPrice();
    string getName();
};
class Store{
    private:
    vector<pair<Beverage,int>> foodperquantity;
    int totalrevenue;
    City *city;
    State *state;
    Country *country;
    public:
    Store(vector<pair<Beverage,int>>,City*,State*,Country*);
    void buy(Beverage,int);
    void quantityLeft();
    void showMenu();
};
Country::Country(string name){
    this->name=name;
    this->totalrevenue=0;
}
void Country::updateRevenue(int cost){
    this->totalrevenue+=cost;
}
State::State(string name){
    this->name=name;
    this->totalrevenue=0;
}
void State::updateRevenue(int cost){
    this->totalrevenue+=cost;
}
City::City(string name){
    this->name=name;
    this->totalrevenue=0;
}
void City::updateRevenue(int cost){
    this->totalrevenue+=cost;
}
void Country::status(){
    cout<<"Total revenue of "<<this->name<<" is "<<this->totalrevenue<<"\n";
}
void State::status(){
    cout<<"Total revenue of "<<this->name<<" is "<<this->totalrevenue<<"\n";
}
void City::status(){
    cout<<"Total revenue of "<<this->name<<" is "<<this->totalrevenue<<"\n";
}
Beverage::Beverage(string food,int price){
    this->name=food;
    this->price=price;
}
string Beverage::getName(){
    return this->name;
}
int Beverage::getPrice(){
    return this->price;
}
// :country(country),state(state),city(city)
Store::Store(vector<pair<Beverage,int>> menu,City *city,State *state,Country *country){
    this->foodperquantity=menu;
    this->totalrevenue=0;
    this->city=city;
    this->country=country;
    this->state=state;
}
void Store::buy(Beverage food,int quanty){
    for(int i=0;i<foodperquantity.size();i++){
        if(foodperquantity[i].first.getName()==food.getName()){
            if(foodperquantity[i].second>=quanty){
                totalrevenue+=food.getPrice()*quanty;
                city->updateRevenue(food.getPrice()*quanty);
                state->updateRevenue(food.getPrice()*quanty);
                country->updateRevenue(food.getPrice()*quanty);
            }else cout<<"We have only "<<foodperquantity[i].second<<" much of "<<food.getName()<<" left"<<"\n";

            break;
        }
    }
}
void Store::quantityLeft(){
    for(int i=0;i<foodperquantity.size();i++){
        cout<<foodperquantity[i].second<<" "<<foodperquantity[i].first.getName()<<" are left"<<"\n";
    }
}

void Store::showMenu(){
    cout<<"Menu:- ";
    for(int i=0;i<foodperquantity.size();i++){
        cout<<foodperquantity[i].first.getName()<<" :- "<<foodperquantity[i].first.getPrice()<<"\n";
    }
}
int main(){
    Beverage b1("Pasta",30);
    Beverage b2("Dosa",35);
    Beverage b3("Maggie",20);
    Beverage b4("Egg",15);
    Country *c1=new Country("India");
    State *s1=new State("Maharastra");
    City *cty1=new City("Nagpur");
    City *cty2=new City("Pune");
    vector<pair<Beverage,int>> menu={{b1,4},{b2,2},{b3,3},{b4,5}};
    Store st1(menu,cty1,s1,c1);
    Store st2(menu,cty2,s1,c1);
    st1.showMenu();
    st1.buy(b1,2);
    st1.buy(b3,3);
    st1.buy(b2,4);
    st2.buy(b3,2);
    st2.buy(b4,5);
    st2.buy(b1,4);
    cty1->status();
    cty2->status();
    s1->status();
    c1->status();
    return 0;
}