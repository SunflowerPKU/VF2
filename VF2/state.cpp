//
//  state.cpp
//  VF2
//
//  Created by TanXin on 2016/11/14.
//  Copyright © 2016年 TanXin. All rights reserved.
//

#include "state.h"

State::State(int count, bool sub)
{
    vertex_count = count;
    subisomorphism = sub;
    M1.clear(), M2.clear();
    in_1.clear(), in_2.clear();
    out_1.clear(), out_2.clear();
    core_1.resize(count);
    fill(core_1.begin(), core_1.end(), -1);
    core_2.resize(count);
    fill(core_2.begin(), core_2.end(), -1);
}

//生成候选匹配对
//如果out_1和out_2都不为空，则取这两个集合中的所有点两两组合，生成候选匹配对集合；否则如果上面两个集合都为空，若in_1和in_2都不为空，则取这两个集合中的所有点两两组合，生成候选匹配对集合；
vector<pair<int, int>> State::getCandiPairSet()
{
    vector<pair<int, int>> Candi;
    if(out_1.size() && out_2.size())
    {
        int max_vid2 = -1;
        for(set<int>::iterator iter = out_2.begin(); iter!=out_2.end(); iter++)
            max_vid2 = max(*iter, max_vid2);
        for(set<int>::iterator iter = out_1.begin(); iter!=out_1.end(); iter++)
            Candi.push_back(make_pair(*iter, max_vid2));
        
    }
    else if(in_1.size() && in_2.size())
    {
        int max_vid2 = -1;
        for(set<int>::iterator iter = in_2.begin(); iter!=in_2.end(); iter++)
            max_vid2 = max(*iter, max_vid2);
        for(set<int>::iterator iter = in_1.begin(); iter!=in_1.end(); iter++)
            Candi.push_back(make_pair(*iter, max_vid2));
    }
    
    else
    {
        int max_vid2;
        //找到G2中未匹配的最大结点
        for(max_vid2 = vertex_count-1; max_vid2>=0 && core_2[max_vid2]!=-1; max_vid2--){}
        for(int i=0; i<vertex_count; i++)
        {
            if(core_1[i]==-1)
                Candi.push_back(make_pair(i, max_vid2));
        }
    }
    
    return Candi;
}

void State::addNewPair(int n, int m, const set<int> &pred1, const set<int> &pred2,
                const set<int> &succ1, const set<int> &succ2)
{
    M1.insert(n);
    M2.insert(m);
    core_1[n] = m;
    core_2[m] = n;
    for(set<int>::iterator iter = pred1.begin(); iter!=pred1.end(); iter++)
    {
        if(core_1[*iter] == -1)
            in_1.insert(*iter);
    }
    for(set<int>::iterator iter = pred2.begin(); iter!=pred2.end(); iter++)
    {
        if(core_2[*iter] == -1)
            in_2.insert(*iter);
    }
    for(set<int>::iterator iter = succ1.begin(); iter!=succ1.end(); iter++)
    {
        if(core_1[*iter] == -1)
            out_1.insert(*iter);
    }
    for(set<int>::iterator iter = succ2.begin(); iter!=succ2.end(); iter++)
    {
        if(core_2[*iter] == -1)
            out_2.insert(*iter);
    }
    if (in_1.find(n) != in_1.end()) in_1.erase(n);
    if (in_2.find(m) != in_2.end()) in_2.erase(m);
    if (out_1.find(n) != out_1.end()) out_1.erase(n);
    if (out_2.find(m) != out_2.end()) out_2.erase(m);
    
}


bool State::checkPredRule(const GRAPH &G1, const GRAPH &G2, int n, int m )
{
    for(int eid1 = G1.head_edge[n]; eid1!= -1; eid1 = G1.edge[eid1].next)
    {
        int vid = G1.edge[eid1].v;
        int map_vid = core_1[vid];
        if(map_vid==-1) continue;
        int label = G1.edge[eid1].label;
        
        bool flag = 0;
        for (int eid2 = G2.head_edge[m]; eid2 != -1; eid2 = G2.edge[eid2].next)
        {
            if (G2.edge[eid2].v == map_vid && G2.edge[eid2].label == label)
            {
                flag = 1;
                break;
            }
        }
        if (!flag) return false;
    }
    set<int> new_pred;
    set_intersection(M2.begin(), M2.end(), G2.pred[m].begin(), G2.pred[m].end(),
                     inserter(new_pred, new_pred.begin()));
    for (set<int>::iterator v2 = new_pred.begin(); v2 != new_pred.end(); v2++)
    {
        int v1 = core_2[*v2];
        assert(v1 != -1);
        if (G1.pred[n].find(v1) == G1.pred[n].end()) return false;
    }
    return true;
}
bool State::checkSuccRule(const GRAPH &G1, const GRAPH &G2, int n, int m)
{
    for (int eid = G1.rev_head_edge[n]; eid != -1; eid = G1.edge[eid].prev)
    {
        int vid = G1.edge[eid].u;
        int map_vid = core_1[vid];
        if (map_vid == -1) continue;
        int label = G1.edge[eid].label;
        
        bool flag = 0;
        for (int eid2 = G2.rev_head_edge[m]; eid2 != -1; eid2 = G2.edge[eid2].prev) {
            if (G2.edge[eid2].u == map_vid && G2.edge[eid2].label == label) {
                flag = 1;
                break;
            }
        }
        if (!flag) return false;
    }
    set<int> new_succ;
    set_intersection(M2.begin(), M2.end(), G2.succ[m].begin(), G2.succ[m].end(),
                     inserter(new_succ, new_succ.begin()));
    for (auto v2: new_succ) {
        int v1 = core_2[v2];
        assert(v1 != -1);
        if (G1.succ[n].find(v1) == G1.succ[n].end()) return false;
    }
    return true;
}

int State::set_intersection_size(const set<int> &a, const set<int> &b)
{
    return count_if(a.begin(), a.end(), [&](int k){return b.find(k) != b.end();});
}

bool State::checkInRule(const GRAPH &G1, const GRAPH &G2, int n, int m)
{
    int card_succ_1 = set_intersection_size(in_1, G1.succ[n]);
    int card_succ_2 = set_intersection_size(in_2, G2.succ[m]);
    if (!subisomorphism && card_succ_1 != card_succ_2)
        return false;
    if (subisomorphism && card_succ_1 > card_succ_2)
        return false;
    int card_pred_1 = set_intersection_size(in_1, G1.pred[n]);
    int card_pred_2 = set_intersection_size(in_2, G2.pred[m]);
    if (!subisomorphism && card_pred_1 != card_pred_2)
        return false;
    if (subisomorphism && card_pred_1 > card_pred_2)
        return false;
    
    return true;
}

bool State::checkOutRule(const GRAPH &G1, const GRAPH &G2, int n, int m)
{
    int card_succ_1 = set_intersection_size(out_1, G1.succ[n]);
    int card_succ_2 = set_intersection_size(out_2, G2.succ[m]);
    if (!subisomorphism && card_succ_1 != card_succ_2)
        return false;
    if (subisomorphism && card_succ_1 > card_succ_2)
        return false;
    int card_pred_1 = set_intersection_size(out_1, G1.pred[n]);
    int card_pred_2 = set_intersection_size(out_2, G2.pred[m]);
    if (!subisomorphism && card_pred_1 != card_pred_2)
        return false;
    if (subisomorphism && card_pred_1 > card_pred_2)
        return false;
    
    return true;
}

set<int> State::genComplementary(int count, const vector<int> &core, const set<int> &in, const set<int> &out)
{
    set<int> res;
    for (int vid = 0; vid < count; vid++)
    {
        if (core[vid] == -1 && in.find(vid) == in.end() && out.find(vid) == out.end())
        {
            res.insert(vid);
        }
    }
    return res;
}

bool State::checkNewRule(const GRAPH &G1, const GRAPH &G2, int n, int m) {
    set<int> N1 = genComplementary(G1.vertex_count, core_1, in_1, out_1);
    set<int> N2 = genComplementary(G2.vertex_count, core_2, in_2, out_2);
    int card_pred_1 = set_intersection_size(G1.pred[n], N1);
    int card_pred_2 = set_intersection_size(G2.pred[m], N2);
    if (!subisomorphism && card_pred_1 != card_pred_2)
        return false;
    if (subisomorphism && card_pred_1 > card_pred_2)
        return false;
    int card_succ_1 = set_intersection_size(G1.succ[n], N1);
    int card_succ_2 = set_intersection_size(G2.succ[m], N2);
    if (!subisomorphism && card_succ_1 != card_succ_2)
        return false;
    if (subisomorphism && card_succ_1 > card_succ_2)
        return false;
    
    return true;
}

bool State::checkSynRules(const GRAPH &G1, const GRAPH &G2, int n, int m)
{
    return checkPredRule(G1, G2, n, m) && checkSuccRule(G1, G2, n, m) &&
    checkInRule(G1, G2, n, m) && checkOutRule(G1, G2, n, m) &&
    checkNewRule(G1, G2, n, m);
}

bool State::checkSemRules(const GRAPH &G1, const GRAPH &G2, int n, int m)
{
    if (G1.vertex[n] != G2.vertex[m])
        return false;
    
    return true;
}
void State::printMapping()
{
    printf("%s mapping relationship found:\n", subisomorphism ? "Subgraph isomorphism": "Isomorphism");
    for (int i = 0; i < vertex_count; i++)
    {
        printf("%d %d\n", i, core_1[i]);
    }
}
