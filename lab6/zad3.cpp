#include<iostream>
#include<cstring>

using namespace std;

class Lekar {
protected:
    int faksimil;
    char ime[10];
    char prezime[11];
    double pocetnaPlata;

    void copy (const Lekar &l){
        this->faksimil = l.faksimil;
        strcpy(this->ime,l.ime);
        strcpy(this->prezime, l.prezime);
        this->pocetnaPlata = l.pocetnaPlata;
    }

public:
    Lekar(){
        faksimil = 0;
        strcpy(ime,"");
        strcpy(prezime,"");
        pocetnaPlata = 0.0;
    }Lekar(int faksimil, char *ime, char *prezime, double pocetnaPlata) {
        this->faksimil = faksimil;
        strcpy(this->ime,ime);
        strcpy(this->prezime, prezime);
        this->pocetnaPlata = pocetnaPlata;
    }Lekar (const Lekar& other){
        copy(other);
    }void pecati(){
        cout << faksimil << ": " << ime << " " << prezime << endl;
    }double plata(){
        return pocetnaPlata;
    }
};

class MaticenLekar : public Lekar {
private:
    int brPacienti;
    double *naplati;

    void copy(const MaticenLekar &m){
        Lekar::copy(m);
        this->brPacienti = m.brPacienti;
        this->naplati = new double[m.brPacienti];
        for (int i = 0; i < m.brPacienti; i++) {
            this->naplati[i] = m.naplati[i];
        }
    }
public:
    MaticenLekar (){
        brPacienti = 0;
        naplati = nullptr;
    }
    MaticenLekar(Lekar &l, int brPacienti, double *naplati):Lekar(l){
        this->brPacienti = brPacienti;
        this->naplati = new double[brPacienti];
        for (int i = 0; i < brPacienti; i++) {
            this->naplati[i] = naplati[i];
        }
    }MaticenLekar& operator= (const MaticenLekar &m){
        if (this != &m) {
            delete[] naplati;
            copy(m);
        }return *this;
    }~MaticenLekar(){
        delete[] naplati;
    }double avgFees(){
        double sum = 0.0;
        for (int i = 0; i < brPacienti; ++i) {
            sum = sum + naplati[i];
        }
        return sum / (double) brPacienti;
    }void pecati(){
        Lekar::pecati();
        cout << "Prosek na kotizacii: " << avgFees() << endl;
    }double plata(){
        return pocetnaPlata + 0.3 * avgFees();
    }
};

int main() {
    int n;
    cin>>n;
    int pacienti;
    double kotizacii[100];
    int faksimil;
    char ime [20];
    char prezime [20];
    double osnovnaPlata;

    Lekar * lekari = new Lekar [n];
    MaticenLekar * maticni = new MaticenLekar [n];

    for (int i=0;i<n;i++){
        cin >> faksimil >> ime >> prezime >> osnovnaPlata;
        lekari[i] = Lekar(faksimil,ime,prezime,osnovnaPlata);
    }

    for (int i=0;i<n;i++){
        cin >> pacienti;
        for (int j=0;j<pacienti;j++){
            cin >> kotizacii[j];
        }
        maticni[i]=MaticenLekar(lekari[i],pacienti,kotizacii);
    }

    int testCase;
    cin>>testCase;

    if (testCase==1){
        cout<<"===TESTIRANJE NA KLASATA LEKAR==="<<endl;
        for (int i=0;i<n;i++){
            lekari[i].pecati();
            cout<<"Osnovnata plata na gorenavedeniot lekar e: "<<lekari[i].plata()<<endl;
        }
    }
    else {
        cout<<"===TESTIRANJE NA KLASATA MATICENLEKAR==="<<endl;
        for (int i=0;i<n;i++){
            maticni[i].pecati();
            cout<<"Platata na gorenavedeniot maticen lekar e: "<<maticni[i].plata()<<endl;
        }
    }

    delete [] lekari;
    delete [] maticni;

    return 0;
}
