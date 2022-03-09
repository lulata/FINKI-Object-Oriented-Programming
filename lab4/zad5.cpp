#include <iostream>
#include <cstring>

using namespace std;

//Vasiot kod tuka
class Pica{
private:
    char ime[15];
    int cena;
    char *sostojki;
    int popust;

    void copy(const Pica &p){
        strcpy(ime,p.ime);
        cena=p.cena;
        sostojki=new char [strlen(p.sostojki)+1];
        strcpy(sostojki,p.sostojki);
        popust=p.popust;
    }
public:
    Pica(char *ime="",int cena=0,char *sostojki="",int popust=0){
        strcpy(this->ime,ime);
        this->cena=cena;
        this->sostojki=new char [strlen(sostojki)+1];
        strcpy(this->sostojki,sostojki);
        this->popust=popust;
    }Pica(const Pica &p){
        copy(p);
    }Pica& operator=(const Pica &p){
        if (this!=&p){
            delete [] sostojki;
            copy(p);
        }return *this;
    }~Pica(){
        delete [] sostojki;
    }void pecati(){
        cout << ime << " - " << sostojki << ", " << cena;
    }bool istiSe(Pica &p){
        if(strcmp(sostojki,p.sostojki) == 0){
            return true;
        }else{
            return false;
        }
    }int getCena(){
        return cena;
    }int getPopust(){
        return popust;
    }
};

class Picerija{
private:
    char ime[15];
    Pica *pizza;
    int brpica;
public:
    Picerija(char *ime=""){
        strcpy(this->ime,ime);
        brpica=0;
        pizza=new Pica[brpica];
    }Picerija(const Picerija &pi){
        strcpy(this->ime,pi.ime);
        this->brpica=pi.brpica;
        this->pizza=new Pica[pi.brpica];
        for (int i = 0; i < brpica; ++i) {
            this->pizza[i]=pi.pizza[i];
        }
    }Picerija& operator=(const Picerija &pi){
        if(this!=&pi){
            strcpy(this->ime,pi.ime);
            this->brpica=pi.brpica;
            delete [] pizza;
            this->pizza=new Pica[pi.brpica];
            for (int i = 0; i < brpica; ++i) {
                this->pizza[i]=pi.pizza[i];
            }
        }return *this;
    }~Picerija(){
        delete [] pizza;
    }bool istaPica (Pica &p){
        for (int i = 0; i < brpica; ++i) {
            if (pizza[i].istiSe(p)) {
                return true;
            }
        }
        return false;
    }void dodadi(Pica &pi){
        if (!istaPica(pi)) {
            Pica *tempPizza = new Pica[brpica + 1];
            for (int i = 0; i < brpica; ++i) {
                tempPizza[i] = pizza[i];
            }
            tempPizza[brpica] = pi;
            delete[] pizza;
            pizza = tempPizza;
            brpica++;
        }
    }void piciNaPromocija(){
        for (int i = 0; i < brpica; ++i) {
            float cpopust;
            if (pizza[i].getPopust() > 0 && pizza[i].getPopust() < 100) {
                cpopust = pizza[i].getCena() - (pizza[i].getPopust() / 100.0 * pizza[i].getCena());
                pizza[i].pecati();
                cout << " " << cpopust << endl;
            }
        }
    }void setIme(char* imee){
        strcpy(ime, imee);
    }char *getIme(){
        return ime;
    }
};

int main () {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for(int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp,100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki,100);
        int popust;
        cin >> popust;
        Pica p(imp,cena,sostojki,popust);
        p1.dodadi(p);
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp,100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki,100);
    int popust;
    cin >> popust;
    Pica p(imp,cena,sostojki,popust);
    p2.dodadi(p);

    cout<<p1.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p1.piciNaPromocija();

    cout<<p2.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p2.piciNaPromocija();

    return 0;
}
