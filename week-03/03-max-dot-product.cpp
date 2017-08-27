#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector< int64_t > a;
    vector< int64_t > b;

    a.reserve( n );
    b.reserve( n );

    int64_t tmp;
    for( int i = 0; i < n; i ++ )
    {
        cin >> tmp;
        a.push_back( tmp );
    }
    for( int i = 0; i < n; i ++ )
    {
        cin >> tmp;
        b.push_back( tmp );
    }

    sort( a.begin(), a.end() );
    sort( b.begin(), b.end() );

    int64_t result = 0;
    for( size_t i = 0; i < a.size(); i ++ )
    {
        result += a[ i ] * b[ i ];
    }

    cout << result << endl;
}
