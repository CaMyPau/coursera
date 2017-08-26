#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

typedef vector < tuple < uint64_t, uint64_t, double > > Loot;

tuple< Loot, size_t > readLoot( istream & inp )
{
    Loot result;
    size_t n;
    size_t size;
    uint64_t weight;
    uint64_t value;

    cin >> n >> size;
    for( size_t i = 0; i < n; i ++ )
    {
        inp >> value >> weight;
        if( inp.eof() )
        {
            break;
        }
        result.emplace_back( weight, value, double( value ) / weight );
    }

    sort( result.begin()
        , result.end()
        , []( const Loot::value_type & r, const Loot::value_type & l ) -> bool
          { return get< 2 >( r ) > get< 2 >( l ); } );

    return tuple< Loot, size_t >( result, size );
}

void printLoot( const Loot & loot )
{
    for( const auto & item : loot )
    {
        cout << get< 0 >( item ) << " " << get< 1 >( item ) << " " << get< 2 >( item ) << endl;
    }
}

double knapsackValue( const Loot & knapsack )
{
    double result = 0;
    for( const auto & item : knapsack )
    {
        result += get< 0 >( item ) * get< 2 >( item );
    }
    return result;
}

Loot fractionalKnapsack( const Loot & loot, size_t size )
{
    Loot result;

    for( auto it = loot.begin(); it != loot.end() && size; it ++ )
    {
        uint64_t fracSize = min( size, get< 0 >( * it ) );
        result.emplace_back( fracSize, get< 1 >( * it ), get< 2 >( * it ) );
        size -= fracSize;
    }

    return result;
}

int main()
{
    Loot loot;
    size_t size;
    tie( loot, size ) = readLoot( cin );

    Loot knapsack = fractionalKnapsack( loot, size );
    cout.precision( 10 );

    cout << knapsackValue( knapsack ) << endl;
}
