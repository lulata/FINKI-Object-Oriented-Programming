#include <iostream>
#include <cstring>
using namespace std;
class Kompjuter {
private:
	char ime[100];
	int ram;
	float  bitcoin;
public:
	Kompjuter(){}
	Kompjuter(const char* imee, int ramm, float bitcoinn) {
		strcpy(ime, imee);
		ram = ramm;
		bitcoin = bitcoinn;
	}~Kompjuter(){}
    void setIme(char *imee){
        strcpy(ime,imee);
    }void setRam(int ramm){
        ram=ramm;;
    }void setBit(float bit){
        bitcoin=bit;;
    }int get_ram()const {
		return ram;
	}float get_bitcoin()const {
		return bitcoin;
	}char getIme(){
        return *ime;
	}void pecati() {
		cout << "Kompjuterot " << ime << " koj ima " << ram << "GB RAM moze da kopa " << bitcoin << " vo edna minuta " << endl;
	}
};

void sortiraj(Kompjuter k[], int n){
    for(int i=0;i<n;i++){
        for(int j=0; j<n-i-1; j++){
            if(k[j].get_bitcoin()>k[j+1].get_bitcoin()){
                 Kompjuter temp = k[j];
                 k[j] = k[j+1];
                 k[j+1] = temp;
            }
        }
    }
}

int main() {

    Kompjuter k[100];
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        char ime[100];
        int ram;
        float bitcoin;
        cin>>ime;
        cin>>ram;
        cin>>bitcoin;
        k[i].setIme(ime);
        k[i].setRam(ram);
        k[i].setBit(bitcoin);

    }for(int i=0;i<n;i++){
        k[i].pecati();
    }

    cout<<"SORTIRAJNE !!!!"<<endl;

    sortiraj(k,n);

    for(int i=0;i<n;i++){
        k[i].pecati();
    }

	return 0;
}
