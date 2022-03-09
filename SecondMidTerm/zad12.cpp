#include<iostream>
#include<cstring>
#include<ctype.h>

using namespace std;

class InvalidProductionDate{
public:
    void msg(){
        cout<<"Невалидна година на производство"<<endl;
    }
};

enum tip {telefon=0, kompjuter};
class Device{
protected:
    char model[100];
    static float proverka;
    tip tipNaured;
    int god;

    void copy(const Device &d){
        strcpy(this->model,d.model);
        this->tipNaured=d.tipNaured;
        this->god=d.god;
    }

public:
    Device(char *model="",tip tipNaured=(tip)0, int god=0){
        strcpy(this->model,model);
        this->tipNaured=tipNaured;
        this->god=god;
    }Device(const Device &d){
        copy(d);
    }Device &operator =(const Device &d){
        if (this!=&d){
            copy(d);
        }return *this;
    }static void setPocetniCasovi(float p){
        proverka=p;
    }friend ostream & operator<<(ostream &out,Device &d){
        float krajnoVreme = d.proverka;
        if (d.god > 2015){
            krajnoVreme += 2;
        }if (d.tipNaured == kompjuter){
            krajnoVreme += 2;
        }const char* enumTekst[] = {"Mobilen","Laptop"};

        out << d.model << endl;
        out << enumTekst[d.tipNaured] << " " << krajnoVreme;
        return out;
    }int getGod(){
        return god;
    }
};

float Device::proverka=1.0;

class MobileServis{
protected:
    char adresa[100];
    Device *uredi;
    int brojUredi;

    void copy(const MobileServis &m){
        strcpy(this->adresa,m.adresa);
        this->brojUredi=m.brojUredi;
        this->uredi=new Device[m.brojUredi];
        for (int i = 0; i < m.brojUredi; ++i) {
            this->uredi[i]=m.uredi[i];
        }
    }

public:
    MobileServis(char *adresa=""){
        strcpy(this->adresa,adresa);
        this->uredi= nullptr;
        brojUredi=0;
    }MobileServis(const MobileServis &m){
        copy(m);
    }MobileServis& operator=(const MobileServis &m){
        if (this!=&m){
            delete [] uredi;
            copy(m);
        }return *this;
    }~MobileServis(){
        delete [] uredi;
    }MobileServis& operator +=( Device &d){
        if (d.getGod() > 2019 || d.getGod() < 2000){
            throw InvalidProductionDate();
        } else{
            Device *temp=new Device[brojUredi+1];
            for (int i = 0; i < brojUredi; ++i) {
                temp[i]=uredi[i];
            }temp[brojUredi++]=d;
            delete [] uredi;
            uredi=temp;
            return  *this;
        }
    }void pecatiCasovi(){
        cout << "Ime: " << adresa << endl;
        for (int i = 0; i < brojUredi; i++){
            cout << uredi[i] << endl;
        }
    }
};

int main(){
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }catch(InvalidProductionDate& e){
                e.msg();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }catch(InvalidProductionDate& e){
                e.msg();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }catch(InvalidProductionDate& e){
                e.msg();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            try{
                t+=tmp;
            }catch(InvalidProductionDate& e){
                e.msg();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }catch(InvalidProductionDate& e){
                e.msg();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}
