#include <cstring>
#include <iostream>
using namespace std;

enum Size {small = 0, big, family};

class Pizza{
protected:
    char ime[20];
    char sostojki[100];
    float pocetnaCena;

    void copy(const Pizza& p){
        strcpy(this->ime, p.ime);
        strcpy(this->sostojki, p.sostojki);
        this->pocetnaCena = p.pocetnaCena;
    }

public:
    Pizza(const char *ime = "", const char *sostojki = "", float pocetnaCena = 0.0){
        strcpy(this->ime, ime);
        strcpy(this->sostojki, sostojki);
        this->pocetnaCena = pocetnaCena;
    }Pizza(const Pizza& p){
        copy(p);
    }virtual float price() = 0;
    virtual void printPizza(ostream& out) = 0;
    friend ostream& operator<< (ostream& out, Pizza& p){
        p.printPizza(out);
        return out;
    }bool operator< (Pizza& other){
        return this->price() < other.price();
    }
};



class FlatPizza : public Pizza{
private:
    Size golemina;
    void copy(const FlatPizza& fp){
        Pizza::copy(fp);
        this->golemina = fp.golemina;
    }
public:
    FlatPizza(const char *ime = "", const char *sostojki = "", float pocetnaCena = 0.0, Size golemina = small)
            : Pizza(ime, sostojki, pocetnaCena) {
        this->golemina = golemina;
    }FlatPizza(const FlatPizza &fp){
        copy(fp);
    }
    FlatPizza& operator= (const FlatPizza& fp){
        if (this != &fp) {
            copy(fp);
        }return *this;
    }float price() override {
        switch (golemina) {
            case 0: return pocetnaCena * 1.1;
            case 1: return pocetnaCena * 1.5;
            case 2: return pocetnaCena * 1.3;
        }
    }void printPizza(ostream &out) override{
        const char *enumValue[] = {"small", "big", "family"};
        out << ime << ": " << sostojki << ", " << enumValue[golemina] << " - " << price() << endl;
    }
};

class FoldedPizza  : public Pizza{
private:
    bool belo;
    void copy(const FoldedPizza& fldp){
        Pizza::copy(fldp);
        this->belo = fldp.belo;
    }
public:
    FoldedPizza(const char *ime = "", const char *sostojki = "", float pocetnaCena = 0.0, bool belo = true)
            : Pizza(ime, sostojki, pocetnaCena) {
        this->belo = belo;
    }FoldedPizza(const FoldedPizza& fldp){
        copy(fldp);
    }
    FoldedPizza& operator= (const FoldedPizza& fldp){
        if (this != &fldp) {
            copy(fldp);
        }return *this;
    }float price() override {
        if (belo) {
            return pocetnaCena * 1.1;
        } else {
            return pocetnaCena * 1.3;
        }
    }void printPizza(ostream &out) override{
        if (belo) {
            out << ime << ": " << sostojki << ", " << "wf" << " - " << price() << endl;
        } else {
            out << ime << ": " << sostojki << ", " << "nwf" << " - " << price() << endl;
        }
    }void setWhiteFlour(bool b){
        belo = b;
    }
};

void expensivePizza (Pizza **picii, int brPici){
    int maxIndex = 0;
    Pizza *mostExpensivePizza = picii[0];
    for (int i = 0; i < brPici; ++i) {
        if (*mostExpensivePizza < *picii[i]) {
            mostExpensivePizza = picii[i];
            maxIndex = i;
        }
    }cout << *picii[maxIndex];
}

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                if (strcmp(ingredients, "tomato sauce, cheese, ham, fresh mushrooms, oregano") == 0) {
                    strcpy(ingredients, "tomato sauce, cheese, ham, fresh mushrooms, orega");

                } else if (strcmp(ingredients, "tomato sauce, cheese, tomatoes, peppers, onion, olives, fresh mushrooms, oregano") == 0) {
                    strcpy(ingredients, "tomato sauce, cheese, tomatoes, peppers, onion, o");
                } else if (strcmp(ingredients, "tomato sauce, cheese, mozzarella, tomatoes, pesto, garlic, oregano") == 0)
                {
                    strcpy(ingredients, "tomato sauce, cheese, mozzarella, tomatoes, pesto");
                }
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi, num_p);
    }
    return 0;
}
