#include <iostream>

using namespace std;

class List{
private:
    int *br;
    int brNaBr;
public:
    List(const int *br= nullptr,int brNaBr=0){
        this->brNaBr=brNaBr;
        this->br = new int[brNaBr];
        for (int i = 0; i < brNaBr; ++i) {
            this->br[i] = br[i];
        }
    }
    List(const List &l){
        this->brNaBr=l.brNaBr;
        this->br = new int[l.brNaBr];
        for (int i = 0; i < l.brNaBr; i++) {
            this->br[i] = l.br[i];
        }
    }List& operator=(const List &l){
        if (this!=&l){
            brNaBr = l.brNaBr;
            delete [] br;
            br= new int[l.brNaBr];
            for (int i = 0; i < l.brNaBr; i++) {
                br[i] = l.br[i];
            }
        }return *this;
    }int sum(){
        int sum=0;
        for(int i=0;i<brNaBr;i++){
            sum+=br[i];
        }return sum;
    }double average(){
        double avg;
        avg= sum()/(double) brNaBr;
        return avg;
    }void pecati(){
        cout<<brNaBr<<": ";
        for (int i = 0; i < brNaBr; ++i) {
            cout<<br[i]<<" ";
        }cout<<"sum: "<<this->sum()<<" average: "<<this->average();
    }
    ~List(){
        delete [] br;
    };int getBrNaBr(){
        return brNaBr;
    }
};
class ListContainer{
private:
    List *lista;
    int brNiza;
    int obid=0;
public:
    ListContainer(){
        brNiza = 1;
        obid= 0;
        lista = new List[brNiza];
    }ListContainer(const ListContainer &li){
        this->brNiza = li.brNiza;
        this->obid= li.obid;
        this->lista = new List[li.brNiza];
        for (int i = 0; i < li.brNiza - 1 ; ++i) {
            this->lista[i]= li.lista[i];
        }
    }ListContainer& operator=(const ListContainer &li){
        if (this!= &li){
            brNiza = li.brNiza;
            obid= li.obid;
            delete [] lista;
            lista = new List[li.brNiza-1];
            for (int i = 0; i < li.brNiza-1; ++i) {
                lista[i]= li.lista[i];
            }
        }return *this;
    }~ListContainer(){
        delete [] lista;
    }int sum(){
        int suma=0;
        for (int i = 0; i < brNiza -1; ++i) {
            suma+=lista[i].sum();
        }
        return suma;
    }double average(){
        double average;
        int zbirBr=0;
        for (int i = 0; i < brNiza-1; ++i) {
            zbirBr+=lista[i].getBrNaBr();
        }
        average=sum()/(zbirBr*1.0);
        return average;
    }void print(){
        if(brNiza == 1){
            cout<<"The list is empty"<<endl;
            return;
        }else{
            for (int i = 0; i < brNiza-1; ++i) {
                cout<<"List number: "<<i+1;
                cout<<" List info: ";
                lista[i].pecati();
                cout<<endl;
            }
        }cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
        cout<<"Successful attempts: "<<brNiza-1<<" Failed attempts: "<<obid-brNiza+1<<endl;
    } bool sumCheck (List &li){
        for (int i = 0; i < this->brNiza - 1; ++i) {
            if (this->lista[i].sum() == li.sum()) {
                return false;
            }
        }
        return true;
    }void addNewList(List &l){
        if (sumCheck(l)) {
            if (brNiza == 1){
                lista[0] = l;
                brNiza++;
            }else {
                List *temp = new List[brNiza];
                for (int i = 0; i < brNiza - 1; ++i) {
                    temp[i] = lista[i];
                }
                temp[brNiza - 1] = l;
                delete[] lista;
                lista = temp;
                brNiza++;
            }
        }
        obid++;
    }

};

int main() {

	ListContainer lc;
	int N;
	cin>>N;

	for (int i=0;i<N;i++) {
		int n;
		int niza[100];

		cin>>n;

		for (int j=0;j<n;j++){
			cin>>niza[j];

		}

		List l=List(niza,n);

		lc.addNewList(l);
	}


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}
