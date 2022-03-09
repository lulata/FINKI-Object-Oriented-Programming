#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const float pi = 3.14;

class Igrachka {
public:
    virtual float getVolumen() = 0;
    virtual float getMasa() = 0;
    virtual float getPlostina() = 0;
};

class Forma {
protected:
    char boja[100];
    int gustina;

    void copy(const Forma &f){
        strcpy(this->boja, f.boja);
        this->gustina = f.gustina;
    }
public:
    // да се имплементираат потребните методи
    Forma(char *boja = "", int gustina = 0){
        strcpy(this->boja, boja);
        this->gustina = gustina;
    }Forma(const Forma &f){
            copy(f);
    }
};

class Topka : public Forma, public Igrachka{
private:
    int radius;

    void copy(const Topka &t){
        Forma::copy(t);
        this->radius = t.radius;
    }
public:
    Topka (char *boja = "", int gustina = 0, int radius = 0) : Forma(boja,gustina){
        this->radius = radius;
    }Topka(const Topka &t){
        copy(t);
    }Topka& operator= (const Topka &t){
        if (this != &t) {
            copy(t);
        }
        return *this;
    }float getVolumen() override{
        return pow(radius, 3) * pi * 4 / 3;
    }float getMasa() override{
        return gustina * getVolumen();
    }float getPlostina() override{
        return 4 * pi * pow(radius, 2);
    }
};

class Kocka : public Forma, public Igrachka{
private:
    int visina;
    int sirina;
    int dlabocina;

    void copy(const Kocka &k){
        Forma::copy(k);
        this->visina = k.visina;
        this->sirina = k.sirina;
        this->dlabocina = k.dlabocina;
    }

public:
    Kocka (char *boja = "", int gustina = 0, int visina = 0, int sirina = 0, int dlabocina = 0) : Forma(boja,gustina){
        this->visina = visina;
        this->sirina = sirina;
        this->dlabocina = dlabocina;
    }Kocka (const Kocka &k){
        copy(k);
    }Kocka& operator= (const Kocka &k){
        if (this != &k) {
            copy(k);
        }return *this;
    }float getVolumen() override{
        return visina * sirina * dlabocina;
    }float getMasa() override{
        return gustina * getVolumen();
    }float getPlostina() override{
        return 2 * (sirina * dlabocina + sirina * visina + dlabocina * visina);
    }
};

void totalMass(Igrachka **igra, Kocka &k, int num){
    float totalMass = 0.0;
    for (int i = 0; i < num; ++i) {
        totalMass += igra[i]->getMasa();
    }cout << (totalMass > k.getMasa() ? "DA" : "NE") << endl;
}

Igrachka *toyWithMaxVolume(Igrachka **igra, int num){
    int brojac = 0;
    float maxV = 0.0;
    for (int i = 0; i < num; ++i) {
        if (maxV < igra[i]->getVolumen()) {
            maxV = igra[i]->getVolumen();
            brojac = i;
        }
    }return igra[brojac];
}

Igrachka *toyWithMinArea(Igrachka **igra, int num){
    int brojac = 0;
    bool flag = true;
    float minP;
    for (int i = 0; i < num; ++i) {
        if (flag) {
            flag = false;
            minP = igra[i]->getPlostina();
            continue;
        }if (minP > igra[i]->getPlostina()) {
            minP = igra[i]->getPlostina();
            brojac = i;
        }
    }return igra[brojac];
}

void differenceVolumes(Igrachka **igra, Kocka &k, int num){
    cout << "Razlikata e: " << fabs(k.getVolumen() - toyWithMaxVolume(igra, num)->getVolumen()) << endl;
}
void differenceAreas(Igrachka **igra, Kocka &k, int num){
    cout << "Razlikata e: " << fabs(k.getPlostina()- toyWithMinArea(igra, num)->getPlostina()) << endl;
}


int main(){
    //vnesi informacii za kupche
    int num, tip, radius, gustina, visina, sirina, dlabocina;
    char boja[100];
    cin >> num;
    Igrachka **igra = new Igrachka *[num];
    for (int i = 0; i < num; ++i) {
        cin >> tip;
        if (tip == 1){
            cin >> boja >> gustina >> radius;
            igra[i] = new Topka(boja, gustina, radius);
        }else if (tip == 2) {
            cin >> boja >> gustina >> visina >> sirina >> dlabocina;
            igra[i] = new Kocka(boja, gustina, visina, sirina, dlabocina);
        }
    }

    //vnesi informacii za igrachkata na Petra
    cin >> boja >> gustina >> visina >> sirina >> dlabocina;
    Kocka k(boja, gustina, visina, sirina, dlabocina);

    //baranje 1
    totalMass(igra, k, num);

    //baranje 2
    differenceVolumes(igra, k, num);

    //дополнително барање 2
    differenceAreas(igra, k, num);

    for(int i = 0; i < num; i++){
        delete igra[i];
    }
    delete[] igra;

    return 0;
}
