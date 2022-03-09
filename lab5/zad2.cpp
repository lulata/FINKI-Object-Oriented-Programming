#include<iostream>
#include<cmath>
#include <cstring>
using namespace std;

class ComplexNumber{
private:
    double realen;
    double im;
public:
    ComplexNumber(double realen=0,double im=0){
        this->realen=realen;
        this->im=im;
    }double module(){
        return(sqrt((pow(realen,2))+pow(im,2)));
    }ComplexNumber&operator=(const ComplexNumber &c){
        if(this!=&c){
            this->realen=c.realen;
            this->im=c.im;
        }return *this;
    }friend ostream&operator<<(ostream &o,const ComplexNumber &c){
        if(c.realen == 0){
            o<<c.im<<"i"<<endl;
        }else if(c.im == 0){
            o<<c.realen<<endl;
        }else{
            o<<c.realen<<"+"<<c.im<<"i"<<endl;
        }
    }ComplexNumber operator+(const ComplexNumber &c){
        ComplexNumber temp(realen+c.realen,im+c.im);
        return temp;
    }ComplexNumber operator-(const ComplexNumber &c){
        ComplexNumber temp(realen-c.realen,im-c.im);
        return temp;
    }ComplexNumber operator*(const ComplexNumber &c){
        ComplexNumber temp(realen*c.realen,im*c.im);
        return temp;
    }ComplexNumber operator/(const ComplexNumber &c){
        ComplexNumber temp(realen/c.realen,im/c.im);
        return temp;
    }bool operator==(const ComplexNumber &c){
        if((this->realen==c.realen) && (this->im==c.im)){
            return true;
        }return false;
    }bool operator<(const ComplexNumber &c){
        if(this->realen==c.realen){
            return (this->im < c.im);
        }return (this->realen < c.realen);
    }bool operator>(const ComplexNumber &c){
        if(this->realen==c.realen){
            return (this->im > c.im);
        }return (this->realen > c.realen);
    }friend istream&operator>>(istream &in,ComplexNumber &c){
        in>>c.realen;
        in>>c.im;
        return in;
    }
};

class Equation{
private:
    ComplexNumber *brojki;
    char *operatori;
    int broj;
public:
    Equation(){
        operatori=NULL;
        brojki=NULL;
        broj=0;
    }friend istream&operator>>(istream &in,Equation &e){
        int brojac=0;
        ComplexNumber *temp=new ComplexNumber[100];
        char *temp1=new char[101];
        while(true){
            in>>temp[brojac];
            in>>temp1[brojac];
            if(temp1[brojac] == '='){
                break;
            }else{
                brojac++;
            }
        }e.broj=brojac;
        delete[] e.brojki;
        e.brojki=temp;
        delete[]e.operatori;
        e.operatori=new char[strlen(temp1)+1];
        strcpy(e.operatori,temp1);
        return in;
    }void print(){
        for(int i=0;i<broj;i++){
            cout<<brojki[i];
        }
    }ComplexNumber result(){
        ComplexNumber temp=brojki[0];
        for(int i=1;i<broj+1;i++){
            if(this->operatori[i-1] == '='){
                temp=temp;
                break;
            }else if(this->operatori[i-1] == '+'){
                temp=temp+brojki[i];
            }else if(this->operatori[i-1] == '-'){
                temp=temp-brojki[i];
            }else if(this->operatori[i-1] == '*'){
                temp=temp*brojki[i];
            }else if(this->operatori[i-1]== '/'){
                temp=temp/brojki[i];
            }
        }return temp;
    }double sumModules(){
        double zbir=0;
        for(int i=0;i<broj+1;i++){
            zbir+=brojki[i].module();
        }return zbir;
    }
};

// Не го менувајте main методот.

int main() {
    int testCase;
    double real, imaginary;
    ComplexNumber first, second, result;

    cin >> testCase;

    if (testCase <= 8) {
        cin >> real;
        cin >> imaginary;
        first = ComplexNumber(real, imaginary);
        cin >> real;
        cin >> imaginary;
        second = ComplexNumber(real, imaginary);
    }

    if (testCase == 1) {
        cout << "===== OPERATOR + =====" << endl;
        result = first + second;
        cout << result;
    }
    else if (testCase == 2) {
        cout << "===== OPERATOR - =====" << endl;
        result = first - second;
        cout << result;
    }
    else if (testCase == 3) {
        cout << "===== OPERATOR * =====" << endl;
        result = first * second;
        cout << result;
    }
    else if (testCase == 4) {
        cout << "===== OPERATOR / =====" << endl;
        result = first / second;
        cout << result;
    }
    else if (testCase == 5) {
        cout << "===== OPERATOR == =====" << endl;
        cout << first;
        cout << second;
        if (first == second)
            cout << "EQUAL" << endl;
        else
            cout << "NOT EQUAL" << endl;
    }
    else if (testCase == 6) {
        cout << "===== OPERATOR > =====" << endl;
        cout << first;
        cout << second;
        if (first > second)
            cout << "FIRST GREATER THAN SECOND" << endl;
        else
            cout << "FIRST LESSER THAN SECOND" << endl;
    }
    else if (testCase == 7) {
        cout << "===== OPERATOR < =====" << endl;
        cout << first;
        cout << second;
        if (first < second)
            cout << "FIRST LESSER THAN SECOND" << endl;
        else
            cout << "FIRST GREATER THAN SECOND" << endl;
    }
    else if (testCase == 8) {
        cout << "===== MODULE =====" << endl;
        double module = first.module();
        cout << first;
        cout << "Module: " << module << endl;
        cout << second;
        module = second.module();
        cout << "Module: " << module << endl;
    }
    else if (testCase == 9) {
        cout << "===== OPERATOR >> & SUM OF MODULES =====" << endl;
        Equation equation;
        cin >> equation;
        cout << equation.sumModules();
    }
    else if (testCase == 10) {
        cout << "===== EQUATION RESULT =====" << endl;
        Equation equation;
        cin >> equation;
        result = equation.result();
        cout << result;
    }
    return 0;
}
