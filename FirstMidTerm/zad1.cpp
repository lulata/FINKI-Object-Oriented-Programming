#include <iostream>
#include <cstring>

using namespace std;

enum tip{pop=0,rap,rok};

class Pesna{
private:
    char *ime;
    int min;
    tip tipmuz;

    void copy(const Pesna &p){
        this->ime=new char[strlen(p.ime)+1];
        strcpy(this->ime,p.ime);
        this->min=p.min;
        this->tipmuz=p.tipmuz;
    }

public:
    Pesna(char *ime="",int min=0,tip tipmuz=(tip) pop){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->min=min;
        this->tipmuz=tipmuz;
    }Pesna(const Pesna &p){
        copy(p);
    }Pesna& operator=(const Pesna &p){
        if (this!=&p){
            delete [] ime;
            copy(p);
        }return *this;
    }void pecati(){
        cout<<'"'<<ime<<'"'<<"-"<<min<<"min"<<endl;
    }~Pesna(){
        delete [] ime;
    }int getTip() {
        return tipmuz;
    }int getMin(){
        return min;
    }
};

class CD{
private:
    Pesna pesni[10];
    int broj;
    int maxmin;
    int zbir=0;

    void copy(const CD &c){
        this->broj=c.broj;
        this->maxmin=c.maxmin;
        for (int i = 0; i < c.broj; ++i) {
            this->pesni[i]=c.pesni[i];
        }
    }

public:
    CD(){}
    CD(int maxmin=0){
        this->broj=0;
        this->maxmin=maxmin;
    }~CD(){}
    Pesna getPesna(int i){
        return pesni[i];
    }int getBroj(){
        return broj;
    } void pecatiPesniPoTip(tip t){
        for(int i=0;i<broj;i++){
            if(pesni[i].getTip()==t){
                pesni[i].pecati();
            }
        }
    }void dodadiPesna(Pesna p){
        if(broj<10 && zbir+p.getMin()<=maxmin){
            broj++;
            pesni[broj-1]=p;
            zbir+=p.getMin();
        }
    }

};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

    return 0;
}
