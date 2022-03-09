#include <iostream>
#include <cstring>

using namespace std;

class Automobile{
private:
    char *marka;
    int *reg;
    int brzina;

    void copy(const Automobile &a){
        this->marka=new char[strlen(a.marka)+1];
        strcpy(this->marka,a.marka);
        this->reg=new int[5];
        for(int i=0;i<5;i++){
            this->reg[i]=a.reg[i];
        }this->brzina=a.brzina;
    }
public:
    Automobile(){
        marka=new char[0];
        reg=new int[5];
        brzina=0;
    }Automobile(char* marka,int *reg,int brzina){
        this->marka=new char[strlen(marka)+1];
        strcpy(this->marka,marka);
        this->reg=new int[5];
        for(int i=0;i<5;i++){
            this->reg[i]=reg[i];
        }this->brzina=brzina;
    }
    Automobile(const Automobile &a){
        copy(a);
    }Automobile& operator=(const Automobile &a){
        if(this!=&a){
           delete [] marka;
           delete [] reg;
           copy(a);
        }return *this;
    }
    bool operator == (const Automobile &a){
        int brojac=0;
        for(int i=0;i<5;i++){
            if(this->reg[i] == a.reg[i]){
                brojac++;
            }
        }if(brojac==5){
            return true;
        }return false;
    }friend ostream&operator<<(ostream &o,const Automobile &a){
        o<<"Marka\t"<<a.marka<<"\tRegistracija[ ";
        for(int i=0;i<5;i++){
            o<<a.reg[i]<<" ";
        }o<<"]"<<endl;
        return o;
    }
    friend class RentACar;
};

class RentACar{
private:
    char ime[100];
    Automobile *kola;
    int broj;
public:
    RentACar(const char *ime){
        strcpy(this->ime,ime);
        this->kola=new Automobile[0];
        this->broj=0;
    }~RentACar(){
        delete [] kola;
    }RentACar &operator+=(const Automobile &a){
        Automobile *temp=new Automobile[broj+1];
        for(int i=0;i<broj;i++){
            temp[i]=kola[i];
        }temp[broj++]=a;
        delete[]kola;
        kola=temp;
        return *this;
    }RentACar &operator-=(const Automobile &a){
        Automobile *temp=new Automobile[broj-1];
        int brojac=0;
        for(int i=0;i<broj;i++){
            if(kola[i]==a){
                continue;
            }else{
                temp[brojac++]=kola[i];
            }
        }delete[] kola;
        kola =temp;
        broj=brojac;
        return *this;
    }void pecatiNadBrzina(int max){
        cout<<ime<<endl;
        for(int i=0;i<broj;i++){
            if(kola[i].brzina > max){
                cout<<kola[i]<<endl;
            }
        }
    }
};

int main()
{
    RentACar agencija("FINKI-Car");
    int n;
    cin>>n;

    for (int i=0;i<n;i++)
    {
        char marka[100];
        int regisracija[5];
        int maximumBrzina;

        cin>>marka;

        for (int i=0;i<5;i++)
            cin>>regisracija[i];

        cin>>maximumBrzina;

        Automobile nov=Automobile(marka,regisracija,maximumBrzina);

        //dodavanje na avtomobil
        agencija+=nov;

    }
    //se cita grehsniot avtmobil, za koj shto avtmobilot so ista registracija treba da se izbrishe
    char marka[100];
    int regisracija[5];
    int maximumBrzina;
    cin>>marka;
    for (int i=0;i<5;i++)
        cin>>regisracija[i];
    cin>>maximumBrzina;

    Automobile greshka=Automobile(marka,regisracija,maximumBrzina);

    //brishenje na avtomobil
    agencija-=greshka;

    agencija.pecatiNadBrzina(150);

    return 0;
}
