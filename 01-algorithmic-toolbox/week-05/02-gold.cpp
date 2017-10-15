#include <algorithm>
#include <limits>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

template< typename T >
typename T::value_type & itemAtCoord( T & cont, size_t width, size_t i, size_t j )
{
    return cont[ i + j * width ];
}

template< typename T >
T maxKnapsack( size_t knapsackSize, const vector < T > & available )
{
    vector< T > variants( ( knapsackSize + 1 ) * ( available.size() + 1 ) );

    for( size_t numItems = 1; numItems <= available.size(); numItems ++ )
    {
        for( size_t curSize = 1; curSize <= knapsackSize; curSize ++ )
        {
            size_t maxWeight = itemAtCoord( variants, knapsackSize + 1, curSize, numItems - 1 );
            size_t curItemWeight = available[ numItems - 1 ];
            if( curSize >= curItemWeight )
            {
                size_t newWeight = itemAtCoord( variants, knapsackSize + 1, ( curSize - curItemWeight ), ( numItems - 1 ) ) + curItemWeight;
                maxWeight = max( maxWeight, newWeight );
            }

            itemAtCoord( variants, knapsackSize + 1, curSize, numItems ) = maxWeight;
        }
    }

    return * variants.crbegin();
}

int main()
{
    size_t knapsackSize;
    cin >> knapsackSize;

    size_t itemNum;
    cin >> itemNum;

    vector< size_t > items;
    items.reserve( itemNum );
    copy( istream_iterator< int64_t >( cin ), istream_iterator< int64_t >(), back_inserter( items ) );

    cout << maxKnapsack( knapsackSize, items ) << endl;
}
