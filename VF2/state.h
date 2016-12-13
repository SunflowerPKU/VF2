//
//  state.h
//  VF2
//
//  Created by TanXin on 2016/11/14.
//  Copyright © 2016年 TanXin. All rights reserved.
//
#ifndef state_h
#define state_h
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <assert.h>
#include "graph.h"
using namespace std;

struct State
{
    int vertex_count;
    bool subisomorphism;
    //M1:在G1中与G2匹配的部分; M2:在G2中与G1匹配的部分
    set<int> M1, M2;
    //in_1:与M1中的点直接相连的点； out_1:M1中的点与其直接相连
    set<int> in_1, in_2, out_1, out_2;
    //core_1:G1中的每个点在G2中匹配的点,若未匹配，则为-1；
    vector<int> core_1, core_2;
    
    State(int count, bool sub);
    //生成候选匹配对
    vector<pair<int, int>> getCandiPairSet();
    void addNewPair(int n, int m, const set<int> &pred1, const set<int> &pred2,
                    const set<int> &succ1, const set<int> &succ2);
    
    bool checkPredRule(const GRAPH &G1, const GRAPH &G2, int n, int m);
    bool checkSuccRule(const GRAPH &G1, const GRAPH &G2, int n, int m);
    int set_intersection_size(const set<int> &a, const set<int> &b);
    bool checkInRule(const GRAPH &G1, const GRAPH &G2, int n, int m);
    bool checkOutRule(const GRAPH &G1, const GRAPH &G2, int n, int m);
    set<int> genComplementary(int count, const vector<int> &core, const set<int> &in, const set<int> &out);
    bool checkNewRule(const GRAPH &G1, const GRAPH &G2, int n, int m);
    bool checkSynRules(const GRAPH &G1, const GRAPH &G2, int n, int m);
    bool checkSemRules(const GRAPH &G1, const GRAPH &G2, int n, int m);
    void printMapping();
};

#endif
