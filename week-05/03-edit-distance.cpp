#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

template < typename T >
class Vector2D
{
public:

    Vector2D( size_t rows, size_t cols )
        : rows( rows )
        , cols( cols )
        , v( rows * cols )
    {
    }

    const T & cell( size_t row, size_t column ) const
    {
        return v[ row * cols + column ];
    }

    T & cell( size_t row, size_t column )
    {
        return v[ row * cols + column ];
    }

    void print() const
    {
        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
        for( size_t i = 0; i < rows; i ++ )
        {
            for( size_t j = 0; j < cols; j ++ )
            {
                cout << cell( i, j ) << " ";
            }
            cout << endl;
        }
        cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
    }

private:

    size_t rows;
    size_t cols;
    vector< T > v;
};

size_t editDistance( const string & s0, const string & s1 )
{
    size_t rowsTotal = s0.size() + 1;
    size_t colsTotal = s1.size() + 1;
    Vector2D< size_t > matrix( rowsTotal, colsTotal );

    // Fill first column
    for( size_t i = 0; i < rowsTotal; i ++ )
    {
        matrix.cell( i, 0 ) = i;
    }

    // Fill first column
    for( size_t i = 1; i < colsTotal; i ++ )
    {
        matrix.cell( 0, i ) = i;
    }

    for( size_t i = 1; i < rowsTotal; i ++ )
    {
        for( size_t j = 1; j < colsTotal; j ++ )
        {
            size_t top  = matrix.cell( i - 1, j     ) + 1;
            size_t left = matrix.cell( i    , j - 1 ) + 1;
            size_t minValue = min( top, left );

            bool notSame = ( s0[ i - 1 ] != s1[ j - 1 ] );
            size_t diag = matrix.cell( i - 1, j - 1 ) + ( notSame ? 1 : 0 );
            minValue = min( minValue, diag );
            matrix.cell( i, j ) = minValue;
        }
    }

    return matrix.cell( rowsTotal - 1, colsTotal - 1 );
}

int main()
{
    string s0;
    string s1;

    cin >> s0 >> s1;
    cout << editDistance( s0, s1 ) << endl;
}
