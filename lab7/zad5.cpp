#include<iostream>
#include <cstring>
using namespace std;


class ZicanInstrument{
protected:
    char ime[20];
    int brojZici;
    double cenaInstrument;

    void copy (const ZicanInstrument& z){
        strcpy(this->ime, z.ime);
        this->brojZici = z.brojZici;
        this->cenaInstrument = z.cenaInstrument;
    }
public:
    ZicanInstrument(char *ime = "", int brojZici = 0, int cenaInstrument = 0){
        strcpy(this->ime, ime);
        this->brojZici = brojZici;
        this->cenaInstrument = cenaInstrument;
    }
    ZicanInstrument(const ZicanInstrument& other){
        copy(other);
    }ZicanInstrument& operator= (const ZicanInstrument &other){
        if (this != &other) {
            copy(other);
        }
        return *this;
    }bool operator==(const ZicanInstrument *other){
        return (brojZici == other->brojZici);
    }friend ostream& operator<< (ostream &out, const ZicanInstrument& z){
        out << z.ime << " " << z.brojZici << " " << z.cenaInstrument << " ";
        return out;
    }
    virtual double cena() = 0;

};

class Mandolina : public ZicanInstrument {
private:
    char forma[20];

    void copy(const Mandolina &m){
        ZicanInstrument::copy(m);
        strcpy(this->forma, m.forma);
    }

public:
    Mandolina(char *ime = "", int brojZici = 0, int cenaInstrument = 0, char *forma="") : ZicanInstrument(ime,brojZici,cenaInstrument) {
        strcpy(this->forma, forma);
    }Mandolina(const Mandolina &m){
        copy (m);
    }Mandolina& operator= (const Mandolina& m){
        if (this != &m) {
            copy(m);
        }return *this;
    }double cena() override{
        if (strcmp(forma, "Neapolitan") == 0) {
            cenaInstrument += cenaInstrument * 0.15;
        }return cenaInstrument;
    }friend ostream& operator<< (ostream& out, Mandolina& m){
        out << static_cast<ZicanInstrument &>(m);
        out << m.forma;
        return out;
    }
};

class Violina  : public ZicanInstrument {
private:
    double golemina;

    void copy(const Violina &v){
        ZicanInstrument::copy(v);
        this->golemina = v.golemina;
    }

public:
    Violina(char *ime = "", int brojZici = 0, int cenaInstrument = 0, double golemina = 0.0) : ZicanInstrument(ime, brojZici, cenaInstrument) {
        this->golemina = golemina;
    }Violina (const Violina& other){
        copy(other);
    }Violina &operator=(const Violina &other){
        if (this != &other) {
            copy(other);
        }
        return *this;
    }double cena() override{
        if (golemina == 0.25) {
            cenaInstrument += cenaInstrument * 0.1;
        } else if (golemina == 1.00) {
            cenaInstrument += cenaInstrument * 0.2;
        }
        return cenaInstrument;
    }friend ostream& operator<< (ostream& out, Violina& v){
        out << static_cast<ZicanInstrument &>(v);
        out << v.golemina;
        return out;
    }
};

void pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **i, int n){
    for (int j = 0; j < n; ++j) {
        if (zi == i[j]) {
            cout << i[j]->cena() << endl;
        }
    }
}

int main() {
    char ime[20];
    int brojZici;
    float cena;
    char forma[20];
    cin >> ime >> brojZici >> cena >> forma;
    Mandolina m(ime, brojZici, cena, forma);
    int n;
    cin >> n;
    ZicanInstrument **zi = new ZicanInstrument*[2 * n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> brojZici >> cena >> forma;
        zi[i] = new Mandolina(ime, brojZici, cena, forma);
    }
    for(int i = 0; i < n; ++i) {
        float golemina;
        cin >> ime >> brojZici >> cena >> golemina;
        zi[n + i] = new Violina(ime, brojZici, cena, golemina);
    }
    pecatiInstrumenti(m, zi, 2 * n);
    for(int i = 0; i < 2 * n; ++i) {
        delete zi[i];
    }
    delete [] zi;
    return 0;
}
