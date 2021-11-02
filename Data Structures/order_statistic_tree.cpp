#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

//comparator function is defined as functors
struct cmp {
    bool operator() (const pair<int,int>&a, const pair<int,int>&b) const {
        return a.first == b.first ? a.second < b.second : a.first > b.first;
    }
};

typedef 
tree<
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update> 
pbds;