#include <limits>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int64_t MaxPairwiseProduct( const vector< int64_t > & numbers )
{
    int64_t max0 = numeric_limits< int64_t >::min();
    int64_t max1 = numeric_limits< int64_t >::min();

    for( auto n : numbers )
    {
        if( n > max0 )
        {
            max1 = max0;
            max0 = n;
            continue;
        }

        if( n > max1 )
        {
            max1 = n;
        }
    }

    return max0 * max1;
}

int main() {

    int64_t _;
    cin >> _;

    vector< int64_t > numbers;
    copy( istream_iterator< int64_t >( cin ), istream_iterator< int64_t >(), back_inserter( numbers ) );

    int64_t result = MaxPairwiseProduct( numbers );
    cout << result << endl;

    return 0;
}
