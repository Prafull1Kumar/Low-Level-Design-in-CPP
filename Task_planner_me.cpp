#include<iostream>
#include<vector>
using namespace std;

enum TaskType {Story,Feature,Bug};

class User{
    private:
    string name;
    public:
    User(string name){
        this->name=name;
    }
    string get_name(){
        return this->name;
    }
};
class Task
{
private:
    TaskType type;
    string status;
    User assign_to;
    int id;
public:
    Task(int id,TaskType type,string status,User user):assign_to(user){
        this->id=id;
        this->status=status;
        this->type=type;
        // this->assign_to=;
    }
    void change_status(string status){
        this->status=status;
    }
    void get_details(){
        cout<<"Id: "<<this->id<<"\n";
        cout<<"Status: "<<this->status<<"\n";
        cout<<"Type: "<<this->type<<"\n";
        cout<<"User: "<<this->assign_to.get_name()<<"\n";
    }
};
class Sprint{
    private:
    vector<Task> sprint;
    public:
    Sprint(vector<Task> tasks){
        this->sprint=tasks;
    }
    void add_task(Task t){
        sprint.push_back(t);
    }
    void add_task(vector<Task> t){
        sprint.insert(sprint.begin(),t.begin(),t.end());
    }
    void add_task_id(Task t){
        // sprint.push_back(t);
    }
    void details(){
        for(Task t:sprint){
            t.get_details();
            cout<<"\n";
        }
    }
};
class Task_Planner{
    public:
    vector<Task> tasks;
    Task_Planner(vector<Task> tks){
        this->tasks=tks;
    }
    public:
    void add_task(Task T){
        tasks.push_back(T);
    }
    void add_tasks_to_sprint(Sprint sp,Task T){
        // this->trial=sp;
        // this->trial.add_task(T);
        // thisadd_task(T);
    }
    void add_tasks_to_sprint(Sprint sp){
        // sp.add_task(this->tasks);
    }
    void add_tasks_to_sprint(Sprint sp,vector<Task> T){
        sp.add_task(T);
    }
    void sprint_detail(Sprint sp){
        sp.details();
    }
};
int main(){
    User u("Ram");
    User u1("Sham");
    Task t1(1,TaskType::Bug,"New",u);
    Task t2(2,TaskType::Bug,"New",u);
    Task t3(3,TaskType::Bug,"New",u);
    Task t4(4,TaskType::Bug,"New",u1);
    Task t5(5,TaskType::Bug,"New",u1);
    Task t6(6,TaskType::Bug,"New",u1);
    // t1.get_details();
    vector<Task> v;
    v.push_back(t1);
    v.push_back(t2);
    v.push_back(t3);
    v.push_back(t4);
    v.push_back(t5);
    v.push_back(t6);
    Task_Planner s(v);
    Sprint Sp(v);
    // cout<<"Hello"<<"\n";
    // s.add_tasks_to_sprint(Sp);
    s.sprint_detail(Sp);
    Task t7(7,TaskType::Bug,"New",u1);
    Sp.add_task(t7);
    // s.add_tasks_to_sprint(Sp,t7);
    s.sprint_detail(Sp);
    return 0;
}