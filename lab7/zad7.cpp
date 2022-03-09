#include<iostream>
#include <cstring>
using namespace std;


class Secret{
public:
    virtual double simpleEntropy() = 0;
    virtual int total() = 0;
    friend bool operator== (Secret& s1, Secret& s2);
    friend bool operator!= (Secret &s1, Secret &s2);
};

bool operator== (Secret& s1, Secret& s2){
    return (s1.total() == s2.total());
}
bool operator!= (Secret& s1, Secret& s2){
    return !(s1 == s2);
}



class DigitSecret : public Secret{
private:
    int brojki[100];
    int len;

    void copy (const DigitSecret& d){
        this->len = d.len;
        for (int i = 0; i < d.len; ++i) {
            this->brojki[i] = d.brojki[i];
        }
    }

public:
    DigitSecret(int *brojki = nullptr, int len = 0){
        this->len = len;
        for (int i = 0; i < len; ++i) {
            this->brojki[i] = brojki[i];
        }
    }DigitSecret (const DigitSecret& d){
        copy(d);
    }DigitSecret& operator= (const DigitSecret& d){
        if (this != &d) {
            copy(d);
        }return *this;
    }double simpleEntropy() override{
        int counter = 0;
        for (int i = 0; i < len; ++i) {
            int flag = 1;
            for (int j = 0; j < len; ++j) {
                if (brojki[i] == brojki[j]) {
                    if (i != j) {
                        flag = 0;
                        break;
                    }
                }
            }if (flag) {
                counter++;
            }
        }return ((double)counter / total());
    }int total() override{
        return len;
    }friend ostream& operator<< (ostream& out, DigitSecret& s){
        for (int i = 0; i < s.len; ++i) {
            out << s.brojki[i];
        }
        out << " Simple entropy: " << s.simpleEntropy() << " Total: " << s.total();
        return out;
    }

};

class CharSecret : public Secret{
private:
    char karakteri[100];

    void copy(const CharSecret& c){
        strcpy(this->karakteri, c.karakteri);
    }

public:
    CharSecret (char* characters=""){
        strcpy(this->karakteri, characters);
    }CharSecret (const CharSecret& c){
        copy(c);
    }CharSecret& operator= (const CharSecret& c){
        if (this != &c) {
            copy(c);
        }return *this;
    }double simpleEntropy() override{
        int counter = 0;
        for (int i = 0; i < strlen(karakteri); ++i) {
            int flag = 1;
            for (int j = 0; j < strlen(karakteri); ++j) {
                if (karakteri[i] == karakteri[j]) {
                    if (i != j) {
                        flag = 0;
                        break;
                    }
                }
            }
            if (flag) {
                counter++;
            }
        }
        return ((double)counter / total());

    }int total() override{
        return strlen(karakteri);
    }friend ostream& operator<< (ostream& out, CharSecret& s){
        out << s.karakteri;
        out << " Simple entropy: " << s.simpleEntropy() << " Total: " << s.total();
        return out;
    }
};

void process(Secret **secrets, int n){
    int index = 0;
    double maxEntropy = 0.0;
    for (int i = 0; i < n; ++i) {
        if (secrets[i]->simpleEntropy() > maxEntropy) {
            maxEntropy = secrets[i]->simpleEntropy();
            index = i;
        }
    }
    DigitSecret *test1 = dynamic_cast<DigitSecret *>(secrets[index]);
    if (test1) {
        cout << *test1;
    }
    CharSecret *test2 = dynamic_cast<CharSecret *>(secrets[index]);
    if (test2) {
        cout << *test2;
    }
}

void printAll(Secret **secrets, int n){
    for (int i = 0; i < n; ++i) {
        DigitSecret *test1 = dynamic_cast<DigitSecret *>(secrets[i]);
        if (test1) {
            cout << *test1 << endl;
        }
        CharSecret *test2 = dynamic_cast<CharSecret *>(secrets[i]);
        if (test2) {
            cout << *test2 << endl;
        }
    }
}


int main() {
    int n;
    cin >> n;
    if(n == 0) {
        cout << "Constructors" << endl;
        int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        cout << "OK" << endl;
    } else if(n == 1) {
        cout << "operator <<" << endl;
        int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        cout << ds << endl;
        cout << cs << endl;
    }  else if(n == 2) {
        cout << "== and !=" << endl;
        int numbers [] = {1,2,3,4,5};
        DigitSecret ds(numbers,5);
        CharSecret cs("abcabc");
        CharSecret css("abcabc");
        cout << (ds == cs) << endl;
        cout << (cs != ds) << endl;
        cout << (cs == css) << endl;
        cout << (cs != css) << endl;
    } else if(n == 3) {
        cout << "Secret processor" << endl;
        int numbers1 [] = {1,2,3,4,5,6,4,3,2,1,1,2,3,4,5};
        DigitSecret ds1(numbers1,15);
        int numbers2 [] = {1,2,3,4,5,0,0,0,5,5,4,4,3,3,2};
        DigitSecret ds2(numbers2,15);
        int numbers3 [] = {1,0,9,4,3,8,4,0,9,3,1,4,3,2,1,4,4,3,7,2};
        DigitSecret ds3(numbers3,20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret** s = new Secret*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        process(s,6);
        delete [] s;
    }
    else if (n==4){
        cout << "Print all secrets" << endl;
        int numbers1 [] = {1,2,3,4,5,5,4,3,2,1,1,2,3,4,5};
        DigitSecret ds1(numbers1,15);
        int numbers2 [] = {1,2,3,4,5,0,0,0,5,5,4,4,3,3,2};
        DigitSecret ds2(numbers2,15);
        int numbers3 [] = {1,0,9,4,3,8,4,0,9,3,1,4,3,2,1,4,4,3,7,2};
        DigitSecret ds3(numbers3,20);
        CharSecret cs1("fhdaieowujkfjdsafjdsakjhueiqoyroq");
        CharSecret cs2("nvzcfsadrqipqhfjdfncxoqw");
        CharSecret cs3("uyoihfdsanmqeqrzvdhfeqyrq");
        Secret** s = new Secret*[6];
        s[0] = &ds1;
        s[1] = &ds2;
        s[2] = &ds3;
        s[3] = &cs1;
        s[4] = &cs2;
        s[5] = &cs3;
        printAll(s,6);
        delete [] s;
    }

    return 0;
}
