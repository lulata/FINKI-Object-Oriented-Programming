
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

template<typename T>
class Array{
private:
    T *pokazuvac;
    int broj;
public:
    Array(int n){
        broj = n;
        pokazuvac = new T[n];
    }~Array(){
        delete[] pokazuvac;
    }void Erase(){
        delete[] pokazuvac;
        broj = 0;
    }T& operator[](int i){
        if (i >= 0 && i <= broj) {
            return pokazuvac[i];
        } else {
            cout << "Index out of bounds!" << endl;
        }
    }int GetLength(){
        return broj;
    }
    friend ostream& operator<< (ostream& out, Array& a){
        int i;
        for (i = 0; i < a.broj-1; ++i) {
            out << "Array[" << i << "] = " << a.pokazuvac[i] << ", ";
        }
        out << "Array[" << i << "] = " <<a.pokazuvac[i];
        out << endl;
        return out;
    }friend istream& operator>> (istream& in, Array& a){
        T tempEnter;
        T *temp = new T[a.broj + 1];
        for (int i = 0, j = 0; i < a.broj; ++i) {
            temp[j++] = a.pokazuvac[i];
        }
        in >> tempEnter;
        temp[a.broj] = tempEnter;
        a.broj++;
        delete[] a.pokazuvac;
        a.pokazuvac = temp;
        return in;
    }T *getPointer(){
        return pokazuvac;
    }
};

template<typename T>
void swap(T *a, T *b){
    T temp = *a;
    *a = *b;
    *b = temp;
}

template<typename T>
void BubbleSort(Array<T> &t){
    int i, j;
    for (i = 0; i < t.GetLength()-1; i++) {
        for (j = 0; j < t.GetLength() - i - 1; j++){
            if (t.getPointer()[j] > t.getPointer()[j + 1]){
                swap(&t.getPointer()[j], &t.getPointer()[j + 1]);
            }
        }
    }
}
template<typename T>
T Sum(Array<T> &t){
    T sum = 0;
    for (int i = 0; i < t.GetLength(); ++i) {
        sum += t.getPointer()[i];
    }return sum;
}

template<typename T>
T Average(Array<T> &t){
    return Sum(t) / (t.GetLength());
}

template<typename T,typename M>
bool Equal (Array<T> &t1, Array<M> &t2){
    if (t1.GetLength() != t2.GetLength()) {
        return false;
    }for (int i = 0; i < t1.GetLength(); ++i) {
        if (t1.getPointer()[i] != t2.getPointer()[i]) {
            return false;
        }
    }return true;
}

template<typename T>
bool Equal (Array <T> &t1, Array<double> &t2){
    double diff1, diff2;
    for (int i = 0; i < t1.GetLength(); ++i) {
        diff1 = t1.getPointer()[i] - t2.getPointer()[i];
        diff2 = Average(t1) - Average(t2);
        if (!((diff1 > -0.1 && diff1 < 0.1) && (diff2 > -0.5 && diff2 < 0.5))) {
            return false;
        }
    }return true;
}

int main()
{

    int n;
    double r;

    cin>>r;
    cin>>n;

    Array<int> anArray(n);
    Array<double> adArray(n);
    Array<int> intArray2(n);

    for (int nCount = 0; nCount < n; nCount++)
    {

        cin>>anArray[nCount];
        adArray[nCount] = anArray[nCount] + r;
    }

    BubbleSort(anArray);

    intArray2 = anArray;

    cout<<"The arrays: "<<endl;
    cout<<anArray;
    cout<<"and "<<endl;
    cout<<intArray2;
    cout<<((Equal(anArray,intArray2))?" ARE":" ARE NOT")<<" same!"<<endl;
    cout<<"The Average of the array adArray is: "<<Average(adArray)<<endl;

    cout<<"The arrays: "<<endl;
    cout<<anArray;
    cout<<"and "<<endl;
    cout<<adArray;
    cout<<((Equal(anArray,adArray))?" ARE":" ARE NOT")<<" same!";


    return 0;
}
