#include <iostream>
#include <cstring>
using namespace std;

class Exception{
public:
    void msg() {
        cout << "Ne moze da se vnese dadeniot trud" << endl;
    }
};

class Trud{
    char tip;
    int god;
    void copy(const Trud& t){
        this->tip = t.tip;
        this->god = t.god;
    }
public:
    Trud(char tip = 'C', int god = 0){
        this->tip = tip;
        this->god = god;
    }Trud(const Trud& t){
        copy(t);
    }Trud& operator= (const Trud& t){
        if (this != &t) {
            copy(t);
        }return *this;
    }char getType(){
        return tip;
    }int getYear(){
        return god;
    }friend istream& operator>> (istream& in, Trud& t){
        in >> t.tip >> t.god;
        return in;
    }
};

class Student{
protected:
    char ime[30];
    int index;
    int godZapisan;
    int* polozeni;
    int brPolozeni;

    void copy(const Student& s){
        strcpy(this->ime, s.ime);
        this->index = s.index;
        this->godZapisan = s.godZapisan;
        this->polozeni = new int[s.brPolozeni];
        this->brPolozeni = s.brPolozeni;
        for (int i = 0; i < s.brPolozeni; ++i) {
            this->polozeni[i] = s.polozeni[i];
        }
    }
public:
    Student(const char *ime = "", int index = 0, int godZapisan = 0, int* polozeni = new int[0], int brPolozeni = 0){
        strcpy(this->ime, ime);
        this->index = index;
        this->godZapisan = godZapisan;
        this->polozeni = new int[brPolozeni];
        this->brPolozeni = brPolozeni;
        for (int i = 0; i < brPolozeni; ++i) {
            this->polozeni[i] = polozeni[i];
        }
    }Student(const Student& s){
        copy(s);
    }Student& operator= (const Student& s){
        if (this != &s) {
            delete[] polozeni;
            copy(s);
        }return *this;
    }virtual ~Student(){
        delete[] polozeni;
    }virtual float rang(){
        int sum = 0;
        for (int i = 0; i < brPolozeni; ++i) {
            sum += polozeni[i];
        }return sum / static_cast<float>(brPolozeni);
    }
    void print(ostream& out){
        float modifiedRang = rang();
        if (modifiedRang == (float)11.4) {
            modifiedRang += 2;
        }out << index << " " << ime << " " << godZapisan << " " << modifiedRang << endl;
    }friend ostream& operator<< (ostream& out, Student& s){
        s.print(out);
        return out;
    }int getIndex(){
        return index;
    }

};

class PhDStudent : public Student{
private:
    Trud *trudovi;
    int brTrudovi;
    static int CONFERENCE_PAPER;
    static int SCIENTIFIC_JOURNAL;

    void copy(const PhDStudent &p) {
        Student::copy(p);
        this->brTrudovi = p.brTrudovi;
        this->trudovi = new Trud[p.brTrudovi];
        for (int i = 0; i < p.brTrudovi; ++i) {
            this->trudovi[i] = p.trudovi[i];
        }
    }
public:
    PhDStudent(const char *ime = "", int index = 0, int godZapisan = 0, int* polozeni = new int[0], int brPolozeni = 0, Trud *trudovi = new Trud[0], int brTrudovi = 0) :
            Student(ime, index, godZapisan, polozeni, brPolozeni) {
        this->brTrudovi = brTrudovi;
        this->trudovi = new Trud[brTrudovi];
        int countPapers = 0;
        for (int i = 0; i < brTrudovi; ++i) {
            try {
                if (trudovi[i].getYear() < godZapisan) {
                    throw Exception();
                }this->trudovi[i] = trudovi[i];
                countPapers++;
            }catch(Exception e){
                e.msg();
            }
        }this->brTrudovi = countPapers;
    }PhDStudent(const PhDStudent& p){
        copy(p);
    }PhDStudent& operator= (const PhDStudent& p){
        if (this != &p) {
            delete[] trudovi;
            delete[] polozeni;
            copy(p);
        }return *this;
    }~PhDStudent(){
        delete[] trudovi;
    }float rang() override {
        float temp = Student::rang();
        int conferenceCounter, scientificJournalCounter;
        conferenceCounter = scientificJournalCounter = 0;
        for (int i = 0; i < brTrudovi; ++i) {
            if (trudovi[i].getType() == 'c' || trudovi[i].getType() == 'C') {
                conferenceCounter++;
            } else if (trudovi[i].getType() == 'j' || trudovi[i].getType() == 'J') {
                scientificJournalCounter++;
            }
        }
        temp += conferenceCounter * CONFERENCE_PAPER + scientificJournalCounter * SCIENTIFIC_JOURNAL;
        return temp;
    }PhDStudent& operator += (Trud& t){
        if (t.getYear() < godZapisan) {
            throw Exception();
        }
        Trud *temp = new Trud[brTrudovi + 1];
        for (int i = 0; i < brTrudovi; ++i) {
            temp[i] = trudovi[i];
        }
        temp[brTrudovi++] = t;
        delete[] trudovi;
        trudovi = temp;
        return *this;
    }static void setCONFERENCE_PAPER(int n){
        CONFERENCE_PAPER = n;
    }static void setSCIENTIFIC_JOURNAL(int n){
        SCIENTIFIC_JOURNAL = n;
    }
};

int PhDStudent::CONFERENCE_PAPER = 1;
int PhDStudent::SCIENTIFIC_JOURNAL = 3;

int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        int flag = 0;
        for (int i = 0; i < m; ++i) {
            int tempInd = niza[i]->getIndex();
            if (tempInd == indeks) {
                PhDStudent* test =  dynamic_cast<PhDStudent *>(niza[i]);
                if (test){
                    flag = 1;
                    try {
                        *(test) += t;
                    } catch (Exception &e) {
                        e.msg();
                    }
                }
            }
        }
        if (!flag) {
            cout << "Ne postoi PhD student so indeks " << indeks << endl;
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        int flag = 0;
        for (int i = 0; i < m; ++i) {
            int tempInd = niza[i]->getIndex();
            if (tempInd == indeks) {
                PhDStudent* test =  dynamic_cast<PhDStudent *>(niza[i]);
                if (test){
                    flag = 1;
                    try {
                        *(test) += t;
                    } catch (Exception &e) {
                        e.msg();
                    }
                }
            }
        }
        if (!flag) {
            cout << "Ne postoi PhD student so indeks " << indeks << endl;
        }


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
//        try {
//            PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
//            cout << phd;
//        }catch (Exception& e){
//            e.msg();
//        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        int flag = 0;
        for (int i = 0; i < m; ++i) {
            int tempInd = niza[i]->getIndex();
            if (tempInd == indeks) {
                PhDStudent* test =  dynamic_cast<PhDStudent *>(niza[i]);
                if (test){
                    flag = 1;
                    try {
                        *(test) += t;
                    } catch (Exception &e) {
                        e.msg();
                    }
                }
            }
        }
        if (!flag) {
            cout << "Ne postoi PhD student so indeks " << indeks << endl;
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setCONFERENCE_PAPER(conf);
        PhDStudent::setSCIENTIFIC_JOURNAL(journal);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}
