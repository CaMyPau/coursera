#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <list>
#include <vector>

using namespace std;

class MyHash
{
public:

    MyHash( size_t m )
        : m( m )
        , buckets( m )
    {
    }

    void add( const string & s )
    {
        size_t bucketNum = bucket( s );
        cerr << "ADD: " << s << " = " << bucketNum << endl;

        Bucket & bucket = buckets[ bucketNum ];
        auto it = std::find( bucket.cbegin(), bucket.cend(), s );
        if( it == bucket.cend() )
        {
            bucket.emplace_front( s );
        }
    }

    void del( const string & s )
    {
        size_t bucketNum = bucket( s );
        cerr << "DEL: " << s << " = " << bucketNum << endl;

        auto & bucket = buckets[ bucketNum ];
        auto it = std::find( bucket.cbegin(), bucket.cend(), s );
        if( it != bucket.cend() )
        {
            bucket.erase( it );
        }
    }

    bool find( const string & s ) const
    {
        size_t bucketNum = bucket( s );
        cerr << "FIND: " << s << " = " << bucketNum << endl;

        auto & bucket = buckets[ bucketNum ];
        auto it = std::find( bucket.cbegin(), bucket.cend(), s );
        return it != bucket.cend();
    }

    const list< string > & check( size_t bucketNum ) const
    {
        cerr << "CHECK " << bucketNum << ": " << endl;
        return buckets[ bucketNum ];
    }

private:

    using Bucket = list< string >;

    size_t bucket( const string & s ) const
    {
        size_t result = 0;

        uint64_t tx = 1;
        for( uint64_t c : s )
        {
            result += ( c * tx );
            result %= p;
            tx *= x;
            tx %= p;
        }

        result %= m;
        return result;
    }

    static const uint64_t p = 1000000007;
    static const uint64_t x = 263;
    uint64_t m;

    vector< Bucket > buckets;
};

int main()
{
    int m;
    cin >> m;
    int n;
    cin >> n;

    MyHash mh( m );
    string op;
    string word;
    int bucket;
    for( int i = 0; i < n; i ++ )
    {
        cin >> op;
        if( op == "#" )
        {
            continue;
        }
        if( op == "add" )
        {
            cin >> word;
            mh.add( word );
        }
        if( op == "check" )
        {
            cin >> bucket;
            auto l = mh.check( bucket );
            copy( l.cbegin(), l.cend(), ostream_iterator< string >( cout, " " ) );
            cout << endl;
        }
        if( op == "del" )
        {
            cin >> word;
            mh.del( word );
        }
        if( op == "find" )
        {
            cin >> word;
            bool found = mh.find( word );
            cout << ( found ? "yes" : "no" ) << endl;
        }
    }
}
