#include<iostream>
#include<cstring>

using namespace std;
enum Extension{pdf=0,txt,exe};
class File{
private:
    char *ime;
    Extension dad;
    char *sopstevink;
    int golemina=0;
public:
    File(){
        ime= nullptr;
        sopstevink= nullptr;
        golemina=0;
        dad=pdf;
    }
    File(char *ime,char *sopstevink,int golemina,Extension dad){
        this->ime =new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->dad=dad;
        this->sopstevink =new char[strlen(sopstevink)+1];
        strcpy(this->sopstevink,sopstevink);
        this->golemina=golemina;
    }File(const File &f){
        this->ime =new char[strlen(f.ime)+1];
        strcpy(this->ime,f.ime);
        this->dad=f.dad;
        this->sopstevink =new char[strlen(f.sopstevink)+1];
        strcpy(this->sopstevink,f.sopstevink);
        this->golemina=f.golemina;
    }~File(){
        delete [] ime;
        delete [] sopstevink;
    }File& operator=(const File &f){
        if(this!=&f){
            delete [] ime;
            this->ime =new char[strlen(f.ime)+1];
            strcpy(this->ime,f.ime);
            this->dad=f.dad;
            delete [] sopstevink;
            this->sopstevink =new char[strlen(f.sopstevink)+1];
            strcpy(this->sopstevink,f.sopstevink);
            this->golemina=f.golemina;
        }return *this;
    }bool equals(const File & that){
        if ((strcmp(ime, that.ime) == 0) && (strcmp(sopstevink, that.sopstevink) == 0) && dad == that.dad){
            return true;
        }else{
            return false;
        }
    }bool equalsType(const File & that){
        if ((strcmp(ime, that.ime) == 0) && that.dad==dad){
            return true;
        }else{
            return false;
        }
    }void print(){
        char *extension[] = {".pdf", ".txt", ".exe"};
        cout<<"File name: "<<ime<<extension[dad]<<endl;
        cout<<"File owner: "<<sopstevink<<endl;
        cout<<"File size: "<<golemina<<endl;
    }
};
class Folder{
private:
    char *dir;
    int br;
    File *dadoteka;
public:
    Folder(const char *dir=""){
        this->dir= new char[strlen(dir)+1];
        strcpy(this->dir,dir);
        br=0;
        dadoteka= new File[br+1];
    }~Folder(){
        delete [] dir;
        delete [] dadoteka;
    }
    void print(){
        cout << "Folder name: " << dir << endl;
        for (int i = 0; i < br; ++i) {
            dadoteka[i].print();
        }
    }void remove(const File & file){
        File *temp= new File[br-1];
        int index=0;
        for (int i = 0; i < br; ++i) {
            if(!(dadoteka[i].equals(file))){
                temp[index++] = dadoteka[i];
            }
        }delete [] dadoteka;
        dadoteka=temp;
        br--;
    }void add(const File & file){
        if (br==0){
            dadoteka[0]=file;
            br++;
        }else{
            File *temp= new File[br+1];
            for (int i = 0; i < br; ++i) {
                temp[i]= dadoteka[i];
            }temp[br]=file;
            br++;
            delete [] dadoteka;
            dadoteka=temp;
        }
    }
};
int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2) {
        cout << "======= FILE EQUALS AND EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}
