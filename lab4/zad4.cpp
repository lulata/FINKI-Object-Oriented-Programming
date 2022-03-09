#include<iostream>
#include <cstring>
using namespace std;

enum zanr{akcija=0,komedija,drama};

class Film {
private:
    char *ime;
    int mem;
    zanr z;
public:
    Film(char *ime="",int mem=0,zanr z=(zanr) 0){
        this->ime= new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->mem=mem;
        this->z=z;
    }Film(const Film &f){
        this->ime= new char[strlen(f.ime)+1];
        strcpy(this->ime,f.ime);
        this->mem=f.mem;
        this->z=f.z;
    }~Film() {
        delete [] ime;
    }Film& operator=(const Film &f){
        if(this!=&f){
            delete [] ime;
            this->ime= new char[strlen(f.ime)+1];
            strcpy(this->ime,f.ime);
            this->mem=f.mem;
            this->z=f.z;
        }return *this;
    }void pecati(){
        cout << mem << "MB-" << "\"" << ime << "\"" << endl;
    }int getMem() const {
        return mem;
    }int getZarn() const {
        return z;
    }
};

class DVD{
private:
    Film filmoj[5];
    int brfilm;
    int memDVD;
public:
    DVD(int memDVD=0){
        brfilm=0;
        this->memDVD=memDVD;
    }DVD(const DVD &d){
        this->brfilm=d.brfilm;
        this->memDVD=d.memDVD;
        for (int i = 0; i < d.brfilm; ++i) {
            filmoj[i]=d.filmoj[i];
        }
    }DVD& operator=(const DVD &d){
        if(this!=&d){
            this->brfilm=d.brfilm;
            this->memDVD=d.memDVD;
            for (int i = 0; i < d.brfilm; ++i) {
                filmoj[i]=d.filmoj[i];
            }
        }return *this;
    }~DVD(){}
    bool isThereEnoguhStorage (const Film &f){
        int brojac = 0;
        for (int i = 0; i < brfilm; ++i) {
            brojac += filmoj[i].getMem();
        }
        return ((brojac + f.getMem()) <= memDVD);
    }void dodadiFilm (Film& f){
        if (brfilm < 5){
            if (isThereEnoguhStorage(f)) {
                filmoj[brfilm] = f;
                brfilm++;
            }
        }
    }void pecatiFilmoviDrugZanr(zanr z){
        for (int i = 0; i < brfilm; ++i) {
            if (filmoj[i].getZarn() != z) {
                filmoj[i].pecati();
            }
        }
    }float procentNaMemorijaOdZanr(zanr z){
        int total = 0;
        int zafmem = 0;
        for (int i = 0; i < brfilm; ++i) {
            if (filmoj[i].getZarn() == z) {
                total += filmoj[i].getMem();
            }
            zafmem += filmoj[i].getMem();
        }
        return (float) 100 * total / zafmem;
    }Film getFilm (int i) {
        return filmoj[i];
    }int getBroj (){
        return brfilm;
    }
};


int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, memorija, kojzanr;
    char ime[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Film ======" << endl;
        cin >> ime;
        cin >> memorija;
        cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
        Film f(ime, memorija, (zanr) kojzanr);
        f.pecati();
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < n; i++)
            (omileno.getFilm(i)).pecati();
    } else if (testCase == 3) {
        cout << "===== Testiranje na metodot dodadiFilm() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getFilm(i)).pecati();
    } else if (testCase == 4) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    } else if (testCase == 5) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    } else if (testCase == 6){
        cout<<"===== Testiranje na metodot procentNaMemorijaOdZanr() od klasata DVD =====" <<endl;
        DVD omileno(40);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        cout<<"Procent na filmovi od dadeniot zanr iznesuva: "<<omileno.procentNaMemorijaOdZanr((zanr) kojzanr)<<"%\n";

    }

    return 0;
}
