#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
class AdjacencyList
{
public:

    using VertexId = uint64_t;

    AdjacencyList( size_t verticesNum )
        : v( verticesNum + 1 ) // input uses 1 based indexing
    {
    }

    void addEdge( VertexId a, VertexId b )
    {
        v[ a ].push_back( b );
        v[ b ].push_back( a );
    }

    bool areConnected( VertexId a, VertexId b ) const
    {
        return dfs( a, [ b ]( VertexId v ){ return v == b; } );
    }

    bool dfs( VertexId start, function< bool( VertexId ) > visitor ) const
    {
        vector< bool > visited( v.size(), false );

        queue< VertexId > toVisit;
        toVisit.push( start );

        while( toVisit.size() )
        {
            VertexId currentVertex = toVisit.front();
            toVisit.pop();
            visited[ currentVertex ] = true;

            if( visitor( currentVertex ) )
            {
                return true;
            }

            for( VertexId adjacent : v[ currentVertex ] )
            {
                if( ! visited[ adjacent ] )
                {
                    toVisit.push( adjacent );
                }
            }
        }

        return false;
    }

private:


    using AdjacentVertices = vector< VertexId >;

    vector< AdjacentVertices > v;
};

int main()
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
        graph.addEdge( a, b );
    }


    AdjacencyList::VertexId u;
    AdjacencyList::VertexId v;
    cin >> u >> v;

    cout << int( graph.areConnected( u, v ) ) << endl;
}
