#include "Matrix.h"
#include <memory>

using std::cout;
using std::endl;


int main(int argc, char **argv)
{
    Matrix<int> m1(2, 3);
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(0, 2) = 3;
    m1(1, 0) = 4;
    m1(1, 1) = 5;
    m1(1, 2) = 6;
    cout << "\n" << m1;
    Matrix<int> m2(3, 2);
    m2(0, 0) = 7;
    m2(0, 1) = 8;
    m2(1, 0) = 9;
    m2(1, 1) = 10;
    m2(2, 0) = 11;
    m2(2, 1) = 12;
    cout << "\n" << m2;

    Matrix<int> m3(3, 2);
    m3 = m1 * m2;
    cout << "address of m3 is " << &m3 << "\n";
    Matrix<int> m4(m3);
    cout << "address of m4 is " << &m4 << "\n";
    Matrix<int> m5 = m3;
    cout << "address of m5 is " << &m5 << "\n";
    return 0;
}