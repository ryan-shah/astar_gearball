#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include "gearball.h"
#include <vector>
#include <map>
#include <queue>
#include <set>

using namespace std;

bool contains(vector<ball> bs, ball b) {
	for(int i = 0; i < bs.size(); i++) {
		if(bs[i] == b) {
			return true;
		}
	}
	return false;
}

ball findMin(map<ball, int> x) {
	int minVal = 999;
	ball minBall;
	for(map<ball,int>::iterator it = x.begin(); it != x.end(); ++it) {
		if(it->second < minVal) {
			minVal = it->second;
			minBall = it->first;
		}
	}
	return minBall;
}

map<ball, int>::iterator findBall(map<ball, int> &x, ball b) {
	for(map<ball, int>::iterator it = x.begin(); it!= x.end(); ++it) {
		if(it->first == b) {
			return it;
		}
	}
	return x.end();
}

ball* find(vector<ball> &bs, ball b) {
	for(int i = 0; i < bs.size(); i++) {
		if(bs[i] == b) {
			return &bs[i];
		}
	}
	return NULL;
}

class Compare {
public:
	bool operator() (ball* x, ball* y) {
		if(x->f > y->f) {
			return true;
		} else {
			return false;
		}
	}
};

struct node {
	node* parent;
	int f;
	int g;
	ball b;
};

ball aStar(ball src) {
	//clear list of previous moves for fresh set
	src.prevMove.clear();
	//initiate solved ball for compare
	ball solved;
	//list of visited balls
	vector<ball> closedList;
	//balls and the length to reach it from start
	src.g = 0;
	src.f = src.estimate();
	//set of balls to be checked
	vector<ball> openList;
	openList.push_back(src);
	//balls and the length to go from start to end including it
	priority_queue<ball*, vector<ball*>, Compare> fScore;
	fScore.push(&openList[openList.size()-1]);

	string moves[6] = {"F", "R", "U", "F'", "R'", "U'"};
	while(!openList.empty()) {
		//ball curr = openList.top();
		ball* currIt = fScore.top();
		ball curr = *currIt;
		if(curr == solved) {
			cout << "SOLVED" << endl;
			for(int i = 0; i < curr.prevMove.size(); i++) {
				cout << curr.prevMove[i] << " ";
			}
			curr.print();
			cin.get();
			return curr;
		}
		fScore.pop();
		for(vector<ball>::iterator it = openList.begin(); it != openList.end(); ++it) {
			if(*it == curr) {
				openList.erase(it);
				break;
			}
		}
		closedList.push_back(curr);

		for(int i = 0; i < 6; i++) {
			if(!curr.validMove(moves[i])) {
				cout << "invalid move" << endl;
		//		cin.get();
				continue;
			}
			ball neighborB = curr;
			neighborB.takeMove(i);
			cout << "testing: ";
			for(int i = 0; i < neighborB.prevMove.size(); i++) {
				cout << neighborB.prevMove[i] << " ";
			}
			cin.get();
			cout << endl;
			if(contains(closedList, neighborB)) {
				cout << "exists in closedList" << endl;
		//		cin.get();
				continue;
			}
			ball* neighp = find(openList, neighborB);
			if(neighp == NULL) {
				cout << "inserting into open set" << endl;
				openList.push_back(neighborB);
				neighp = &openList[openList.size() -1];
				fScore.push(neighp);
			}
			int tempG = curr.g + 1;
			if(neighborB.g != -1) {
				if(tempG >= neighp->g) {
					cout << neighp->g << endl;
					cout << "worse solution" << endl;
					continue;
				}
			}
			neighp->g = tempG;
			neighp->f = tempG + neighp->estimate();
			fScore.push(neighp);
			cout << "made it to end" << endl;
		//	cin.get();
		}

	}
	return src;
}

#endif
