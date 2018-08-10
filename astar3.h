#ifndef ASTAR_H
#define ASTAR_H

#include "gearball.h"
#include <queue>

struct node {
	ball b;
	node* parent;
};

struct nodeDistance {
	node* node;
	int dist;
};

class CompareDist {
public:
	bool operator()(nodeDistance& n1, nodeDistance& n2) {
		if(n1.dist > n2.dist) {
			return true;
		} else {
			return false;
		}
	}
};

ball aStar(ball src) {
	ball goal;
	priority_queue<nodeDistance,vector<nodeDistance>,CompareDist> pq;
	vector<node*> cameFrom;
	vector<int> cost_so_far;
	nodeDistanace first;
	node start;
	src.g = 0;
	src.f = src.estimate();
	start.ball = src;
	start.parent = NULL;
	first.node = &start;
	first.dist = src.f;
	pq.push(first);
	while(!pq.empty()) {
		nodeDistance temp = pq.top();
		pq.pop();
		node* curr = temp.node;
		if(curr.b == goal) {
			return curr.b;
		}
		for(int i = 0; i < 6; i++) {
			if(!curr->validMove(moves[i])) {
                //              cout << "invalid move" << endl;
                //              cin.get();
                                continue;
                        }
                        ball neighborB = curr;
                        neighborB.takeMove(i);
			int tempG = curr->g + 1;
			//
		}
	}
}

#endif
