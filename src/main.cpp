#include "Matrix.h"

using std::cout;
using std::endl;

int main(int argc, char** argv)
{

    const int size = 10;
    Matrix m1( size,size,1.0 );
    for (size_t row_index = 0; row_index < size; ++ row_index)
        for (size_t col_index = 0; col_index < size; ++col_index)
            m1(row_index, col_index) = (68.556*rand()/RAND_MAX - 32.768);
    cout << "M1: \n" << m1 << endl;

    Matrix m2( size,size,1.0 );
    for (size_t row_index = 0; row_index < size; ++ row_index)
        for (size_t col_index = 0; col_index < size; ++col_index)
            m2(row_index, col_index) = (68.556*rand()/RAND_MAX - 32.768);
    cout << "M2: \n" << m1 << endl;

    Matrix m3 = m1 * m2;
    cout << "M3: \n" << m3 << endl;
}