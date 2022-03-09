#include<iostream>
#include<cstring>

using namespace std;

class Kvadrat {
protected:
    //TODO da se deklariraat promenlivite
    double a;

    void copy(const Kvadrat &k){
        this->a = k.a;
    }
public:
    //TODO default konstruktor
    Kvadrat(){
        a=0.0;
    }
    //TODO konstruktor so argumenti
    Kvadrat(double a){
        this->a=a;
    }
    //TODO copy konstruktor
    Kvadrat(const Kvadrat &k){
        copy(k);
    }
    //TODO double perimentar() {}
    double perimentar(){
        return 4 * a;
    }
    //TODO double plostina() {}
    double plostina(){
        return a * a;
    }
    //TODO void pecati();
    void pecati(){
        cout<< "Kvadrat so dolzina a=" << a << " ima plostina P=" << plostina() << " i perimetar L=" << perimentar()<< endl;
    }
};

class Pravoagolnik : public Kvadrat{ //da se vmetni nasleduvanjeto
private:
    //deklariranje na promenlivite
    double x;
    double y;
public:
    //TODO default konstruktor
    Pravoagolnik(){
        x = 0.0;
        y = 0.0;
    }
    //TODO konstruktor
    Pravoagolnik (const Kvadrat &k, double x, double y) : Kvadrat(k){
        this->x = x;
        this->y = y;
    }
    //TODO copy konstruktor
    Pravoagolnik (const Pravoagolnik &p){
        Kvadrat::copy(p);
        x = p.x;
        y = p.y;
    }
    //TODO prepokrivanje na metodite perimetar, plostina i pecati od klasata Kvadrat
    double perimentar(){
        return Kvadrat::perimentar() + 2 * x + 2 * y;
    }double plostina(){
        return Kvadrat::plostina() + a * x + a * y + y * x;
    }void pecati(){
        if ((a + x) == (a + y)) {
            a = a + x;
            Kvadrat::pecati();
        } else {
            cout << "Pravoagolnik so strani: " << a + x << " i " << a + y << " ima plostina P=" <<plostina() << " i perimetar L="<< perimentar()<< endl;
        }
    }
};

int main() {
    int n;
    double a,x,y;
    Kvadrat * kvadrati;
    Pravoagolnik * pravoagolnici;

    cin>>n;

    kvadrati = new Kvadrat [n];
    pravoagolnici = new Pravoagolnik [n];

    for (int i=0;i<n;i++){
        cin>>a;

        kvadrati[i] = Kvadrat(a);
    }

    for (int i=0;i<n;i++){
        cin>>x>>y;

        pravoagolnici[i]=Pravoagolnik(kvadrati[i],x,y);
    }

    int testCase;
    cin>>testCase;

    if (testCase==1){
        cout<<"===Testiranje na klasata Kvadrat==="<<endl;
        for (int i=0;i<n;i++)
            kvadrati[i].pecati();
    }
    else {
        cout<<"===Testiranje na klasata Pravoagolnik==="<<endl;
        for (int i=0;i<n;i++)
            pravoagolnici[i].pecati();
    }
}
