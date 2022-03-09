#include<iostream>
#include<cstring>
using namespace std;

class Rabotnik{
private:
    char ime[30];
    char prezime[30];
    int plata;
public:
    Rabotnik(){}
    Rabotnik(char *ime,char *prezime, int plata){
        strcpy(this->ime,ime);
        strcpy(this->prezime,prezime);
        this->plata=plata;
    }int getPlata(){
        return plata;
    }void pecati(){
        cout<<ime<<" "<<prezime<<" "<<plata;
    }
};

class Fabrika{
private:
    Rabotnik r[100];
    int brRab;
public:
    Fabrika(){}
    Fabrika(Rabotnik r, int brRab){
        *this->r=r;
        this->brRab=brRab;
    }int pecatiSoPlata(int plata){
        if(r->getPlata()>=plata){
            r->pecati();
            cout<<endl;
        }
    }void pecatiRaboteni(){
        r->pecati();
    }
};

int zad5(){
    int n,mplata;
    cin>>n;
    Fabrika fabriki[100];

    for(int i=0;i<n;i++){
        int plata;
        char ime[30],prezime[30];
        cin>>ime;
        cin>>prezime;
        cin>>plata;
         Rabotnik rab(ime, prezime, plata);

        fabriki[i]= Fabrika(rab,n);
    }cin>>mplata;
    cout<<"Site vraboteni:"<<endl;
    for (int i = 0; i < n;i++) {
        fabriki[i].pecatiRaboteni();
        cout<<endl;
    }
    cout<<"Vraboteni so plata povisoka od "<<mplata<<" : "<<endl;
    for (int i = 0; i < n; ++i) {
        fabriki[i].pecatiSoPlata(mplata);
    }

    return 0;
}
