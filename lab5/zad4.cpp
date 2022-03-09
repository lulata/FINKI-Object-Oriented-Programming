#include <iostream>
#include <cstring>

using namespace std;

class PlDrustvo{
private:
    char *ime;
    int tura;
    int clen;

    void copy(const PlDrustvo &p){
        this->ime=new char[strlen(p.ime)+1];
        strcpy(this->ime,p.ime);
        this->tura=p.tura;
        this->clen=p.clen;
    }

public:
    PlDrustvo(char *ime="",int tura=0,int clen=0){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->tura=tura;
        this->clen=clen;
    }PlDrustvo(const PlDrustvo &p){
        copy(p);
    }PlDrustvo& operator=(const PlDrustvo &p){
        if(this!=&p){
            delete [] ime;
            copy(p);
        }return *this;
    }~PlDrustvo(){
        delete [] ime;
    } friend ostream& operator<<(ostream &o, const PlDrustvo &p){
        o<<"Ime: "<<p.ime<<" Turi: "<<p.tura<<" Clenovi: "<<p.clen<<endl;
    }bool operator >(PlDrustvo &p){
        return this->clen>p.clen;
    }bool operator <(PlDrustvo &p){
        return this->clen<p.clen;
    }PlDrustvo operator+(PlDrustvo &p){
        PlDrustvo temp;
        temp.clen=this->clen+p.clen;
        if(this->clen>p.clen){
            temp.ime=new char[strlen(this->ime)+1];
            strcpy(temp.ime,this->ime);
            temp.tura=this->tura;
        }else{
            temp.ime=new char[strlen(p.ime)+1];
            strcpy(temp.ime,p.ime);
            temp.tura=p.tura;
        }
        return temp;
    }
};
void najmnoguClenovi(PlDrustvo p[],int n){
    PlDrustvo max=p[0];
    for (int i = 0; i < n; ++i) {
        if(p[i]>max){
            max=p[i];
        }
    }
    cout<<"Najmnogu clenovi ima planinarskoto drustvo: "<<max;
}
int main(){

    PlDrustvo drustva[3];
    PlDrustvo pl;
    for (int i=0;i<3;i++)
    {
        char ime[100];
        int brTuri;
        int brClenovi;
        cin>>ime;
        cin>>brTuri;
        cin>>brClenovi;
        PlDrustvo p(ime,brTuri,brClenovi);
        drustva[i] = p;

    }

    pl = drustva[0] + drustva[1];
    cout<<pl;

    najmnoguClenovi(drustva, 3);

    return 0;
}
