#include<iostream>
using namespace std;
//вашиот код треба да биде тука
class Vozilo{
protected:
    double tezina;
    int sirina;
    int visina;
public:
    Vozilo(double tezina = 0, int sirina = 0, int visina = 0){
        this->tezina = tezina;
        this->sirina = sirina;
        this->visina = visina;
    }void setMass(double m){
        tezina = m;
    }void setWidth(int m){
        sirina = m;
    }void setHeight(int m){
        visina = m;
    }double getMass(){
        return tezina;
    }int getWidth(){
        return sirina;
    }int getHeight(){
        return visina;
    }
    virtual int vratiDnevnaCena() = 0;

};

class Avtomobil : public Vozilo {
private:
    int brojVrati;
public:
    Avtomobil (double tezina = 0, int sirina = 0, int visina = 0, int brojVrati = 0):Vozilo(tezina,sirina,visina){
        this->brojVrati = brojVrati;
    }void setNumDoors(int m){
        brojVrati = m;
    }int getNumDoors(){
        return brojVrati;
    }int vratiDnevnaCena() override{
        if (brojVrati < 5) {
            return 100;
        }
        return 130;
    }
};

class Avtobus : public Vozilo {
private:
    int brojPatnici;
public:
    Avtobus (double tezina = 0, int sirina = 0, int visina = 0, int brojPatnici = 0):Vozilo(tezina,sirina,visina){
        this->brojPatnici = brojPatnici;
    }void setNumPassengers(int m){
        brojPatnici = m;
    }int getNumPassengers(){
        return brojPatnici;
    }int vratiDnevnaCena() override{
        return 5 * brojPatnici;
    }
};

class Kamion : public Vozilo {
private:
    double maxTezina;
public:
    Kamion (double tezina = 0, int sirina = 0, int visina = 0, double maxTezina = 0.0):Vozilo(tezina,sirina,visina){
        this->maxTezina = maxTezina;
    }void setMaxMass(double m){
        maxTezina = m;
    }double getMaxMass(){
        return maxTezina;
    }int vratiDnevnaCena() override{
        return (tezina + maxTezina) * 0.02;
    }
};

class ParkingPlac {
private:
    Vozilo **vozila;
    int brojVozila;
public:
    ParkingPlac(){
        vozila = nullptr;
        brojVozila = 0;
    }~ParkingPlac(){
        delete[] vozila;
    }ParkingPlac& operator+= (Vozilo *v){
        Vozilo **temp = new Vozilo *[brojVozila + 1];
        for (int i = 0; i < brojVozila; ++i) {
            temp[i] = vozila[i];
        }
        temp[brojVozila++] = v;
        delete[] vozila;
        vozila = temp;
    }float presmetajVkupnaMasa(){
        float sum = 0.0;
        for (int i = 0; i < brojVozila; ++i) {
            sum += vozila[i]->getMass();
        }
        return sum;
    }int brojVozilaPoshirokiOd(int l){
        int counter = 0;
        for (int i = 0; i < brojVozila; ++i) {
            if (vozila[i]->getWidth() > l) {
                counter++;
            }
        }
        return counter;
    }void calculateApearences(int &c, int &b, int &t){
        for (int i = 0; i < brojVozila; ++i) {
            Avtomobil *test1 = dynamic_cast<Avtomobil *>(vozila[i]);
            if (test1) {
                c++;
            }
            Avtobus *test2 = dynamic_cast<Avtobus *>(vozila[i]);
            if (test2) {
                b++;
            }
            Kamion *test3 = dynamic_cast<Kamion *>(vozila[i]);
            if (test3) {
                t++;
            }
        }
    }

    void pecati(){
        int cars, busses, trucks;
        cars = busses = trucks = 0;
        calculateApearences(cars, busses, trucks);
        cout << "Brojot na avtomobili e " << cars << ", brojot na avtobusi e " << busses << " i brojot na kamioni e "<< trucks << "." << endl;
    }int pogolemaNosivostOd(Vozilo& v){
        int counter = 0;
        for (int i = 0; i < brojVozila; ++i) {
            Kamion *test3 = dynamic_cast<Kamion *>(vozila[i]);
            if (test3) {
                if (test3->getMaxMass() > v.getMass()) {
                    counter++;
                }
            }
        }return counter;
    }double vratiDnevnaZarabotka(){
        double sum = 0.0;
        for (int i = 0; i < brojVozila; ++i) {
            sum += vozila[i]->vratiDnevnaCena();
        }
        return sum;
    }
};

int main(){
    ParkingPlac p;

    int n;
    cin>>n;
    int shirina,visina, broj;
    float masa,nosivost;
    for (int i=0;i<n;i++){
        int type;
        cin>>type;
        if(type==1){
            cin>>masa>>shirina>>visina>>broj;
            Avtomobil *a=new Avtomobil(masa,shirina,visina,broj);
            p+=a;
        }
        if(type==2){
            cin>>masa>>shirina>>visina>>broj;
            p+=new Avtobus(masa,shirina,visina,broj);
        }
        if(type==3){
            cin>>masa>>shirina>>visina>>nosivost;
            p+=new Kamion(masa,shirina,visina,nosivost);
        }
    }

    p.pecati();

    cout<<"\nZarabotkata e "<<p.vratiDnevnaZarabotka()<<endl;
    cout<<"Vkupnata masa e "<<p.presmetajVkupnaMasa()<<endl;
    cout<<"Brojot poshiroki od 5 e "<<p.brojVozilaPoshirokiOd(5)<<endl;
    Avtomobil a(1200,4,3,5);
    cout<<"Brojot na kamioni so nosivost pogolema od avtomobilot e "<<p.pogolemaNosivostOd(a)<<endl;


}
