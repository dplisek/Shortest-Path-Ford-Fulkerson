//
//  main.cpp
//  FordFulkerson
//
//  Created by Dominik Plíšek on 6/25/13.
//  Copyright (c) 2013 Dominik Plíšek. All rights reserved.
//

#include <iostream>
#include <climits>
#include <vector>
#ifndef __PROGTEST__
#include "CGraph.h"
#endif

#define STATE_FRESH 0
#define STATE_OPEN 1
#define STATE_CLOSED 2

#define TYPE_NORMAL 0
#define TYPE_START 1
#define TYPE_END 2

using namespace std;

void init(CGraph& g) {
    for (int i = 1; i <= g.getEdgeCounter(); i++) {
        t_edge e = g.getEdge(i);
        e.f = 0;
        g.setEdge(i, e);
    }
}

void initStatesPDT(CGraph& g, int* states, int* p, int* d, int* t) {
    for (int i = 1; i <= g.getNodeCounter(); i++) {
        if (g.getNode(i).type == TYPE_START) {
            states[i - 1] = STATE_OPEN;
            d[i - 1] = INT_MAX;
            p[i - 1] = +i;
        } else {
            states[i - 1] = STATE_FRESH;
        }
        if (g.getNode(i).type == TYPE_END) {
            *t = i;
        }
    }
}

int getAnyOpenNode(CGraph& g) {
    return 0;
}

vector<int>* getAdjEdges(CGraph& g, int nodeIndex) {
    vector<int>* adjEdges = new vector<int>();
    for (int i = 1; i <= g.getEdgeCounter(); ++i) {
        t_edge edge = g.getEdge(i);
		if (edge.sourceIndex != nodeIndex) continue;
        adjEdges->push_back(i);
	}
	return adjEdges;
}

vector<int>* getAdjEdgesMinus(CGraph& g, int nodeIndex) {
    vector<int>* adjEdges = new vector<int>();
    for (int i = 1; i <= g.getEdgeCounter(); ++i) {
        t_edge edge = g.getEdge(i);
		if (edge.destinationIndex != nodeIndex) continue;
        adjEdges->push_back(i);
	}
	return adjEdges;
}

bool findRoute(CGraph& g, int* p, int* d) {
    int* states = new int[g.getNodeCounter()];
    int t;
    initStatesPDT(g, states, p, d, &t);
    int u;
    while ((u = getAnyOpenNode(g)) != -1) {
        states[u - 1] = STATE_CLOSED;
        vector<int>* adjEdges = getAdjEdges(g, u);
        for (vector<int>::iterator it = adjEdges->begin(); it != adjEdges->end(); it++) {
            t_edge adjEdge = g.getEdge(*it);
            if (states[adjEdge.destinationIndex - 1] != STATE_FRESH || adjEdge.f >= adjEdge.q) {
                continue;
            }
            states[adjEdge.destinationIndex - 1] = STATE_OPEN;
            p[adjEdge.destinationIndex - 1] = +u;
            d[adjEdge.destinationIndex - 1] = min(d[u - 1], adjEdge.q - adjEdge.f);
        }
        delete adjEdges;
        vector<int>* adjEdgesMinus = getAdjEdgesMinus(g, u);
        for (vector<int>::iterator it = adjEdgesMinus->begin(); it != adjEdgesMinus->end(); it++) {
            t_edge adjEdge = g.getEdge(*it);
            if (states[adjEdge.destinationIndex - 1] != STATE_FRESH || adjEdge.f <= 0) {
                continue;
            }
            states[adjEdge.destinationIndex - 1] = STATE_OPEN;
            p[adjEdge.destinationIndex - 1] = -u;
            d[adjEdge.destinationIndex - 1] = min(d[u - 1], adjEdge.f);
        }
        delete adjEdgesMinus;
        if (u == t) break;
    }
    delete [] states;
    return u == t;
}

void getStartEnd(CGraph& g, int* s, int* t) {
    for (int i = 1; i <= g.getNodeCounter(); i++) {
        t_node node = g.getNode(i);
        if (node.type == TYPE_START) {
            *s = i;
        }
        if (node.type == TYPE_END) {
            *t = i;
        }
    }
}

int getEdgeIndex(CGraph& g, int a, int b) {
    for (int i = 1; i <= g.getEdgeCounter(); i++) {
        t_edge edge = g.getEdge(i);
        if (edge.sourceIndex == a && edge.destinationIndex == b) {
            return i;
        }
    }
    return -1;
}

void increaseFlow(CGraph& g, int* p, int* d) {
    int s, t, u, v, sgn;
    getStartEnd(g, &s, &t);
    int x = t;
    int delta = d[t - 1];
    do {
        v = x;
        sgn = p[v - 1];
        u = abs(sgn);
        if (sgn > 0) {
            int edgeIndex = getEdgeIndex(g, u, v);
            t_edge edge = g.getEdge(edgeIndex);
            edge.f += delta;
            g.setEdge(edgeIndex, edge);
        } else {
            int edgeIndex = getEdgeIndex(g, v, u);
            t_edge edge = g.getEdge(edgeIndex);
            edge.f -= delta;
            g.setEdge(edgeIndex, edge);
        }
        x = u;
    } while (v != s);
}

int FordFulkerson(CGraph& g) {
    init(g);
    int* p = new int[g.getNodeCounter()];
    int* d = new int[g.getNodeCounter()];
    while (findRoute(g, p, d)) {
        increaseFlow(g, p, d);
    }
    delete [] p;
    delete [] d;
    return 0;
}

#ifndef __PROGTEST__
int main(int argc, const char * argv[]) {
    CGraph* g = new CGraph(8, 15, true);
    
    t_node startNode;
    startNode.type = TYPE_START;
    g->setNode(1, startNode);
    for (int i = 2; i <= 7; i++) {
        t_node normalNode;
        normalNode.type = TYPE_NORMAL;
        g->setNode(i, normalNode);
    }
    t_node endNode;
    endNode.type = TYPE_END;
    g->setNode(8, endNode);
    
    g->setEdge(1, t_edge(1, 2, 4));
    g->setEdge(2, t_edge(1, 5, 3));
    g->setEdge(3, t_edge(2, 3, 5));
    g->setEdge(4, t_edge(2, 5, 2));
    g->setEdge(5, t_edge(3, 4, 6));
    g->setEdge(6, t_edge(4, 7, 2));
    g->setEdge(7, t_edge(4, 8, 4));
    g->setEdge(8, t_edge(5, 3, 2));
    g->setEdge(9, t_edge(5, 6, 4));
    g->setEdge(10, t_edge(6, 2, 2));
    g->setEdge(11, t_edge(6, 3, 2));
    g->setEdge(12, t_edge(6, 4, 2));
    g->setEdge(13, t_edge(6, 7, 1));
    g->setEdge(14, t_edge(7, 3, 2));
    g->setEdge(15, t_edge(7, 8, 4));
    
    int flow = FordFulkerson(*g);
    
    cout << "Resulting graph:" << endl;
    cout << g << endl;
    cout << "Flow: " << flow << endl;
    
    return 0;
}
#endif