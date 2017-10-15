#include <sys/resource.h>

#include <limits>
#include <iostream>
#include <vector>

using namespace std;

//{ Copy-pasted from starter file
class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};
//}

void increaseStack()
{
    //{ Copy-pasted from starter file
    // Allow larger stack space
    const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                std::cerr << "setrlimit returned result = " << result << std::endl;
            }
        }
    }
    //}
}

Node * readTree( std::vector<Node> & nodes )
{
    //{ Copy-pasted from starter file
    std::ios_base::sync_with_stdio(0);
    int n;
    std::cin >> n;

    nodes.resize(n);
    int rootPos = 0;
    for (int child_index = 0; child_index < n; child_index++) {
        int parent_index;
        std::cin >> parent_index;
        if (parent_index >= 0)
            nodes[child_index].setParent(&nodes[parent_index]);
        else
            rootPos = child_index;
        nodes[child_index].key = child_index;
    }
    // }

    return & nodes[ rootPos ];
}

size_t height( const Node * root )
{
    if( ! root )
        return 0;

    if( root->children.empty() )
        return 1;

    size_t result = numeric_limits< size_t >::min();
    for( const auto child : root->children )
    {
        cerr << "Child ID: " << root->key << endl;
        result = max( result, height( child ) );
    }
    return result + 1;
}

int main()
{
    increaseStack();
    std::vector<Node> nodes;
    Node * root = readTree( nodes );
    cout << height( root ) << endl;
    return 0;
}
