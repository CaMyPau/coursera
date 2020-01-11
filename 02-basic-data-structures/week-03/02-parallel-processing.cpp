#include <queue>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <vector>

using namespace std;

template < typename T, typename Comp = std::less< T > >
class Heap
{
public:

    Heap()
        : v()
    {
    }

    Heap( const vector< T > & v )
        : v( v )
    {
    }

    Heap( vector< T > && v )
        : v( std::move( v ) )
    {
    }

    void heapify()
    {
        for( int i = ( v.size() / 2 ); i >= 0; i -- )
        {
            siftDown( i );
        }
    }

    void insert( const T & e )
    {
        v.emplace_back( e );
        siftUp( v.size() - 1 );
    }

    T pop()
    {
        T result = v[ 0 ];
        swap( v[ 0 ], v[ v.size() - 1 ] );
        v.pop_back();
        siftDown( 0 );
        return result;
    }

    const std::vector< T > & get() const
    {
        return v;
    }

private:

    void siftUp( uint64_t i )
    {
        while( i > 0 && Comp{}( v[ parentPos( i ) ], v[ i ] ) )
        {
            swap( v[ parentPos( i ) ], v[ i ] );
            i = parentPos( i );
        }
    }

    void siftDown( uint64_t i )
    {
        while( true )
        {
            uint64_t indexToSwap = i;
            uint64_t lc = leftChildPos( i );
            // If there's left child and it doesn't satisfy heap property
            if( lc < v.size() && Comp{}( v[ i ], v[ lc ] ) )
            {
                indexToSwap = lc;
            }

            // If there's right child, it doesn't satisfy heap property and
            // it is violates heap property "stronger" than left child
            uint64_t rc = rightChildPos( i );
            if( rc < v.size()
                && Comp{}( v[ i ], v[ rc ] )
                && Comp{}( v[ lc ], v[ rc ] ) )
            {
                indexToSwap = rc;
            }

            if( i != indexToSwap )
            {
                swap( v[ i ], v[ indexToSwap ] );
                i = indexToSwap;
            }
            else
            {
                break;
            }
        }
    }

    static uint64_t parentPos( uint64_t s )
    {
        return s / 2;
    }

    static uint64_t leftChildPos( uint64_t s )
    {
        return 2 * s + 1;
    }

    uint64_t rightChildPos( uint64_t s )
    {
        return 2 * s + 2;
    }

    std::vector< T > v;
};

template < typename T, typename Comp = std::less< T > >
class StdHeap
{
public:

    void insert( const T & v )
    {
        pq.emplace( v );
    }

    T pop()
    {
        T result = pq.top();
        pq.pop();
        return result;
    }

    const std::priority_queue< T > & get() const
    {
        return pq;
    }

private:

    std::priority_queue< T, std::vector< T >, Comp > pq;
};

struct Job
{
    Job()
    {
    }

    Job( uint64_t threadId, uint64_t jobIndex, uint64_t startTime, uint64_t finishTime )
        : threadId( threadId )
        , jobIndex( jobIndex )
        , startTime( startTime )
        , finishTime( finishTime )
    {
    }

    uint64_t threadId;
    uint64_t jobIndex;
    uint64_t startTime;
    uint64_t finishTime;
};

ostream & operator << ( ostream & os, Job j )
{
    os << "Job( "
       << j.threadId << ", "
       << j.jobIndex << ", "
       << j.startTime << ", "
       << j.finishTime << " )";

    return os;
}

namespace std
{
template<>
struct less< Job >
{
    using value_type = bool;
    using first_argument_type = Job;
    using second_argument_type = Job;

    bool operator()( const Job & lhs, const Job & rhs )
    {
        if( lhs.finishTime > rhs.finishTime )
            return true;

        if( lhs.finishTime == rhs.finishTime )
            return lhs.threadId > rhs.threadId;

        if( lhs.finishTime < rhs.finishTime )
            return false;

        return false;
    }
};
}

int main( int argc, char ** argv )
{
    StdHeap< Job > h;

    uint64_t numThreads;
    uint64_t numJobs;
    cin >> numThreads;
    cin >> numJobs;

    vector< int64_t > jobsDuration;
    jobsDuration.reserve( numJobs );

    copy( istream_iterator< uint64_t >( cin ),
          istream_iterator< uint64_t >(),
          back_inserter( jobsDuration ) );

    // Initial per-thread job dispatching
    for( uint64_t jobIndex = 0; jobIndex < numThreads && jobIndex < numJobs; ++ jobIndex )
    {
        Job newJob( jobIndex,                // thread ID
                    jobIndex,                // job index
                    0,                       // start time
                    jobsDuration[ jobIndex ] // finish time
            );

        h.insert( newJob );
    }

    // Store result in order of jobs in input file
    vector< Job > results;
    results.resize( numJobs );

    // Process the rest of job list
    for( uint64_t jobIndex = numThreads ; jobIndex < numJobs; ++ jobIndex )
    {
        Job finishedJob = h.pop();
        results[ finishedJob.jobIndex ] = finishedJob;

        Job newJob( finishedJob.threadId,                             // thread ID
                    jobIndex,                                         // job index
                    finishedJob.finishTime,                           // start time
                    jobsDuration[ jobIndex ] + finishedJob.finishTime // finish time
            );

        h.insert( newJob );
    }

    // Pop remaining jobsDuration from heap
    while( h.get().size() )
    {
        Job result = h.pop();
        results[ result.jobIndex ] = result;
    }

    for( const auto & j : results )
    {
        cout << j.threadId << " " << j.startTime << endl;
    }

    return 0;
}
