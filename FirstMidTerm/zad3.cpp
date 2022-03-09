#include<iostream>
#include<cstring>
using namespace std;

// vasiot kod za klasite ovde

class StockRecord{
private:
    char id[12];
    char ime[50];
    double cena;
    double momentalnaCena;
    int broj;
public:
    StockRecord(char *id="",char *ime="",double cena=0,int broj=0){
        strcpy(this->id,id);
        strcpy(this->ime,ime);
        this->cena=cena;
        this->momentalnaCena=momentalnaCena;
        this->broj=broj;
    }void setNewPrice(double c){
        this->momentalnaCena=c;
    }double value(){
        return broj*momentalnaCena;
    } double profit(){
        return broj*(momentalnaCena-cena);
    }friend ostream& operator<<(ostream &o,StockRecord &s){
        o<<s.ime<<" "<<s.broj<<" "<<s.cena<<" "<<s.momentalnaCena<<" "<<s.profit()<<endl;
    }~StockRecord(){}
};

class Client{
private:
    char imeprez[60];
    int idSmetka;
    StockRecord *stock;
    int brojStock;

    void copy(const Client &c){
        strcpy(this->imeprez,c.imeprez);
        this->idSmetka=c.idSmetka;
        this->brojStock=c.brojStock;
        this->stock=new StockRecord[c.brojStock];
        for (int i = 0; i < c.brojStock; ++i) {
            this->stock[i]=c.stock[i];
        }
    }

public:
    Client(char *imeprez="",int idSmetka=0,int brojStock=0){
        strcpy(this->imeprez,imeprez);
        this->idSmetka=idSmetka;
        this->brojStock=brojStock;
        this->stock=new StockRecord[brojStock];
        for (int i = 0; i < brojStock; ++i) {
            this->stock[i]=stock[i];
        }
    }Client(const Client &c){
        copy(c);
    }~Client(){
        delete [] stock;
    }double totalValue(){
        float total=0.0;
        for (int i = 0; i < brojStock; ++i) {
            total+=stock[i].value();
        }return total;
    }Client& operator +=(const StockRecord &s){
        StockRecord *temp=new StockRecord[brojStock+1];
        for (int i = 0; i < brojStock; ++i) {
            temp[i]=stock[i];
        }temp[brojStock++]=s;
        delete [] stock;
        stock=temp;
        return *this;
    }friend ostream& operator<<(ostream &o,Client &c){
        o<<c.idSmetka<<" "<<c.totalValue()<<endl;
        for (int i = 0; i < c.brojStock; ++i) {
            o<<c.stock[i];
        }return o;
    }
};
// ne menuvaj vo main-ot

int main(){

    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}
