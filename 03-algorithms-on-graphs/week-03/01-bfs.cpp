#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Graph
{
public:
    using VertexId = uint64_t;
    using AdjacentVertecies = vector< VertexId >;

    Graph( size_t verticesNum )
        : v( verticesNum + 1 ) // input uses 1 based indexing
    {
    }

    void addEdge( VertexId a, VertexId b )
    {
        v[ a ].push_back( b );
        v[ b ].push_back( a );
    }

    using Depths = unordered_map< VertexId, size_t >;
    using PathTree = unordered_map< VertexId, VertexId >;

    PathTree bfs( VertexId start ) const
    {
        PathTree pathTree;
        Depths depths;

        queue< VertexId > queue;
        queue.push( start );
        depths[ start ] = 0;

        while( queue.size() )
        {
            VertexId vertex = queue.front();
            queue.pop();

            for( VertexId adjacentVertex : v[ vertex ] )
            {
                if( ! depths.count( adjacentVertex ) )
                {
                    queue.push( adjacentVertex );
                    depths[ adjacentVertex ] = depths[ vertex ] + 1;
                    pathTree[ adjacentVertex ] = vertex;
                }
            }
        }

        return pathTree;
    }

    int shortestPathLength( VertexId from, VertexId to )
    {
        int result = -1;
        PathTree pathTree = bfs( from );

        if ( pathTree.count( to ) )
        {
            VertexId vertex = to;
            AdjacentVertecies invPath;

            while( vertex != from )
            {
                invPath.push_back( vertex );
                vertex = pathTree[ vertex ];
            }

            result = invPath.size();
        }

        return result;
    }

private:

    vector< AdjacentVertecies > v;
};

int main( int argc, char ** argv )
{
    size_t verticeNum;
    size_t edgeNum;

    cin >> verticeNum >> edgeNum;

    Graph graph( verticeNum );

    for( size_t i = 0; i < edgeNum; i ++ )
    {
        Graph::VertexId a;
        Graph::VertexId b;

        cin >> a >> b;
        graph.addEdge( a, b );
    }

    Graph::VertexId from;
    Graph::VertexId to;

    cin >> from >> to;

    cout << graph.shortestPathLength( from, to ) << endl;

    return 0;
}
