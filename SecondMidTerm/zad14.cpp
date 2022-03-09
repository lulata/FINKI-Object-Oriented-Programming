#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class SMS{
protected:
    float osnovnaCena;
    char kadeEPratena[15];
    static const int TAX = 18;
    void copy(const SMS& other){
        strcpy(this->kadeEPratena, other.kadeEPratena);
        this->osnovnaCena = other.osnovnaCena;
    }
public:
    SMS(const char *kadeEPratena = "", float osnovnaCena = 0) {
        strcpy(this->kadeEPratena, kadeEPratena);
        this->osnovnaCena = osnovnaCena;
    }SMS (const SMS& other){
        copy(other);
    }SMS& operator= (const SMS& other){
        if (this != &other) {
            copy(other);
        }return *this;
    }virtual float SMS_cena() = 0;
    void print(ostream& out){
        out << "Tel: " << kadeEPratena << " - cena: " << SMS_cena() << "den." <<endl;
    }friend ostream& operator<< (ostream& out, SMS& s){
        s.print(out);
        return out;
    }
};

class RegularSMS : public SMS{
private:
    char poraka[1000];
    bool roaming;
    static int PERCENT_REGULAR;
    void copy(const RegularSMS& other){
        SMS::copy(other);
        strcpy(this->poraka, other.poraka);
        this->roaming = other.roaming;
    }
public:
    RegularSMS(const char *kadeEPratena = "", float osnovnaCena = 0, const char *poraka = "", bool roaming = false) : SMS(kadeEPratena, osnovnaCena) {
        strcpy(this->poraka, poraka);
        this->roaming = roaming;
    }RegularSMS (const RegularSMS& other){
        copy(other);
    }RegularSMS& operator= (const RegularSMS& other){
        if (this != &other) {
            copy(other);
        }return *this;
    }float SMS_cena() override {
        float price;
        if (roaming) {
            price = osnovnaCena + osnovnaCena * PERCENT_REGULAR / 100;
        } else {
            price = osnovnaCena + osnovnaCena * TAX / 100;
        }price = price + price * floor(strlen(poraka) / 160);
        return price;
    }static int getPERCENT_REGULAR(){
        return PERCENT_REGULAR;
    }static void setPERCENT_REGULAR(int n){
        PERCENT_REGULAR = n;
    }
};

class SpecialSMS : public SMS{
private:
    bool humanitarna;
    static int PERCENT_SPECIAL;
    void copy(const SpecialSMS& other){
        SMS::copy(other);
        this->humanitarna = other.humanitarna;
    }
public:
    SpecialSMS(const char *kadeEPratena = "", float osnovnaCena = 0, bool humanitarna = false) : SMS(kadeEPratena, osnovnaCena) {
        this->humanitarna = humanitarna;
    }SpecialSMS (const SpecialSMS& other){
        copy(other);
    }SpecialSMS& operator= (const SpecialSMS& other){
        if (this != &other) {
            copy(other);
        }return *this;
    }float SMS_cena() override {
        float price;
        if (!humanitarna) {
            price = osnovnaCena + (osnovnaCena * PERCENT_SPECIAL / 100.0);
        } else {
            return osnovnaCena;
        }return price;
    }static int getPERCENT_SPECIAL(){
        return PERCENT_SPECIAL;
    }static void setPERCENT_SPECIAL(int n){
        PERCENT_SPECIAL = n;
    }

};

void vkupno_SMS(SMS **msgs, int n) {
    int numRegular, numSpecial;
    numRegular = numSpecial = 0;
    float priceRegual, priceSpecial;
    priceRegual = priceSpecial = 0.0;
    for (int i = 0; i < n; ++i) {
        RegularSMS *test = dynamic_cast<RegularSMS *>(msgs[i]);
        if (test) {
            numRegular++;
            priceRegual += msgs[i]->SMS_cena();
        } else {
            numSpecial++;
            priceSpecial += msgs[i]->SMS_cena();
        }
    }

    cout << "Vkupno ima " << numRegular << " regularni SMS poraki i nivnata cena e: " << priceRegual << endl;
    cout << "Vkupno ima " << numSpecial << " specijalni SMS poraki i nivnata cena e: " << priceSpecial << endl;
}

int RegularSMS::PERCENT_REGULAR = 300;
int SpecialSMS::PERCENT_SPECIAL = 150;

int main(){

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i<n; i++){

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            }
            else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::setPERCENT_REGULAR(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::setPERCENT_SPECIAL(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}
