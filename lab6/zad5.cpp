#include<iostream>
#include<cstring>

using namespace std;

class Ekipa{
protected:
    char ime[15];
    int poraz;
    int pobedi;
public:
   Ekipa(char *ime="",int pobedi=0,int poraz=0){
        strcpy(this->ime,ime);
        this->poraz=poraz;
        this->pobedi=pobedi;
    }void pecati(){
        cout<<"Ime: "<<ime<<" Pobedi: "<<pobedi<<" Porazi: "<<poraz;
    }
};

class FudbalskaEkipa: public Ekipa{
private:
    int crveni;
    int zolti;
    int nereseni;

public:
    FudbalskaEkipa(char *ime,int pobedi,int poraz,int crveni=0,int zolti=0,int nereseni=0):Ekipa(ime,pobedi,poraz){
        this->crveni=crveni;
        this->zolti=zolti;
        this->nereseni=nereseni;
    }void pecati(){
        Ekipa::pecati();
        cout << " Nereseni: " << nereseni << " Poeni: " << pobedi * 3 + nereseni;
    }
};

int main(){
    char ime[15];
    int pob,por,ck,zk,ner;
    cin>>ime>>pob>>por>>ck>>zk>>ner;
    FudbalskaEkipa f1(ime,pob,por,ck,zk,ner);
    f1.pecati();
    return 0;
}
