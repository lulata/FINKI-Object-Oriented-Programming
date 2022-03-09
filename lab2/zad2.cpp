#include <iostream>
using namespace std;

class Krug {
private:
    float radius;
    const float pi=3.14;
public:
    Krug(){
        radius=0;
    }
    Krug(float r){
        radius=r;
    }
    ~Krug(){}
    float perimetar(){
        float l=2*pi*radius;
        return l;
    }float plostina(){
        float p=radius*radius*pi;
        return p;
    }float ednakvi(){
        if(perimetar()==plostina()){
            return 1;
        }else{
            return 0;
        }
    }
};

int zad2() {
	float r;
	cin >> r;
	//instanciraj objekt od klasata Krug cij radius e vrednosta procitana od tastatura
	 Krug k(r);
	cout << k.perimetar() << endl;
	cout << k.plostina() << endl;
	cout << k.ednakvi() <<endl;
    //instanciraj objekt od klasata Krug cij radius ne e definiran
    Krug k2;
	return 0;
}

