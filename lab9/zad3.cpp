#include <iostream>
#include <cstring>
using namespace std;

class RegistrationException{
public:
    void print(){
        cout << "Pogresno vnesena registracija" << endl;
    }
};

class HasMass {
public:
    virtual double returnMass() = 0;
    virtual void print() = 0;
};

class PacketBeverage : public HasMass {
protected:
    double volume;
    int quantity;
    static float MASS_PACKING;
    static float DENSITY;
public:
    PacketBeverage(double volume = 0, int quantity = 0){
        this->volume = volume;
        this->quantity = quantity;
    };
    virtual double returnMass() override{
        return quantity * (volume * DENSITY + MASS_PACKING);
    }
    int getQuantity(){
        return quantity;
    }
    void print() override{
        cout << "Printing product" << endl;
    }
};


class PacketJuice : public PacketBeverage {
private:
    bool isSparkling;
    static const float ADDITIONAL_MASS;
public:
    PacketJuice(double volume = 0, int quantity = 0, bool isSparkling = false):PacketBeverage(volume,quantity) {
        this->isSparkling = isSparkling;
    }
    double returnMass() override{
        if (isSparkling) {
            return PacketBeverage::returnMass();
        } else {
            return PacketBeverage::returnMass() + quantity * ADDITIONAL_MASS; // int to float
        }
    }
    void print() override{
        //kolicina 50, so po 0.4 l(dm3)
        cout << "Paket sok" << endl;
        cout << "kolicina " << quantity << ", so po " << volume * DENSITY << " l(dm3)" << endl;
    }
};

class PacketWines : public PacketBeverage {
private:
    static const float COEFFICIENT;
    double alcoholPercentage;
public:
    PacketWines(double volume = 0, int quantity = 0, double alcoholPercentage = 0.0) : PacketBeverage(volume,quantity) {
        this->alcoholPercentage = alcoholPercentage;
    }
    double returnMass() override{
        return PacketBeverage::returnMass() * (COEFFICIENT + alcoholPercentage);
    }
    void print() override{
        //kolicina 12, 80% alkohol od po 4 l(dm3)
        cout << "Paket vino" << endl;
        cout << "kolicina " << quantity << ", " << alcoholPercentage * 100 << "% alkohol od po " << volume * DENSITY
             << " l(dm3)"
             << endl;
    }
};

class Truck{
private:
    char* registration;
    char* driverName;
    HasMass** objectsBeingTransported;
    int numObjectsBeingTransported;

    void deleteDynamicallyAllocated(){
        delete[] registration;
        delete[] driverName;
        delete[] objectsBeingTransported;
    }
    void copy(const Truck& other){
        this->registration = new char[strlen(other.registration) + 1];
        this->driverName = new char[strlen(other.driverName) + 1];
        strcpy(this->registration, other.registration);
        strcpy(this->driverName,other.driverName);
        this->numObjectsBeingTransported = other.numObjectsBeingTransported;
        this->objectsBeingTransported = new HasMass *[other.numObjectsBeingTransported];
        for (int i = 0; i < other.numObjectsBeingTransported; ++i) {
            this->objectsBeingTransported[i] = other.objectsBeingTransported[i];
        }
    }
    void checkRegistration(char* registration){
        int regLen = strlen(registration);
        if (!(isalpha(registration[0]) && isalpha(registration[1]) && isalpha(registration[6]) &&
              isalpha(registration[7]) && regLen == 8)) {
            throw RegistrationException();
        }
    }
public:
    Truck(char* driverName = ""){
        this->driverName = new char[strlen(driverName) + 1];
        strcpy(this->driverName, driverName);
        registration = nullptr;
        objectsBeingTransported = nullptr;
        numObjectsBeingTransported = 0;
    }
    Truck(char *registration = "", char *driverName = "") {
        checkRegistration(registration);
        this->registration = new char[strlen(registration) + 1];
        this->driverName = new char[strlen(driverName) + 1];
        strcpy(this->registration, registration);
        strcpy(this->driverName,driverName);
        this->objectsBeingTransported = nullptr;
        this->numObjectsBeingTransported = 0;
    }
    Truck(const Truck& other){
        copy(other);
    }
    Truck& operator= (const Truck& other){
        if (this != &other) {
            deleteDynamicallyAllocated();
            copy(other);
        }
        return *this;
    }
    ~Truck(){
        deleteDynamicallyAllocated();
    }

    void registerTruck(char* newRegistration){
        registration = new char[strlen(newRegistration) + 1];
        strcpy(registration, newRegistration);
    }
    void addNewObject(HasMass *h){
        HasMass **temp = new HasMass *[numObjectsBeingTransported + 1];
        for (int i = 0; i < numObjectsBeingTransported; ++i) {
            temp[i] = objectsBeingTransported[i];
        }
        temp[numObjectsBeingTransported++] = h;
        delete[] objectsBeingTransported;
        objectsBeingTransported = temp;
    }
    double returnTotalMass(){
        double sum = 0.0;
        for (int i = 0; i < numObjectsBeingTransported; ++i) {
            sum += objectsBeingTransported[i]->returnMass();
        }
        return sum;
    }
    void print(){
        //Kamion so registracija SK3456RG i vozac Ljupcho prenesuva:
        cout << "Kamion so registracija " << registration << " i vozac " << driverName << " prenesuva: " << endl;
        for (int i = 0; i < numObjectsBeingTransported; ++i) {
            objectsBeingTransported[i]->print();
        }
    }
    HasMass* packetWithGreatestMass(){
        int index = 0;
        double maxMass = 0.0;
        for (int i = 0; i < numObjectsBeingTransported; ++i) {
            if (maxMass < objectsBeingTransported[i]->returnMass()) {
                maxMass = objectsBeingTransported[i]->returnMass();
                index = i;
            }
        }
        return objectsBeingTransported[index];
    }
    Truck truckOverload(char* registration,  char* driverName){
        Truck tempTruck(registration, driverName);
        HasMass *tempPacket = packetWithGreatestMass();
        for (int i = 0; i < numObjectsBeingTransported; ++i) {
            if (objectsBeingTransported[i] != tempPacket) {
                tempTruck.addNewObject(objectsBeingTransported[i]);
            }
        }
        return tempTruck;
    }

};

float PacketBeverage::MASS_PACKING = 0.2;
float PacketBeverage::DENSITY = 0.8;
const float PacketJuice::ADDITIONAL_MASS = 0.1;
const float PacketWines::COEFFICIENT = 0.9;

int main(){
    char ime[20], reg[9];
    double vol;
    int kol;
    bool g;
    double proc;

    cin>>reg;
    cin>>ime;
    try {
        Truck A(reg, ime);
        HasMass **d = new HasMass*[5];
        cin>>vol>>kol;
        cin>>g;
        d[0] = new PacketJuice(vol, kol, g);
        cin>>vol>>kol;
        cin>>proc;
        d[1] = new PacketWines(vol, kol, proc);
        cin>>vol>>kol;
        cin>>proc;
        d[2] = new PacketWines(vol, kol, proc);
        cin>>vol>>kol;
        cin>>g;
        d[3] = new PacketJuice(vol, kol, g);
        cin>>vol>>kol;
        cin>>proc;
        d[4] = new PacketWines(vol, kol, proc);

        A.addNewObject(d[0]);
        A.addNewObject(d[1]);
        A.addNewObject(d[2]);
        A.addNewObject(d[3]);
        A.addNewObject(d[4]);
        A.print();
        cout<<"Vkupna masa: "<<A.returnTotalMass()<<endl;
        cin>>reg;
        cin>>ime;
        Truck B = A.truckOverload(reg, ime);
        B.print();
        cout<<"Vkupna masa: "<<B.returnTotalMass()<<endl;
    }catch (RegistrationException &e){
        e.print();
    }
}
