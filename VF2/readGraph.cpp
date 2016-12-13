//
//  readGraph.cpp
//  VF2
//
//  Created by TanXin on 2016/11/14.
//  Copyright © 2016年 TanXin. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <assert.h>
#include "readGraph.h"
using namespace std;

void readGraph(vector<GRAPH> &G, int total)
{
    GRAPH new_graph;
    new_graph.initial();
    char str[10000];
    while (gets(str))
    {
        if (strlen(str) == 0) continue;
        stringstream stream;
        if (str[0] == 't')
        {
            int gid;
            stream << str + 4;
            stream >> gid;
            total--;
            if (gid == 0) continue;
            G.push_back(new_graph);
            if (total == 0) break;
            new_graph.initial();
        } else if (str[0] == 'v')
        {
            int vid, vlabel;
            stream << str + 2;
            stream >> vid >> vlabel;
            new_graph.addVertex(vlabel);
        } else if (str[0] == 'e')
        {
            int uid, vid, elabel;
            stream << str + 2;
            stream >> uid >> vid >> elabel;
            new_graph.addEdge(uid, vid, elabel);
        }
    }
    printf("Total size: %lu\n", G.size()+1);
}
