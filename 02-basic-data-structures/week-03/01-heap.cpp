#include <iostream>
#include <vector>
#include <iterator>
#include <functional>

using namespace std;

typedef pair< size_t, size_t > Swap;
vector< Swap > swaps; // Made as global variable to easily remove this variable which is necessary for assignment only

template < typename T, typename Comp = std::less< T > >
class Heap
{
public:

    Heap( const vector< T > & v )
        : v( v )
    {
    }

    Heap( vector< T > && v )
        : v( std::move( v ) )
    {
    }

    void heapify()
    {
        for( int i = ( v.size() / 2 ); i >= 0; i -- )
        {
            siftDown( i );
        }
    }

    void siftDown( size_t i )
    {
        while( true )
        {
            size_t indexToSwap = i;
            size_t lc = leftChildPos( i );
            // If there's left child and it doesn't satisfy heap property
            if( lc < v.size() && Comp{}( v[ i ], v[ lc ] ) )
            {
                indexToSwap = lc;
            }

            // If there's right child, it doesn't satisfy heap property and
            // it is violates heap property "stronger" than left child
            size_t rc = rightChildPos( i );
            if( rc < v.size()
                && Comp{}( v[ i ], v[ rc ] )
                && Comp{}( v[ lc ], v[ rc ] ) )
            {
                indexToSwap = rc;
            }

            if( i != indexToSwap )
            {
                swap( v[ i ], v[ indexToSwap ] );
                swaps.emplace_back( i, indexToSwap );

                i = indexToSwap;
            }
            else
            {
                break;
            }
        }
    }

    const std::vector< T > & get() const
    {
        return v;
    }

private:

    static size_t parentPos( size_t s )
    {
        return s / 2;
    }

    static size_t leftChildPos( size_t s )
    {
        return 2 * s + 1;
    }

    size_t rightChildPos( size_t s )
    {
        return 2 * s + 2;
    }

    std::vector< T > v;
};

int main()
{
    size_t n;
    cin >> n;

    vector< int64_t > v;
    v.reserve( n );

    copy( istream_iterator< int64_t >( cin ),
          istream_iterator< int64_t >(),
          back_inserter( v ) );

    Heap< int64_t, std::greater< int64_t > > h( std::move( v ) );
    h.heapify();

    cout << swaps.size() << endl;
    for( const auto & s : swaps )
    {
        cout << s.first << " " << s.second << endl;
    }

    copy( h.get().cbegin(), h.get().cend(), ostream_iterator< int64_t >( cerr, " " ) );
}
