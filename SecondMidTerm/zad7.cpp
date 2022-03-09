#include<iostream>
#include<cstring>
using namespace std;

class OutOfBoundException{
public:
    void message(){
        cout << "Brojot na pin kodovi ne moze da go nadmine dozvolenoto" << endl;
    }
};

class Card{
protected:
    char korisnik[16];
    int pin;
    bool pojcePinoj;
    void copy(const Card& c){
        strcpy(this->korisnik, c.korisnik);
        this->pin = c.pin;
        this->pojcePinoj = c.pojcePinoj;
    }
public:
    Card(const char* korisnik = "", int pin = 0){
        strcpy(this->korisnik, korisnik);
        this->pin = pin;
        this->pojcePinoj = false;
    }Card(const Card& c){
        copy(c);
    }Card& operator= (const Card& c){
        if (this != &c) {
            copy(c);
        }return *this;
    }virtual int pinWeight(){
        int counter = 0;
        int temp = pin;
        while (temp > 0){
            counter++;
            temp = temp / 10;
        }return counter;
    }void print(ostream& out){
        out << korisnik << ": " << pinWeight() << endl;
    }friend ostream& operator<< (ostream& out, Card& c){
        c.print(out);
        return out;
    }bool getMultiplePins(){
        return pojcePinoj;
    }const char* getAcc(){
        return korisnik;
    }
};

class SpecialCard : public Card{
private:
    int* dopolnitelnPin;
    int brDopolnitelniPinoj;
    static const int P = 4;
    void copy(const SpecialCard& s){
        Card::copy(s);
        this->brDopolnitelniPinoj = s.brDopolnitelniPinoj;
        this->dopolnitelnPin = new int[s.brDopolnitelniPinoj];
        for (int i = 0; i < s.brDopolnitelniPinoj; ++i) {
            this->dopolnitelnPin[i] = s.dopolnitelnPin[i];
        }
    }

public:
    SpecialCard(const char *korisnik, int pin) : Card(korisnik, pin) {
        dopolnitelnPin = nullptr;
        brDopolnitelniPinoj = 0;
        pojcePinoj = true;
    }SpecialCard(const SpecialCard& s){
        copy(s);
    }~SpecialCard(){
        delete[] dopolnitelnPin;
    }SpecialCard& operator= (const SpecialCard& s){
        if (this != &s) {
            delete[] dopolnitelnPin;
            copy(s);
        }return *this;
    }int pinWeight() override {
        return Card::pinWeight() + brDopolnitelniPinoj;
    }
    SpecialCard& operator+= (int newPin){
        if (brDopolnitelniPinoj >= P) {
            throw OutOfBoundException();
        } else {
            int *temp = new int[brDopolnitelniPinoj + 1];
            for (int i = 0; i < brDopolnitelniPinoj; ++i) {
                temp[i] = dopolnitelnPin[i];
            }temp[brDopolnitelniPinoj++] = newPin;
            delete[] dopolnitelnPin;
            dopolnitelnPin = temp;
            return *this;
        }
    }

};

class Banka {
private:
    char ime[30];
    Card *karticki[20];
    int brKarticki;
    static int LIMIT;
public:
    Banka(char *ime, Card** karticki, int broj ){
        strcpy(this->ime, ime);
        for (int i=0;i<broj;i++){
            if (karticki[i]->getMultiplePins()){
                this->karticki[i]=new SpecialCard(*dynamic_cast<SpecialCard*>(karticki[i]));
            }else this->karticki[i]=new Card(*karticki[i]);
        }this->brKarticki=broj;
    }~Banka(){
        for (int i=0; i < brKarticki; i++){
            delete karticki[i];
        }
    }static void setLIMIT(int n){
        LIMIT = n;
    }void printHackableCards(){
        cout << "Vo bankata " << ime << " moze da se probijat kartickite:" << endl;
        for (int i = 0; i < brKarticki; ++i) {
            if (karticki[i]->pinWeight() <= LIMIT) {
                cout << *karticki[i];
            }
        }
    }void addAditionalPin(const char* acc, int newPin){
        for (int i = 0; i < brKarticki; ++i) {
            if (strcmp(karticki[i]->getAcc(), acc) == 0) {
                SpecialCard *test = dynamic_cast<SpecialCard *>(karticki[i]);
                if (test) {
                    *(test) += newPin;
                }break;
            }
        }
    }


};

int Banka::LIMIT = 7;


int main(){

    Card **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Card*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Card(smetka, pin);
        else
            niza[i]=new SpecialCard(smetka,pin);
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0;i<m;i++){
        cin>>smetka>>pin;

        komercijalna.addAditionalPin(smetka,pin);

    }

    Banka::setLIMIT(5);

    komercijalna.printHackableCards();

    return 0;
}
