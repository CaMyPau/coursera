#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

template < typename T >
bool majority( vector < T > & data )
{
    if( data.size() )
    {
        sort( data.begin(), data.end() );

        T value = *data.cbegin();
        size_t cnt = 0;
        for( const auto & d : data )
        {
            if( value == d )
            {
                cnt ++;
                if( cnt > data.size() / 2 )
                    return true;
            }
            else
            {
                value = d;
                cnt = 1;
            }
        }
    }
    return false;
}

int main()
{
    int n;
    cin >> n;

    vector< int64_t > data;
    copy( istream_iterator< int64_t >( cin ), istream_iterator< int64_t >(), back_inserter( data ) );

    cout << majority( data ) << endl;
}
