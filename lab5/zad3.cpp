#include <iostream>
#include <cstring>

using namespace std;

class Matrica{
private:
    float matrica[10][10];
    int n,m;
public:
    Matrica(){
        n=0;
        m=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                matrica[i][j]=0;
            }
        }
    }Matrica operator +(int br){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                matrica[i][j]+=br;
            }
        }return *this;
    } Matrica operator*(const Matrica &mat){
        Matrica temp;
        temp.n=this->n;
        temp.m=this->m;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                float zbir=0;
                for(int k=0;k<n;k++){
                    zbir+=this->matrica[i][k]*mat.matrica[k][j];
                }temp.matrica[i][j]=zbir;
            }
        }return temp;
    }Matrica operator-(const Matrica &mat){
        Matrica temp;
        temp.n=this->n;
        temp.m=this->m;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                temp.matrica[i][j]=this->matrica[i][j]-mat.matrica[i][j];
            }
        }return temp;
    } friend istream&operator>>(istream &in,Matrica &mat){
        in>>mat.n;
        in>>mat.m;
        for(int i=0;i<mat.n;i++){
            for(int j=0;j<mat.m;j++){
                in>>mat.matrica[i][j];
            }
        }return in;
    }
    friend ostream&operator<<(ostream &out,const Matrica &mat){
        for(int i=0;i<mat.n;i++){
            for(int j=0;j<mat.m;j++){
                out<<mat.matrica[i][j]<<" ";
            }out<<endl;
        }return out;
    }
};

int main(){

    Matrica A,B,C;
    cin>>A>>B>>C;
    Matrica D=B*C;
    Matrica R=A-D+2;
    cout<<R;

    return 0;
}
