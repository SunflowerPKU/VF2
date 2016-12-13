//
//  main.cpp
//  VF2
//
//  Created by TanXin on 2016/11/12.
//  Copyright © 2016年 TanXin. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <set>
#include <assert.h>
#include "readGraph.h"
using namespace std;

bool solve(const GRAPH &G1, const GRAPH &G2, State &state);
bool isomorphism(const GRAPH &G1, const GRAPH &G2);
bool subisomorphism(const GRAPH &G1, const GRAPH &G2);
vector<GRAPH> database, query;
int main()
{
    //string dir = "/Users/tanxin/课程/海量图数据/作业2-VF2/VF2/VF2";
    freopen("../VF2/graphDB/mygraphdb.data", "r", stdin);
    freopen("../VF2/graphDB/output.txt", "w", stdout);
    readGraph(database, 10000);
    
    string filename[] = {"../VF2/graphDB/Q24.my"
                         /*
                          "../VF2/graphDB/Q20.my",
                         "../VF2/graphDB/Q16.my",
                         "../VF2/graphDB/Q12.my",
                         "../VF2/graphDB/Q8.my",
                         "../VF2/graphDB/Q4.my"
                          */
                          };
    
    for (auto s: filename)
    {
        query.clear();
        freopen(s.c_str(), "r", stdin);
        readGraph(query, 500);
        time_t start_time = 0, end_time = 0;
        
        time(&start_time);
        for (auto G1: query)
        {
            for (auto G2: database)
            {
                isomorphism(G1, G2);
                //subisomorphism(G1, G2);
            }
        }
        time(&end_time);
        printf("cost %ld seconds\n", end_time - start_time);
      
    }
    
    return 0;
}

bool solve(const GRAPH &G1, const GRAPH &G2, State &state)
{
    
    if (state.M1.size() == state.vertex_count)
    {
        state.printMapping();
        return true;
    }
    vector<pair<int, int>> P = state.getCandiPairSet();
    for (vector<pair<int, int >>::iterator p = P.begin(); p!= P.end(); p++)
    {
        int n = p->first;
        int m = p->second;
        if (state.checkSemRules(G1, G2, n, m) && state.checkSynRules(G1, G2, n, m))
        {
            State new_state = state;
            new_state.addNewPair(n, m, G1.pred[n], G2.pred[m], G1.succ[n], G2.succ[m]);
            if (solve(G1, G2, new_state))
            {
                new_state.printMapping();
                return true;
            }
        }
    }
    return false;
}
//图同构
bool isomorphism(const GRAPH &G1, const GRAPH &G2) {
    if (G1.vertex_count != G2.vertex_count)
        return false;
    if (G1.edge_count != G2.edge_count)
        return false;
    State state(G1.vertex_count, 0);
    return solve(G1, G2, state);
}

//子图同构
bool subisomorphism(const GRAPH &G1, const GRAPH &G2)
{
    if (G1.vertex_count > G2.vertex_count)
        return false;
    if (G1.edge_count > G2.edge_count)
        return false;
    State state(G1.vertex_count, 1);
    return solve(G1, G2, state);
}

