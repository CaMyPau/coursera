#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

template< typename T >
int64_t binarySearch( const vector< T > & data, T value )
{
    int64_t begin = 0;
    int64_t end = data.size() - 1;
    int64_t pivot = ( end - begin ) / 2;

    while( begin <= end )
    {
        if( value == data[ pivot ] )
        {
            return pivot;
        }
        else if( value < data[ pivot ] )
        {
            end = pivot - 1;
        }
        else if( value > data[ pivot ] )
        {
            begin = pivot + 1;
        }

        pivot = begin + ( ( end - begin ) / 2 );
    }

    return -1;
}

int main()
{
    size_t n;
    cin >> n; // Datum size
    vector< int64_t > data;
    data.reserve( n );

    for( size_t i = 0; i < n; i ++ )
    {
        int64_t value;
        cin >> value;
        data.push_back( value );
    }

    cin >> n; // Queries size
    for( size_t i = 0; i < n; i ++ )
    {
        int64_t query;
        cin >> query;
        cout << binarySearch( data, query ) << " ";
    }

    cout << endl;
}
