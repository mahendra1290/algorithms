#include <bits/stdc++.h>

using namespace std;

template<class T>
class Comparable {
    public:
       virtual int compareTo(T object) = 0;
};

class Square : public Comparable<Square> {
    int side;
    public:
        Square(int side) {
            this->side = side;
        }
        int getArea();
        int compareTo(Square square);
};

int Square::getArea() {
    return side * side;
}

int Square::compareTo(Square square) {
    if (getArea() > square.getArea()) {
        return 1;
    }
    else if (getArea() < square.getArea()) {
        return -1;
    }
    return 0;
}

int main() {
    Square sqr1 = Square(5);
    Square sqr2 = Square(6);
    cout << sqr1.compareTo(sqr2) << endl;
}