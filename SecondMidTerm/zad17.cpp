#include <iostream>
#include <cstring>
using namespace std;

class FudbalskaEkipa{
protected:
    char ime[100];
    int brPoeni[10];
public:
    void copy(const FudbalskaEkipa& f){
        strcpy(this->ime, f.ime);
        for (int i = 0; i < 10; ++i) {
            this->brPoeni[i] = f.brPoeni[i];
        }
    }FudbalskaEkipa(const char* ime = "", const int* brPoeni = nullptr){
        strcpy(this->ime, ime);
        for (int i = 0; i < 10; ++i) {
            this->brPoeni[i] = brPoeni[i];
        }
    }FudbalskaEkipa(const FudbalskaEkipa& f){
        copy(f);
    }FudbalskaEkipa& operator= (const FudbalskaEkipa& f){
        if (this != &f) {
            copy(f);
        }return *this;
    }FudbalskaEkipa& operator+= (int gol){
        int temp[10];
        int j = 0;
        for (int i = 1; i < 10; ++i) {
            temp[j++] = brPoeni[i];
        }temp[j] = gol;
        for (int i = 0; i < 10; ++i) {
            brPoeni[i] = temp[i];
        }
    }bool operator> (FudbalskaEkipa& other){
        return this->uspeh() > other.uspeh();
    }virtual float uspeh() = 0;
    virtual void print(ostream &out) = 0;
    friend ostream& operator<< (ostream& out, FudbalskaEkipa& f){
        f.print(out);
        return out;
    }

};

class Klub : public FudbalskaEkipa{
private:
    char imeKlub[100];
    int brTituli;
    void copy(const Klub& k){
        FudbalskaEkipa::copy(k);
        strcpy(this->imeKlub, k.imeKlub);
        this->brTituli = k.brTituli;
    }
public:
    Klub(const char* ime = "", const int* brPoeni = nullptr, const char *imeKlub = "",
         int brTituli = 0) : FudbalskaEkipa(ime, brPoeni) {
        strcpy(this->imeKlub, imeKlub);
        this->brTituli = brTituli;
    }Klub(const Klub& k){
        copy(k);
    }Klub& operator= (const Klub& k){
        if (this != &k) {
            copy(k);
        }return *this;
    }float uspeh() override {
        int sum = 0;
        for (int i = 0; i < 10; ++i) {
            sum += brPoeni[i];
        }return 3 * (float)sum + brTituli * 1000;
    }void print(ostream &out) override {
        out << imeKlub << endl;
        out << ime << endl;
        out << uspeh() << endl;
    }
};

class Reprezentacija : public FudbalskaEkipa {
private:
    char drzava[100];
    int brNastani;
    void copy(const Reprezentacija& r){
        FudbalskaEkipa::copy(r);
        strcpy(this->drzava, r.drzava);
        this->brNastani = r.brNastani;
    }
public:
    Reprezentacija(const char* ime = "", const int* brPoeni = nullptr, const char *drzava = "",
                   int brNastani = 0) : FudbalskaEkipa(ime, brPoeni){
        strcpy(this->drzava, drzava);
        this->brNastani = brNastani;
    }
    Reprezentacija(const Reprezentacija& r){
        copy(r);
    }Reprezentacija& operator= (const Reprezentacija& r){
        if (this != &r) {
            copy(r);
        }return *this;
    }float uspeh() override {
        int sum = 0;
        for (int i = 0; i < 10; ++i) {
            sum += brPoeni[i];
        }return 3 * (float) sum + brNastani * 50;
    }void print(ostream &out) override {
        out << drzava << endl;
        out << ime << endl;
        out << uspeh() << endl;
    }

};

void najdobarTrener(FudbalskaEkipa **fe, int num){
    int maxIndex = 0;
    for (int i = 1; i < num; ++i) {
        if (!(*fe[maxIndex] > *fe[i])) {
            maxIndex = i;
        }
    }
    cout << *fe[maxIndex];
}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}
