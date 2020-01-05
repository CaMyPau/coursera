#include <algorithm>
#include <iostream>
#include <limits>
#include <iterator>
#include <vector>

using namespace std;

template < typename T >
struct TreeNode
{
    TreeNode( T value = T() )
        : value( value   )
        , left ( nullptr )
        , right( nullptr )
    {
    }

    T value;
    TreeNode * left  = nullptr;
    TreeNode * right = nullptr;
};

template < typename T >
void populateNode(
    TreeNode< T > * node,
    int64_t index,
    const vector< int64_t > & keys,
    const vector< int64_t > & lefts,
    const vector< int64_t > & rights )
{
    node->value = keys[ index ];

    int64_t leftIndex = lefts[ index ];
    if( leftIndex != -1 )
    {
        node->left = new TreeNode< T >;
        populateNode( node->left, leftIndex, keys, lefts, rights );
    }

    int64_t rightIndex = rights[ index ];
    if( rightIndex != -1 )
    {
        node->right = new TreeNode< T >;
        populateNode( node->right, rightIndex, keys, lefts, rights );
    }
}

TreeNode< int64_t > * createTree(
     const vector< int64_t > & keys,
     const vector< int64_t > & lefts,
     const vector< int64_t > & rights )
{
    TreeNode< int64_t > * root = new TreeNode< int64_t >;

    if( keys.size() )
    {
        populateNode( root, 0, keys, lefts, rights );
    }

    return root;
}

template < typename T >
bool isBinarySearchTree(
    const TreeNode< T > * node,
    T minValue = numeric_limits< T >::min(),
    T maxValue = numeric_limits< T >::max() )
{
    bool result = true;

    if( node )
    {
        // cerr << minValue << " " << node->value << " " << maxValue << endl;

        if( ! ( node->value >= minValue && node->value < maxValue ) )
        {
            return false;
        }

        T newMaxValue = min( node->value, maxValue );
        if( ! isBinarySearchTree( node->left, minValue, newMaxValue ) )
        {
            return false;
        }

        T newMinValue = max( node->value, minValue );
        if( ! isBinarySearchTree( node->right, newMinValue, maxValue ) )
        {
            return false;
        }
    }

    return result;
}

int main( int argc, char ** argv )
{
    int64_t numNodes;
    cin >> numNodes;

    int64_t key;
    int64_t left;
    int64_t right;

    vector< int64_t > keys;
    vector< int64_t > lefts;
    vector< int64_t > rights;

    keys  .reserve( numNodes );
    lefts .reserve( numNodes );
    rights.reserve( numNodes );

    for( int64_t i = 0; i < numNodes; i ++ )
    {
        cin >> key >> left >> right;

        keys  .emplace_back( key   );
        lefts .emplace_back( left  );
        rights.emplace_back( right );
    }

    TreeNode< int64_t > * root = createTree( keys, lefts, rights );

    cout << ( isBinarySearchTree( root ) ? "CORRECT" : "INCORRECT" ) << endl;

    return 0;
}
