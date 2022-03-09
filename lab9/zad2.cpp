#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class ArithmeticException{
public:
    void message(){
        cout << "Division by zero is not allowed" << endl;
    }
};

class NumbersNotDivisibleException {
private:
    int n;
public:
    NumbersNotDivisibleException(int n){
        this->n = n;
    }
    void message(){
        cout << "Division by " << n << " is not supported" << endl;
    }
};

class ArrayFullException {
public:
    void message(){
        cout << "The array is full. Increase the capacity" << endl;
    }
};

class IndexOutOfBoundsException{
private:
    int n;
public:
    IndexOutOfBoundsException(int n){
        this->n = n;
    }
    void message(){
        cout << "Index " << n << " is out of bounds" << endl;
    }
};

class NumberIsNotPositiveException {
private:
    int n;
public:
    NumberIsNotPositiveException(int n){
        this->n = n;
    }
    void message(){
        cout << "Number " << n << " is not positive integer" << endl;
    }
};


class PositiveIntegers{
    int *niza;
    int brElementi;
    int maxKapacitet;

    void copy(const PositiveIntegers &p){
        this->maxKapacitet = p.maxKapacitet;
        this->brElementi = p.brElementi;
        niza = new int[p.brElementi + 1];
        for (int i = 0; i < p.brElementi; ++i) {
            niza[i] = p.niza[i];
        }
    }

public:
    PositiveIntegers (int maxKapacitet = 0){
        this->maxKapacitet = maxKapacitet;
        this->brElementi = 0;
        niza = new int[brElementi + 1];
    }PositiveIntegers(const PositiveIntegers &p){
        copy(p);
    }~PositiveIntegers(){
        delete[] niza;
    }PositiveIntegers& operator= (const PositiveIntegers &p){
        if (this != &p) {
            delete[] niza;
            copy(p);
        }return *this;
    }PositiveIntegers& operator+= (int n){
        if (brElementi == maxKapacitet) {
            throw ArrayFullException();
        }if (n <= 0) {
            throw NumberIsNotPositiveException(n);
        }int *temp = new int[maxKapacitet];
        for (int i = 0; i < brElementi; ++i) {
            temp[i] = niza[i];
        }temp[brElementi++] = n;
        delete[] niza;
        niza = temp;
        return *this;
    }PositiveIntegers operator* (int n){
        PositiveIntegers p(*this);
        for (int i = 0; i < brElementi; ++i) {
            p.niza[i] = niza[i] * n;
        }
        return p;
    }PositiveIntegers operator/ (int n){
        if (n == 0){
            throw ArithmeticException();
        } else if (!isDivisible(n)) {
            throw NumbersNotDivisibleException(n);
        } else {
            PositiveIntegers p(*this);
            for (int i = 0; i < brElementi; ++i) {
                p.niza[i] = niza[i] / n;
            }
            return p;
        }
    }int& operator[] (int num){
        if (num > 0 && num < brElementi) {
            return niza[num];
        } else {
            throw IndexOutOfBoundsException(num);
        }
    }void increaseCapacity(int c){
        maxKapacitet += c;
    }bool isDivisible(int n){
        for (int i = 0; i < brElementi; ++i) {
            if (niza[i] % n != 0) {
                return false;
            }
        }return true;
    }void print(){
        cout << "Size: " << brElementi << " Capacity: " << maxKapacitet << " Numbers: ";
        for (int i = 0; i < brElementi; ++i) {
            cout << niza[i] << " ";
        }cout << endl;
    }
};

int main() {

    int n, capacity;
    cin >> n >> capacity;
    PositiveIntegers pi(capacity);
    for (int i = 0; i < n; i++) {
        int number;
        cin >> number;
        try {
            pi += number;
        } catch (NumberIsNotPositiveException &e) {
            e.message();
        } catch (ArrayFullException &e) {
            e.message();
        }
    }

    cout << "===FIRST ATTEMPT TO ADD NUMBERS===" << endl;
    pi.print();
    int incCapacity;
    cin >> incCapacity;
    pi.increaseCapacity(incCapacity);
    cout << "===INCREASING CAPACITY===" << endl;
    pi.print();

    int n1;
    cin >> n1;
    for (int i = 0; i < n1; i++) {
        int number;
        cin >> number;
        try {
            pi += number;
        } catch (NumberIsNotPositiveException &e) {
            e.message();
        } catch (ArrayFullException &e) {
            e.message();
        }
    }
    cout << "===SECOND ATTEMPT TO ADD NUMBERS===" << endl;

    pi.print();
    PositiveIntegers pi1;

    cout << "===TESTING DIVISION===" << endl;

    try {
        pi1 = pi / 0;
        pi1.print();
    } catch (ArithmeticException &e) {
        e.message();
    } catch (NumbersNotDivisibleException &e) {
        e.message();
    }


    try {
        pi1 = pi / 1;
        pi1.print();
    } catch (ArithmeticException &e) {
        e.message();
    } catch (NumbersNotDivisibleException &e) {
        e.message();
    }


    try {
        pi1 = pi / 2;
        pi1.print();
    } catch (ArithmeticException &e) {
        e.message();
    } catch (NumbersNotDivisibleException &e) {
        e.message();
    }


    cout << "===TESTING MULTIPLICATION===" << endl;
    pi1 = pi * 3;
    pi1.print();


    cout << "===TESTING [] ===" << endl;
    try {
        cout << "PositiveIntegers[-1] = " << pi[-1] << endl;
    } catch (IndexOutOfBoundsException &e) {
        e.message();
    }
    try {
        cout << "PositiveIntegers[2] = " << pi[2] << endl;
    } catch (IndexOutOfBoundsException &e) {
        e.message();
    }
    try {
        cout << "PositiveIntegers[3] = " << pi[3] << endl;
    }catch (IndexOutOfBoundsException &e){
        e.message();
    }
    try{
        cout << "PositiveIntegers[12] = " << pi[12] << endl;
    }catch (IndexOutOfBoundsException &e){
        e.message();
    }

    return 0;
}

