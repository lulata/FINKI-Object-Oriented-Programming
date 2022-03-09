#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

class NoCourseException{
private:
    int indeks;
public:
    NoCourseException(int indeks){
        this->indeks = indeks;
    }void msg(){
        cout << "Demonstratorot so indeks " << indeks << " ne drzi laboratoriski vezbi" << endl;
    }
};

class Kurs{
private:
    char ime[20];
    int krediti;
public:
    Kurs (char *ime,int krediti){
        strcpy(this->ime, ime);
        this->krediti = krediti;
    }Kurs (){
        strcpy(this->ime, "");
        krediti=0;
    }bool operator==(const char *ime) const{
        return strcmp(this->ime, ime) == 0;
    }char const * getIme()const{
        return ime;
    }void print ()const{
        cout << ime << " " << krediti << "ECTS";
    }
};

class Student{
private:
    int *ocenki;
    int brOcenki;

protected:
    int indeks;
    void copy(const Student& s){
        this->indeks = s.indeks;
        this->brOcenki = s.brOcenki;
        this->ocenki = new int[s.brOcenki];
        for (int i = 0; i < s.brOcenki; i++){
            this->ocenki[i] = s.ocenki[i];
        }
    }
    void deleteGrades(){
        delete[] ocenki;
    }
public:
    Student(int indeks = 000000,const int *ocenki = new int[0], int brOcenki = 0){
        this->indeks = indeks;
        this->brOcenki = brOcenki;
        this->ocenki = new int[brOcenki];
        for (int i = 0; i < brOcenki; i++){
            this->ocenki[i] = ocenki[i];
        }
    }Student(const Student &s){
        copy(s);
    }Student operator=(const Student &s){
        if (this!=&s) {
            delete [] ocenki;
            copy(s);
        }return *this;
    }~Student(){
        delete [] ocenki;
    }virtual int getPoints(){
        int counter = 0;
        for (int i = 0; i < brOcenki; ++i) {
            if (ocenki[i] > 5){
                counter++;
            }
        }return floor(100 / (float)brOcenki * (float)counter);
    }virtual void print(){
        cout << indeks << " ";
    }

};

class Predavach{
private:
    Kurs kursoj[10];
    int brKursoj;

protected:
    char *imePredavajne;
    void copy(const Predavach& p){
        this->brKursoj = p.brKursoj;
        for (int i = 0; i < p.brKursoj; i++){
            this->kursoj[i] = p.kursoj[i];
        }this->imePredavajne = new char[strlen(p.imePredavajne) + 1];
        strcpy(this->imePredavajne, p.imePredavajne);
    }
    void deleteNameOfLecturer(){
        delete[] imePredavajne;
    }
public:
    Predavach(const char *imePredavajne = "", Kurs *kursoj = new Kurs[0], int brKursoj = 0) {
        this->brKursoj = brKursoj;
        for (int i = 0; i < brKursoj; i++){
            this->kursoj[i] = kursoj[i];
        }this->imePredavajne = new char[strlen(imePredavajne) + 1];
        strcpy(this->imePredavajne, imePredavajne);
    }Predavach(const Predavach &p){
        copy(p);
    }Predavach operator=(const Predavach &p){
        if (this!=&p) {
            delete [] imePredavajne;
            copy(p);
        }return *this;
    }~Predavach(){
        delete[] imePredavajne;
    }int getCourses()const {
        return brKursoj;
    }char * const getNameOfLecturer()const{
        return imePredavajne;
    }Kurs operator[](int i) const {
        if (i < brKursoj && i >= 0) {
            return kursoj[i];
        }else{
            return Kurs();
        }
    }virtual void print() const  {
        cout << imePredavajne << " (";
        for (int i=0; i < brKursoj; i++){
            kursoj[i].print();
            if (i < brKursoj - 1){
                cout << ", ";
            }else{
                cout << ")";
            }
        }
    }
    int getNumCourses(){
        return brKursoj;
    }
};


class Demonstrator : public Student, public Predavach{
private:
    int brLab;
    void copy (const Demonstrator& d){
        Student::copy(d);
        Predavach::copy(d);
        this->brLab = d.brLab;
    }
public:
    Demonstrator(int indeks = 000000,const int *ocenki = new int[0], int brOcenki = 0,
                 const char *imePredavajne = "", Kurs *kursoj = new Kurs[0], int brKursoj = 0, int brLab = 0) :
            Student(indeks,ocenki,brOcenki), Predavach(imePredavajne,kursoj,brKursoj){
        this->brLab = brLab;
    }Demonstrator(const Demonstrator& d){
        copy(d);
    }Demonstrator& operator= (const Demonstrator& d){
        if (this != &d) {
            deleteGrades();
            deleteNameOfLecturer();
            copy(d);
        }return *this;
    }void print() override{
        cout << indeks << ": ";
        Predavach::print();
    }int getPoints() override {
        if (getNumCourses() == 0){
            throw NoCourseException(indeks);
        }return Student::getPoints() + (20 * brLab) / getNumCourses();
    }
};

Student &vratiNajdobroRangiran(Student **studenti, int n) {
    Student *bestRankedStudent = studenti[0];
    int bestSIndex, pointsOne, pointsTwo;
    bestSIndex = pointsOne = pointsTwo = 0;
    for (int i = 0; i < n; ++i) {
        try{
            pointsOne = bestRankedStudent->getPoints();
        }catch (NoCourseException& e){
            pointsOne = 0;
            e.msg();
        }try{
            pointsTwo = studenti[i]->getPoints();
        } catch (NoCourseException& e) {
            pointsTwo = 0;
            e.msg();
        }if (pointsOne < pointsTwo) {
            bestRankedStudent = studenti[i];
            bestSIndex = i;
        }
    }
    return *studenti[bestSIndex];
}

void pecatiDemonstratoriKurs(const char *kurs, Student **studenti, int n) {
    for (int i = 0; i < n; ++i) {
        Demonstrator *test = dynamic_cast<Demonstrator *>(studenti[i]);
        if (test) {
            for (int j = 0; j < test->getNumCourses(); ++j) {
                if ((*test)[i] == kurs) {
                    test->print();
                    cout << endl;
                    break;
                }
            }
        }
    }
}

int main(){

    Kurs kursevi[10];
    int indeks,brojKursevi, ocenki[20],ocenka,brojOcenki,tip,brojCasovi,krediti;
    char ime[20],imeIPrezime[50];

    cin>>tip;

    if (tip==1) //test class Demonstrator
    {
        cout<<"-----TEST Demonstrator-----"<<endl;
        cin>>indeks>>brojOcenki;
        for (int i=0;i<brojOcenki;i++){
            cin>>ocenka;
            ocenki[i]=ocenka;
        }
        cin>>imeIPrezime>>brojKursevi;
        for (int i=0;i<brojKursevi;i++){
            cin>>ime>>krediti;
            kursevi[i]=Kurs(ime,krediti);
        }
        cin>>brojCasovi;

        Demonstrator d(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
        cout<<"Objekt od klasata Demonstrator e kreiran";

    } else if (tip==2) //funkcija print vo Student
    {
        cout<<"-----TEST pecati-----"<<endl;
        cin>>indeks>>brojOcenki;
        for (int i=0;i<brojOcenki;i++){
            cin>>ocenka;
            ocenki[i]=ocenka;
        }

        Student s(indeks,ocenki,brojOcenki);
        s.print();

    } else if (tip==3) //funkcija getVkupnaOcenka vo Student
    {
        cout<<"-----TEST getVkupnaOcenka-----"<<endl;
        cin>>indeks>>brojOcenki;
        for (int i=0;i<brojOcenki;i++){
            cin>>ocenka;
            ocenki[i]=ocenka;
        }
        Student s(indeks,ocenki,brojOcenki);
        try {
            cout << "Broj na bodovi: " << s.getPoints() << endl;
        }catch (NoCourseException& e){
            e.msg();
        }

    } else if (tip==4) //funkcija getVkupnaOcenka vo Demonstrator
    {
        cout<<"-----TEST getVkupnaOcenka-----"<<endl;
        cin>>indeks>>brojOcenki;
        for (int i=0;i<brojOcenki;i++){
            cin>>ocenka;
            ocenki[i]=ocenka;
        }
        cin>>imeIPrezime>>brojKursevi;
        for (int i=0;i<brojKursevi;i++){
            cin>>ime>>krediti;
            kursevi[i]=Kurs(ime,krediti);
        }
        cin>>brojCasovi;

        Demonstrator d(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
        cout<<"Broj na bodovi: "<<d.getPoints()<<endl;

    } else if (tip==5) //funkcija print vo Demonstrator
    {
        cout<<"-----TEST pecati -----"<<endl;
        cin>>indeks>>brojOcenki;
        for (int i=0;i<brojOcenki;i++){
            cin>>ocenka;
            ocenki[i]=ocenka;
        }
        cin>>imeIPrezime>>brojKursevi;
        for (int i=0;i<brojKursevi;i++){
            cin>>ime>>krediti;
            kursevi[i]=Kurs(ime,krediti);
        }
        cin>>brojCasovi;

        Demonstrator d(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
        d.print();

    } else if (tip==6) //site klasi
    {
        cout<<"-----TEST Student i Demonstrator-----"<<endl;
        cin>>indeks>>brojOcenki;
        for (int i=0;i<brojOcenki;i++){
            cin>>ocenka;
            ocenki[i]=ocenka;
        }
        cin>>imeIPrezime>>brojKursevi;
        for (int i=0;i<brojKursevi;i++){
            cin>>ime>>krediti;
            kursevi[i]=Kurs(ime,krediti);
        }
        cin>>brojCasovi;

        Student *s=new Demonstrator(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
        s->print();
        cout<<"\nBroj na bodovi: "<<s->getPoints()<<endl;
        delete s;


    } else if (tip==7) //funkcija vratiNajdobroRangiran
    {
        cout<<"-----TEST vratiNajdobroRangiran-----"<<endl;
        int k, opt;
        cin>>k;
        Student **studenti=new Student*[k];
        for (int j=0;j<k;j++){
            cin>>opt; //1 Student 2 Demonstrator
            cin>>indeks>>brojOcenki;
            for (int i=0;i<brojOcenki;i++)
            {
                cin>>ocenka;
                ocenki[i]=ocenka;
            }
            if (opt==1){
                studenti[j]=new Student(indeks,ocenki,brojOcenki);
            }else{
                cin>>imeIPrezime>>brojKursevi;
                for (int i=0;i<brojKursevi;i++){
                    cin>>ime>>krediti;
                    kursevi[i]=Kurs(ime,krediti);
                }
                cin>>brojCasovi;
                studenti[j]=new Demonstrator(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
            }
        }
        Student& najdobar=vratiNajdobroRangiran(studenti,k);
        cout<<"Maksimalniot broj na bodovi e:"<<najdobar.getPoints();
        cout<<"\nNajdobro rangiran:";
        najdobar.print();

        for (int j=0;j<k;j++) delete studenti[j];
        delete [] studenti;
    } else if (tip==8) //funkcija pecatiDemonstratoriKurs
    {
        cout<<"-----TEST pecatiDemonstratoriKurs-----"<<endl;
        int k, opt;
        cin>>k;
        Student **studenti=new Student*[k];
        for (int j=0;j<k;j++){
            cin>>opt; //1 Student 2 Demonstrator
            cin>>indeks>>brojOcenki;
            for (int i=0;i<brojOcenki;i++)
            {
                cin>>ocenka;
                ocenki[i]=ocenka;
            }
            if (opt==1){
                studenti[j]=new Student(indeks,ocenki,brojOcenki);
            }else{
                cin>>imeIPrezime>>brojKursevi;
                for (int i=0;i<brojKursevi;i++)
                {
                    cin>>ime>>krediti;
                    kursevi[i]=Kurs(ime,krediti);
                }
                cin>>brojCasovi;
                studenti[j]=new Demonstrator(indeks,ocenki,brojOcenki,imeIPrezime,kursevi,brojKursevi,brojCasovi);
            }
        }
        char kurs[20];
        cin>>kurs;
        cout<<"Demonstratori na "<<kurs<<" se:"<<endl;
        pecatiDemonstratoriKurs (kurs,studenti,k);
        for (int j=0;j<k;j++) delete studenti[j];
        delete [] studenti;

    }


    return 0;
}

