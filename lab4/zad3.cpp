#include<iostream>
#include <cstring>
using namespace std;

class Avtomobil{
private:
    char boja[20];
    char marka[20];
    char model[20];
public:
    Avtomobil(char *boja="",char *marka="",char *model=""){
        strcpy(this->boja,boja);
        strcpy(this->marka,marka);
        strcpy(this->model,model);
    }Avtomobil(const Avtomobil &a){
        strcpy(this->boja,a.boja);
        strcpy(this->marka,a.marka);
        strcpy(this->model,a.model);
    }~Avtomobil(){}
    Avtomobil& operator=(const Avtomobil &a){
        if(this!=&a){
            strcpy(this->boja,a.boja);
            strcpy(this->marka,a.marka);
            strcpy(this->model,a.model);
        }return *this;
    }void print(){
        cout<<boja<<" "<<marka<<" "<<model;
    }
};

class ParkingPlac{
private:
    char add[20];
    char *ide;
    int cena;
    int zarabotka;
    Avtomobil *avto;
    int br;
public:
    ParkingPlac(char *add="",char *ide="",int cena=0){
        strcpy(this->add,add);
        this->ide = new char[strlen(ide)+1];
        strcpy(this->ide,ide);
        this->cena=cena;
        this->avto = new Avtomobil[1];
        br=0;
        zarabotka=0;
    }ParkingPlac(const ParkingPlac &p){
        strcpy(this->add,p.add);
        this->ide = new char[strlen(p.ide)+1];
        strcpy(this->ide,p.ide);
        this->cena=p.cena;
        this->br=p.br;
        this->zarabotka=p.zarabotka;
        this->avto = new Avtomobil[p.br];
        for (int i = 0; i < br; ++i) {
            avto[i]=p.avto[i];
        }
    }~ParkingPlac(){
        delete [] ide;
        delete [] avto;
    }ParkingPlac& operator= (const ParkingPlac &p){
        if (this!=&p){
            strcpy(this->add,p.add);
            delete [] ide;
            this->ide = new char[strlen(p.ide)+1];
            strcpy(this->ide,p.ide);
            this->cena=p.cena;
            this->br=p.br;
            this->zarabotka=p.zarabotka;
            delete [] avto;
            this->avto = new Avtomobil[p.br];
            for (int i = 0; i < br; ++i) {
                avto[i]=p.avto[i];
            }
        }return *this;
    }const char* getId(){
        return ide;
    }void pecati(){
        cout<<ide<<" "<<add;
        if (zarabotka>0){
            cout<<" - "<<zarabotka<<" denari"<<endl;
        }
    }void platiCasovi (int h){
        zarabotka += (h * cena);
    }bool daliIstaAdresa(ParkingPlac& p){
        return (strcmp(add, p.add) == 0);
    }void parkirajVozilo(Avtomobil &v){
        if (br == 0) {
            avto[0] = v;
            br++;
        } else {
            Avtomobil *temp = new Avtomobil[br + 1];
            for (int i = 0; i < br; ++i) {
                temp[i] = avto[i];
            }
            temp[br] = v;
            delete[] avto;
            avto = temp;
            br++;
        }
    }void pecatiParkiraniVozila(){
        cout << "Vo parkingot se parkirani slednite vozila: " << endl;
        for (int i = 0; i < br; i++){
            cout << i+1 << ".";
            avto[i].print();
            cout << endl;
        }
    }
};
// вашиот код

int main(){

    ParkingPlac p[100];
    int n,m;
    char adresa[50],id[50];
    int brojcasovi,cenacas;
    cin>>n;
    if(n > 0){


        for (int i=0;i<n;i++){
            cin.get();
            cin.getline(adresa,50);
            cin>>id>>cenacas;

            ParkingPlac edna(adresa,id,cenacas);

            p[i]=edna;
        }

        //plakjanje
        cin>>m;
        for (int i=0;i<m;i++){

            cin>>id>>brojcasovi;

            int findId=false;
            for (int j=0;j<m;j++){
                if (strcmp(p[j].getId(),id)==0){
                    p[j].platiCasovi(brojcasovi);
                    findId=true;
                }
            }
            if (!findId)
                cout<<"Ne e platen parking. Greshen ID."<<endl;
        }

        cout<<"========="<<endl;
        ParkingPlac pCentar("Cvetan Dimov","C10",80);
        for (int i=0;i<n;i++)
            if (p[i].daliIstaAdresa(pCentar))
                p[i].pecati();
    } else {

        ParkingPlac najdobarPlac("Mars", "1337", 1);
        int brVozila;
        cin >> brVozila;
        for(int i = 0; i < brVozila; ++i){

            char boja[20];
            char brend[20];
            char model[20];

            cin >> boja >> brend >> model;
            Avtomobil novAvtomobil(boja, brend, model);
            najdobarPlac.parkirajVozilo(novAvtomobil);
        }
        if(brVozila != 0)
            najdobarPlac.pecatiParkiraniVozila();

    }
}
