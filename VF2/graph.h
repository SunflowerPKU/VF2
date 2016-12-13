//
//  graph.h
//  VF2
//
//  Created by TanXin on 2016/11/14.
//  Copyright © 2016年 TanXin. All rights reserved.
//

#ifndef graph_h
#define graph_h

#include <vector>
#include <set>

#include "edge.h"

using namespace std;

struct GRAPH
{
    int edge_count, vertex_count;
    vector<int> vertex;
    vector<int> head_edge;
    vector<int> rev_head_edge;
    vector<EDGE> edge;
    vector<set<int>> pred;
    vector<set<int>> succ;
    
    void addVertex(int label);
    void addEdge(int u, int v, int label);
    void initial();
    void printGraphInfo();
};

#endif
