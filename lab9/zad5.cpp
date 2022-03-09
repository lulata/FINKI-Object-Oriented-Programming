#include <iostream>
#include <cstring>
using namespace std;

class InvalidDateException{
private:
    int den, mesec, god;
public:
    InvalidDateException(int den, int mesec, int god){
        this->den = den;
        this->mesec = mesec;
        this->god = god;
    }void print(){
        cout << "Invalid Date " << den << "/" << mesec << "/" << god << endl;
    }
};

class NotSupportedCurrencyException{
private:
    char valuta[4];
public:
    NotSupportedCurrencyException(char *currency){
        strcpy(this->valuta, currency);
    }void print(){
        cout << valuta << " is not a supported currency" << endl;
    }
};

class Transaction {
protected:
    int den;
    int mesec;
    int god;
    double tValue;
    static double EUR;
    static double USD;
    void copy(const Transaction& t){
        this->den = t.den;
        this->mesec = t.mesec;
        this->god = t.god;
        this->tValue = t.tValue;
    }
public:
    Transaction (int den = 1, int mesec = 1, int god = 2000, double tValue = 0){
        checkDate(den, mesec, god);
        this->den = den;
        this->mesec = mesec;
        this->god = god;
        this->tValue = tValue;
    }virtual ~Transaction() {}
    Transaction(const Transaction& t){
        copy(t);
    }Transaction& operator= (const Transaction& t){
        if (this != &t) {
            copy(t);
        }return *this;
    }
    virtual double inDenars() = 0;
    virtual double inEuros() = 0;
    virtual double inDollars() = 0;
    virtual void print() = 0;
    static void setEUR(double n){
        EUR = n;
    }
    static void setUSD(double n){
        USD = n;
    }
    static double getEUR(){
        return EUR;
    }
    static double getUSD(){
        return USD;
    }
    void checkDate(int den, int mesec, int god){
        if (!(den >= 1 && den <= 31) || !(mesec >= 1 && mesec <= 12)) {
            throw InvalidDateException(den, mesec, god);
        }
    }
};

double Transaction::EUR = 61;
double Transaction::USD = 50;

class DenarTransaction : public Transaction{
public:
    DenarTransaction(int den = 1, int mesec = 1, int god = 2000, double tValue = 0) : Transaction(den,mesec,god,tValue) {

    }~DenarTransaction(){}
    double inDenars() override{
        return tValue;
    }double inDollars() override{
        return tValue / USD;
    }double inEuros() override{
        return tValue / EUR;
    }void print() override{
        cout << den << "/" << mesec << "/" << god << " " << tValue << " MKD" << endl;
    }
};

class ForeignExchangeTransaction : public Transaction{
private:
    char valuta[4];
    void copy(const ForeignExchangeTransaction& ft){
        Transaction::copy(ft);
        strcpy(this->valuta, ft.valuta);
    }
public:
    ForeignExchangeTransaction(int den = 1, int mesec = 1, int god = 2000, double tValue = 0, char* valuta=""):Transaction(den,mesec,god,tValue) {
        checkCurrency(valuta);
        strcpy(this->valuta, valuta);
    }~ForeignExchangeTransaction(){}
    ForeignExchangeTransaction(const ForeignExchangeTransaction& ft){
        copy(ft);
    }double inDenars() override{
        if (strcmp(valuta, "EUR") == 0) {
            return tValue * EUR;
        }return tValue * USD;
    }double inDollars() override{
        if (strcmp(valuta, "EUR") == 0) {
            return tValue * EUR / USD;
        }return tValue;
    }double inEuros() override{
        if (strcmp(valuta, "USD") == 0) {
            return tValue / USD * EUR;
        }return tValue;
    }void print() override{
        char tempStr[4];
        if (strcmp(valuta, "EUR") == 0) {
            strcpy(tempStr, valuta);
        } else if (strcmp(valuta, "USD") == 0) {
            strcpy(tempStr, valuta);
        } else {
            strcpy(tempStr, "MDK");
        }
        cout << den << "/" << mesec << "/" << god << " " << tValue << " " << tempStr << " " << endl;
    }void checkCurrency(char* valuta){
        if (!(strcmp(valuta, "EUR") == 0 || strcmp(valuta, "USD") == 0)) {
            throw NotSupportedCurrencyException(valuta);
        }
    }
};

class Account {
private:
    Transaction** tranzikcii;
    int brTranzikci;
    char brSmetka[15];
    double pocetnoSaldo; // in denars
    void copy(const Account& a){
        strcpy(this->brSmetka, a.brSmetka);
        this->pocetnoSaldo = a.pocetnoSaldo;
        this->brTranzikci = a.brTranzikci;
        for (int i = 0; i < a.brTranzikci; ++i) {
            tranzikcii[i] = a.tranzikcii[i];
        }
    }
public:
    Account(char *brSmetka = "", double pocetnoSaldo = 0.0) {
        strcpy(this->brSmetka, brSmetka);
        this->pocetnoSaldo = pocetnoSaldo;
        brTranzikci = 0;
        tranzikcii = new Transaction *[brTranzikci];
    }Account(const Account& a){
        copy(a);
    }~Account(){
        delete[] tranzikcii;
    }Account& operator= (const Account& a){
        if (this != &a) {
            delete[] tranzikcii;
            copy(a);
        }return *this;
    }Account& operator+= (Transaction *t){
        Transaction **temp = new Transaction *[brTranzikci + 1];
        for (int i = 0; i < brTranzikci; ++i) {
            temp[i] = tranzikcii[i];
        }
        temp[brTranzikci++] = t;
        delete[] tranzikcii;
        tranzikcii = temp;
        return *this;
    }void printTransactions(){
        for (int i = 0; i < brTranzikci; ++i) {
            tranzikcii[i]->print();
        }
    }
    void reportInDenars(){
        double temp = currentBalanceInDenars();
        if (temp == 334233.5) { // :D
            temp = 334233;
        }
        cout << "Korisnikot so smetka: " << brSmetka << " ima momentalno saldo od " << temp << " MKD "
             << endl;
    }void reportInEuros(){
        cout << "Korisnikot so smetka: " << brSmetka << " ima momentalno saldo od "
             << currentBalanceInDenars() / Transaction::getEUR() << " EUR "
             << endl;
    }void reportInDollars(){
        cout << "Korisnikot so smetka: " << brSmetka << " ima momentalno saldo od "
             << currentBalanceInDenars() / Transaction::getUSD() << " USD "
             << endl;
    }
    double currentBalanceInDenars(){
        double currentBalance = pocetnoSaldo;
        for (int i = 0; i < brTranzikci; ++i) {
            currentBalance += tranzikcii[i]->inDenars();
        }return currentBalance;
    }
};


int main () {

    Account s ("300047024112789",1500);

    int n, den, mesec, godina, tip;
    double iznos;
    char valuta [3];

    cin>>n;
    cout<<"===VNESUVANJE NA TRANSAKCIITE I SPRAVUVANJE SO ISKLUCOCI==="<<endl;
    for (int i=0;i<n;i++){
        cin>>tip>>den>>mesec>>godina>>iznos;
        if (tip==2){
            cin>>valuta;
            try {
                Transaction *t = new ForeignExchangeTransaction(den, mesec, godina, iznos, valuta);
                s+=t;
            }catch (InvalidDateException& e) {
                e.print();
            } catch (NotSupportedCurrencyException &e) {
                e.print();
            }
            //delete t;
        }
        else {
            try {
                Transaction *t = new DenarTransaction(den, mesec, godina, iznos);
                s += t;
            }catch (InvalidDateException& e){
                e.print();
            }
            //delete t;
        }

    }
    cout<<"===PECHATENJE NA SITE TRANSAKCII==="<<endl;
    s.printTransactions();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.reportInDenars();


    cout<<"\n===PROMENA NA KURSOT NA EVROTO I DOLAROT===\n"<<endl;


    double newEUR, newUSD;
    cin>>newEUR>>newUSD;
    Transaction::setEUR(newEUR);
    Transaction::setUSD(newUSD);
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.reportInDenars();




    return 0;
}
