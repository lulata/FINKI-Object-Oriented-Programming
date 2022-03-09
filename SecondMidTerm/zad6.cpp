#include <iostream>
#include <cstring>

using namespace std;

class ExistingGame{
private:
    char msg[256];

public:
    ExistingGame(char msg_txt[]){
        strcpy(this->msg, msg_txt);
    }void message(){
        cout<<this->msg<<endl;
    }
};

class Game {
protected:
    char ime[100];
    float cena;
    bool prodazba;
public:
    Game(){
        ime[0] = '\0';
    }Game(char *ime, float cena, bool prodazba=false){
        strcpy(this->ime,ime);
        this->cena = cena;
        this->prodazba = prodazba;
    }virtual float get_price(){
        if (prodazba){
            return cena * 0.3F;
        }return cena;
    }bool operator==(Game& g){
        return !strcmp(this->ime, g.ime);
    }friend ostream & operator<<(ostream & o, const Game& g) {
        o<<"Game: "<< g.ime <<", regular price: $" << g.cena;
        if (g.prodazba){
            o<<", bought on sale";
        }return o;
    }friend istream & operator>>(istream & is, Game &g){
        is.get();
        is.getline(g.ime,100);
        is>>g.cena>>g.prodazba;
        return is;
    }

};

class SubscriptionGame : public Game {
protected:
    float mesecno;
    int mesec, god;

public:
    SubscriptionGame(){
        ime[0] = '\0';
    }SubscriptionGame(char *ime, float cena, bool prodazba, float mesecno, int mesec, int god):Game(ime, cena, prodazba){
        this->mesecno=mesecno;
        this->mesec=mesec;
        this->god=god;
    }float get_price(){
        float cena = Game::get_price();
        int meseci=0;
        if (god<2018){
            meseci = (12 - this->mesec) + (2017 - god)*12 + 5;
        }else {
            meseci = 5 - this->mesec;
        }cena += meseci * mesecno;
        return cena;
    }friend ostream & operator<<(ostream & o, SubscriptionGame& sg) {
        Game * tmp = dynamic_cast<Game*>(&sg);
        o << *tmp;
        o<<", monthly fee: $"<< sg.mesecno<<", purchased: "<< sg.mesec<< "-" << sg.god<<endl;
        return o;
    }friend istream & operator>>(istream & is, SubscriptionGame &g){
        is.get();
        is.getline(g.ime,100);
        is>>g.cena>>g.prodazba;
        is>>g.mesecno >> g.mesec >> g.god;
        return is;
    }

};

class User {
private:
    void obj_copy(const User * orig, User * cpy){
        strcpy(cpy->korisnickoIme, orig->korisnickoIme);
        cpy->brojIgri = orig->brojIgri;
        cpy->igri = new Game*[cpy->brojIgri];
        for (int i=0; i< cpy->brojIgri; ++i){
            cpy->igri[i] = new Game(*(orig->igri[i]));
        }
    }

protected:
    char korisnickoIme[100];
    Game ** igri;
    int brojIgri;
public:
    User (char const * const korisnickoIme="") {
        strcpy(this->korisnickoIme, korisnickoIme);
        igri = 0;
        brojIgri = 0;
    }User (const User& orig){
        obj_copy(&orig,this);
    }~User(){
        for (int i=0; i < this->brojIgri; ++i){
            delete this->igri[i];
        }delete [] igri;
    }User& operator=(User & orig){
        if (&orig != this){
            for (int i=0; i < this->brojIgri; ++i){
                delete orig.igri[i];
            }delete [] orig.igri;
            obj_copy(&orig, this);
        }return *this;
    }User& operator+=(Game&g){
        Game ** new_games = new Game*[this->brojIgri+1];

        for (int i=0; i < (this->brojIgri); ++i) {
            if ( (*(this->igri[i])) == g){
                throw ExistingGame("The game is already in the collection");
            }new_games[i] = igri[i];
        }for (int i=0; i < (this->brojIgri); ++i) {
            new_games[i] = igri[i];
        }SubscriptionGame * sg = dynamic_cast< SubscriptionGame* >(&g);
        if(sg){
            new_games[brojIgri] = new SubscriptionGame(*sg);
        }else {
            new_games[brojIgri] = new Game(g);
        }delete [] this->igri;
        this->igri = new_games;
        this->brojIgri++;
        return *this;
    }Game& get_game(int i){
        return (*(this->igri[i]));
    }float total_spent(){
        float sum = 0.0f;
        for (int i=0; i<this->brojIgri; ++i){
            sum += igri[i]->get_price();
        }return sum;
    }char const * const get_username(){
        return this->korisnickoIme;
    }int get_games_number(){
        return this->brojIgri;
    }

};

ostream & operator<<(ostream & o, User& u) {
    o<<"\nUser: "<<u.get_username()<<"\n";
    for (int i=0; i < u.get_games_number(); ++i){
        Game * g;
        SubscriptionGame * sg;
        g = &(u.get_game(i));
        sg = dynamic_cast<SubscriptionGame *> (g);
        if (sg){
            cout<<"- "<<(*sg);
        }else {
            cout<<"- "<<(*g);
        }cout<<"\n";
    }return o;
}

int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1){
        cout<<"Testing class Game and operator<< for Game"<<std::endl;
        cin.get();
        cin.getline(game_name,100);
        //cin.get();
        cin>>game_price>>game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout<<g;
    }
    else if (test_case_num == 2){
        cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
        cin.get();
        cin.getline(game_name, 100);

        cin>>game_price>>game_on_sale;

        cin>>sub_game_monthly_fee;
        cin>>sub_game_month>>sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout<<sg;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator>> for Game"<<std::endl;
        Game g;

        cin>>g;

        cout<<g;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
        SubscriptionGame sg;

        cin>>sg;

        cout<<sg;
    }
    else if (test_case_num == 5){
        cout<<"Testing class User and operator+= for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        try {

            for (int i=0; i<num_user_games; ++i){

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;

                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }

                //cout<<(*g);


                u+=(*g);
            }
        }catch(ExistingGame &ex){
            ex.message();
        }

        cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingGame for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingGame &ex){
                ex.message();
            }
        }

        cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);


            u+=(*g);
        }

        cout<<u;

        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
}
