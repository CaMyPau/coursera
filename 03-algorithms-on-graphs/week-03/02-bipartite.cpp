#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

template< typename VertexIdType = uint64_t >
class Graph
{
public:
    using VertexId = VertexIdType;
    using AdjacentVertices = vector< VertexId >;
    using VertexSet = unordered_set< VertexId >;

    enum class Color : uint8_t
    {
        NONE,
        BLACK,
        GRAY,
        WHITE,
    };
    using ColorMap = unordered_map< VertexId, Color >;

    Graph( size_t verticesNum )
        : v( verticesNum + 1 )
    {
    }

    void addEdge( VertexId a, VertexId b )
    {
        v[ a ].push_back( b );
        v[ b ].push_back( a );
    }

    bool bfs( VertexId start, ColorMap & colors ) const
    {
        queue< VertexId > q;
        q.push( start );

        colors[ start ] = Color::BLACK;
        while( q.size() )
        {
            VertexId vertex = q.front();
            q.pop();
            Color vertexColor = colors[ vertex ];

            for( VertexId adjacentVertex : v[ vertex ] )
            {
                if( colors[ adjacentVertex ] == vertexColor )
                {
                    return false;
                }
                if( colors[ adjacentVertex ] == Color::NONE )
                {
                    q.push( adjacentVertex );
                    colors[ adjacentVertex ] = ( vertexColor == Color::BLACK ? Color::WHITE : Color::BLACK );
                }
            }
        }

        return true;
    }

    bool bipartite() const
    {
        VertexSet toVisit;
        for( VertexId i = 1; i < v.size(); ++ i )
        {
            toVisit.insert( i );
        }

        while( toVisit.size() )
        {
            const VertexId start = * toVisit.cbegin();
            ColorMap colors;

            if( bfs( start, colors ) )
            {
                for( const auto & vertexColor : colors )
                {
                    toVisit.erase( vertexColor.first );
                }
            }
            else
            {
                return false;
            }
        }
        return true;
    }

private:

    vector< AdjacentVertices > v;
};

int main( int argc, char ** argv )
{
    size_t verticeNum;
    size_t edgeNum;

    cin >> verticeNum >> edgeNum;

    using BasicGraph = Graph< uint64_t >;
    BasicGraph graph( verticeNum );

    for( size_t i = 0; i < edgeNum; i ++ )
    {
        BasicGraph::VertexId a;
        BasicGraph::VertexId b;

        cin >> a >> b;
        graph.addEdge( a, b );
    }

    cout << int( graph.bipartite() ) << endl;

    return 0;
}
