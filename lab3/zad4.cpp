#include<iostream>
#include<cstring>
using namespace std;

class Masa{
private:
    int dol;
    int sir;
public:
    Masa(int dol=0,int sir=0){
        this->dol=dol;
        this->sir=sir;
    }~Masa(){}
    void print(){
        cout<<"Masa: "<<dol<<" "<<sir<<endl;
    }
};

class Soba{
private:
    Masa m;
    int dol;
    int sir;
public:
    Soba(){}
    Soba(int dol,int sir,Masa m){
        this->dol=dol;
        this->sir=sir;
        this->m=m;
    }~Soba(){}
    void print(){
        cout<<"Soba: "<<dol<<" "<<sir<<" ";
        m.print();
    }

};

class Kukja{
private:
    Soba s;
    char adresa[50];
public:
    Kukja(){}
    Kukja(Soba s,char *adresa=""){
        this->s=s;
        strcpy(this->adresa,adresa);
    }~Kukja(){}
    void pecati(){
        cout<<"Adresa: "<<adresa<<" ";
        s.print();
    }
};
//ne smee da se menuva main funkcijata!
int zad4(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
    	int masaSirina,masaDolzina;
        cin>>masaSirina;
        cin>>masaDolzina;
    	Masa m(masaSirina,masaDolzina);
    	int sobaSirina,sobaDolzina;
        cin>>sobaSirina;
        cin>>sobaDolzina;
    	Soba s(sobaSirina,sobaDolzina,m);
    	char adresa[30];
        cin>>adresa;
    	Kukja k(s,adresa);
    	k.pecati();
	}

    return 0;
}
