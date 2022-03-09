#include<iostream>
#include<cstring>

using namespace std;

class NBAPlayer {
protected:
    char *ime;
    char tim[40];
    double poeni;
    double asistencii;
    double skokoj;

    void copy(const NBAPlayer& n){
        this->ime = new char[strlen(n.ime) + 1];
        strcpy(this->ime, n.ime);
        strcpy(this->tim, n.tim);
        this->poeni = n.poeni;
        this->asistencii = n.asistencii;
        this->skokoj = n.skokoj;
    }
public:
    NBAPlayer() {
        ime = nullptr;
        strcpy(tim, "");
        poeni = 0.0;
        asistencii = 0.0;
        skokoj = 0.0;
    }NBAPlayer(char *ime, char *tim, double poeni, double asistencii, double skokoj){
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        strcpy(this->tim, tim);
        this->poeni = poeni;
        this->asistencii = asistencii;
        this->skokoj = skokoj;
    }NBAPlayer (const NBAPlayer &n){
        copy(n);
    }NBAPlayer & operator=(const NBAPlayer & n){
        if (this != &n) {
            delete[] ime;
            copy(n);
        }return *this;
    }~NBAPlayer(){
        delete[] ime;
    }double rating() const{
        return 0.45 * poeni + 0.3 * asistencii + 0.25 * skokoj;
    }void print(){
        cout << ime << " - " << tim << endl;
        cout << "Points: " << poeni << endl;
        cout << "Assists: " << asistencii << endl;
        cout << "Rebounds: " << skokoj << endl;
        cout << "Rating: " << rating() << endl;
    }
};

class AllStarPlayer : public NBAPlayer {
private:
    double allstarPoeni;
    double allstarAsistencii;
    double allStarSkokoj;

    void copy(const AllStarPlayer &a){
        NBAPlayer::copy(a);
        this->allstarPoeni = a.allstarPoeni;
        this->allstarAsistencii = a.allstarAsistencii;
        this->allStarSkokoj = a.allStarSkokoj;
    }

public:
    AllStarPlayer(){
        allstarPoeni = 0.0;
        allstarAsistencii = 0.0;
        allStarSkokoj = 0.0;
    }AllStarPlayer(char *ime, char *tim, double poeni, double asistencii, double skokoj,double allstarPoeni, double allstarAsistencii, double allStarSkokoj) : NBAPlayer(ime, tim,poeni,asistencii,skokoj){
        this->allstarPoeni = allstarPoeni;
        this->allstarAsistencii = allstarAsistencii;
        this->allStarSkokoj = allStarSkokoj;
    }AllStarPlayer(NBAPlayer &n, double allstarPoeni, double allstarAsistencii, double allStarSkokoj) : NBAPlayer(n) {
        this->allstarPoeni = allstarPoeni;
        this->allstarAsistencii = allstarAsistencii;
        this->allStarSkokoj = allStarSkokoj;
    }~AllStarPlayer(){}
    AllStarPlayer (const AllStarPlayer & a){
        copy(a);
    }AllStarPlayer & operator= (const AllStarPlayer& a){
        if (this != &a) {
            delete[] ime;
            copy(a);
        }
        return *this;
    }double allStarRating(){
        return 0.3 * allstarPoeni + 0.4 * allstarAsistencii + 0.3 * allStarSkokoj;
    }double rating(){
        return (NBAPlayer::rating() + allStarRating()) / 2.0;
    }void print(){
        NBAPlayer::print();
        cout << "All Star Rating: " << allStarRating() << endl;
        cout << "New Rating: " << rating() << endl;
    }
};


int main() {

    char name[50];
    char team[40];
    double points;
    double assists;
    double rebounds;
    double allStarPoints;
    double allStarAssists;
    double allStarRebounds;

    NBAPlayer * players = new NBAPlayer[5];
    AllStarPlayer * asPlayers = new AllStarPlayer[5];
    int n;
    cin >> n;

    if (n == 1) {

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            cin >> name >> team >> points >> assists >> rebounds;
            players[i] = NBAPlayer(name,team,points,assists,rebounds);
            players[i].print();
        }
    }
    else if (n == 2) {

        for (int i=0; i < 5; ++i){
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            players[i] = NBAPlayer(name,team,points,assists,rebounds);
            asPlayers[i] = AllStarPlayer(players[i],allStarPoints,allStarAssists,allStarRebounds);
        }

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            players[i].print();

        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            asPlayers[i].print();

    }
    else if (n == 3) {

        for (int i=0; i < 5; ++i){
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,
                                         allStarPoints,allStarAssists,allStarRebounds);
        }
        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            asPlayers[i].print();

    }

    delete [] players;
    delete [] asPlayers;
}
