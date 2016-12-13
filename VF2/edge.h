//
//  edge.h
//  VF2
//
//  Created by TanXin on 2016/11/14.
//  Copyright © 2016年 TanXin. All rights reserved.
//
#ifndef edge_h
#define edge_h


struct EDGE
{
    int u, v, label, next, prev;
    EDGE(int u1, int v1, int l, int n, int p);
    
};

#endif /* edge_h */
