//
//  t_node.h
//  JarnikPrim
//
//  Created by Dominik Plíšek on 5/20/13.
//  Copyright (c) 2013 Dominik Plíšek. All rights reserved.
//

#ifndef __JarnikPrim__t_node__
#define __JarnikPrim__t_node__

#include <iostream>

using namespace std;

struct t_node {
    int type;
    friend ostream& operator<<(ostream& os, const t_node & node);
};

#endif /* defined(__JarnikPrim__t_node__) */
