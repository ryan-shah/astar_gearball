#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <climits>

using namespace std;

//holds the number of nodes touched in last run of a*
int NODE_COUNT;

//given a vector<vall> and ball b, pops b from vector
//used to simulate the effect of a priority_queue, albeit much less efficent
void pop(vector<ball> &bs, ball b) {
	for(vector<ball>::iterator it = bs.begin(); it < bs.end(); ++it) {
		if(*it == b) {
			bs.erase(it);
			return;
		}
	}
}

//given a vector<pair<ball,int>> returns the int matching ball b
int getVal(vector<pair<ball,int>> v, ball b) {
	for(int i = 0; i < v.size(); i++) {
		if(v[i].first == b) {
			return v[i].second;
		}
	}
}

//returns the ball with the minimum value in v2 from v1
//used where v is openSet and v2 is list of fScores
ball findMin(vector<ball> v, vector<pair<ball,int>> v2) {
	int minV = INT_MAX;
	ball min;
	for(int i = 0; i < v.size(); i++) {
		int x = getVal(v2, v[i]);
		if(x < minV) {
			minV = x;
			min = v[i];
		}
	}
	return min;
}

//returns index of ballV in vector<ball> v
int findB(vector<ball> v, ball b) {
	for(int i = 0; i < v.size(); i++) {
		if(v[i] == b) {
			return i;
		}
	}
	return -1;
}

//same as findB but for vector<pair<ball,int>>
int find(vector<pair<ball,int>> v, ball b) {
	for(int i = 0; i < v.size(); i++) {
		if(v[i].first == b) {
			return i;
		}
	}
	return -1;
}

//prints out a vector of string
void printMoves(vector<string> x) {
	for(int i = 0; i < x.size(); i++) {
		cout << x[i] << " ";
	}
	cout << endl;
}

//the a* algorithm
ball aStar(ball src) {
	//comparison solved ball
	ball complete;
	//list of balls to be expanded
	vector<ball> openList;
	//list of already expanded balls
	vector<ball> closedList;
	//list of gScores for each ball
	vector<pair<ball,int>> gScore;
	//list of fScores for each ball
	vector<pair<ball,int>> fScore;
	//reset the moveList for src ball
	src.prevMove.clear();
	//add src ball to openList
	openList.push_back(src);
	//set gScore = 0 and fScore = heuristic()
	gScore.push_back(pair<ball,int>(src, 0));
	fScore.push_back(pair<ball,int>(src, src.estimate()));

	//while nodes to search
	while(!openList.empty()) {
		//get ball with minimum fScore
		ball curr = findMin(openList, fScore);
		//remove it from openList
		pop(openList, curr);
		//if its the solution, return and record number of nodes
		if(curr == complete) {
			NODE_COUNT = closedList.size() + openList.size();
			return curr;
		}
		//add node to closedList
		closedList.push_back(curr);
		//debugging. prints out what move set is being tested. cin.get() waits for input before continuing
		/*
		cout << "curr is :";
		printMoves(curr.prevMove);
		cin.get();
		*/
		//list of possible moves
		string moves[6] = {"F", "R", "U", "F'", "R'", "U'"};
		//for each possible moves
		for(int i = 0; i < 6; i++) {
			//make sure its not undoing previous move or the complete rotation of the ball (12 turns)
                        if(!curr.validMove(moves[i])) {
                                continue;
                        }
			//create neighbor and have it move into position
                        ball neighborB = curr;
                        neighborB.takeMove(i);
			//check if its the solution
			if(neighborB == complete) {
				NODE_COUNT = closedList.size() + openList.size();
				return neighborB;
			}
			//if its in the closed list, we've searched it already so we can skip it
			if(findB(closedList, neighborB) != -1) {
				continue;
			}
			//if its not already in open list, add it
			if(findB(openList, neighborB) == -1) {
				openList.push_back(neighborB);
			}
			//calculate temp gScore (1 more move than what current was)
			int tempG = getVal(gScore, curr) + 1;
			//find the gScore for this particular ball
			int gLoc = find(gScore, neighborB);
			//if it's -1, we haven't seen this ball before so add it
			if(gLoc == -1) {
				gScore.push_back(pair<ball,int>(neighborB, tempG));
				fScore.push_back(pair<ball,int>(neighborB, tempG + neighborB.estimate()));
			} else {
			//otherwise see if it's better than the old instance
				if(tempG >= gScore[gLoc].second) {
					continue;
				}
				//if it is, update the values
				gScore[gLoc].second = tempG;
				int fLoc = find(fScore, neighborB);
				fScore[fLoc].second = tempG + neighborB.estimate();
			}
		}
	}
}
