#include<iostream>
#include<cstring>
#include<ctype.h>
using namespace std;

class Koncert{
protected:
    char ime[20];
    char lokacija[20];
    static float popust;
    float pariBilet;

    void copy(Koncert const &k){
        strcpy(this->ime,k.ime);
        strcpy(this->lokacija,k.lokacija);
        this->pariBilet=k.pariBilet;
    }
public:
    Koncert( char* ime="", char *lokacija="", float pariBilet=0.0){
        strcpy(this->ime,ime);
        strcpy(this->lokacija,lokacija);
        this->pariBilet=pariBilet;
    }~Koncert(){}
    Koncert(const Koncert &k){
        strcpy(this->ime,k.ime);
        strcpy(this->lokacija,k.lokacija);
        this->pariBilet=k.pariBilet;
    }Koncert &operator = (const Koncert &k){
        if (this!=&k){
            strcpy(this->ime,k.ime);
            strcpy(this->lokacija,k.lokacija);
            this->pariBilet=k.pariBilet;
        }return *this;
    }static float setSezonskiPopust(float p){
        popust=p;
    }char *getNaziv(){
        return ime;
    }virtual float cena(){
        return pariBilet-(pariBilet * popust);
    }static float getSezonskiPopust(){
        return popust;
    }
};

float Koncert::popust=0.2;

class  ElektronskiKoncert: public Koncert{
protected:
    char *DJ;
    float vreme;
    bool dnevna;
public:
    ElektronskiKoncert(char *ime="",char *lokacija="",float pariBilet=0.0,char *DJ="",float vreme=0.0,bool dnevna=true): Koncert(ime,lokacija,pariBilet) {
        this->DJ= new char[strlen(DJ)+1];
        strcpy(this->DJ,DJ);
        this->vreme=vreme;
        this->dnevna=dnevna;
    }ElektronskiKoncert(const ElektronskiKoncert &e){
        Koncert::copy(e);
        this->DJ= new char[strlen(e.DJ)+1];
        strcpy(this->DJ,e.DJ);
        this->vreme=e.vreme;
        this->dnevna=e.dnevna;
    }ElektronskiKoncert& operator =(const ElektronskiKoncert &e){
        if (this!=&e) {
            Koncert::copy(e);
            this->DJ = new char[strlen(e.DJ) + 1];
            strcpy(this->DJ, e.DJ);
            this->vreme = e.vreme;
            this->dnevna = e.dnevna;
        }return *this;
    }virtual float cena() override{
       float tempCena= Koncert::cena();
        if (dnevna){
            tempCena-=50;
        }else{
            tempCena+=100;
        }if(vreme>7){
            tempCena+=360;
        }else if (vreme>5){
            tempCena+=150;
        }return tempCena;
    }
};

void najskapKoncert(Koncert ** koncerti, int n){
    int brojac=0,elek=0;
    Koncert *najskap=koncerti[0];
    for (int i = 0; i < n; ++i) {
        ElektronskiKoncert *elektro= dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
        if(elektro){
            elek++;
        }if (najskap->cena()<koncerti[i]->cena()){
            brojac=i;
            najskap=koncerti[i];
        }
    }cout << "Najskap koncert: " << koncerti[brojac]->getNaziv() << " " << koncerti[brojac]->cena() << endl;
    cout << "Elektronski koncerti: " << elek << " od vkupno " << n << endl;
}

bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski) {
    for (int i = 0; i < n; ++i) {
        if (elektronski) {
            ElektronskiKoncert *elektro = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
            if (elektro) {
                if (strcmp(koncerti[i]->getNaziv(), naziv) == 0) {
                    cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
                    return true;
                }
            }
        } else {
            if (strcmp(koncerti[i]->getNaziv(), naziv) == 0) {
                cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
                return true;
            }
        }
    } return false;
}
int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin>>tip;
    if (tip==1){//Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
    }
    else if (tip==2){//cena - Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
    }
    else if (tip==3){//ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
    }
    else if (tip==4){//cena - ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
    }
    else if (tip==5) {//najskapKoncert

    }
    else if (tip==6) {//prebarajKoncert
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        najskapKoncert(koncerti,5);
    }
    else if (tip==7){//prebaraj
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        bool elektronski;
        cin>>elektronski;
        if(prebarajKoncert(koncerti,5, "Area",elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

        if(prebarajKoncert(koncerti,5, "Area",!elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

    }
    else if (tip==8){//smeni cena
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[2] -> setSezonskiPopust(0.9);
        najskapKoncert(koncerti,4);
    }

    return 0;
}
