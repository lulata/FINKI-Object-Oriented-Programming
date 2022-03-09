#include<iostream>
#include<cstring>
using namespace std;

class Task {
protected:
    char ID[5];
public:
    Task(char *ID = "") {
        strcpy(this->ID, ID);
    }virtual ~Task() {}
    Task (const Task& t){
        strcpy(this->ID, t.ID);
    }
    virtual int getOrder() const = 0;
    virtual void print() = 0;
    friend bool operator== (const Task *t1,const Task &t){
        return (strcmp(t1->ID,t.ID) == 0 && (t1->getOrder() == t.getOrder()));
    }
};

class TimedTask : public Task{
private:
    int vreme;
public:
    TimedTask(char *id = "", int time = 0) : Task(id) {
        this->vreme = time;
    }int getOrder() const override{
        return vreme;
    }TimedTask (const TimedTask& other){
        strcpy(this->ID, other.ID);
        this->vreme = other.vreme;
    }void print() override{
        cout << "TT->" << ID <<":" << getOrder() << endl;
    }
};

class PriorityTask  : public Task{
private:
    int prioritet;
public:
    PriorityTask(char *id = "", int prioritet = 0) : Task(id) {
        this->prioritet = prioritet;
    }
    int getOrder() const override{
        return prioritet;
    }
    PriorityTask (const PriorityTask& p){
        strcpy(this->ID, p.ID);
        this->prioritet = p.prioritet;
    }void print() override{
        cout << "PT->" << ID <<":" << getOrder() << endl;
    }
};

void scheduleTimedTasks (Task ** tasks, int n, int t){
    Task *temp;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; j++) {
            Task *test1 = dynamic_cast<TimedTask *>(tasks[i]);
            Task *test2 = dynamic_cast<TimedTask *>(tasks[j]);
            if (test1 && test2) {
                if (tasks[i]->getOrder() > tasks[j]->getOrder()) {
                    temp = tasks[i];
                    tasks[i] = tasks[j];
                    tasks[j] = temp;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        Task *test1 = dynamic_cast<TimedTask *>(tasks[i]);
        if (test1) {
            if (tasks[i]->getOrder() < t) {
                tasks[i]->print();
            }
        }
    }
}

void schedulePriorityTasks (Task ** tasks, int n, int p){
    Task *temp;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; j++) {
            Task *test1 = dynamic_cast<PriorityTask *>(tasks[i]);
            Task *test2 = dynamic_cast<PriorityTask *>(tasks[j]);
            if (test1 && test2) {
                if (tasks[i]->getOrder() > tasks[j]->getOrder()) {
                    temp = tasks[i];
                    tasks[i] = tasks[j];
                    tasks[j] = temp;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        Task *test1 = dynamic_cast<PriorityTask *>(tasks[i]);
        if (test1) {
            if (tasks[i]->getOrder() < p) {
                tasks[i]->print();
            }
        }
    }
}

int main () {
    int testCase;
    int n;
    cin>>testCase;

    if (testCase==0){
        cin>>n;
        Task ** tasks;
        tasks = new Task * [n];
        for (int i=0;i<n;i++){
            char id [5];
            int timeOrPriority;
            int type; //0 za timed, 1 za priority
            cin >> type >>id >> timeOrPriority;
            if (type==0)
                tasks[i] = new TimedTask(id,timeOrPriority);
            else
                tasks[i] = new PriorityTask(id,timeOrPriority);
            //tasks[i]->print();
        }

        cout<<"SCHEDULING PRIORITY TASKS WITH PRIORITY DEGREE LESS THAN 10"<<endl;
        schedulePriorityTasks(tasks,n,10);

    }
    else if (testCase==1) {
        cin>>n;
        Task ** tasks;
        tasks = new Task * [n];
        for (int i=0;i<n;i++){
            char id [5];
            int timeOrPriority;
            int type; //0 za timed, 1 za priority
            cin >> type >>id >> timeOrPriority;
            if (type==0)
                tasks[i] = new TimedTask(id,timeOrPriority);
            else
                tasks[i] = new PriorityTask(id,timeOrPriority);
            //tasks[i]->print();
        }


        cout<<"SCHEDULING TIMED TASKS WITH EXECUTION TIME LESS THAN 50"<<endl;
        scheduleTimedTasks(tasks,n,50);
    }
    else {
        TimedTask * tt1 = new TimedTask("11",10);
        TimedTask * tt2 = new TimedTask("11",11);
        TimedTask * tt3 = new TimedTask("11",11);
        PriorityTask * pp1 = new PriorityTask("aa",10);
        PriorityTask * pp2 = new PriorityTask("11",10);

        cout << (tt1==(*tt2))<<endl;
        cout << (tt2==(*tt3))<<endl;
        cout << (pp1==(*pp2))<<endl;
        cout << (pp2==(*tt1))<<endl;
    }

    return 0;
}
