#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class InvalidPassword {
    char *poraka;
public:
    InvalidPassword(char *poraka){
        this->poraka = new char[strlen(poraka) + 1];
        strcpy(this->poraka, poraka);
    }void message(){
        cout << poraka << endl;
    }~InvalidPassword(){
        delete[] poraka;
    }
};

class InvalidEmail  {
    char *poraka;
public:
    InvalidEmail(char *poraka){
        this->poraka = new char[strlen(poraka) + 1];
        strcpy(this->poraka, poraka);
    }void message(){
        cout << poraka << endl;
    }~InvalidEmail(){
        delete[] poraka;
    }
};

class MaximumSizeLimit  {
private:
    int maxNumUsers;
public:
    MaximumSizeLimit (int num){
        maxNumUsers = num;
    }void message(){
        cout << "You can't add more than " << maxNumUsers << " users." << endl;
    }
};

class User{
protected:
    char username[50];
    char pwd[50];
    char email[50];

public:
    User(char *username = "", char *pwd = "", char *email = "")  {
        checkPassword(pwd);
        checkEmail(email);
        strcpy(this->username, username);
        strcpy(this->pwd, pwd);
        strcpy(this->email, email);
    }

    virtual double popularity() = 0;

    void checkPassword(char *pwd){
        bool fUppercase,fLowercase, fNumber;
        fUppercase = fLowercase = fNumber = false;
        for (int i = 0; i < strlen(pwd); ++i) {
            if (isupper(pwd[i])) {
                fUppercase = true;
            }
            if (islower(pwd[i])) {
                fLowercase = true;
            }
            if (isdigit(pwd[i])) {
                fNumber = true;
            }
        }if (!(fUppercase && fLowercase && fNumber)) {
            throw InvalidPassword("Password is too weak.");
        }
    };void checkEmail(char *e_mail){
        int counter = 0;
        for (int i = 0; i < strlen(e_mail); ++i) {
            if (e_mail[i] == '@') {
                counter++;
            }
        }
        if (counter != 1) {
            throw InvalidEmail("Mail is not valid.");
        }
    }
};

class FacebookUser : public User {
private:
    int brPrijateli;
    int brLikes;
    int brKom;
    static const float koefLike;
    static const float koefKom;
public:
    FacebookUser(char *username = "", char *pwd = "", char *email = "", int brPrijateli = 0, int brLikes = 0,int brKom = 0) : User(username,pwd,email){
        this->brPrijateli = brPrijateli;
        this->brLikes = brLikes;
        this->brKom = brKom;
    }double popularity() override{
        return brPrijateli + brLikes * koefLike + brKom * koefKom;
    }
};

const float FacebookUser::koefLike = 0.1;
const float FacebookUser::koefKom = 0.5;

class TwitterUser : public User {
private:
    int brSledaci;
    int brTweets;
    static const float koefTweets;
public:
    TwitterUser(char *username = "", char *pwd = "", char *email = "", int brSledaci = 0, int brTweets = 0): User(username, pwd, email) {
        this->brSledaci = brSledaci;
        this->brTweets = brTweets;
    }double popularity() override{
        return brSledaci + brTweets * koefTweets;
    }
};

const float TwitterUser::koefTweets = 0.5;

class SocialNetwork{
private:
    User **korisinic;
    int brKorisinci;
    static int brMaxKorisinici;

    void copy(const SocialNetwork &s){
        this->korisinic = s.korisinic;
        korisinic = new User *[s.brKorisinci];
        for (int i = 0; i < s.brKorisinci; ++i) {
            this->korisinic[i] = korisinic[i];
        }
    }

public:
    SocialNetwork (){
        this->brKorisinci = 0;
        korisinic = new User *[brKorisinci];
    }SocialNetwork (const SocialNetwork &s){
        copy(s);
    }SocialNetwork& operator= (const SocialNetwork &s){
        if (this != &s) {
            delete[] korisinic;
            copy(s);
        }return *this;
    }
    SocialNetwork& operator+= (User *u){
        if (brMaxKorisinici == brKorisinci) {
            throw MaximumSizeLimit(brKorisinci);
        }else{
            User **temp = new User *[brKorisinci + 1];
            for (int i = 0; i < brKorisinci; ++i) {
                temp[i] = korisinic[i];
            }temp[brKorisinci++] = u;
            delete[] korisinic;
            korisinic = temp;
        }
    }bool isThereAnother(User *u){
        for (int i = 0; i < brKorisinci; ++i) {
            if (korisinic[i] == u) {
                return false;
            }
        }return true;
    }float avgPopularity(){
        float sum = 0.0;
        for (int i = 0; i < brKorisinci; ++i) {
            sum += korisinic[i]->popularity();
        }return sum / (float) brKorisinci;
    }
    void changeMaximumSize(int number){
        brMaxKorisinici = number;
    }

};

int SocialNetwork::brMaxKorisinici = 5;



int main() {

    SocialNetwork network = SocialNetwork();
    int n;
    cin >> n;
    char username[50];
    char password[50];
    char email[50];
    int userType;
    for (int i=0; i < n; ++i) {
        cin >> username;
        cin >> password;
        cin >> email;
        cin >> userType;
        if (userType == 1) {
            int friends;
            int likes;
            int comments;
            cin >> friends >> likes >> comments;

            // TODO: Try-catch
            try {
                User *u = new FacebookUser(username, password, email, friends, likes, comments);
                network += u;
            } catch (InvalidPassword & i){
                i.message();
            } catch (InvalidEmail & i){
                i.message();
            } catch (MaximumSizeLimit & i){
                i.message();
            }

        }
        else {
            int followers;
            int tweets;
            cin >> followers >> tweets;

            // TODO: Try-catch
            try {
                User *u = new TwitterUser(username, password, email, followers, tweets);
                network += u;
            }catch (InvalidPassword & i){
                i.message();
            } catch (InvalidEmail & i){
                i.message();
            } catch (MaximumSizeLimit & i){
                i.message();
            }
        }

    }
    network.changeMaximumSize(6);
    cin >> username;
    cin >> password;
    cin >> email;
    int followers;
    int tweets;
    cin >> followers >> tweets;

    // TODO: Try-catch
    try {
        User *u = new TwitterUser(username, password, email, followers, tweets);
        network += u;
    }catch (InvalidPassword & i){
        i.message();
    } catch (InvalidEmail & i){
        i.message();
    } catch (MaximumSizeLimit & i){
        i.message();
    }

    cout << network.avgPopularity();
    return 0;

}
