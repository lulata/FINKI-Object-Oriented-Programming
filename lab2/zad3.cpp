#include <iostream>
#include <cstring>
using namespace std;

// vashiot kod ovde
class Film{
private:
    char ime[100];
    char reziser[50];
    char zarn[50];
    int god;

public:
    Film(){}
    Film(char *imee,char *reziserr,char *zarnn,int g){
        strcpy(ime, imee);
        strcpy(reziser, reziserr);
        strcpy(zarn, zarnn);
        god=g;
    }
    ~Film(){}
    void pecati(){
        cout<<"Ime: "<<ime<<endl;
        cout<<"Reziser: "<<reziser<<endl;
        cout<<"Zanr: "<<zarn<<endl;
        cout<<"Godina: "<<god<<endl;
    }void setIme(char *imee){
        strcpy(ime,imee);
    }void setReziser(char *reziserr){
        strcpy(reziser,reziserr);
    }void setZarn(char *zarnn){
        strcpy(zarn,zarnn);
    }void setGod(int g){
        god=g;
    }
    int getgod(){
        return god;
    }
};

void pecati_po_godina(Film *f, int n, int godina){
    for(int i=0;i<n;i++){
        if(godina==f[i].getgod()){
            f[i].pecati();
        }
    }
}

int zad2() {
    Film f[100];
 	int n;
 	cin >> n;
 	//da se inicijalizira niza od objekti od klasata Film
 	for(int i = 0; i < n; ++i) {
 		char ime[100];
 		char reziser[50];
 		char zanr[50];
 		int godina;
 		cin >> ime;
 		cin >> reziser;
 		cin >> zanr;
 		cin >> godina;
 		//da se kreira soodveten objekt
 		f[i].setIme(ime);
 		f[i].setReziser(reziser);
 		f[i].setZarn(zanr);
 		f[i].setGod(godina);
 	}
 	int godina;
 	cin >> godina;
 	//da se povika funkcijata pecati_po_godina
    pecati_po_godina(f,n,godina);
 	return 0;
 }
