#include<iostream>
#include<cstring>
#include<ctype.h>
using namespace std;

class BadInputException{
private:
    char* momentalnaOcenka;
public:
    BadInputException(const char* momentalnaOcenka){
        this->momentalnaOcenka = new char[strlen(momentalnaOcenka) + 1];
        strcpy(this->momentalnaOcenka, momentalnaOcenka);
    }~BadInputException(){
        delete[] momentalnaOcenka;
    }void correctTheGrade(){
        int digitCounter = 0;
        for (int i = 0; i < strlen(momentalnaOcenka); i++){
            if (isdigit(momentalnaOcenka[i])){
                digitCounter++;
            }
        }int newLen = strlen(momentalnaOcenka) - digitCounter;
        char* temp = new char[newLen + 1];
        for (int i = 0, j = 0; i < strlen(momentalnaOcenka); i++){
            if (!isdigit(momentalnaOcenka[i])){
                temp[j++] = momentalnaOcenka[i];
            }
        }delete[] momentalnaOcenka;
        momentalnaOcenka = temp;
    }const char* getCorrectedGrade(){
        correctTheGrade();
        return momentalnaOcenka;
    }
    void msg(){
        cout << "Greshna opisna ocenka" << endl;
    }
};

class StudentKurs{
protected:
    char ime[30];
    int ocenka;
    bool daliUsno;
    static const int MINOCENKA = 6;
    static int MAX;
    void copy(const StudentKurs& s){
        strcpy(this->ime,s.ime);
        this->ocenka = s.ocenka;
        this->daliUsno = s.daliUsno;
    }
public:
    StudentKurs(const char* ime = "",int ocenka = 0){
        strcpy(this->ime,ime);
        this->ocenka = ocenka;
        this->daliUsno = false;
    }StudentKurs(const StudentKurs& s){
        copy(s);
    }StudentKurs& operator= (const StudentKurs& s){
        if (this != &s){
            copy(s);
        }return *this;
    }static void setMAX(int n){
        MAX = n;
    }static int getMAX(){
        return MAX;
    }static int getMINOCENKA(){
        return MINOCENKA;
    }const char* getName(){
        return ime;
    }virtual int getOcenka(){
        return ocenka;
    }bool getDaliUsno(){
        return daliUsno;
    }void print(ostream& out){
        out << ime << " --- " << getOcenka() << endl;
    }friend ostream& operator << (ostream& out, StudentKurs& s){
        s.print(out);
        return out;
    }
};


class StudentKursUsno : public StudentKurs{
private:
    char *ocenkaUsno;
    void copy(const StudentKursUsno& su){
        StudentKurs::copy(su);
        this->ocenkaUsno = nullptr;
        this->daliUsno = su.daliUsno;
    }
public:
    StudentKursUsno(const char* ime = "",int ocenka = 0) : StudentKurs(ime, ocenka){
        this->ocenkaUsno = nullptr;
        this->daliUsno = true;
    }StudentKursUsno(const StudentKursUsno& su){
        copy(su);
    }StudentKursUsno& operator= (const StudentKursUsno& su){
        if (this != &su){
            delete[] ocenkaUsno;
            copy(su);
        }return *this;
    }~StudentKursUsno(){
        delete[] ocenkaUsno;
    }int getOcenka() override{
        if (strcmp(ocenkaUsno,"odlicen") == 0){
            if (ocenka + 2 <= MAX){
                return ocenka + 2;
            }else if (ocenka + 1 <= MAX){
                return ocenka + 1;
            } else {
                return ocenka;
            }
        }else if (strcmp(ocenkaUsno,"dobro") == 0){
            if (ocenka + 1 <= MAX){
                return ocenka + 1;
            } else {
                return ocenka;
            }
        }else if (strcmp(ocenkaUsno,"losho") == 0){
            if (ocenka - 1 >= MINOCENKA) {
                return ocenka - 1;
            } else {
                return ocenka;
            }
        }
    }bool checkForInvalidGrade(const char* grade){
        for(int i = 0; i < strlen(grade); i++){
            if (isdigit(grade[i])){
                return true;
            }
        }return false;
    }StudentKursUsno& operator += (const char* grade){
        if (checkForInvalidGrade(grade)){
            throw BadInputException(grade);
        }ocenkaUsno = new char[strlen(grade) + 1];
        strcpy(ocenkaUsno, grade);
    }
};

int StudentKurs::MAX = 10;

class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs** studenti, int broj){
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++){
            if (studenti[i]->getDaliUsno()){
                this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            }else{
                this->studenti[i]=new StudentKurs(*studenti[i]);
            }
        }this->broj = broj;
    }~KursFakultet(){
        for (int i=0;i < broj; i++){
            delete studenti[i];
        }
    }void pecatiStudenti(){
        cout << "Kursot " << naziv << " go polozile:" << endl;
        for (int i = 0; i < broj; i++){
            if (studenti[i]->getOcenka() >= studenti[i]->getMINOCENKA()){
                cout << *studenti[i];
            }
        }
    }void postaviOpisnaOcenka(char * ime, const char* opisnaOcenka){
        for (int i = 0; i < broj; i++){
            if (strcmp(studenti[i]->getName(), ime) == 0){
                *(dynamic_cast<StudentKursUsno*>(studenti[i])) += opisnaOcenka;
            }
        }
    }
};

int main(){

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0;i<n;i++){
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0;i<m;i++){
        cin>>ime>>opisna;
        try{
            programiranje.postaviOpisnaOcenka(ime,opisna);
        }catch(BadInputException& b){
            b.msg();
            programiranje.postaviOpisnaOcenka(ime,b.getCorrectedGrade());
        }
    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}
