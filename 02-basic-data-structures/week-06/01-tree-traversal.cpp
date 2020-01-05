#include <algorithm>
#include <iostream>
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
    populateNode( root, 0, keys, lefts, rights );
    return root;
}

template < typename T >
ostream & operator<< ( ostream & out, const vector< T > & v )
{
    out << "{ ";
    copy( v.cbegin(), v.cend(), ostream_iterator< T >( out, " " ) );
    out << "}";

    return out;
}

template < typename T >
void inOrder( const TreeNode< T > * node )
{
    if( node )
    {
        inOrder( node->left );
        cout << node->value << " ";
        inOrder( node->right );
    }
}

template < typename T >
void preOrder( const TreeNode< T > * node )
{
    if( node )
    {
        cout << node->value << " ";
        preOrder( node->left );
        preOrder( node->right );
    }
}

template < typename T >
void postOrder( const TreeNode< T > * node )
{
    if( node )
    {
        postOrder( node->left );
        postOrder( node->right );
        cout << node->value << " ";
    }
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

    inOrder( root );
    cout << endl;

    preOrder( root );
    cout << endl;

    postOrder( root );
    cout << endl;

    return 0;
}
