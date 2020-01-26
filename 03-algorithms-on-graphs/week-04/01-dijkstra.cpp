#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class WeightedGraph
{
public:

    using Id = uint64_t;
    using Weight = uint64_t;

    struct Edge
    {
        Edge( Id i, Weight w )
            : id( i )
            , weight( w )
        {
        }

        bool operator==( const Edge & e ) const
        {
            return id == e.id;
        }

        Id id;
        Weight weight;
    };

    using AdjacentVertices = vector< Edge >;
    using VertexQueue = queue< Id >;

    WeightedGraph( size_t vertexNum )
        : edges( vertexNum + 1 )
    {
    }

    void addEdge( Id a, Id b, Weight w )
    {
        edges[ a ].emplace_back( b, w );
    }

    int dijkstra( Id from, Id to ) const
    {
        vector< Weight > result( edges.size(), numeric_limits< Weight >::max() );
        result[ from ] = 0;

        using VertexDist = Edge;
        vector< VertexDist > queue;
        queue.emplace_back( from, 0 );

        while( queue.size() )
        {
            auto it = min_element( queue.cbegin(),
                                   queue.cend(),
                                   []( const VertexDist & l, const VertexDist & r ) {
                                       return l.weight < r.weight;
                                   } );

            VertexDist vertex = * it;
            queue.erase( it );

            for( const auto & edge : edges[ vertex.id ] )
            {
                Weight oldWeight = result[ edge.id ];
                Weight newWeight = result[ vertex.id ] + edge.weight;

                if( newWeight < oldWeight )
                {
                    result[ edge.id ] = newWeight;
                    if( oldWeight == numeric_limits< Weight >::max() )
                    {
                        queue.emplace_back( edge.id, newWeight );
                    }
                    else
                    {
                        auto it = find_if( queue.begin(),
                                           queue.end(),
                                           [ edge ]( const VertexDist & v ){ return v.id == edge.id; } );

                        it->weight = newWeight;
                    }
                }
            }
        }

        return result[ to ] != numeric_limits< Weight >::max() ? result[ to ] : -1;
    }

private:

    vector< AdjacentVertices > edges;
};

int main( int argc, char ** argv )
{
    size_t vertexNum;
    size_t edgeNum;

    cin >> vertexNum >> edgeNum;

    WeightedGraph graph( vertexNum );

    for( size_t i = 0; i < edgeNum; i ++ )
    {
        WeightedGraph::Id a;
        WeightedGraph::Id b;
        WeightedGraph::Weight w;

        cin >> a >> b >> w;
        graph.addEdge( a, b, w );
    }

    WeightedGraph::Id from;
    WeightedGraph::Id to;

    cin >> from >> to;

    cout << graph.dijkstra( from, to ) << endl;

    return 0;
}
