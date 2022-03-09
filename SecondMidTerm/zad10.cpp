#include<iostream>
#include<cstring>
#include<ctype.h>

using namespace std;

class NegativnaVrednost{
public:
    void msg(){
        cout << "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!" << endl;
    }
};

class Oglas{
private:
    char naslov[50];
    char kategorija[30];
    char desc[100];
    float cena;

    void copy(const Oglas& other){
        strcpy(this->naslov, other.naslov);
        strcpy(this->kategorija, other.kategorija);
        strcpy(this->desc, other.desc);
        this->cena = other.cena;
    }
public:
    Oglas(char *naslov = "", char *kategorija = "", char *desc = "", float cena = 0.0){
        strcpy(this->naslov, naslov);
        strcpy(this->kategorija, kategorija);
        strcpy(this->desc, desc);
        this->cena = cena;
    }Oglas(const Oglas& other){
        copy(other);
    }Oglas& operator= (const Oglas& other){
        if (this != &other) {
            copy(other);
        }return *this;
    }bool operator> (const Oglas& other){
        return this->cena > other.cena;
    }friend ostream& operator<< (ostream& out, Oglas& o){
        out << o.naslov << endl;
        out << o.desc << endl;
        out << o.cena << " evra" << endl;
        out << endl;
        return out;
    }float getPrice(){
        return cena;
    }
    const char* getCategory(){
        return kategorija;
    }
};

class Oglasnik{
    char imeOglasnik[20];
    Oglas *oglasi;
    int brOglasi;
    void copy(const Oglasnik& other){
        strcpy(this->imeOglasnik, other.imeOglasnik);
        this->brOglasi = other.brOglasi;
        this->oglasi = new Oglas[other.brOglasi];
        for (int i = 0; i < other.brOglasi; ++i) {
            this->oglasi[i] = other.oglasi[i];
        }
    }
public:
    Oglasnik(const char* imeOglasnik = ""){
        strcpy(this->imeOglasnik, imeOglasnik);
        oglasi = nullptr;
        brOglasi = 0;
    }Oglasnik (const Oglasnik& other){
        copy(other);
    }~Oglasnik(){
        delete[] oglasi;
    }Oglasnik& operator= (const Oglasnik& other){
        if (this != &other) {
            delete[] oglasi;
            copy(other);
        }return *this;
    }Oglasnik& operator+= (Oglas& newOglas){
        if (newOglas.getPrice() < 0) {
            throw NegativnaVrednost();
        }else {
            Oglas *temp = new Oglas[brOglasi + 1];
            for (int i = 0; i < brOglasi; ++i) {
                temp[i] = oglasi[i];
            }temp[brOglasi++] = newOglas;
            delete[] oglasi;
            oglasi = temp;
            return *this;
        }
    }friend ostream& operator<< (ostream& out, Oglasnik& o){
        out << o.imeOglasnik << endl;
        for (int i = 0; i < o.brOglasi; ++i) {
            cout << o.oglasi[i];
        }return out;
    }void oglasiOdKategorija(const char *k){
        for (int i = 0; i < brOglasi; ++i) {
            if (strcmp(oglasi[i].getCategory(), k) == 0) {
                cout << oglasi[i];
            }
        }
    }void najniskaCena(){
        Oglas temp(oglasi[0]);
        for (int i = 1; i < brOglasi; ++i) {
            if (temp > oglasi[i]) {
                temp = oglasi[i];
            }
        }cout << temp;
    }
};

int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            }catch (NegativnaVrednost& e){
                e.msg();
            }
        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            }catch (NegativnaVrednost& e){
                e.msg();
            }
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            }catch (NegativnaVrednost& e){
                e.msg();
            }
        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            }catch (NegativnaVrednost& e){
                e.msg();
            }
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try {
                ogl += o;
            }catch (NegativnaVrednost& e){
                e.msg();
            }
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}
