#include <iostream>
#include <cstring>
using namespace std;

#define MAX 50

enum TypeCustomer {standard = 0, loyal, vip};

class UserExistsException{
public:
    UserExistsException(){}
    void msg(){
        cout << "The user already exists in the list!" << endl;
    }
};

class Customer{
protected:
    char ime[50];
    char email[50];
    TypeCustomer vidKupuvac;
    static int BASE_DISCOUNT;
    static const int ADDITIONAL_DISCOUNT;
    int brojKupeni;

    void copy(const Customer& c){
        strcpy(this->ime, c.ime);
        strcpy(this->email, c.email);
        this->vidKupuvac = c.vidKupuvac;
        this->brojKupeni = c.brojKupeni;
    }

public:
    Customer(const char* ime = "", const char* email = "", TypeCustomer vidKupuvac = standard, int brojKupeni = 0){
        strcpy(this->ime, ime);
        strcpy(this->email, email);
        this->vidKupuvac = vidKupuvac;
        this->brojKupeni = brojKupeni;
    }Customer (const Customer& c){
        copy(c);
    }Customer& operator= (const Customer& c){
        if (this != &c) {
            copy(c);
        }return *this;
    }static void setDiscount1(int n){
        BASE_DISCOUNT = n;
    }int availableDiscount() const{
        if (vidKupuvac == standard) {
            return 0;
        } else if (vidKupuvac == loyal) {
            return BASE_DISCOUNT;
        } else {
            return BASE_DISCOUNT + ADDITIONAL_DISCOUNT;
        }
    }friend ostream& operator<< (ostream& out, const Customer& c){
        const char *enumToText[] = {"standard", "loyal", "vip"};
        out << c.ime << endl;
        out << c.email << endl;
        out << c.brojKupeni << endl;
        out << enumToText[c.vidKupuvac] << " " << c.availableDiscount() << endl;
        return out;
    }const char* getEmail(){
        return email;
    }TypeCustomer& getTypeCustomer(){
        return vidKupuvac;
    }int getNumBoughtProducts(){
        return brojKupeni;
    }
};

class FINKI_bookstore{
private:
    Customer *musterii;
    int brMusteri;

    void copy(const FINKI_bookstore& f){
        this->brMusteri = f.brMusteri;
        this->musterii = new Customer[f.brMusteri];
        for (int i = 0; i < f.brMusteri; ++i) {
            this->musterii[i] = f.musterii[i];
        }
    }

public:
    FINKI_bookstore(){
        musterii = nullptr;
        brMusteri = 0;
    }FINKI_bookstore (const FINKI_bookstore& f){
        copy(f);
    }FINKI_bookstore& operator= (const FINKI_bookstore& f){
        if (this != &f) {
            delete[] musterii;
            copy(f);
        }return *this;
    }~FINKI_bookstore(){
        delete[] musterii;
    }void setCustomers(Customer *newCustomers, int n){
        Customer *temp = new Customer[brMusteri + n];
        int i = 0;
        for (i = 0; i < brMusteri; ++i) {
            temp[i] = musterii[i];
        }int j = 0;
        while (i < brMusteri + n) {
            temp[i++] = newCustomers[j++];
        }
        brMusteri = brMusteri + n;
        delete[] musterii;
        musterii = temp;
    }friend ostream& operator<< (ostream& out, const FINKI_bookstore& f){
        for (int i = 0; i < f.brMusteri; ++i) {
            out << f.musterii[i];
        }return out;
    }
    FINKI_bookstore& operator+= (Customer& c){
        if (isThereAnother(c)) {
            throw UserExistsException();
        }this->setCustomers(&c, 1);
    }bool isThereAnother(Customer& c){
        for (int i = 0; i < brMusteri; ++i) {
            if (strcmp(musterii[i].getEmail(), c.getEmail()) == 0) {
                return true;
            }
        }return false;
    }
    void update(){
        for (int i = 0; i < brMusteri; ++i) {
            if (musterii[i].getTypeCustomer() == standard && musterii[i].getNumBoughtProducts() > 5) {
                musterii[i].getTypeCustomer() = loyal;
            } else if (musterii[i].getTypeCustomer() == loyal && musterii[i].getNumBoughtProducts() > 10) {
                musterii[i].getTypeCustomer() = vip;
            }
        }
    }

};

int Customer::BASE_DISCOUNT = 10;
const int Customer::ADDITIONAL_DISCOUNT = 20;


int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (TypeCustomer) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (TypeCustomer) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (TypeCustomer) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (TypeCustomer) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (TypeCustomer) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (TypeCustomer) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (TypeCustomer) tC, numProducts);

        try {
            fc += c;
        }catch (UserExistsException& e){
            e.msg();
        }

        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (TypeCustomer) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
