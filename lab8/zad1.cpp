#include <iostream>

using namespace std;

class Shape {
public:
    virtual void draw() {
        cout << "Drawing a shape.\n";
    }
};

class Recatangle : public Shape{
public:
    void draw() override{
        cout << "Drawing a rectangle.\n";
    }
};

int main() {
    Shape* shape;
    shape = new Shape();

    shape->draw();

    Recatangle *rectangle = new Recatangle();
    shape = rectangle;
    shape->draw();

    delete shape;
    return 0;
}
