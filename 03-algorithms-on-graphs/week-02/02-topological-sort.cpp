#include <functional>
#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <vector>

using namespace std;
class AdjacencyList
{
public:

    using VertexId = uint64_t;
    using AdjacentVertices = vector< VertexId >;

    AdjacencyList( size_t verticesNum )
        : v( verticesNum + 1 ) // input uses 1 based indexing
    {
    }

    void addDirectedEdge( VertexId a, VertexId b )
    {
        v[ a ].push_back( b );
    }

    void dfs( VertexId vid, vector< bool > & visited, AdjacentVertices & order ) const
    {
        cerr << '\t' << vid << endl;
        visited[ vid ] = true;
        for( VertexId adjacent : v[ vid ] )
        {
            if( ! visited[ adjacent ] )
            {
                dfs( adjacent, visited, order );
            }
        }
        order.push_back( vid );
    }

    AdjacentVertices topologicalSort() const
    {
        set< VertexId > notVisited;
        for( size_t i = 1; i < v.size(); ++ i )
        {
            notVisited.insert( i );
        }

        AdjacentVertices reversedResult;
        vector< bool > visited( v.size(), false );

        while( notVisited.size() )
        {
            VertexId start = * notVisited.cbegin();

            AdjacentVertices order;

            dfs( start, visited, order );

            for( VertexId v : order )
            {
                notVisited.erase( v );
            }

            copy( order.cbegin(), order.cend(), back_inserter( reversedResult ) );
        }

        AdjacentVertices result( reversedResult.crbegin(), reversedResult.crend() );
        return result;
    }

private:

    friend ostream & operator << ( ostream & out, const AdjacencyList & g );

    vector< AdjacentVertices > v;
};

ostream & operator << ( ostream & out,
                        const AdjacencyList::AdjacentVertices & vertices )
{
    copy( vertices.cbegin(),
          vertices.cend(),
          ostream_iterator< AdjacencyList::VertexId >( out, " " ) );
    return out;
}

ostream & operator << ( ostream & out, const AdjacencyList & g )
{
    out << "{" << endl;
    for( size_t i = 0; i < g.v.size(); ++ i )
    {
        const auto & adjacentVertices = g.v[ i ];
        out << "\t" << i << ": { ";
        for( const auto & vertex : adjacentVertices )
        {
            out << vertex << " ";
        }
        out << "}" << endl;
    }
    out << endl << "}" << endl;

    return out;
}

int main( int argc, char** argv )
{
    size_t verticeNum;
    size_t edgeNum;

    cin >> verticeNum >> edgeNum;

    AdjacencyList graph( verticeNum );

    for( size_t i = 0; i < edgeNum; i ++ )
    {
        AdjacencyList::VertexId a;
        AdjacencyList::VertexId b;

        cin >> a >> b;
        graph.addDirectedEdge( a, b );
    }

    cout << graph.topologicalSort() << endl;

    return 0;
}
