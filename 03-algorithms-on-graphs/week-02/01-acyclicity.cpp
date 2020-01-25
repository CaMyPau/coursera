#include <functional>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

template < typename T >
ostream & operator << ( ostream & out, const unordered_set < T > & us )
{
    out << "{ ";
    for( const T & element: us )
    {
        out << element << " ";
    }
    out << "}";
    return out;
}

class AdjacencyList
{
public:

    using VertexId = uint64_t;

    AdjacencyList( size_t verticesNum )
        : v( verticesNum + 1 ) // input uses 1 based indexing
    {
    }

    void addDirectedEdge( VertexId a, VertexId b )
    {
        v[ a ].push_back( b );
    }

    bool dfs( const VertexId vertex,
              unordered_set< VertexId > & visited,
              unordered_set< VertexId > & traversionStack ) const
    {
        cerr << "\tvertex id: " << vertex << endl;
        cerr << "\t" << traversionStack << endl;

        visited.insert( vertex );
        traversionStack.insert( vertex );

        for( VertexId adjacenVertex : v[ vertex ] )
        {
            if( traversionStack.count( adjacenVertex ) )
            {
                return true;
            }

            if( ! visited.count( adjacenVertex ) )
            {
                bool result = dfs( adjacenVertex, visited, traversionStack );
                if( result )
                {
                    return true;
                }
            }
        }

        traversionStack.erase( vertex );
        return false;
    }

    bool isCyclic() const
    {
        unordered_set< VertexId > toVisit;
        for( size_t i = 1; i < v.size(); ++ i )
        {
            toVisit.insert( i );
        }

        while( toVisit.size() )
        {
            const VertexId start = * toVisit.cbegin();
            unordered_set< VertexId > visited;
            unordered_set< VertexId > traversionStack;

            if( dfs( start, visited, traversionStack ) )
            {
                return true;
            }
            else
            {
                for( VertexId vertex : visited )
                {
                    toVisit.erase( vertex );
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
    out << "}" << endl;

    return out;
}


int main( int argc, char ** argv )
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

    cerr << graph << endl;

    cout << int( graph.isCyclic() ) << endl;
}
