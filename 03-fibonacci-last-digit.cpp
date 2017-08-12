#include <iostream>

using namespace std;

int8_t fib( int64_t n )
{
    int8_t i0 = 0;
    int8_t i1 = 1;

    for( int64_t i = 0; i < n; i ++ )
    {
        int8_t tmp = i0;
        i0 = ( i0 + i1 ) % 10;
        i1 = tmp;
    }

    return i0;
}

int main()
{
    int64_t n = 0;
    cin >> n;

    cout << int( fib( n ) ) << endl;
}
