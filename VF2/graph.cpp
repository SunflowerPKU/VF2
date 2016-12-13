//
//  graph.cpp
//  VF2
//
//  Created by TanXin on 2016/11/14.
//  Copyright © 2016年 TanXin. All rights reserved.
//

#include "graph.h"
#include <stdio.h>

void GRAPH::addVertex(int label)
{
    vertex.push_back(label);
    head_edge.push_back(-1);
    rev_head_edge.push_back(-1);
    pred.push_back({});
    succ.push_back({});
    vertex_count++;
}

void GRAPH::addEdge(int u, int v, int label)
{
    edge.push_back(EDGE(u, v, label, head_edge[u], rev_head_edge[v]));
    head_edge[u] = edge_count;
    rev_head_edge[v] = edge_count++;
    pred[v].insert(u);
    succ[u].insert(v);
}

void GRAPH::initial()
{
    vertex_count = edge_count = 0;
    vertex.clear();
    edge.clear();
    head_edge.clear();
    rev_head_edge.clear();
    pred.clear();
    succ.clear();
}

void GRAPH::printGraphInfo()
{
    printf("vertex count: %d\n", vertex_count);
    printf("vertex label:\n");
    for (vector<int>::iterator iter = vertex.begin(); iter!=vertex.end(); iter++)
        printf("%d ", *iter);
    puts("");
    printf("vertex predecessors:\n");
    int cnt = 0;
    for (vector<set<int>>::iterator iter = pred.begin(); iter!=pred.end(); iter++)
    {
        printf("No.%d:", cnt++);
        for (set<int>::iterator v = iter->begin(); v!=iter->end(); v++) {
            printf(" %d", *v);
        }
        puts("");
    }
    printf("edge count: %d\n", edge_count);
    puts("");
}
