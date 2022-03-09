#include <iostream>
#include <cstring>

using namespace std;

enum Tip{LINUX=0, UNIX, WINDOWS};

class OperativenSistem{
private:
    char *ime;
    float verzija;
    Tip op;
    float golemina;

    void copy(const OperativenSistem &o){
        ime= new char[strlen(o.ime)+1];
        strcpy(ime,o.ime);
        verzija=o.verzija;
        op=o.op;
        golemina=o.golemina;
    }

public:
    OperativenSistem(){
        this->ime= nullptr;
        this->verzija=0.0;
        this->op=(Tip) 0;
        this->golemina=0.0;
    }OperativenSistem(char *ime,float verzija, Tip op,float golemina){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->verzija=verzija;
        this->op=op;
        this->golemina=golemina;
    }OperativenSistem(const OperativenSistem &o){
        copy(o);
    }OperativenSistem& operator=(const OperativenSistem &o){
        if (this!=&o){
            copy(o);
        }return *this;
    }~OperativenSistem(){
        delete [] ime;
    }void pecati(){
        cout << "Ime: " << ime << " Verzija: " << verzija << " Tip: " << op << " Golemina:" << golemina << "GB"<< endl;
    }bool ednakviSe (const OperativenSistem &os){
        return ((strcmp(ime, os.ime) == 0) && verzija == os.verzija && op == os.op && golemina == os.golemina);
    }int sporediVerzija (const OperativenSistem &os){
        if (verzija == os.verzija) {
            return 0;
        }else if (verzija < os.verzija) {
            return -1;
        }else{
            return 1;
        }
    }bool istaFamilija(const OperativenSistem &sporedba){
        if ((strcmp(ime, sporedba.ime) == 0) && op == sporedba.op){
            return true;
        }else{
            return false;
        }
    }
};

class Repozitorium{
private:
    char ime[20];
    OperativenSistem *os;
    int broj;

    void copy(const Repozitorium &r){
        strcpy(ime,r.ime);
        broj=r.broj;
        os = new OperativenSistem[r.broj];
        for (int i = 0; i < r.broj; ++i) {
            os[i] = r.os[i];
        }
    }

public:
    Repozitorium (char *ime=""){
        strcpy(this->ime, ime);
        broj = 0;
        os = new OperativenSistem[broj];
    }Repozitorium (const Repozitorium &r){
        copy(r);
    }~Repozitorium(){
        delete[] os;
    }void pecatiOperativniSistemi() {
        cout << "Repozitorium: " << ime << endl;
        for (int i = 0; i < broj; ++i) {
            os[i].pecati();
        }
    }bool proveri (const OperativenSistem &op){
        for (int i = 0; i < broj; ++i) {
            if (os[i].istaFamilija(op) && os[i].sporediVerzija(op) == -1) {
                os[i] = op;
                return true;
            }
        }
        return false;
    }bool duplicat (const OperativenSistem &op){
        for (int i = 0; i < broj; ++i) {
            if (os[i].ednakviSe(op)) {
                return true;
            }
        }
        return false;
    }void izbrishi (const OperativenSistem &op) {
        if (duplicat(op)) {
            OperativenSistem *tempOs = new OperativenSistem[broj - 1];
            int brojac = 0;
            for (int i = 0; i < broj; ++i) {
                if (!(os[i].ednakviSe(op))) {
                    tempOs[brojac++] = os[i];
                }
            }
            delete[] os;
            os = tempOs;
            broj--;
        }
    } void dodadi(const OperativenSistem &op) {
        if (proveri(op)) {
        } else {
            OperativenSistem *tempOs = new OperativenSistem[broj + 1];
            for (int i = 0; i < broj; ++i) {
                tempOs[i] = os[i];
            }
            tempOs[broj] = op;
            delete[] os;
            os = tempOs;
            broj++;
        }
    }
};
int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}
