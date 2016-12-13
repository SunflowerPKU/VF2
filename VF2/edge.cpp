//
//  edge.cpp
//  VF2
//
//  Created by TanXin on 2016/11/14.
//  Copyright © 2016年 TanXin. All rights reserved.
//

#include "edge.h"

EDGE::EDGE(int u1, int v1, int l, int n, int p)
{
    u=u1, v=v1, label=l, next=n, prev=p;
}
