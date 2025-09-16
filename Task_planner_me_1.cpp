#include<iostream>
#include<vector>
using namespace std;

class Task;
class Sprint;
enum TaskType {Story,Feature,Bug};
enum TaskStatus {New, Active, Resolved, QA_Pass, Completed};
class User{
    private:
    string name;
    vector<Task> tasks;
    vector<Sprint> sprints;
    public:
    User(string );
    Task createTask(TaskType);
    Sprint createSprint(int ,int ,string );
    bool addToSprint(Sprint ,Task );
    bool removefromSprint(Sprint ,Task );
    void printAllTasks();
    bool changeStatus(Task ,TaskStatus );
};
class Task
{
private:
    TaskType type;
    string status;
    User assign_to;
    int id;
public:
    Task(User);
    int getId();
    int getUniqueId();
    void setType(TaskType );
    void setStatus(TaskStatus );
    void setUser(User );
    void get_details();
    
    // Task(int id,TaskType type,string status,User user):assign_to(user){
    //     this->id=id;
    //     this->status=status;
    //     this->type=type;
    //     // this->assign_to=;
    // }
    // void setId(){
    //     this->id=getUniqueId();
    // }
};
class Sprint{
    private:
    int begin;
    int end;
    string name;
    vector<Task> tasks;
    public:
    Sprint(int ,int ,string );
    void addTask(Task t);
    bool operator==(Sprint sprint);
    void removeTask(Task t);
    void printDetails();
};
Sprint::Sprint(int begin,int end,string name){
    this->begin=begin;
    this->end=end;
    this->name=name;
}
void Sprint::printDetails()
{
	cout << "Sprint Name: " << this->name << "\nSprint Begins: " << this->begin << "\nSprint Ends: " << this->end << endl;
}
void Sprint::addTask(Task t){
    tasks.push_back(t);
}
void Sprint::removeTask(Task t){
    for(int i=0;i<tasks.size();i++){
        if(tasks[i].getId()==t.getId()){
            tasks.erase(tasks.begin()+i);
            break;
        }
    }
}
inline bool Sprint::operator==(Sprint sprint)
{
	return (this->begin == sprint.begin) && (this->end == sprint.end) && (this->name == sprint.name);
}
Task User::createTask(TaskType type){
    Task t(*this);
    // t.setId();
    t.setType(type);
    t.setStatus(TaskStatus::New);
    // t.setUser(*this);
    tasks.push_back(t);
    return t;
}

User::User(string name){
    this->name=name;
}
Sprint User::createSprint(int start,int end,string name){
    Sprint s(start,end,name);
    sprints.push_back(s);
    return s;
}  

bool User::addToSprint(Sprint s,Task t){
    for(int i=0;i<sprints.size();i++){
        if(sprints[i]==s){
            // tasks.push_back(t);
            sprints[i].addTask(t);
            return true;
        }
    }
    return false;
}
bool User::removefromSprint(Sprint s,Task t){
    for(int i=0;i<sprints.size();i++){
        if(s==sprints[i]){
            // tasks.push_back(t);
            sprints[i].removeTask(t);
            return true;
        }
    }
    return false;
}
void User::printAllTasks(){
    for(Task task: tasks)
    {
        cout << task.getId() << " ";
    }
    cout << endl;
}
bool User::changeStatus(Task t,TaskStatus status){
    for(int i=0;i<tasks.size();i++){
        if(t.getId()==tasks[i].getId()){
            tasks[i].setStatus(status);
            return true;
        }
    }
    return false;
}
Task::Task(User user):assign_to(user){
    this->id=getUniqueId();
    this->status=TaskStatus::New;
}
int Task::getId(){
    return this->id;
}
int Task::getUniqueId(){
    static int taskid=0;
    return taskid++;
}
void Task::setType(TaskType t){
    this->type=t;
}
void Task::setStatus(TaskStatus status){
    this->status=status;
}
void Task::setUser(User u){
    this->assign_to=u;
}
// void Task::get_details(){
//     cout<<"Id: "<<this->id<<"\n";
//     cout<<"Status: "<<this->status<<"\n";
//     cout<<"Type: "<<this->type<<"\n";
//     cout<<"User: "<<this->assign_to.get_name()<<"\n";
// }


// void Sprint::details(){
//     for(Task t:sprint){
//         t.get_details();
//         cout<<"\n";
//     }
// }
int main(){
    User u1("Ram");
    User u2("Sham");
    Task t1=u1.createTask(TaskType::Bug);
    Task t2=u1.createTask(TaskType::Feature);
    Task t3=u1.createTask(TaskType::Story);
    Task t4=u2.createTask(TaskType::Bug);
    Task t5=u2.createTask(TaskType::Feature);
    Task t6=u2.createTask(TaskType::Story);
	Sprint sprint1 = u1.createSprint(22,33,"Sprint1");
	Sprint sprint2 = u2.createSprint(44,55,"Sprint2");

    cout << u1.changeStatus(t1, TaskStatus::Active) <<endl ;//1

	cout << u1.addToSprint(sprint1, t1) << "\n"; //1
	cout << u1.addToSprint(sprint1, t2) << "\n"; //1
	cout << u1.addToSprint(sprint2, t3) << "\n"; //0
	cout << u1.removefromSprint(sprint1, t2) << "\n"; //1
	cout << u2.addToSprint(sprint1, t2) << "\n"; //0
	cout << u2.removefromSprint(sprint1, t2) << "\n"; //0
	cout << u2.addToSprint(sprint2, t4) << "\n"; //1
	cout << u2.addToSprint(sprint2, t5) << "\n"; //1

	sprint1.printDetails();
	cout << endl;
	u1.printAllTasks();
	// u2.printAllTasks();
    // Task t1(1,TaskType::Bug,"New",u);
    // Task t2(2,TaskType::Bug,"New",u);
    // Task t3(3,TaskType::Bug,"New",u);
    // Task t4(4,TaskType::Bug,"New",u1);
    // Task t5(5,TaskType::Bug,"New",u1);
    // Task t6(6,TaskType::Bug,"New",u1);
    // // t1.get_details();
    // vector<Task> v;
    // v.push_back(t1);
    // v.push_back(t2);
    // v.push_back(t3);
    // v.push_back(t4);
    // v.push_back(t5);
    // v.push_back(t6);
    // Task_Planner s(v);
    // Sprint Sp(v);
    // // cout<<"Hello"<<"\n";
    // // s.add_tasks_to_sprint(Sp);
    // s.sprint_detail(Sp);
    // Task t7(7,TaskType::Bug,"New",u1);
    // Sp.add_task(t7);
    // // s.add_tasks_to_sprint(Sp,t7);
    // s.sprint_detail(Sp);
    return 0;
}