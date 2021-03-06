#include <iostream>

using namespace std;

int64_t gcd( int64_t a, int64_t b )
{
    int64_t * max = nullptr;
    int64_t * min = nullptr;

    if( a > b )
    {
        max = & a;
        min = & b;
    }
    else
    {
        max = & b;
        min = & a;
    }

    int64_t r = ( * max ) % ( * min );
    if( r == 0 )
    {
        return * min;
    }

    return gcd( * min, r );
}

int main()
{
    int64_t a;
    int64_t b;

    cin >> a >> b;
    cout << gcd( a, b ) << endl;
}
