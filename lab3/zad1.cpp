#include<iostream>
#include<cstring>
using namespace std;

class Date{
private:
    int datum;
    int mesec;
    int god;
public:
    Date(int god=0,int mesec=0,int datum=0){
        this->god=god;
        this->mesec=mesec;
        this->datum=datum;
    }~Date(){}
    Date(const Date &d){
        this->god=d.god;
        this->mesec=d.mesec;
        this->datum=d.datum;
    }
    void print(){
        cout<<god<<"."<<mesec<<"."<<datum<<endl;
    }
};

class Person{
private:
    char ime[20];
    char prezime[20];
public:
    Person(char *ime="",char *prezime=""){
        strcpy(this->ime, ime);
        strcpy(this->prezime,prezime);
    }~Person(){}
    void print(){
        cout<<ime<<" "<<prezime<<endl;
    }
};

class Car{
private:
    Person sopstvenik;
    Date datum;
    float cena;
public:
    Car(){}
    Car(Person sopstvenik,Date datum,float cena=0){
        this->sopstvenik=sopstvenik;
        this->datum=datum;
        this->cena=cena;
    }~Car(){}
    float getPrice(){
        return cena;
    }void print(){
        sopstvenik.print();
        datum.print();
        cout<<"Price: "<<cena<<endl;
    }

};
void cheaperThan(Car* cars, int numCars, float price){
        if(price>cars->getPrice()){
            cars->print();
        }
}

int zad1() {
	char name[20];
	char lastName[20];
	int year;
	int month;
	int day;
	float price;

	int testCase;
	cin >> testCase;

	if (testCase == 1) {
		cin >> name;
		cin >> lastName;
		Person lik(name, lastName);

		cin >> year;
		cin >> month;
		cin >> day;
		Date date(year, month, day);

		cin >> price;
		Car car(lik, date,  price);

		car.print();
	}
	else if (testCase == 2) {
		cin >> name;
		cin >> lastName;
		Person lik(name, lastName);

		cin >> year;
		cin >> month;
		cin >> day;
		Date date(Date(year, month, day));

		cin >> price;
		Car car(lik, date,  price);
		car.print();
	}
	else {
		int numCars;
		cin >> numCars;

		Car cars[10];
		for (int i = 0; i < numCars; i++) {
			cin >> name;
			cin >> lastName;
			Person lik(name, lastName);

			cin >> year;
			cin >> month;
			cin >> day;
			Date date(year, month, day);

			cin >> price;
			cars[i] = Car(lik, date,  price);
		}
        float priceLimit;
        cin >> priceLimit;
		cheaperThan(cars, numCars, priceLimit);
	}


	return 0;
}
