//
//  CGraph.h
//  JarnikPrim
//
//  Created by Dominik Plíšek on 5/20/13.
//  Copyright (c) 2013 Dominik Plíšek. All rights reserved.
//

#ifndef __JarnikPrim__CGraph__
#define __JarnikPrim__CGraph__

#include "t_edge.h"
#include "t_node.h"
#include <vector>

class CGraph {
    bool oriented;
    int nodeCounter;
    int edgeCounter;
    t_node **nodes;
    t_edge **edges;
    void deleteNodes();
    void deleteEdges();
public:
    CGraph(int nodeCounter, int edgeCounter, bool oriented);
    ~CGraph();
    int getEdgeCounter() const;
    t_edge& getEdge(const int index) const;
    void setEdge(const int index, const t_edge& edge);
    int getNodeCounter() const;
    t_node& getNode(const int index) const;
    void setNode(const int index, const t_node& node);
    friend ostream& operator<<(ostream& os, const CGraph & graph);
};

#endif /* defined(__JarnikPrim__CGraph__) */
