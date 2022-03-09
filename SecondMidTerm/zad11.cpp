#include<iostream>
#include<cstring>
using namespace std;

class Delo{
private:
    char ime[50];
    int god;
    char drzava[50];
    void copy(const Delo& d){
        strcpy(this->ime, d.ime);
        this->god = d.god;
        strcpy(this->drzava, d.drzava);
    }
public:
    Delo(const char *ime = "", int god = 2000, const char *drzava = ""){
        strcpy(this->ime, ime);
        this->god = god;
        strcpy(this->drzava, drzava);
    }Delo(const Delo& d){
        copy(d);
    }Delo& operator= (const Delo& d){
        if (this != &d) {
            copy(d);
        }return *this;
    }bool operator== (const Delo& d){
        return (strcmp(this->ime, d.ime) == 0);
    }bool operator== (char* d){
        return (strcmp(this->drzava, d) == 0);
    }const char* getIme(){
        return ime;
    }const char* getCountryOrigin(){
        return drzava;
    }int getYear(){
        return god;
    }void setName(const char* n){
        strcpy(this->ime, n);
    }void setCountryOrigin(const char* n){
        strcpy(this->drzava, n);
    }void setYear(int n){
        this->god = n;
    }
};

class Pretstava{
protected:
    Delo delo;
    int brProdaeni;
    char datum[15];
    void copy(const Pretstava& p){
        this->delo = p.delo;
        this->brProdaeni = p.brProdaeni;
        strcpy(this->datum, p.datum);
    }
public:
    Pretstava(const Delo& delo = Delo(), int brProdaeni = 0, const char* datum = ""){
        this->delo = delo;
        this->brProdaeni = brProdaeni;
        strcpy(this->datum, datum);
    }
    Pretstava(const Pretstava& p){
        copy(p);
    }Pretstava& operator= (const Pretstava& p){
        if (this != &p) {
            copy(p);
        }return *this;
    }void setDelo(Delo &delo){
        this->delo = delo;
    }Delo& getDelo(){
        return delo;
    }int yearToCentury(Delo& d){
        if (d.getYear() <= 100){
            return 1;
        }else if (d.getYear() % 100 == 0){
            return d.getYear()/ 100;
        }else{
            return d.getYear()/ 100 + 1;
        }
    }virtual int cena(){
        int m, n;
        m = n = 0;
        int vek = yearToCentury(delo);
        if (vek == 20 || vek == 21) {
            m = 50;
        } else if (vek == 19) {
            m = 75;
        }else if (vek < 19) {
            m = 100;
        }if (delo == "Italija") {
            n = 100;
        } else if (delo == "Rusija") {
            n = 150;
        } else {
            n = 80;
        }return m + n;
    }int getNumSoldTickets(){
        return brProdaeni;
    }
};

class Opera : public Pretstava {
private:
public:
    Opera(const Delo& delo = Delo(), int brProdaeni = 0, const char* datum = "") : Pretstava(delo,brProdaeni,datum){}
    Opera(const Opera& o){
        copy(o);
    }Opera& operator= (const Opera& o){
        if (this != &o) {
            copy(o);
        }return *this;
    }
};

class Balet : public Pretstava {
private:
    static int dopolnitelnaCena;

    void copy(const Opera &o){
        Pretstava::copy(o);
    }void copy(const Balet &b){
        Pretstava::copy(b);
    }
public:
    Balet(const Delo& delo = Delo(), int brProdaeni = 0, const char* datum = "") : Pretstava(delo,brProdaeni,datum){}
    Balet(const Balet& b){
        copy(b);
    }Balet& operator= (const Balet& b){
        if (this != &b) {
            copy(b);
        }return *this;
    }static void setCenaBalet(int n){
        dopolnitelnaCena = n;
    }int cena() override{
        return Pretstava::cena() + dopolnitelnaCena;
    }
};
int Balet::dopolnitelnaCena = 150;

int prihod(Pretstava **prestavi, int n){
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += prestavi[i]->cena() * prestavi[i]->getNumSoldTickets();
    }return sum;
}

int brojPretstaviNaDelo (Pretstava **prestavi, int n, Delo& d){
    int counter = 0;
    for (int i = 0; i < n; ++i) {
        if (prestavi[i]->getDelo() == d) {
            counter++;
        }
    }return counter;
}

Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}

int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}
