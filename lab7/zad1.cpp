#include<iostream>
#include<cstring>

using namespace std;

class Employee{
protected:
    char ime[50];
    int god;
    int iskusvo;

    void copy(const Employee &e){
        strcpy(this->ime, e.ime);
        this->god = e.god;
        this->iskusvo = e.iskusvo;
    }
public:
    Employee(char *ime = "", int god = 0, int iskusvo = 0){
        strcpy(this->ime, ime);
        this->god = god;
        this->iskusvo = iskusvo;
    }Employee (const Employee &e){
        copy(e);
    }
    virtual double plata() = 0;
    virtual double bonus() = 0;
    bool operator== (Employee *e){
        return ((this->god == e->god) && (this->bonus() == e->bonus()));
    }
};

class SalaryEmployee : public Employee{
private:
    double plataa;

    void copy(const SalaryEmployee& s){
        Employee::copy(s);
        this->plataa = s.plataa;
    }

public:
    SalaryEmployee(char *ime = "", int god = 0, int iskusvo = 0, double plataa = 0.0) : Employee(ime, god,iskusvo) {
        this->plataa = plataa;
    }SalaryEmployee(const SalaryEmployee &other){
        copy(other);
    }double bonus() override{
        return iskusvo / 100.0 * plataa;
    }double plata() override{
        return plataa + bonus();
    }
};

class HourlyEmployee : public Employee {
private:
    int brRabotniH;
    int platah;

    void copy (const HourlyEmployee& h){
        Employee::copy(h);
        this->brRabotniH = h.brRabotniH;
        this->platah = h.platah;
    }

public:
    HourlyEmployee(char *ime = "", int god = 0, int iskusvo = 0, int brRabotniH = 0, int platah = 0): Employee(ime, god,iskusvo) {
        this->brRabotniH = brRabotniH;
        this->platah = platah;
    }
    HourlyEmployee (const HourlyEmployee& h){
        copy(h);
    }
    HourlyEmployee& operator= (const HourlyEmployee& h){
        if (this != &h) {
            copy(h);
        }
        return *this;
    }double bonus() override{
        if (brRabotniH > 320) {
            return ((brRabotniH-320) * 0.5 * platah);
        }
        return 0.0;
    }double plata() override{
        return (brRabotniH * platah + bonus());
    }
};

class Freelancer : public Employee {
private:
    int brProekti;
    double *plataProekt;

    void copy (const Freelancer& f){
        Employee::copy(f);
        this->brProekti = f.brProekti;
        this->plataProekt = new double[f.brProekti];
        for (int i = 0; i < f.brProekti; i++) {
            this->plataProekt[i] = f.plataProekt[i];
        }
    }

public:
    Freelancer(char *ime = "", int god = 0, int iskusvo = 0, int brProekti = 0,double *plataProekt = 0) : Employee(ime, god, iskusvo) {
        this->brProekti = brProekti;
        this->plataProekt = new double[brProekti];
        for (int i = 0; i < brProekti; i++) {
            this->plataProekt[i] = plataProekt[i];
        }
    }Freelancer(const Freelancer& f){
        copy(f);
    }Freelancer& operator= (const Freelancer& f){
        if (this != &f) {
            delete[] plataProekt;
            copy(f);
        }return *this;
    }~Freelancer(){
        delete[] plataProekt;
    }double bonus() override{
        if (brProekti > 5) {
            return ((brProekti - 5) * 1000);
        }
        return 0.0;
    }
    double plata() override {
        double totalSum = 0.0;
        for (int i = 0; i < brProekti; i++) {
            totalSum += plataProekt[i];
        }
        totalSum += bonus();
        return totalSum;
    }
};

class Company{
private:
    char imee[50];
    int brojVraboteni;
    Employee **vrabotenii;

    void copy(const Company& c){
        strcpy(this->imee, c.imee);
        this->brojVraboteni = c.brojVraboteni;
        for (int i = 0; i < c.brojVraboteni; ++i) {
            vrabotenii[i] = c.vrabotenii[i];
        }
    }

public:
    Company(char *imee = ""){
        strcpy(this->imee, imee);
        brojVraboteni = 0;
        vrabotenii = nullptr;
    }Company(const Company& other){
        copy(other);
    }~Company(){
        delete[] vrabotenii;
    }Company& operator+= (Employee* em){
        Employee **temp = new Employee*[brojVraboteni + 1];
        for (int i = 0; i < brojVraboteni; ++i) {
            temp[i] = vrabotenii[i];
        }
        temp[brojVraboteni++] = em;
        delete[] vrabotenii;
        vrabotenii = temp;
        return *this;
    }double vkupnaPlata(){
        double totalSum = 0.0;
        for (int i = 0; i < brojVraboteni; ++i) {
            totalSum += vrabotenii[i]->plata();
        }
        return totalSum;
    }double filtriranaPlata(Employee * emp){
        double sum = 0.0;
        for (int i = 0; i < brojVraboteni; ++i) {
            if (*(vrabotenii[i]) == emp) {
                sum += vrabotenii[i]->plata();
            }
        }return sum;
    }void pecatiRabotnici(){
        int kPlata, kSat, kFrilanceri;
        kPlata = kSat = kFrilanceri = 0;
        for (int i = 0; i < brojVraboteni; ++i) {
            SalaryEmployee *sEm = dynamic_cast<SalaryEmployee *>(vrabotenii[i]);
            if (sEm != nullptr) {
                kPlata++;
            }
            HourlyEmployee *hEm = dynamic_cast<HourlyEmployee *>(vrabotenii[i]);
            if (hEm != nullptr) {
                kSat++;
            }
            Freelancer *fEm = dynamic_cast<Freelancer *>(vrabotenii[i]);
            if (fEm != nullptr) {
                kFrilanceri++;
            }
        }
        cout << "Vo kompanijata " << imee << " rabotat:" << endl;
        cout << "Salary employees: " << kPlata << endl;
        cout << "Hourly employees: " << kSat << endl;
        cout << "Freelancers: " << kFrilanceri << endl;
    }
};

int main() {

    char name[50];
    cin >> name;
    Company c(name);

    int n;
    cin >> n;

    char employeeName[50];
    int age;
    int experience;
    int type;

    for (int i=0; i <n; ++i) {
        cin >> type;
        cin >> employeeName >> age >> experience;

        if (type == 1) {
            int basicSalary;
            cin >> basicSalary;
            c += new SalaryEmployee(employeeName, age, experience, basicSalary);
        }

        else if (type == 2) {
            int hoursWorked;
            int hourlyPay;
            cin >> hoursWorked >> hourlyPay;
            c += new HourlyEmployee(employeeName, age, experience, hoursWorked, hourlyPay);
        }

        else {
            int numProjects;
            cin >> numProjects;
            double projects[10];
            for (int i=0; i < numProjects; ++i) {
                cin >> projects[i];
            }
            c += new Freelancer(employeeName, age, experience, numProjects, projects);
        }
    }

    c.pecatiRabotnici();
    cout << "Vkupnata plata e: " << c.vkupnaPlata() << endl;
    Employee * emp = new HourlyEmployee("Petre_Petrov",31,6,340,80);
    cout << "Filtriranata plata e: " << c.filtriranaPlata(emp);

    delete emp;
}
