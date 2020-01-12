#include <iostream>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
#include <set>

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

    size_t connectedComponents() const
    {
        set< VertexId > notVisited;
        for( size_t i = 1; i < v.size(); ++ i )
        {
            notVisited.insert( i );
        }

        size_t componentsNum = 0;
        while( ! notVisited.empty() )
        {
            VertexId start = * notVisited.cbegin();
            set< VertexId > component;
            dfs( start, [ & component ]( VertexId v ){ component.insert( v ); return false; } );
            for( VertexId v : component )
            {
                notVisited.erase( v );
            }
            ++ componentsNum;
        }

        return componentsNum;
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

    friend ostream & operator << ( ostream & out, const AdjacencyList & g );

    using AdjacentVertices = vector< VertexId >;

    vector< AdjacentVertices > v;
};


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
        graph.addEdge( a, b );
    }

    cerr << graph << endl;
    cout << graph.connectedComponents() << endl;

    return 0;
}
