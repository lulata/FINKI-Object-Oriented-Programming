#include<iostream>
#include<cstring>
using namespace std;

class Zichara{
private:
    char *mesto;
    int cenaZaden;

    void copy (const Zichara &z){
        this->mesto = new char[strlen(z.mesto) + 1];
        strcpy(this->mesto, z.mesto);
        this->cenaZaden = z.cenaZaden;
    }
public:
    Zichara(char *mesto = "", int cenaZaden = 0){
        this->mesto = new char[strlen(mesto) + 1];
        strcpy(this->mesto, mesto);
        this->cenaZaden = cenaZaden;
    }~Zichara(){
        delete[] mesto;
    }Zichara (const Zichara &z){
        copy(z);
    }Zichara& operator= (const Zichara &z){
        if (this != &z){
            delete[] mesto;
            copy(z);
        }return *this;
    }int getPrice() const {
        return cenaZaden;
    }
};

class PlaninarskiDom{
private:
    char ime[15];
    int cenaPoSezona[2];
    char klasa;
    bool zicara;
    Zichara *pokZicara;

    void copy (const PlaninarskiDom &p){
        strcpy(this->ime, p.ime);
        for (int i = 0; i < 2; ++i) {
            this->cenaPoSezona[i] = p.cenaPoSezona[i];
        }this->klasa = p.klasa;
        this->zicara= p.zicara;
        this->pokZicara = p.pokZicara;
    }
public:
    PlaninarskiDom(){
        strcpy(this->ime, "");
        for (int i = 0; i < 2; ++i) {
            this->cenaPoSezona[i] = 0;
        }this->klasa = 'F';
        this->zicara= false;
        this->pokZicara = 0;
    }PlaninarskiDom(char *ime, int *cenaPoSezona, char klasa) { //ceni 12 el
        strcpy(this->ime, ime);
        for (int i = 0; i < 2; ++i) {
            this->cenaPoSezona[i] = cenaPoSezona[i];
        }this->klasa = klasa;
        this->zicara= false;
        this->pokZicara = 0;
    }~PlaninarskiDom(){}
    PlaninarskiDom (const PlaninarskiDom &p){
        copy(p);
    }PlaninarskiDom& operator= (const PlaninarskiDom & other){
        if (this != &other) {
            copy(other);
        }
        return *this;
    }PlaninarskiDom& operator-- (){
        if (klasa == 'F') {
            return *this;
        }
        klasa++;
        return *this;
    }friend ostream& operator<< (ostream& out, const PlaninarskiDom& pd);
    bool operator<= (char character){
        if (character >= 'A' && character <= 'F') {
            return (klasa >= character);
        }
        return false;
    }void presmetajDnevenPrestoj(int day, int month, int &priceForDay) const {
        if (day > 0 && day <= 31 && month > 0 && month <= 12) {
            if (month >= 4 && month < 9) {
                priceForDay = cenaPoSezona[0];
            } else {
                priceForDay = cenaPoSezona[1];
            }if (zicara) {
                priceForDay += pokZicara->getPrice();
            }
        } else {
            throw 1;
        }
    }void setZichara(Zichara &r){
        zicara = true;
        pokZicara = &r;
    }

};
ostream& operator<< (ostream& out, const PlaninarskiDom& pd){
    if (pd.zicara) {
        cout << pd.ime << " klasa:" << pd.klasa << " " << "so Zichara" << endl;
    } else {
        cout << pd.ime << " klasa:" << pd.klasa << " "<< endl;
    }return out;
}

int main(){

    PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

    //во следниот дел се вчитуваат информации за планинарскиот дом
    char imePlaninarskiDom[15],mestoZichara[30],klasa;
    int ceni[12];
    int dnevnakartaZichara;
    bool daliZichara;
    cin>>imePlaninarskiDom;
    for (int i=0;i<2;i++) cin>>ceni[i];
    cin>>klasa;
    cin>>daliZichara;

    //во следниот дел се внесуваат информации и за жичарата ако постои
    if (daliZichara) {
        cin>>mestoZichara>>dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom,ceni,klasa);
        Zichara r(mestoZichara,dnevnakartaZichara);
        pom.setZichara(r);
        p=pom;
    }
    else{
        PlaninarskiDom *pok=new PlaninarskiDom(imePlaninarskiDom,ceni,klasa);
        p=*pok;
    }

    //се намалува класата на планинарскиот дом за 2
    --p;
    --p;

    int cena;
    int den,mesec;
    cin>>den>>mesec;
    try{
        p.presmetajDnevenPrestoj(den,mesec,cena); //тука се користи функцијата presmetajDnevenPrestoj
        cout<<"Informacii za PlaninarskiDomot:"<<endl;
        cout<<p;
        if (p<='D')
            cout<<"Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";

        cout<<"Cenata za "<<den<<"."<<mesec<<" e "<<cena; //се печати цената за дадениот ден и месец
    }
    catch (int){
        cout<<"Mesecot ili denot e greshno vnesen!";
    }
}
