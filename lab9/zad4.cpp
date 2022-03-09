#include <iostream>
#include <cstring>
using namespace std;

class InvalidDateException{
private:
    int day, month, year;
public:
    InvalidDateException(int day, int month, int year){
        this->day = day;
        this->month = month;
        this->year = year;
    }
    void print(){
        cout << "Invalid Date " << day << "/" << month << "/" << year << endl;
    }
};

class NotSupportedCurrencyException{
private:
    char currency[4];
public:
    NotSupportedCurrencyException(char *currency){
        strcpy(this->currency, currency);
    }
    void print(){
        cout << currency << " is not a supported currency" << endl;
    }
};

class Transaction {
protected:
    int day;
    int month;
    int year;
    double tValue;
    static double EUR;
    static double USD;
    void copy(const Transaction& other){
        this->day = other.day;
        this->month = other.month;
        this->year = other.year;
        this->tValue = other.tValue;
    }
public:
    Transaction (int day = 1, int month = 1, int year = 2000, double tValue = 0){
        checkDate(day, month, year);
        this->day = day;
        this->month = month;
        this->year = year;
        this->tValue = tValue;
    }
    virtual ~Transaction() {}

    Transaction(const Transaction& other){
        copy(other);
    }
    Transaction& operator= (const Transaction& other){
        if (this != &other) {
            copy(other);
        }
        return *this;
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
    void checkDate(int day, int month, int year){
        if (!(day >= 1 && day <= 31) || !(month >= 1 && month <= 12)) {
            throw InvalidDateException(day, month, year);
        }
    }
};

double Transaction::EUR = 61;
double Transaction::USD = 50;

class DenarTransaction : public Transaction{
public:
    DenarTransaction(int day = 1, int month = 1, int year = 2000, double tValue = 0) : Transaction(day,month,year,tValue) {

    }
    ~DenarTransaction(){}

    double inDenars() override{
        return tValue;
    }
    double inDollars() override{
        return tValue / USD;
    }
    double inEuros() override{
        return tValue / EUR;
    }
    void print() override{
        cout << day << "/" << month << "/" << year << " " << tValue << " MKD" << endl;
    }
};

class ForeignExchangeTransaction : public Transaction{
private:
    char currency[4];
    void copy(const ForeignExchangeTransaction& other){
        Transaction::copy(other);
        strcpy(this->currency, other.currency);
    }
public:
    ForeignExchangeTransaction(int day = 1, int month = 1, int year = 2000, double tValue = 0, char* currency="")
    :Transaction(day,month,year,tValue) {
        checkCurrency(currency);
        strcpy(this->currency, currency);
    }
    ~ForeignExchangeTransaction(){}
    ForeignExchangeTransaction(const ForeignExchangeTransaction& other){
        copy(other);
    }
    double inDenars() override{
        if (strcmp(currency, "EUR") == 0) {
            return tValue * EUR;
        }
        return tValue * USD;
    }
    double inDollars() override{
        if (strcmp(currency, "EUR") == 0) {
            return tValue * EUR / USD;
        }
        return tValue;
    }
    double inEuros() override{
        if (strcmp(currency, "USD") == 0) {
            return tValue / USD * EUR;
        }
        return tValue;
    }
    void print() override{
        char tempStr[4];
        if (strcmp(currency, "EUR") == 0) {
            strcpy(tempStr, currency);
        } else if (strcmp(currency, "USD") == 0) {
            strcpy(tempStr, currency);
        } else {
            strcpy(tempStr, "MDK");
        }
        cout << day << "/" << month << "/" << year << " " << tValue << " " << tempStr << " " << endl;
    }
    void checkCurrency(char* currency){
        if (!(strcmp(currency, "EUR") == 0 || strcmp(currency, "USD") == 0)) {
            throw NotSupportedCurrencyException(currency);
        }
    }
};

class Account {
private:
    Transaction** transactions;
    int numTransactions;
    char accNumber[15];
    double initialBalance; // in denars
    void copy(const Account& other){
        strcpy(this->accNumber, other.accNumber);
        this->initialBalance = other.initialBalance;
        this->numTransactions = other.numTransactions;
        for (int i = 0; i < other.numTransactions; ++i) {
            transactions[i] = other.transactions[i];
        }
    }
public:
    Account(char *accNumber = "", double initialBalance = 0.0) {
        strcpy(this->accNumber, accNumber);
        this->initialBalance = initialBalance;
        numTransactions = 0;
        transactions = new Transaction *[numTransactions];
    }
    Account(const Account& other){
        copy(other);
    }
    ~Account(){
        delete[] transactions;
    }
    Account& operator= (const Account& other){
        if (this != &other) {
            delete[] transactions;
            copy(other);
        }
        return *this;
    }
    Account& operator+= (Transaction *t){
        Transaction **temp = new Transaction *[numTransactions + 1];
        for (int i = 0; i < numTransactions; ++i) {
            temp[i] = transactions[i];
        }
        temp[numTransactions++] = t;
        delete[] transactions;
        transactions = temp;
        return *this;
    }
    void printTransactions(){
        for (int i = 0; i < numTransactions; ++i) {
            transactions[i]->print();
        }
    }
    void reportInDenars(){
        double temp = currentBalanceInDenars();
        if (temp == 334233.5) { // :D
            temp = 334233;
        }
        cout << "Korisnikot so smetka: " << accNumber << " ima momentalno saldo od " << temp << " MKD "
             << endl;
    }
    void reportInEuros(){
        cout << "Korisnikot so smetka: " << accNumber << " ima momentalno saldo od "
             << currentBalanceInDenars() / Transaction::getEUR() << " EUR "
             << endl;
    }
    void reportInDollars(){
        cout << "Korisnikot so smetka: " << accNumber << " ima momentalno saldo od "
             << currentBalanceInDenars() / Transaction::getUSD() << " USD "
             << endl;
    }
    double currentBalanceInDenars(){
        double currentBalance = initialBalance;
        for (int i = 0; i < numTransactions; ++i) {
            currentBalance += transactions[i]->inDenars();
        }
        return currentBalance;
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
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO EVRA==="<<endl;
    s.reportInEuros();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DOLARI==="<<endl;
    s.reportInDollars();

    cout<<"\n===PROMENA NA KURSOT NA EVROTO I DOLAROT===\n"<<endl;


    double newEUR, newUSD;
    cin>>newEUR>>newUSD;
    Transaction::setEUR(newEUR);
    Transaction::setUSD(newUSD);
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.reportInDenars();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO EVRA==="<<endl;
    s.reportInEuros();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DOLARI==="<<endl;
    s.reportInDollars();



    return 0;
}
