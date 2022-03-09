#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Image{
protected:
    char *imeSlika;
    char imeAvtor[50];
    int dimenzijaX;
    int dimenzijaY;

    void copy(const Image& other){
        imeSlika = new char[strlen(other.imeSlika) + 1];
        strcpy(this->imeSlika,other.imeSlika);
        strcpy(this->imeAvtor,other.imeAvtor);
        this->dimenzijaX = other.dimenzijaX;
        this->dimenzijaY = other.dimenzijaY;
    }
public:
    Image(const char* imeSlika = "untitled", const char* imeAvtor = "unknown", int dimenzijaX = 800, int dimenzijaY = 800){
        this->imeSlika = new char[strlen(imeSlika) + 1];
        strcpy(this->imeSlika,imeSlika);
        strcpy(this->imeAvtor,imeAvtor);
        this->dimenzijaX = dimenzijaX;
        this->dimenzijaY = dimenzijaY;
    }Image(const Image& other){
        copy(other);
    }virtual ~Image(){
        delete[] imeSlika;
    }Image& operator= (const Image& other){
        if (this != &other){
            delete[] imeSlika;
            copy(other);
        }return *this;
    }const char* getNamePicture(){
        return imeSlika;
    }const char* getNameAuthor(){
        return imeAvtor;
    }virtual int fileSize(){
        return dimenzijaX * dimenzijaY * 3;
    }virtual void print(ostream& out){
        out << imeSlika << " " << imeAvtor << " " << fileSize() << endl;
    }friend ostream& operator << (ostream& out, Image& i){
        i.print(out);
        return out;
    }bool operator > (Image &other){
        return (fileSize() > other.fileSize());
    }
};

class TransparentImage : public Image{
protected:
    bool prasalnik;
    void copy(const TransparentImage& other){
        Image::copy(other);
        this->prasalnik = other.prasalnik;
    }
public:
    TransparentImage(const char* imeSlika = "untitled", const char* imeAvtor = "unknown", int dimenzijaX = 800, int dimenzijaY = 800, bool prasalnik = true) : Image(imeSlika,imeAvtor,dimenzijaX,dimenzijaY){
        this->prasalnik = prasalnik;
    }
    int fileSize() override {
        if(prasalnik) {
            return dimenzijaX * dimenzijaY * 4;
        }return dimenzijaX * dimenzijaY + dimenzijaX * dimenzijaY / 8.0;
    }void print(ostream& out){
        out << imeSlika << " " << imeAvtor << " " << fileSize() << endl;
    }
};

class Folder{
protected:
    char imeFolder[255];
    char imeKorisnik[50];
    Image *sliki[100];
    int brojSliki;
    void copy(const Folder& other){
        strcpy(this->imeFolder, other.imeFolder);
        strcpy(this->imeKorisnik, other.imeKorisnik);
        this->brojSliki = other.brojSliki;
        for (int i = 0; i < other.brojSliki; i++){
            this->sliki[i] = other.sliki[i];
        }
    }
public:
    Folder(const char* imeFolder = "", const char* imeKorisnik = "unknown"){
        strcpy(this->imeFolder, imeFolder);
        strcpy(this->imeKorisnik, imeKorisnik);
        this->brojSliki = 0;
    }Folder(const Folder& other){
        copy(other);
    }Folder& operator= (const Folder& other){
        if (this != &other){
            copy(other);
        }return *this;
    }int folderSize(){
        int sum = 0;
        for (int i = 0; i < brojSliki; i++){
            sum += sliki[i]->fileSize();
        }return sum;
    }void print(ostream& out){
        out << imeFolder << " " << imeKorisnik << endl;
        out << "--" << endl;
        for (int i = 0; i < brojSliki; i++){
            out << *sliki[i];
        }out << "--" << endl;
        out << "Folder size: " << folderSize() << endl;
    }friend ostream& operator << (ostream &out, Folder &f){
        f.print(out);
        return out;
    }Image* getMaxFile(){
        int index = 0;
        for (int i = 1; i < brojSliki; i++){
            if (!(*sliki[index] > *sliki[i])){
                index = i;
            }
        }return sliki[index];
    }Folder& operator+= (Image &i){
        sliki[brojSliki] = &i;
        brojSliki++;
        return *this;
    }Image* operator[] (int n){
        if (true){
            return sliki[n];
        }else{
            return nullptr;
        }
    }
};

Folder& max_folder_size(Folder *folderArr, int n){
    int index = 0;
    for (int i = 1; i < n; i++){
        if (folderArr[index].folderSize() < folderArr[i].folderSize()){
            index = i;
        }
    }
    return folderArr[index];
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;


        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};
