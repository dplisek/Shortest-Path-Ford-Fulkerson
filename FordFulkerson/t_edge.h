//
//  t_edge.h
//  JarnikPrim
//
//  Created by Dominik Plíšek on 5/20/13.
//  Copyright (c) 2013 Dominik Plíšek. All rights reserved.
//

#ifndef __JarnikPrim__t_edge__
#define __JarnikPrim__t_edge__

#include <iostream>

using namespace std;

struct t_edge {
    int sourceIndex;
    int destinationIndex;
    int q;
    int f;
    t_edge(int sourceIndex, int destinationIndex, int q);
	friend ostream& operator<<(ostream& os, const t_edge & edge);
};

#endif /* defined(__JarnikPrim__t_edge__) */
