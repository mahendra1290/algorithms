#include <iostream>
#include <vector>

using namespace std;

class SquareMatrix {
    int size;
    int **matrix;

    public:
        SquareMatrix();
        SquareMatrix(int size);
        void setMatrix();
        void printMatrix();
        int getElem(int i, int j);
        void setElem(int i, int j, int val);
        vector<SquareMatrix> splitIntoFour();
        void joinFourIntoOne(vector<SquareMatrix> grid);
        void copyOneFourth(SquareMatrix bigMat, int rowIndex, int colIndex);
        void copyPartAt(int rowIndex, int colIndex, SquareMatrix smallMat);
        static SquareMatrix multiply(SquareMatrix first, SquareMatrix second);
        static SquareMatrix add(SquareMatrix first, SquareMatrix second);
        friend SquareMatrix operator*(SquareMatrix first, SquareMatrix second);
        friend SquareMatrix operator+(SquareMatrix first, SquareMatrix second);
};

SquareMatrix::SquareMatrix() {
    size = 0;
    matrix = NULL;
}

SquareMatrix::SquareMatrix(int size) { 
    this->size = size;
    this->matrix = new int *[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }        
}

void SquareMatrix::setMatrix() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int elem;
            cin >> elem;
            this->setElem(i, j, elem);
        }
    }
}

void SquareMatrix::setElem(int i, int j, int val) {
    if ( (i >= 0 && i < size) && (j >= 0 && j < size) ) {
        matrix[i][j] = val;
    }
    else {
        std::string msg = "INDEX ERROR \n can't set elem at position " +
                    std::to_string(i) + " " + std::to_string(j);
        throw std::runtime_error(msg);
    }
}

int SquareMatrix::getElem(int i, int j) {
    if ( (i >= 0 && i < size) && (j >= 0 && j < size) ) {
        return matrix[i][j];
    }
    else {
        std::string msg = "INDEX ERROR \n can't set elem at position " +
                    std::to_string(i) + " " + std::to_string(j);
        throw std::runtime_error(msg);
    }
}

void SquareMatrix::copyOneFourth(SquareMatrix bigMat, int rowIndex, int colIndex) {
    int tempRow = rowIndex;
    int tempCol = colIndex;
    for (int i = 0; i < size; i++) {
        tempCol = colIndex;
        for (int j = 0; j < size; j++) {
            setElem(i, j, bigMat.getElem(tempRow, tempCol));
            tempCol++;
        }
        tempRow++;
    }
}

void SquareMatrix::copyPartAt(int rowIndex, int colIndex, SquareMatrix smallMat){
    int tempRow = rowIndex;
    int tempCol = colIndex;
    for (int i = 0; i < size/2; i++) {
        for (int j = 0; j < size/2; j++) {
            int val = smallMat.getElem(i, j);
            this->setElem(tempRow, tempCol, val);
            tempCol++;
        }
        tempCol = colIndex;
        tempRow++;
    }
}

void SquareMatrix::joinFourIntoOne(vector<SquareMatrix> grid) {
    int mid = size/2;
    copyPartAt(0, 0, grid[0]);
    copyPartAt(0, mid, grid[1]);
    copyPartAt(mid, 0, grid[2]);
    copyPartAt(mid, mid, grid[3]);
}

vector<SquareMatrix> SquareMatrix::splitIntoFour() {
    int mid = size/2;
    int smallSize = size/2;
    vector<SquareMatrix> grid;
    for (int i = 0; i < 4; i++) {
        SquareMatrix mat = SquareMatrix(smallSize);
        grid.push_back(mat);
    }
    grid[0].copyOneFourth(*this, 0, 0);
    grid[1].copyOneFourth(*this, 0, mid);
    grid[2].copyOneFourth(*this, mid, 0);
    grid[3].copyOneFourth(*this, mid, mid);
    return grid;
}

void SquareMatrix::printMatrix() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] <<" ";
        }
        cout << endl;
    }
}

SquareMatrix operator+(SquareMatrix first, SquareMatrix second) {
    return SquareMatrix::add(first, second);
}

SquareMatrix SquareMatrix::add(SquareMatrix first, SquareMatrix second) {
    SquareMatrix mat = SquareMatrix(first.size);
    for (int i = 0; i < first.size; i++) {
        for (int j = 0; j < first.size; j++) {
            int elem = first.getElem(i, j) + second.getElem(i, j);
            mat.setElem(i, j, elem);
        }
    }
    return mat;
}

SquareMatrix operator*(SquareMatrix first, SquareMatrix second) {
    return SquareMatrix::multiply(first, second);
}

SquareMatrix SquareMatrix::multiply(SquareMatrix first, SquareMatrix second) {
    if (first.size == 1 && second.size == 1) {
        SquareMatrix mat = SquareMatrix(1);
        mat.matrix[0][0] = first.matrix[0][0] * second.matrix[0][0];
        return mat;
    }
    else {
        int n = first.size;
        SquareMatrix ans(n); 
        vector<SquareMatrix> matricesOfFirst = first.splitIntoFour();
        vector<SquareMatrix> matricesOfSecond = second.splitIntoFour();
        vector<SquareMatrix> ansGrid;
        SquareMatrix temp = (matricesOfFirst[0] * matricesOfSecond[0]) + 
                            (matricesOfFirst[1] * matricesOfSecond[2]);
        ansGrid.push_back(temp);
        SquareMatrix temp1 = (matricesOfFirst[0] * matricesOfSecond[1]) + 
                            (matricesOfFirst[1] * matricesOfSecond[3]);
        ansGrid.push_back(temp1);
        SquareMatrix temp2 = (matricesOfFirst[2] * matricesOfSecond[0]) + 
                            (matricesOfFirst[3] * matricesOfSecond[2]);
        ansGrid.push_back(temp2);
        SquareMatrix temp3 = (matricesOfFirst[2] * matricesOfSecond[1]) + 
                            (matricesOfFirst[3] * matricesOfSecond[3]);
        ansGrid.push_back(temp3);
        ans.joinFourIntoOne(ansGrid);
        return ans;
    } 
}

int main() {
    SquareMatrix mat(4);
    mat.setMatrix();
    SquareMatrix mat1(4);
    mat1.setMatrix();
    SquareMatrix mat3 = mat + mat1;
    SquareMatrix multi = mat * mat1;
    multi.printMatrix();
    mat3.printMatrix();
    return 0;
}