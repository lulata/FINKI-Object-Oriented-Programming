#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

enum pozicija{vraboten, direktor, shef};

class Vraboten{
    private:
        char ime[50];
        int plata;
        pozicija rabotna_pozicija;
    public:
        Vraboten(){}
        Vraboten(char *imee, int plataa, pozicija poz){
            strcpy(ime, imee);
            plata=plataa;
        rabotna_pozicija = poz;
        }void set_ime(char *imee){
         strcpy(ime, imee);
        }void set_plata(int plataa){
         plata=plataa;
         }void set_pozicija(int poz){
         rabotna_pozicija = (pozicija)poz;
         }int get_plata(){
         return plata;
         }void pecati(){
         cout<<ime<<" "<<plata<<" "<<rabotna_pozicija<<endl;
         }
};
void sortiraj(Vraboten v[], int n){
     for(int i=0; i<n; i++){
         for(int j=0; j<n-i-1; j++){
             if(v[j].get_plata()>v[j+1].get_plata()){
             Vraboten temp = v[j];
             v[j] = v[j+1];
             v[j+1] = temp;
             }
         }
     }
}
int aud2(){
     Vraboten v[100];
     int n;
     cin>>n;
     for(int i=0; i<n; i++){
         char ime[50];
         int plata;
         int pozicija;
         cin>>ime;
         cin>>plata>>pozicija;
         v[i].set_ime(ime);
         v[i].set_plata(plata);
         v[i].set_pozicija(pozicija);
     }sortiraj(v, n);
     for(int i=0; i<n; i++){
        v[i].pecati();
     }
}

