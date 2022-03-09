#include<iostream>
#include<cstring>

using namespace std;

class Nedviznina {
protected:
    char *adresa;
    int kvadrati;
    int cenaKvadrat;

    void copy(const Nedviznina &n){
        this->adresa = new char[strlen(n.adresa) + 1];
        strcpy(this->adresa, n.adresa);
        this->kvadrati = n.kvadrati;
        this->cenaKvadrat = n.cenaKvadrat;
    }

public:
    Nedviznina (char *adresa="", int kvadrati=0, int cenaKvadrat=0){
        this->adresa = new char[strlen(adresa) + 1];
        strcpy(this->adresa, adresa);
        this->kvadrati = kvadrati;
        this->cenaKvadrat = cenaKvadrat;
    }Nedviznina& operator=(const Nedviznina &n){
        if (this != &n) {
            delete[] adresa;
            copy(n);
        }return *this;
    }~Nedviznina(){
        delete[] adresa;
    }friend istream& operator>> (istream& in, Nedviznina &n){
        string temp;
        getline(in, temp);
        n.adresa = new char[temp.length() + 1];
        int i;
        for (i = 0; i < temp.length(); i++) {
            n.adresa[i] = temp[i];
        }n.adresa[i] = '\0';
        in >> n.kvadrati;
        in >> n.cenaKvadrat;
        in.ignore();
        return in;
    }int cena(){
        return kvadrati * cenaKvadrat;
    }double danokNaImot(){
        return 0.05 * cena();
    }void pecati(){
        cout << adresa << ", Kvadratura: " << kvadrati << ", Cena po Kvadrat: " << cenaKvadrat << endl;
    }const char* getAdresa(){
        return adresa;
    }
};

class Vila : public Nedviznina {
private:
    int luksuz;
public:
    Vila () {
        luksuz = 0;
    }Vila (Nedviznina &n, int luksuz) : Nedviznina(n){
        this->luksuz = luksuz;
    }friend istream& operator>> (istream &in, Vila &v){
        string temp;
        getline(in, temp);
        v.adresa = new char[temp.length() + 1];
        int i;
        for (i = 0; i < temp.length(); i++) {
            v.adresa[i] = temp[i];
        }v.adresa[i] = '\0';
        in >> v.kvadrati;
        in >> v.cenaKvadrat;
        in >> v.luksuz;
        in.ignore();
        return in;
    }double danokNaImot(){
        return (cena() * (0.05 + (double)luksuz / 100));
    }void pecati(){
        cout << adresa << ", Kvadratura: " << kvadrati << ", Cena po Kvadrat: " << cenaKvadrat
             << ", Danok na luksuz: " << luksuz << endl;
    }Vila& operator= (const Vila &v){
        if (this != &v) {
            delete[] adresa;
            copy(v);
            luksuz = v.luksuz;
        }return *this;
    }
};

int main(){
    Nedviznina n;
    Vila v;
    cin>>n;
    cin>>v;
    n.pecati();
    cout<<"Danok za: "<<n.getAdresa()<<", e: "<<n.danokNaImot()<<endl;
    v.pecati();
    cout<<"Danok za: "<<v.getAdresa()<<", e: "<<v.danokNaImot()<<endl;
    return 0;
}
