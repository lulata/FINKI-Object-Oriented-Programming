#include<iostream>
#include<cstring>
using namespace std;

class Patnik{
private:
    char ime[100];
    int klasa;
    bool velosiped;

public:
    Patnik(char *ime="",int klasa=1,bool velosiped=0){
        strcpy(this->ime,ime);
        this->klasa=klasa;
        this->velosiped=velosiped;
    }~Patnik(){}
   friend ostream& operator<<(ostream &o,Patnik &p){
        o<<p.ime<<endl;
        o<<p.klasa<<endl;
        o<<p.velosiped<<endl;
        o<<endl;
        return o;
    }int getKlasa(){
        return klasa;
    }int getVelosiped(){
        return velosiped;
    }
};

class Voz{
private:
    char dest[100];
    Patnik *patnici;
    int dozvoleniVelosipedi;
    int broj=0;

    void copy(const Voz &v){
        strcpy(this->dest,v.dest);
        this->dozvoleniVelosipedi=v.dozvoleniVelosipedi;
        this->broj=v.broj;
        this->patnici=new Patnik[broj];
        for (int i = 0; i < broj; ++i) {
            this->patnici[i]=v.patnici[i];
        }
    }
public:
    Voz(char *dest="",int dozvoleniVelosipedi=0){
        strcpy(this->dest,dest);
        this->dozvoleniVelosipedi=dozvoleniVelosipedi;
        this->broj=broj;
        this->patnici=new Patnik[broj];
        for (int i = 0; i < broj; ++i) {
            this->patnici[i]=patnici[i];
        }
    }Voz(const Voz &v) {
        copy(v);
    }Voz& operator+=(const Patnik &p){
        Patnik *temp= new Patnik[broj+1];
        for (int i = 0; i < broj; ++i) {
            temp[i]=patnici[i];
        }temp[broj++]=p;
        delete [] patnici;
        patnici=temp;
        return *this;
    }friend ostream& operator<<(ostream &o,Voz &v){
        o<<v.dest<<endl;
        for (int i = 0; i < v.broj; ++i) {
            if (v.patnici[i].getVelosiped()==0){
                o<<v.patnici[i];
            }
        }return o;
    }void patniciNemaMesto(){
        int prva=0,vtora=0,vkupno;
        for (int i = 0; i < broj; ++i) {
            if(patnici[i].getKlasa() ==1 ){
                if (patnici[i].getVelosiped()==1){
                    prva++;
                }
            }else if(patnici[i].getKlasa()==2){
                if (patnici[i].getVelosiped()==1){
                    vtora++;
                }
            }vkupno++;
        }if (vkupno<dozvoleniVelosipedi){
            cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: 0"<<endl;
            cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: 0"<<endl;
        }

        if (prva>dozvoleniVelosipedi){
            cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e:"<<prva-dozvoleniVelosipedi<<endl;
            cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e:"<<vtora<<endl;
        }else if(prva<dozvoleniVelosipedi){
            if (vtora>dozvoleniVelosipedi){
                cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: 0"<<endl;
                cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e:"<<vtora-dozvoleniVelosipedi<<endl;
            }
        }
    }~Voz(){
        delete [] patnici;
    }
};


int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}
