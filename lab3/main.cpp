#include <iostream>
#include <cstring>

using namespace std;

class Potpisuvac
{
private:
    char ime[20];
    char prezime[20];
    char embg[14];
public:
    Potpisuvac(){}
    Potpisuvac(char *ime,char *prezime,char *embg){
        strcpy(this->ime,ime);
        strcpy(this->prezime,prezime);
        strcpy(this->embg,embg);
    }~Potpisuvac(){}
    Potpisuvac(const Potpisuvac &p){
        strcpy(this->ime,p.ime);
        strcpy(this->prezime,p.prezime);
        strcpy(this->embg,p.embg);
    }char *getEmbg(){
        return embg;
    }
};
class Dogovor{
private:
    int brdog;
    char kat[50];
    Potpisuvac pole[3];
public:
    Dogovor(){}
    Dogovor(int brdog,char *kat,Potpisuvac pole[]){
        this->brdog=brdog;
        strcpy(this->kat,kat);
        this->pole[0]=pole[0];
        this->pole[1]=pole[1];
        this->pole[2]=pole[2];
    }~Dogovor(){}
    bool proverka(){
        if(strcmp(pole[0].getEmbg(),pole[1].getEmbg()) == 0){
            return 1;
        } if(strcmp(pole[1].getEmbg(),pole[2].getEmbg()) == 0){
            return 1;
        } if(strcmp(pole[0].getEmbg(),pole[2].getEmbg()) == 0){
            return 1;
        }else {
            return 0;
        }
    }
};


//ne smee da se menuva main funkcijata
int main()
{
    char embg[13], ime[20], prezime[20], kategorija[20];
    int broj, n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> embg >> ime >> prezime;
        Potpisuvac p1(ime, prezime, embg);
        cin >> embg >> ime >> prezime;
        Potpisuvac p2(ime, prezime, embg);
        cin >> embg >> ime >> prezime;
        Potpisuvac p3(ime, prezime, embg);
        cin >> broj >> kategorija;
        Potpisuvac p[3];
        p[0] = p1; p[1] = p2; p[2] = p3;
        Dogovor d(broj, kategorija, p);
        cout << "Dogovor " << broj << ":" << endl;
        if(d.proverka() == true)
            cout << "Postojat potpishuvaci so ist EMBG" << endl;
        else
            cout << "Ne postojat potpishuvaci so ist EMBG" << endl;
    }
    return 0;
}
