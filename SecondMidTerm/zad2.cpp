#include <iostream>
#include <cstring>
using namespace std;

class Vozac{
protected:
    char ime[100];
    int god;
    int brTrki;
    bool veterinar;

    void copy(const Vozac& v){
        strcpy(this->ime, v.ime);
        this->god = v.god;
        this->brTrki = v.brTrki;
        this->veterinar = v.veterinar;
    }
public:
    Vozac(const char* ime = "", int god = 18, int brTrki = 0, bool veterinar = false){
        strcpy(this->ime, ime);
        this->god = god;
        this->brTrki = brTrki;
        this->veterinar = veterinar;
    }Vozac(const Vozac& v){
        copy(v);
    }friend ostream& operator<< (ostream& out, Vozac& v){
        out << v.ime << endl;
        out << v.god << endl;
        out << v.brTrki << endl;
        if(v.veterinar)
        {
            out << "VETERAN" << endl;
        }
        return out;
    }
    virtual float profitPerRace() = 0;
    virtual float danok() = 0;
    bool operator== (Vozac& v){
        return this->profitPerRace() == v.profitPerRace();
    }
};

class Avtomobilist : public Vozac{
private:
    float cenaKola;
    void copy(const Avtomobilist& a){
        Vozac::copy(a);
        this->cenaKola = a.cenaKola;
    }
public:
    Avtomobilist(const char* ime = "", int god = 18, int brTrki = 0, bool veterinar = false, float cenaKola = 0.0) : Vozac(ime,god,brTrki,veterinar){
        this->cenaKola = cenaKola;
    }Avtomobilist(const Avtomobilist& a){
        copy(a);
    }Avtomobilist& operator= (const Avtomobilist& a){
        if (this != &a){
            copy(a);
        }return *this;
    }float profitPerRace() override{
        return cenaKola / 5.0;
    }float danok(){
        if (brTrki > 10){
            return profitPerRace() * 0.15;
        }return profitPerRace() * 0.1;
    }
};

class Motociklist : public Vozac{
private:
    int motor;
    void copy(const Motociklist& m){
        Vozac::copy(m);
        this->motor = m.motor;
    }
public:
    Motociklist(const char* ime = "", int god = 18, int brTrki = 0, bool veterinar = false, int motor = 0) : Vozac(ime,god,brTrki,veterinar){
        this->motor = motor;
    }Motociklist(const Motociklist& m){
        copy(m);
    }
    Motociklist& operator= (const Motociklist& other){
        if (this != &other){
            copy(other);
        }
        return *this;
    }float profitPerRace() override{
        return motor * 20;
    }
    float danok(){
        if (veterinar){
            return profitPerRace() * 0.25;
        }return profitPerRace() * 0.2;
    }
};

int soIstaZarabotuvachka(Vozac **vozaci, int brVozaci, Vozac* v){
    int counter = 0;
    for (int i = 0; i < brVozaci; ++i) {
        if (*vozaci[i] == *v){
            counter++;
        }
    }
    return counter;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}
