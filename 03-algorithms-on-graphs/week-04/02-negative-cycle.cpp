#include <iostream>
#include <limits>
#include <vector>

using namespace std;

using Id = uint64_t;
using Weight = int64_t;

struct Edge
{
    Edge( Id id, Weight weight )
        : id( id )
        , weight( weight )
    {
    }

    Id id;
    Weight weight;
};

template < typename T >
ostream & operator << ( ostream & out, const vector < T > & v )
{
    out << "[ ";
    for( const auto & element : v )
    {
        out << element << " ";
    }
    out << "]";
    return out;
}

class WeightedGraph
{
public:

    using AdjacentVertecies = vector< Edge >;
    WeightedGraph( size_t vertexNum )
        : v( vertexNum + 1 )
    {
    }

    void addDirectedEdge( Id a, Id b, Weight w )
    {
        v[ a ].emplace_back( b, w );
    }

    bool relaxEdges( vector< Weight > & distances, vector< Id > & path ) const
    {
        bool relaxed = false;
        for( size_t vertex = 1; vertex < v.size(); ++ vertex )
        {
            for( const auto & edge : v[ vertex ] )
            {
                Weight oldWeight = distances[ edge.id ];
                Weight newWeight = distances[ vertex ] + edge.weight;

                // // Detecting possible overflow
                // if( distances[ vertex ] > 0
                //     && ( numeric_limits< Weight >::max() - distances[ vertex ] ) > edge.weight )
                // {
                //     newWeight = distances[ vertex ] + edge.weight;
                // }
                // else
                // {
                //     distances[ vertex ] = numeric_limits< Weight >::max();
                // }

                // cerr << "\trelaxing ( " << vertex << ", " << edge.id << ", " << edge.weight << " ): "
                //      << oldWeight << " -> " << newWeight
                //      << " [ " << distances[ vertex ] << " + " << edge.weight << " ]" << endl;
                if( newWeight < oldWeight )
                {
                    // cerr << "\t\tRelaxed!" << endl;
                    distances[ edge.id ] = newWeight;
                    path[ edge.id ] = vertex;
                    relaxed = true;
                }
                // cerr << "\t\tdistances: " << distances << endl;
                // cerr << "\t\tpath     : " << path << endl;
            }
        }
        return relaxed;
    }

    bool hasNegativeCycle() const
    {
        const Id start = 1;
        vector< Weight > distances( v.size(), 1000000 );
        distances[ start ] = 0;

        vector< Id > path( v.size(), 0 );

        for( size_t i = 1; i < v.size() - 1; ++ i )
        {
            // cerr << "Relaxing pass #" << i << endl;
            bool relaxed = relaxEdges( distances, path );
            if( ! relaxed )
            {
                return false;
            }
        }

        // cerr << "Final relaxing pass..." << endl;
        bool hasNegativeCycle = relaxEdges( distances, path );
        return hasNegativeCycle;
    }

private:
    friend ostream & operator << ( ostream & out, const WeightedGraph & g );
    vector < AdjacentVertecies > v;
};

ostream & operator << ( ostream & out, const WeightedGraph & g )
{
    out << "{" << endl;
    for( size_t i = 0; i < g.v.size(); ++ i )
    {
        const auto & edges = g.v[ i ];
        out << "\t" << i << ": { ";
        for( const auto & edge : edges )
        {
            out << "( " << edge.id << ", " << edge.weight << " ) ";
        }
        out << "}" << endl;
    }
    out << "}" << endl;

    return out;
}

int main( int argc, char ** argv )
{
    size_t vertexNum;
    size_t edgeNum;

    cin >> vertexNum >> edgeNum;

    WeightedGraph graph( vertexNum );

    for( size_t i = 0; i < edgeNum; i ++ )
    {
        Id a;
        Id b;
        Weight w;

        cin >> a >> b >> w;
        graph.addDirectedEdge( a, b, w );
    }

    // cerr << graph << endl;

    cout << int( graph.hasNegativeCycle() ) << endl;

    return 0;
}
