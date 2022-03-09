#include <iostream>
#include <cstring>
using namespace std;

class Ucesnik {
private:
    char *ime;
    bool pol;
    int god;

    void copy(const Ucesnik  &u){
        this->ime=new char[strlen(u.ime)+1];
        strcpy(this->ime,u.ime);
        this->pol=u.pol;
        this->god=u.god;
    }

public:
    Ucesnik(char *ime="",bool pol=0,int god=0){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->pol=pol;
        this->god=god;
    }Ucesnik(const Ucesnik  &u){
        copy(u);
    }~Ucesnik(){
        delete [] ime;
    }Ucesnik& operator=(const Ucesnik &u){
        if (this!=&u){
            delete [] ime;
            copy(u);
        }return *this;
    }bool operator>(Ucesnik &u){
        return this->god>u.god;
    }friend ostream& operator<<(ostream &o,Ucesnik &u){
        o<<u.ime<<endl;
        if (u.pol==0){
            o<<"zhenski"<<endl;
        }else{
            o<<"mashki"<<endl;
        }o<<u.god<<endl;

        return o;
    }int getGod(){
        return god;
    }
};

class Maraton{
private:
    char lokacija[100];
    Ucesnik  *ucesnici;
    int broj;

    void copy(const Maraton &m){
        strcpy(this->lokacija,m.lokacija);
        this->broj=m.broj;
        this->ucesnici = new Ucesnik [m.broj];
        for (int i = 0; i < broj; ++i) {
            this->ucesnici[i]=m.ucesnici[i];
        }
    }

public:
    Maraton(char *lokacija=""){
        strcpy(this->lokacija,lokacija);
        broj=0;
        ucesnici= new Ucesnik[broj];
    }~Maraton(){
        delete [] ucesnici;
    }Maraton(const Maraton &m){
        copy(m);
    }Maraton& operator+=(const Ucesnik &u){
        Ucesnik *temp= new Ucesnik[broj+1];
        for (int i = 0; i < broj; ++i) {
            temp[i]=ucesnici[i];
        }temp[broj++]=u;
        delete [] ucesnici;
        ucesnici = temp;
        return *this;
    }float prosecnoVozrast(){
        float prosek=0.0;
        int zbir=0;
        for (int i = 0; i < broj; ++i) {
            zbir+=ucesnici[i].getGod();
        }
        prosek= zbir/(broj*1.0);
        return prosek;
    }void pecatiPomladi(Ucesnik &u){
        int god=u.getGod();
        for (int i = 0; i < broj; ++i) {
            if(god>ucesnici[i].getGod()){
                cout<<ucesnici[i];
            }
        }
    }
};


int main() {
    // vashiot kod ovde

        char ime[100];
        bool maski;
        int vozrast, n;
        cin >> n;
        char lokacija[100];
        cin >> lokacija;
        Maraton m(lokacija);
        Ucesnik **u = new Ucesnik*[n];
        for(int i = 0; i < n; ++i) {
            cin >> ime >> maski >> vozrast;
            u[i] = new Ucesnik(ime, maski, vozrast);
            m += *u[i];
        }
        m.pecatiPomladi(*u[n - 1]);
        cout << m.prosecnoVozrast() << endl;
        for(int i = 0; i < n; ++i) {
            delete u[i];
        }
        delete [] u;
        return 0;

}

