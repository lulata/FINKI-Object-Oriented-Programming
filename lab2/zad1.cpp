#include <iostream>
using namespace std;

class Agol {
private:
    int agol;
    int minuti;
    int sec;
public:
    Agol(){}
    Agol(int a, int m, int s){
        agol=a;
        minuti=m;
        sec=s;
    }
    ~Agol(){}
    void set_stepeni(int a){
        agol=a;
    }void set_minuti(int m){
        minuti=m;
    }void set_sekundi(int s){
        sec=s;
    }int to_sekundi(){
        int vkupno=0;
        vkupno= (agol*3600)+(minuti*60)+sec;
    }int getSekundi(){
        return sec;
    }
};


bool changeOfSeconds(Agol a, int sec){
	return a.getSekundi()!=sec;
}
int proveri(int st,int m, int s){
    if(st<=90&&m<=60&&s<=60){
        return 1;
    }else{
        return 0;
    }
}

int zad1() {
    Agol a1;

    //da se instancira objekt od klasata Agol
    int deg, min, sec;
    cin >> deg >> min >> sec;

    if (proveri(deg, min, sec)) {

    	a1.set_stepeni(deg);
        a1.set_minuti(min);
        a1.set_sekundi(sec);
        cout << a1.to_sekundi();
        if (changeOfSeconds(a1,sec))
			cout << "Ne smeete da gi menuvate sekundite vo ramkite na klasata!" << endl;

    }else{
        cout<<"Nevalidni vrednosti za agol"<<endl;
    }

    return 0;
}

