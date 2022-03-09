#include<iostream>
#include<cstring>
#include<ctype.h>

using namespace std;

class Transport{
protected:
    char *destinacija;
    int cena;
    int rastojanie;

    void copy(const Transport &t){
        this->destinacija=new char[strlen(t.destinacija)+1];
        strcpy(this->destinacija,t.destinacija);
        this->cena=t.cena;
        this->rastojanie=t.rastojanie;
    }

public:
    Transport(char *destinacija="",int cena=0,int rastojanie=0){
        this->destinacija=new char[strlen(destinacija)+1];
        strcpy(this->destinacija,destinacija);
        this->cena=cena;
        this->rastojanie=rastojanie;
    }Transport(const Transport &t){
        copy(t);
    }Transport& operator=(const Transport &t){
        if(this!=&t){
            delete [] destinacija;
            copy(t);
        }return *this;
    }~Transport(){
        delete [] destinacija;
    }virtual float cenaTransport(){
        return cena;
    } bool operator< (const Transport& t){
        return this->rastojanie < t.rastojanie;
    }friend void pecatiPoloshiPonudi(Transport **t, int n, Transport &newT);
};

class AvtomobilTransport: public  Transport{
protected:
    bool sofer;

    void copy(const AvtomobilTransport &a){
        Transport::copy(a);
        this->sofer=a.sofer;
    }

public:
    AvtomobilTransport(char *destinacija="",int cena=0,int rastojanie=0, bool  sofer=false): Transport(destinacija,cena,rastojanie){
        this->sofer=sofer;
    }AvtomobilTransport(const AvtomobilTransport &a){
        copy(a);
    }AvtomobilTransport& operator=(const AvtomobilTransport &a){
        if(this!=&a){
            delete [] destinacija;
            copy(a);
        }return *this;
    }virtual float cenaTransport() override{
        if (sofer){
            return cena*1.2;
        }else{
            return cena;
        }
    }
};

class KombeTransport: public Transport{
protected:
    int brojPatnici;

    void copy(const KombeTransport &k){
        Transport::copy(k);
        this->brojPatnici=k.brojPatnici;
    }

public:
    KombeTransport(char *destinacija="",int cena=0,int rastojanie=0, int  brojPatnici=0): Transport(destinacija,cena,rastojanie){
     this->brojPatnici=brojPatnici;
    }KombeTransport(const KombeTransport &k){
        copy(k);
    }KombeTransport& operator=(const KombeTransport &k){
        if(this!=&k){
            delete [] destinacija;
            copy(k);
        }return *this;
    }virtual float cenaTransport() override{
        return cena-(brojPatnici*200);
    }
};

void bubbleSort(Transport **t, int n){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (!(*t[j] < *t[j + 1])) {
                Transport *temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;
            }
        }
    }
}

void pecatiPoloshiPonudi(Transport **t, int n, Transport &newT){
    int counter = 0;
    for (int i = 0; i < n; ++i) {
        if (t[i]->cenaTransport() > newT.cenaTransport()) {
            counter++;
        }
    }Transport **temp = new Transport *[counter];
    for (int i = 0, j = 0; i < n; ++i) {
        if (t[i]->cenaTransport() > newT.cenaTransport()) {
            temp[j++] = t[i];
        }
    }bubbleSort(temp, counter);
    for (int i = 0; i < counter; ++i) {
        cout << temp[i]->destinacija << " " << temp[i]->rastojanie << " " << temp[i]->cenaTransport() << endl;
    }
}

int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
