#include<iostream>
#include<cstring>

using namespace std;

class Number {
public:
    virtual double doubleValue() const = 0;
    virtual int intValue() const = 0;
    virtual void print() const = 0;
};

bool operator== (const Number& num1, const Number& num2){
    return (num1.doubleValue() == num2.doubleValue() || num1.intValue() == num2.doubleValue());
}

class Integer : public Number{
private:
    int brojInt;
public:
    Integer(int num = 0){
        brojInt = num;
    }double doubleValue() const override{
        return (double) brojInt;
    }int intValue() const override{
        return brojInt;
    }void print() const override{
        cout << brojInt << endl;
    }
};

class Double : public Number{
private:
    double brojDouble;
public:
    Double(double num = 0){
        brojDouble = num;
    }double doubleValue() const override{
        return brojDouble;
    }int intValue() const override{
        return (int) brojDouble;
    }void print() const override{
        cout << brojDouble << endl;
    }
};

class Numbers{
private:
    Number **brojoj;
    int brojOdBrojoj;
public:
    Numbers(){
        brojoj = nullptr;
        brojOdBrojoj = 0;
    }bool IsThereAnother (Number &num){
        for (int i = 0; i < brojOdBrojoj; ++i) {
            if (*brojoj[i] == num) {
                return true;
            }
        }return false;
    }Numbers& operator+= (Number* num){
        if (!IsThereAnother(*num)) {
            Number **temp = new Number *[brojOdBrojoj + 1];
            for (int i = 0; i < brojOdBrojoj; ++i) {
                temp[i] = brojoj[i];
            }
            temp[brojOdBrojoj++] = num;
            delete[] brojoj;
            brojoj = temp;
        }
    }double sumNumbers(){
        double suma = 0.0;
        for (int i = 0; i < brojOdBrojoj; ++i) {
            suma += brojoj[i]->doubleValue();
        }return suma;
    }int countOfInts(){
        int brojac = 0;
        for (int i = 0; i < brojOdBrojoj; ++i) {
            Integer *testInt = dynamic_cast<Integer *>(brojoj[i]);
            if (testInt) {
                brojac++;
            }
        }return brojac;
    }int sumInts(){
        int suma = 0;
        for (int i = 0; i < brojOdBrojoj; ++i) {
            Integer *testInt = dynamic_cast<Integer *>(brojoj[i]);
            if (testInt) {
                suma += brojoj[i]->intValue();
            }
        }return suma;
    }int countOfDoubles(){
        int brojac = 0;
        for (int i = 0; i < brojOdBrojoj; ++i) {
            Double *testD = dynamic_cast<Double *>(brojoj[i]);
            if (testD) {
                brojac++;
            }
        }return brojac;
    }double sumDoubles(){
        double suma = 0.0;
        for (int i = 0; i < brojOdBrojoj; ++i) {
            Double *testD = dynamic_cast<Double *>(brojoj[i]);
            if (testD) {
                suma+= brojoj[i]->doubleValue();
            }
        }return suma;
    }void statistics(){
        cout << "Count of numbers: " << brojOdBrojoj << endl;
        cout << "Sum of all numbers: " << sumNumbers() << endl;
        cout << "Count of integer numbers: " << countOfInts() << endl;
        cout << "Sum of integer numbers: " << sumInts() << endl;
        cout << "Count of double numbers: " << countOfDoubles() << endl;
        cout << "Sum of double numbers: " << sumDoubles() << endl;
    }

    void integersLessThan (Integer n){
        int flag = 0;
        for (int i = 0; i < brojOdBrojoj; ++i) {
            Integer *testInt = dynamic_cast<Integer *>(brojoj[i]);
            if (testInt) {
                if ((brojoj[i]->intValue()) < n.intValue()) {
                    cout << "Integer: " << brojoj[i]->intValue() << endl;
                    flag = 1;
                }
            }
        }
        if (!flag) {
            cout << "None" << endl;
        }
    }
    void doublesBiggerThan (Double n){
        int flag = 0;
        for (int i = 0; i < brojOdBrojoj; ++i) {
            Double *testD = dynamic_cast<Double *>(brojoj[i]);
            if (testD) {
                if ((brojoj[i]->doubleValue()) > n.doubleValue()) {
                    cout << "Double: " << brojoj[i]->doubleValue() << endl;
                    flag = 1;
                }
            }
        }
        if (!flag) {
            cout << "None" << endl;
        }
    }

};

int main() {

    int n;
    cin>>n;
    Numbers numbers;
    for (int i=0;i<n;i++){
        int type;
        double number;
        cin>>type>>number;
        if (type==0){//Integer object
            Integer * integer = new Integer((int) number);
            numbers+=integer;
        }
        else {
            Double * doublee = new Double(number);
            numbers+=doublee;
        }
    }

    int lessThan;
    double biggerThan;

    cin>>lessThan;
    cin>>biggerThan;

    cout<<"STATISTICS FOR THE NUMBERS\n";
    numbers.statistics();
    cout<<"INTEGER NUMBERS LESS THAN "<<lessThan<<endl;
    numbers.integersLessThan(Integer(lessThan));
    cout<<"DOUBLE NUMBERS BIGGER THAN "<<biggerThan<<endl;
    numbers.doublesBiggerThan(Double(biggerThan));

    return 0;
}
