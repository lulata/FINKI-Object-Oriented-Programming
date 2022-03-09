#include<iostream>
#include<cstring>
using namespace std;

class Category {
private:
    char ime[20];
public:
    Category(char *ime="unnamed"){
        strcpy(this->ime,ime);
    }void print(){
        cout<<"Category: "<<ime<<endl;
    }~Category(){}
};

class NewsArticle  {
private:
    Category cat;
    char naslov[30]="untitled";
public:
    NewsArticle(){}
    NewsArticle(Category cat,char *naslov="untitled"){
        this->cat=cat;
        strcpy(this->naslov,naslov);
    }void print(){
        cout<<"Article title: "<<naslov<<endl;
        cat.print();
    }~NewsArticle(){}
};

class FrontPage   {
private:
    NewsArticle news;
    float cena;
    int brIzd;
public:
    FrontPage(){
        brIzd=0;
        cena=0;
    }
    FrontPage(NewsArticle news,float cena=0,int brIzd=0){
        this->news=news;
        this->cena=cena;
        this->brIzd=brIzd;
    }void print(){
        cout<<"Price: "<<cena<<", Edition number: "<<brIzd<<endl;
        news.print();
    }~FrontPage(){}
};

int zad3() {
	char categoryName[20];
	char articleTitle[30];
	float price;
	int editionNumber;

	int testCase;
	cin >> testCase;


	if (testCase == 1) {
		int iter;
		cin >> iter;
		while (iter > 0) {
			cin >> categoryName;
			cin >> articleTitle;
			cin >> price;
			cin >> editionNumber;
			Category category(categoryName);
			NewsArticle article(category, articleTitle);
			FrontPage frontPage(article, price, editionNumber);
			frontPage.print();
			iter--;
		}
	}
	else if (testCase == 2) {
		cin >> categoryName;
		cin >> price;
		cin >> editionNumber;
		Category category(categoryName);
		NewsArticle article(category);
		FrontPage frontPage(article, price, editionNumber);
		frontPage.print();
	}// test case 3
	else if (testCase == 3) {
		cin >> categoryName;
		cin >> articleTitle;
		cin >> price;
		Category category(categoryName);
		NewsArticle article(category, articleTitle);
		FrontPage frontPage(article, price);
		frontPage.print();
	}
    else {
    	FrontPage frontPage = FrontPage();
        frontPage.print();
    }
	return 0;
}
