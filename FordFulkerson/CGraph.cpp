//
//  CGraph.cpp
//  JarnikPrim
//
//  Created by Dominik Plíšek on 5/20/13.
//  Copyright (c) 2013 Dominik Plíšek. All rights reserved.
//

#include "CGraph.h"
#include <iostream>

using namespace std;

CGraph::CGraph(int nodeCounter, int edgeCounter, bool oriented) : nodeCounter(nodeCounter), edgeCounter(edgeCounter), oriented(oriented) {
    nodes = new t_node*[nodeCounter];
    edges = new t_edge*[edgeCounter];
}

void CGraph::deleteNodes() {
    for (int i = 0; i < nodeCounter; i++) {
        delete nodes[i];
    }
    delete [] nodes;
}

void CGraph::deleteEdges() {
    for (int i = 0; i < edgeCounter; i++) {
        delete edges[i];
    }
    delete [] edges;
}

CGraph::~CGraph() {
    deleteNodes();
    deleteEdges();
}

ostream& operator<<(ostream& os, const CGraph & graph) {
	os << "Graph: " << endl;
    for (int i = 1; i <= graph.getNodeCounter(); i++) {
        os << graph.getNode(i) << endl;
    }
    for (int i = 1; i <= graph.getEdgeCounter(); i++) {
        os << graph.getEdge(i) << endl;
    }
	return os;
}

int CGraph::getEdgeCounter() const {
    return edgeCounter;
}

t_edge& CGraph::getEdge(const int index) const {
	return *(edges[index - 1]);
}

void CGraph::setEdge(const int index, const t_edge& edge) {
	edges[index - 1] = new t_edge(edge);
}

int CGraph::getNodeCounter() const {
	return nodeCounter;
}

t_node& CGraph::getNode(const int index) const {
	return *(nodes[index - 1]);
}

void CGraph::setNode(const int index, const t_node& node) {
    nodes[index - 1] = new t_node(node);
}
