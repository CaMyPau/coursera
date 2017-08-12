#include <iostream>

using namespace std;

int64_t fib_mod( int64_t n, int64_t m )
{
    int64_t i0 = 0;
    int64_t i1 = 1;

    for( int64_t i = 0; i < n; i ++ )
    {
        int64_t tmp = i0;
        i0 = ( i0 + i1 ) % m;
        i1 = tmp;
    }

    return i0;
}

int main()
{
    int64_t n = 0;
    int64_t m = 1;
    cin >> n;
    cin >> m;

    cout << fib_mod( n, m ) << endl;
}
