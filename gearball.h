#ifndef GEARBALL_H
#define GEARBALL_H

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

string oppS(string m);


/*

(rotating left)
1	1	2	2	2	1	1
- ->	\ ->	/ ->	- ->	\ ->	/ ->	-
2	2	1	1	1	2	2

0	1	2	3	4	5	6

1|2	1/2	2\1	2|1	2/1	1\2	1|2

correct position on mod6

color1 = top/left
color2 = bot/right

*/

class Gear {
    public:
	char color1;
	char color2;
	int rotations = 0;

	void rotateL() {
		rotations--;
	}

	void rotateR() {
		rotations++;
	}
	void print() const;

	Gear() {}

	Gear(char c1, char c2) { color1 = c1; color2 = c2; }

	bool operator==(const Gear& other) const {
		if(color1 != other.color1) {
			return false;
		}
		if(color2 != other.color2) {
			return false;
		}
		int curr = rotations % 6;
		if(curr < 0) {
			curr += 6;
		}
		int ocurr = other.rotations % 6;
		if(ocurr < 0) {
			ocurr += 6;
		}
		if(curr != ocurr) {
			return false;
		}
		return true;
	}
	bool operator!=(const Gear& other) const {
		return !(*this == other);
	}
};

/*
		G

	1	2	3
  G	4	5	6    G
	7	8	9

		G

258	012	630
147  <-	345 ->	741
036	678	852

*/
class side {
public:
	//{0, 1, 2, 3, 4, 5, 6, 7, 8}
	char color;
	char face[9];
	Gear* leftG;
	Gear* rightG;
	Gear* topG;
	Gear* bottomG;
/*
	side* leftS;
	side* rightS;
	side* topS;
	side* bottomS;
	side* rearS;
*/
	void rotateL();
	void rotateR();

	side() {};
	side(char c) {
		for(int i = 0; i < 9; i++) {
			face[i] = c;
		}
		color = c;
	}
	bool compFaces(const char x[9], const char y[9]) const {
		for(int i = 0; i < 9; i++) {
			if(x[i] != y[i]) {
				return false;
			}
		}
		return true;
	}
	void printRow(int row) const {
		int start = 3 * (row-1);
		int end = 3 * row;
		for (int i = start; i < end; i++) {
			cout << face[i];
		}
	}
	bool operator==(const side& other) const {
		if(!compFaces(face, other.face)) {
			return false;
		}
		if((*topG != *other.topG) || (*leftG != *other.leftG) || (*rightG != *other.rightG) || (*bottomG != *other.bottomG)) {
			return false;
		}
		return true;
	}
	bool operator!=(const side& other) const {
		return !(*this == other);
	}
};

/*
			P|G

			GGG
		Y|G	GGG	G|O
			GGG

			G|R

	YYY		RRR		OOO
P|Y	YYY	Y|R	RRR	R|O	OOO	O|P
	YYY		RRR		OOO

			R|B

			BBB
		Y|B	BBB	B|O
			BBB

			B|P

			PPP
	P|Y		PPP		O|P
			PPP

			P|G
*/

class ball {
public:
	//values for use in astar
	int g = -1;
	int h;
	int f = -1;
	//previous move made on the ball
	// [F, U, R, F', U', R']
	vector<string> prevMove;

	//gears
	Gear pg = Gear('P', 'G');
	Gear yg = Gear('Y', 'G');
	Gear go = Gear('G', 'O');
	Gear gr = Gear('G', 'R');
	Gear yr = Gear('Y', 'R');
	Gear ro = Gear('R', 'O');
	Gear rb = Gear('R', 'B');
	Gear yb = Gear('Y', 'B');
	Gear bo = Gear('B', 'O');
	Gear bp = Gear('B', 'P');
	Gear py = Gear('P', 'Y');
	Gear po = Gear('P', 'O');

	//sides
	side front = side('R');
	side top = side('G');
	side left = side('Y');
	side right = side('O');
	side bottom = side('B');
	side rear = side('P');

	//functions
	void rotateFrontR();
	void rotateFrontL();
	void rotateRightR();
	void rotateRightL();
	void rotateTopR();
	void rotateTopL();
	void print() const;
	void randMoves(int n);
	bool validMove(string m);
	void takeMove(int n);
	int estimate() const;
	bool operator<(const ball& other) const {
		if(*this == other) {
			return false;
		}
		return (this->estimate() < other.estimate());
	}
	bool operator==(const ball& other) const {
		side s1s[6] = {front, left, right, top, bottom, rear};
		side s2s[6] = {other.front, other.left, other.right, other.top, other.bottom, other.rear};
		for(int i = 0; i < 6; i++) {
			if(s1s[i] != s2s[i]) {
				return false;
			}
		}
		return true;
	}
	bool operator!=(const ball& other) const {
		return !(*this == other);
	}
	ball(const ball& other) {
		prevMove = other.prevMove;
		front = other.front;
		left = other.left;
		right = other.right;
		top = other.top;
		bottom = other.bottom;
		rear = other.rear;
		Gear* Gs[12] = {
		&bp, &py, &po, &yb, &bo, &rb, &ro, &yr, &gr, &go, &yg, &pg
		};
		const Gear* G2s[12] = {
		&other.bp, &other.py, &other.po, &other.yb, &other.bo, &other.rb, &other.ro, &other.yr, &other.gr, &other.go, &other.yg, &other.pg
		};
		for(int i = 0; i < 12; i++) {
			*Gs[i] = *G2s[i];
		}
		for(int i = 0; i < 12; i++) {
		//front
			if(front.topG == G2s[i]) {
				front.topG = Gs[i];
			}
			if(front.leftG == G2s[i]) {
				front.leftG = Gs[i];
			}
			if(front.rightG == G2s[i]) {
				front.rightG = Gs[i];
			}
			if(front.bottomG == G2s[i]) {
				front.bottomG = Gs[i];
			}
		//top
			if(top.topG == G2s[i]) {
                                top.topG = Gs[i];
                        }
                        if(top.leftG == G2s[i]) {
                                top.leftG = Gs[i];
                        }
                        if(top.rightG == G2s[i]) {
                                top.rightG = Gs[i];
                        }
                        if(top.bottomG == G2s[i]) {
                                top.bottomG = Gs[i];
                        }
		//left
			if(left.topG == G2s[i]) {
                                left.topG = Gs[i];
                        }
                        if(left.leftG == G2s[i]) {
                                left.leftG = Gs[i];
                        }
                        if(left.rightG == G2s[i]) {
                                left.rightG = Gs[i];
                        }
                        if(left.bottomG == G2s[i]) {
                                left.bottomG = Gs[i];
                        }
		//right
                        if(right.topG == G2s[i]) {
                                right.topG = Gs[i];
                        }
                        if(right.leftG == G2s[i]) {
                                right.leftG = Gs[i];
                        }
                        if(right.rightG == G2s[i]) {
                                right.rightG = Gs[i];
                        }
                        if(right.bottomG == G2s[i]) {
                                right.bottomG = Gs[i];
                        }
		//bottom
                        if(bottom.topG == G2s[i]) {
                                bottom.topG = Gs[i];
                        }
                        if(bottom.leftG == G2s[i]) {
                                bottom.leftG = Gs[i];
                        }
                        if(bottom.rightG == G2s[i]) {
                                bottom.rightG = Gs[i];
                        }
                        if(bottom.bottomG == G2s[i]) {
                                bottom.bottomG = Gs[i];
                        }
		//rear
                        if(rear.topG == G2s[i]) {
                                rear.topG = Gs[i];
                        }
                        if(rear.leftG == G2s[i]) {
                                rear.leftG = Gs[i];
                        }
                        if(rear.rightG == G2s[i]) {
                                rear.rightG = Gs[i];
                        }
                        if(rear.bottomG == G2s[i]) {
                                rear.bottomG = Gs[i];
                        }
		}
	}
	ball& operator=(const ball& other) {
                if(&other == this) {
                        return *this;
                }
		prevMove = other.prevMove;
                front = other.front;
                left = other.left;
                right = other.right;
                top = other.top;
                bottom = other.bottom;
                rear = other.rear;
                Gear* Gs[12] = {
                &bp, &py, &po, &yb, &bo, &rb, &ro, &yr, &gr, &go, &yg, &pg
                };
                const Gear* G2s[12] = {
		&other.bp, &other.py, &other.po, &other.yb, &other.bo, &other.rb, &other.ro, &other.yr, &other.gr, &other.go, &other.yg, &other.pg
                };
                for(int i = 0; i < 12; i++) {
                        *Gs[i] = *G2s[i];
                }
                for(int i = 0; i < 12; i++) {
                //front
                        if(front.topG == G2s[i]) {
                                front.topG = Gs[i];
                        }
                        if(front.leftG == G2s[i]) {
                                front.leftG = Gs[i];
                        }
                        if(front.rightG == G2s[i]) {
                                front.rightG = Gs[i];
                        }
                        if(front.bottomG == G2s[i]) {
                                front.bottomG = Gs[i];
                        }
                //top
                        if(top.topG == G2s[i]) {
                                top.topG = Gs[i];
                        }
                        if(top.leftG == G2s[i]) {
                                top.leftG = Gs[i];
                        }
                        if(top.rightG == G2s[i]) {
                                top.rightG = Gs[i];
                        }
                        if(top.bottomG == G2s[i]) {
                                top.bottomG = Gs[i];
                        }
                //left
                        if(left.topG == G2s[i]) {
                                left.topG = Gs[i];
                        }
                        if(left.leftG == G2s[i]) {
                                left.leftG = Gs[i];
                        }
                        if(left.rightG == G2s[i]) {
                                left.rightG = Gs[i];
                        }
                        if(left.bottomG == G2s[i]) {
                                left.bottomG = Gs[i];
                        }
                //right
                        if(right.topG == G2s[i]) {
                                right.topG = Gs[i];
                        }
                        if(right.leftG == G2s[i]) {
                                right.leftG = Gs[i];
                        }
                        if(right.rightG == G2s[i]) {
                                right.rightG = Gs[i];
                        }
                        if(right.bottomG == G2s[i]) {
                                right.bottomG = Gs[i];
                        }
                //bottom
                        if(bottom.topG == G2s[i]) {
                                bottom.topG = Gs[i];
                        }
                        if(bottom.leftG == G2s[i]) {
                                bottom.leftG = Gs[i];
                        }
                        if(bottom.rightG == G2s[i]) {
                                bottom.rightG = Gs[i];
                        }
                        if(bottom.bottomG == G2s[i]) {
                                bottom.bottomG = Gs[i];
                        }
                //rear
                        if(rear.topG == G2s[i]) {
                                rear.topG = Gs[i];
                        }
                        if(rear.leftG == G2s[i]) {
                                rear.leftG = Gs[i];
                        }
                        if(rear.rightG == G2s[i]) {
                                rear.rightG = Gs[i];
                        }
                        if(rear.bottomG == G2s[i]) {
                                rear.bottomG = Gs[i];
                        }
                }
		return *this;
        }

	ball() {
		//assigning gears and sides
		//front
//		front.rearS = &rear;

//		front.topS = &top;
		front.topG = &gr;

//		front.leftS = &left;
		front.leftG = &yr;

//		front.rightS = &right;
		front.rightG = &ro;

//		front.bottomS = &bottom;
		front.bottomG = &rb;

		//top
//		top.rearS = &bottom;

//		top.topS = &rear;
		top.topG = &pg;

//		top.leftS = &left;
		top.leftG = &yg;

//		top.rightS = &right;
		top.rightG = &go;

//		top.bottomS = &front;
		top.bottomG = &gr;

		//left
//		left.rearS = &right;

//		left.topS = &top;
		left.topG = &yg;

//		left.leftS = &rear;
		left.leftG = &py;

//		left.rightS = &front;
		left.rightG = &yr;

//		left.bottomS = &bottom;
		left.bottomG = &yb;

		//right
//		right.rearS = &left;
//		right.topS = &top;
		right.topG = &go;

//		right.leftS = &front;
		right.leftG = &ro;

//		right.rightS = &rear;
		right.rightG = &po;

//		right.bottomS = &bottom;
		right.bottomG = &bo;

		//bottom
//		bottom.rearS = &top;

//		bottom.topS = &front;
		bottom.topG = &rb;

//		bottom.leftS = &left;
		bottom.leftG = &yb;

//		bottom.rightS = &right;
		bottom.rightG = &bo;

//		bottom.bottomS = &rear;
		bottom.bottomG = &bp;

		//rear
//		rear.rearS = &front;

//		rear.topS = &top;
		rear.topG = &pg;

//		rear.leftS = &right;
		rear.leftG = &po;

//		rear.rightS = &left;
		rear.rightG = &py;

//		rear.bottomS = &bottom;
		rear.bottomG = &bp;
	}
};

#endif
