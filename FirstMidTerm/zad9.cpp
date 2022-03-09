#include<iostream>
#include <cstring>
using namespace std;

struct Voz{
    char dest[50];
    float km;
    int patnici;
};

struct  ZeleznickaStanica{
    char grad[20];
    Voz vozovi[30];
    int brVoz;
};

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad){
    ZeleznickaStanica min=zs[0];
    for (int i = 0; i < n; ++i) {
        if (strcmp(grad,zs[i].grad)==0){
                if (min.vozovi[i].km>=zs[i].vozovi[i].km){
                    min=zs[i];
            }
        }
    }cout<<"Najkratka relacija: "<<min.vozovi->dest<<"("<<min.vozovi->km<<")"<<endl;
}

int main(){

    int n;
    cin>>n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
        //se citaat infomracii za n zelezlnichkite stanici i se zacuvuvaat vo poleto zStanica
        char grad[30];
        int brVoz;
        cin>>zStanica[i].grad;
        cin>>zStanica[i].brVoz;
        Voz vozovi[30];

        for (int j = 0; j < brVoz; ++j) {
            char dest[50];
            float km;
            int patnici;
            cin>>vozovi[j].dest>>vozovi[j].km>>vozovi[i].patnici;
        }
    }

    char grad[25];
    cin>>grad;

    najkratkaRelacija(zStanica,n,grad);
    return 0;
}
