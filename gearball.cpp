#include <iostream>
#include "gearball.h"
#include <cmath>
#include <vector>
#include <stdlib.h>

using namespace std;

void tab() {
	cout << "\t";
}

void nl() {
	cout << "\n";
}

void side::rotateL() {
	//rotate face
	char buff[9];
	buff[0] = face[2];
	buff[1] = face[5];
	buff[2] = face[8];
	buff[3]	= face[1];
	buff[4]	= face[4];
	buff[5] = face[7];
	buff[6] = face[0];
	buff[7] = face[3];
	buff[8] = face[6];
	for(int i = 0; i < 9; i++) {
		face[i] = buff[i];
	}

}

void side::rotateR() {
	//rotate face
	char buff[9];
	buff[0] = face[6];
	buff[1] = face[3];
	buff[2] = face[0];
	buff[3]	= face[7];
	buff[4]	= face[4];
	buff[5] = face[1];
	buff[6] = face[8];
	buff[7] = face[5];
	buff[8] = face[2];
	for(int i = 0; i < 9; i++) {
		face[i] = buff[i];
	}
}

void ball::rotateFrontR() {
	prevMove.push_back("F");
	front.rotateR();
	rear.rotateR();
	//rotate gears
	Gear* buffG = front.topG;
	Gear* buffG2;
	front.topG = front.leftG;
	buffG2 = front.rightG;
	front.rightG = buffG;
	buffG = front.bottomG;
	front.bottomG = buffG2;
	front.leftG = buffG;
	left.rightG = front.leftG;
	right.leftG = front.rightG;
	top.bottomG = front.topG;
	bottom.topG = front.bottomG;
	//rotate layers
	char layer[3];
	char buff[3];
	//rotate left and store top
	layer[0] = top.face[6];
	layer[1] = top.face[7];
	layer[2] = top.face[8];
	top.face[8] = left.face[2];
	top.face[7] = left.face[5];
	top.face[6] = left.face[8];
	//rotate top and store right
	buff[0] = right.face[6];
	buff[1] = right.face[3];
	buff[2] = right.face[0];
	right.face[0] = layer[0];
	right.face[3] = layer[1];
	right.face[6] = layer[2];
	layer[0] = buff[0];
	layer[1] = buff[1];
	layer[2] = buff[2];
	//rotate right and store bot
	buff[0] = bottom.face[0];
	buff[1] = bottom.face[1];
	buff[2] = bottom.face[2];
	bottom.face[0] = layer[0];
	bottom.face[1] = layer[1];
	bottom.face[2] = layer[2];
	//rotate bottom
	left.face[2] = buff[0];
	left.face[5] = buff[1];
	left.face[8] = buff[2];

	//rotate the rear
	//rotate gears
	buffG = rear.topG;
	rear.topG = rear.leftG;
	buffG2 = rear.rightG;
	rear.rightG = buffG;
	buffG = rear.bottomG;
	rear.bottomG = buffG2;
	rear.leftG = buffG;

	right.rightG = rear.leftG;
	left.leftG = rear.rightG;
	bottom.bottomG = rear.bottomG;
	top.topG = rear.topG;
	//rotate layers
	//rotate leftside (right) and store top
	layer[0] = top.face[0];
	layer[1] = top.face[1];
	layer[2] = top.face[2];
	top.face[0] = right.face[2];
	top.face[1] = right.face[5];
	top.face[2] = right.face[8];
	//rotate top and store rightside (left)
	buff[0] = left.face[0];
	buff[1] = left.face[3];
	buff[2] = left.face[6];
	left.face[0] = layer[2];
	left.face[3] = layer[1];
	left.face[6] = layer[0];
	layer[0] = buff[0];
	layer[1] = buff[1];
	layer[2] = buff[2];
	//rotate right and store bot
	buff[0] = bottom.face[6];
	buff[1] = bottom.face[7];
	buff[2] = bottom.face[8];
	bottom.face[8] = layer[2];
	bottom.face[7] = layer[1];
	bottom.face[6] = layer[0];
	//rotate bottom
	right.face[2] = buff[2];
	right.face[5] = buff[1];
	right.face[8] = buff[0];
	//rotate gears
	top.leftG->rotateL();
	top.rightG->rotateL();
	bottom.leftG->rotateL();
	bottom.rightG->rotateL();
}

void ball::rotateFrontL() {
	prevMove.push_back("F'");

	front.rotateL();
 	rear.rotateL();
	//rotate gears
	Gear* buffG = front.topG;
	Gear* buffG2;
	front.topG = front.rightG;
	buffG2 = front.leftG;
	front.leftG = buffG;
	buffG = front.bottomG;
	front.bottomG = buffG2;
	front.rightG = buffG;
	left.rightG = front.leftG;
	right.leftG = front.rightG;
	top.bottomG = front.topG;
	bottom.topG = front.bottomG;
	//rotate layers
	char buff[3];
	char layer[3];
	//rotate layers
	//rotate right and store top
	layer[0] = top.face[6];
	layer[1] = top.face[7];
	layer[2] = top.face[8];
	top.face[6] = right.face[0];
	top.face[7] = right.face[3];
	top.face[8] = right.face[6];
	//rotate top and store left
	buff[0] = left.face[2];
	buff[1] = left.face[5];
	buff[2] = left.face[8];
	left.face[2] = layer[2];
	left.face[5] = layer[1];
	left.face[8] = layer[0];
	layer[0] = buff[0];
	layer[1] = buff[1];
	layer[2] = buff[2];
	//rotate left and store bot
	buff[0] = bottom.face[0];
	buff[1] = bottom.face[1];
	buff[2] = bottom.face[2];
	bottom.face[0] = layer[0];
	bottom.face[1] = layer[1];
	bottom.face[2] = layer[2];
	//rotate bottom
	right.face[0] = buff[2];
	right.face[3] = buff[1];
	right.face[6] = buff[0];

	//rotate the rear
	//rotate gears
	buffG = rear.topG;
	rear.topG = rear.rightG;
	buffG2 = rear.leftG;
	rear.leftG = buffG;
	buffG = rear.bottomG;
	rear.bottomG = buffG2;
	rear.rightG = buffG;
	right.rightG = rear.leftG;
	left.leftG = rear.rightG;
	top.topG = rear.topG;
	bottom.bottomG = rear.bottomG;
	//layers
	//rotate right side (left) and store top
	layer[0] = top.face[0];
	layer[1] = top.face[1];
	layer[2] = top.face[2];
	top.face[0] = left.face[6];
	top.face[1] = left.face[3];
	top.face[2] = left.face[0];
	//rotate top and store left side (right)
	buff[0] = right.face[2];
	buff[1] = right.face[5];
	buff[2] = right.face[8];
	right.face[2] = layer[0];
	right.face[5] = layer[1];
	right.face[8] = layer[2];
	layer[0] = buff[0];
	layer[1] = buff[1];
	layer[2] = buff[2];
	//rotate left side (right) and store bot
	buff[0] = bottom.face[6];
	buff[1] = bottom.face[7];
	buff[2] = bottom.face[8];
	bottom.face[6] = layer[2];
	bottom.face[7] = layer[1];
	bottom.face[8] = layer[0];
	//rotate bottom
	left.face[0] = buff[0];
	left.face[3] = buff[1];
	left.face[6] = buff[2];

	//rotate gears
	top.leftG->rotateR();
	top.rightG->rotateR();
	bottom.leftG->rotateR();
	bottom.rightG->rotateR();
}

void ball::rotateTopR() {
	prevMove.push_back("U");
	top.rotateR();
	bottom.rotateR();
	//rotate gears
	Gear* buffG = top.topG;
	Gear* buffG2 = top.rightG;
	top.topG = top.leftG;
	top.rightG = buffG;
	buffG = top.bottomG;
	top.bottomG = buffG2;
	top.leftG = buffG;
	//assign neighbor gears
	left.topG = top.leftG;
	rear.topG = top.topG;
	right.topG = top.rightG;
	front.topG = top.bottomG;
	//rotate layers
	char layer[3];
	char buff[3];
	//rotate left and store top (rear)
	layer[0] = rear.face[0];
	layer[1] = rear.face[1];
	layer[2] = rear.face[2];
	rear.face[0] = left.face[0];
	rear.face[1] = left.face[1];
	rear.face[2] = left.face[2];
	//rotate top (rear) and store right
	buff[0] = right.face[0];
	buff[1] = right.face[1];
	buff[2] = right.face[2];
	right.face[0] = layer[0];
	right.face[1] = layer[1];
	right.face[2] = layer[2];
	//rotate right and store bot (front)
	layer[0] = front.face[0];
	layer[1] = front.face[1];
	layer[2] = front.face[2];
	front.face[0] = buff[0];
	front.face[1] = buff[1];
	front.face[2] = buff[2];
	//rotate bot
	left.face[0] = layer[0];
	left.face[1] = layer[1];
	left.face[2] = layer[2];

	//rotate rear (bottom)
	//rotate gears
	buffG = bottom.topG;
	buffG2 = bottom.rightG;
	bottom.topG = bottom.leftG;
	bottom.rightG = buffG;
	buffG = bottom.bottomG;
	bottom.bottomG = buffG2;
	bottom.leftG = buffG;
	//assign neighbor gears
	left.bottomG = bottom.leftG;
	rear.bottomG = bottom.bottomG;
	right.bottomG = bottom.rightG;
	front.bottomG = bottom.topG;
	//rotate layers
	//rotate left and store top (front)
	layer[0] = front.face[6];
	layer[1] = front.face[7];
	layer[2] = front.face[8];
	front.face[6] = left.face[6];
	front.face[7] = left.face[7];
	front.face[8] = left.face[8];
	//rotate top (front) and store right
	buff[0] = right.face[6];
	buff[1] = right.face[7];
	buff[2] = right.face[8];
	right.face[6] = layer[0];
	right.face[7] = layer[1];
	right.face[8] = layer[2];
	//rotate right and store bot (rear)
	layer[0] = rear.face[6];
	layer[1] = rear.face[7];
	layer[2] = rear.face[8];
	rear.face[6] = buff[0];
	rear.face[7] = buff[1];
	rear.face[8] = buff[2];
	//rotate bot (rear)
	left.face[6] = layer[0];
	left.face[7] = layer[1];
	left.face[8] = layer[2];

	//rotate gears
	front.leftG->rotateL();
	front.rightG->rotateL();
	rear.leftG->rotateL();
	rear.rightG->rotateL();
}

void ball::rotateTopL() {
	prevMove.push_back("U'");

	bottom.rotateL();
	top.rotateL();
	//rotate gear positions
	Gear* buffG = top.topG;
	Gear* buffG2 = top.leftG;
	top.topG = top.rightG;
	top.leftG = buffG;
	buffG = top.bottomG;
	top.bottomG = buffG2;
	top.rightG = buffG;
	//assign neighbor gears
	left.topG = top.leftG;
        rear.topG = top.topG;
        right.topG = top.rightG;
        front.topG = top.bottomG;
	//rotate layers
	char layer[3];
	char buff[3];
	//rotate top (rear) and store left
	layer[0] = left.face[0];
	layer[1] = left.face[1];
	layer[2] = left.face[2];
	left.face[0] = rear.face[0];
	left.face[1] = rear.face[1];
	left.face[2] = rear.face[2];
	//rotate left and store bottom (front)
	buff[0] = front.face[0];
	buff[1] = front.face[1];
	buff[2] = front.face[2];
	front.face[0] = layer[0];
	front.face[1] = layer[1];
	front.face[2] = layer[2];
	//rotate bottom (front) and store right
	layer[0] = right.face[0];
	layer[1] = right.face[1];
	layer[2] = right.face[2];
	right.face[0] = buff[0];
	right.face[1] = buff[1];
	right.face[2] = buff[2];
	//rotate right to top (rear)
	rear.face[0] = layer[0];
	rear.face[1] = layer[1];
	rear.face[2] = layer[2];

	//rotate rear (bottom)
	//rotate gears
	buffG = bottom.topG;
	buffG2 = bottom.leftG;
	bottom.topG = bottom.rightG;
	bottom.leftG = buffG;
	buffG = bottom.bottomG;
	bottom.bottomG = buffG2;
	bottom.rightG = buffG;
	//assign neighbor gears
	left.bottomG = bottom.leftG;
	right.bottomG = bottom.rightG;
	front.bottomG = bottom.topG;
	rear.bottomG = bottom.bottomG;
	//rotate layers
	//rotate right and store top (front)
	layer[0] = front.face[6];
	layer[1] = front.face[7];
	layer[2] = front.face[8];
	for(int i = 6; i < 9; i++) {
		front.face[i] = right.face[i];
	}
	//rotate top (front) and store left
	buff[0] = left.face[6];
	buff[1] = left.face[7];
	buff[2] = left.face[8];
	left.face[6] = layer[0];
	left.face[7] = layer[1];
	left.face[8] = layer[2];
	//rotate left and store bottom (rear)
	right.face[6] = rear.face[6];
	right.face[7] = rear.face[7];
	right.face[8] = rear.face[8];
	rear.face[6] = buff[0];
	rear.face[7] = buff[1];
	rear.face[8] = buff[2];
	//rotate gears
	front.leftG->rotateR();
	front.rightG->rotateR();
	rear.leftG->rotateR();
	rear.rightG->rotateR();
}

void ball::rotateRightR() {
	prevMove.push_back("R");
	left.rotateR();
	right.rotateR();
	//rotate gears
	Gear* buffG = right.topG;
	Gear* buffG2 = right.rightG;
	right.topG = right.leftG;
	right.rightG = buffG;
	buffG = right.bottomG;
	right.bottomG = buffG2;
	right.leftG = buffG;
	//assign neighbor gears
	front.rightG = right.leftG;
	top.rightG = right.topG;
	rear.leftG = right.rightG;
	bottom.rightG = right.bottomG;
	//rotate layers
	char layer[3];
	char buff[3];
	//rotate left (Front) and store top
	layer[0] = top.face[2];
	layer[1] = top.face[5];
	layer[2] = top.face[8];
	top.face[2] = front.face[2];
	top.face[5] = front.face[5];
	top.face[8] = front.face[8];
	//rotate top and store right (rear)
	buff[0] = rear.face[6];
	buff[1] = rear.face[3];
	buff[2] = rear.face[0];
	rear.face[6] = layer[0];
	rear.face[3] = layer[1];
	rear.face[0] = layer[2];
	//rotate right (rear) and store bot
	front.face[2] = bottom.face[2];
	front.face[5] = bottom.face[5];
	front.face[8] = bottom.face[8];
	bottom.face[2] = buff[0];
	bottom.face[5] = buff[1];
	bottom.face[8] = buff[2];

	//rotate rear (left)
	//rotate gears
	buffG = left.topG;
	buffG2 = left.rightG;
	left.topG = left.leftG;
	left.rightG = buffG;
	left.leftG = left.bottomG;
	left.bottomG = buffG2;
	//assign neighbor gears
	rear.rightG = left.leftG;
	top.leftG = left.topG;
	bottom.leftG = left.bottomG;
	front.leftG = left.rightG;
	//rotate layers
	//rotate left (rear) and store top
	layer[0] = top.face[0];
	layer[1] = top.face[3];
	layer[2] = top.face[6];
	top.face[0] = rear.face[8];
	top.face[3] = rear.face[5];
	top.face[6] = rear.face[2];
	//rotate top and store right (front)
	buff[0] = front.face[0];
	buff[1] = front.face[3];
	buff[2] = front.face[6];
	front.face[0] = layer[0];
	front.face[3] = layer[1];
	front.face[6] = layer[2];
	//rotate right(Front) and bottom
	rear.face[8] = bottom.face[0];
	rear.face[5] = bottom.face[3];
	rear.face[2] = bottom.face[6];
	bottom.face[0] = buff[0];
	bottom.face[3] = buff[1];
	bottom.face[6] = buff[2];
	//rotate gears
	front.topG->rotateL();
	front.bottomG->rotateL();
	rear.topG->rotateL();
	rear.bottomG->rotateL();
}

void ball::rotateRightL() {
	prevMove.push_back("R'");
	right.rotateL();
	left.rotateL();
	//rotate gears
	Gear* buffG = right.topG;
	Gear* buffG2 = right.leftG;
	right.topG = right.rightG;
	right.leftG = buffG;
	right.rightG = right.bottomG;
	right.bottomG = buffG2;
	//assign neighbor gears
	front.rightG = right.leftG;
	rear.leftG = right.rightG;
	top.rightG = right.topG;
	bottom.rightG = right.bottomG;
	//rotate layers
	char layer[3];
	char buff[3];
	//rotate right (rear) and store top
	layer[0] = top.face[2];
	layer[1] = top.face[5];
	layer[2] = top.face[8];
	top.face[2] = rear.face[6];
	top.face[5] = rear.face[3];
	top.face[8] = rear.face[0];
	//rotate top and store left (Front)
	buff[0] = front.face[2];
	buff[1] = front.face[5];
	buff[2] = front.face[8];
	front.face[2] = layer[0];
	front.face[5] = layer[1];
	front.face[8] = layer[2];
	//rotate left (front) and store bot
	layer[0] = bottom.face[2];
	layer[1] = bottom.face[5];
	layer[2] = bottom.face[8];
	bottom.face[2] = buff[0];
	bottom.face[5] = buff[1];
	bottom.face[8] = buff[2];
	//rotate bottom and right (rear)
	top.face[8] = rear.face[0];
	top.face[5] = rear.face[3];
	top.face[2] = rear.face[6];
	rear.face[6] = layer[0];
	rear.face[3] = layer[1];
	rear.face[0] = layer[2];
	//rotate rear (left)
	//rotate gears
	buffG = left.topG;
	buffG2 = left.leftG;
	left.topG = left.rightG;
	left.leftG = buffG;
	left.rightG = left.bottomG;
	left.bottomG = buffG2;
	//assign neighbor gears
	top.leftG = left.topG;
	rear.rightG = left.leftG;
	bottom.leftG = left.bottomG;
	front.leftG = left.rightG;
	//rotate layers
	//rotate right (front) and store top
	layer[0] = top.face[0];
	layer[1] = top.face[3];
	layer[2] = top.face[6];
	top.face[0] = front.face[0];
	top.face[3] = front.face[3];
	top.face[6] = front.face[6];
	//rotate top and store left (rear)
	buff[0] = rear.face[8];
	buff[1] = rear.face[5];
	buff[2] = rear.face[2];
	rear.face[8] = layer[0];
	rear.face[5] = layer[1];
	rear.face[2] = layer[2];
	//rotate left (rear)  and bottom
	front.face[0] = bottom.face[0];
	front.face[3] = bottom.face[3];
	front.face[6] = bottom.face[6];
	bottom.face[0] = buff[0];
	bottom.face[3] = buff[1];
	bottom.face[6] = buff[2];
	//rotate gears
	front.topG->rotateR();
	front.bottomG->rotateR();
	rear.topG->rotateR();
	rear.bottomG->rotateR();
}

void Gear::print() const {
	int x = rotations % 6;
	if(x < 0) {
		x = 6 + x;
	}
	switch(x) {
		case 0:
			cout << color1 << "|" << color2;
			break;
		case 1:
			cout << color1 << "\\" << color2;
			break;
		case 2:
			cout << color2 << "/" << color1;
			break;
		case 3:
			cout << color2 << "|" << color1;
			break;
		case 4:
			cout << color2 << "\\" << color1;
			break;
		case 5:
			cout << color1 << "/" << color2;
			break;
	}
}

void ball::print() const {
	//top
	cout << "\t\t\t";
	top.topG->print();
	cout << "\n\n";
	cout << "\t\t\t";
	top.printRow(1);
	cout << "\n";
	cout << "\t\t";
	top.leftG->print();
	cout << "\t";
	top.printRow(2);
	cout << "\t";
	top.rightG->print();
	cout << "\n";
	cout << "\t\t\t";
	top.printRow(3);
	cout << "\n\n";
	cout << "\t\t\t";
	top.bottomG->print();
	cout << "\n\n";

	//left | front | right
	tab();
	left.printRow(1);
	tab();tab();
	front.printRow(1);
	tab();tab();
	right.printRow(1);
	nl();
	left.leftG->print();
	tab();
	left.printRow(2);
	tab();
	left.rightG->print();
	tab();
	front.printRow(2);
	tab();
	front.rightG->print();
	tab();
	right.printRow(2);
	tab();
	right.rightG->print();
	nl(); tab();
	left.printRow(3);
	tab(); tab();
	front.printRow(3);
	tab(); tab();
	right.printRow(3);
	nl(); nl(); tab(); tab(); tab();
	bottom.topG->print();
	nl(); nl();
	//bottom
	tab(); tab(); tab();
	bottom.printRow(1);
	nl();
	tab(); tab();
	bottom.leftG->print();
	tab();
	bottom.printRow(2);
	tab();
	bottom.rightG->print();
	nl(); tab(); tab(); tab();
	bottom.printRow(3);
	nl(); nl(); tab(); tab(); tab();
	bottom.bottomG->print();
	nl(); nl(); tab(); tab(); tab();
	//rear
	cout << rear.face[8] << rear.face[7] << rear.face[6];
	nl(); tab();
	rear.rightG->print();
	tab(); tab();
	cout << rear.face[5] << rear.face[4] << rear.face[3];
	tab(); tab();
	rear.leftG->print();
	nl(); tab(); tab(); tab();
	cout << rear.face[2] << rear.face[1] << rear.face[0];
	nl(); nl(); tab(); tab(); tab();
	rear.topG->print();
	nl();
}

int ball::estimate() const {
	int val = 0;
	for(int i = 0; i < 9; i++) {
		if(front.face[i] != 'R') {
			val++;
		}
		if(left.face[i] != 'Y') {
			val++;
		}
		if(right.face[i] != 'O') {
			val++;
		}
		if(top.face[i] != 'G') {
			val++;
		}
		if(bottom.face[i] != 'B') {
			val++;
		}
		if(rear.face[i] != 'P') {
			val++;
		}
	}
	if(rear.topG != &pg) {// || (pg.rotations % 6 != 0)) {
		val++;
	}
	if((pg.rotations % 6) != 0) {
		val++;
	}
	if(top.leftG != &yg) {// || (yg.rotations % 6 != 0)) {
		val++;
	}
	if((yg.rotations % 6) != 0) {
		val++;
	}
	if(top.rightG != &go) {// || (go.rotations % 6 != 0)) {
		val++;
	}
	if((go.rotations % 6) != 0) {
		val++;
	}
	if(front.topG != &gr) {// || (gr.rotations % 6 != 0)) {
		val++;
	}
	if((gr.rotations % 6) != 0) {
		val++;
	}
	if(front.leftG != &yr) {// || (yr.rotations % 6 != 0)) {
		val++;
	}
	if((yr.rotations % 6) != 0) {
		val++;
	}
	if(front.rightG != &ro) {// || (ro.rotations % 6 != 0)) {
		val++;
	}
	if((ro.rotations % 6) != 0) {
		val++;
	}
	if(front.bottomG != &rb) {// || (rb.rotations % 6 != 0)) {
		val++;
	}
	if((rb.rotations % 6) != 0) {
		val++;
	}
	if(bottom.rightG != &bo) {// || (bo.rotations % 6 != 0)) {
		val++;
	}
	if((bo.rotations % 6) != 0) {
		val++;
	}
	if(bottom.bottomG != &bp) {// || (bp.rotations % 6 != 0)) {
		val++;
	}
	if((bp.rotations % 6) != 0) {
		val++;
	}
	if(bottom.leftG != &yb) {
		val++;
	}
	if((yb.rotations % 6) != 0) {
		val++;
	}
	if(rear.rightG != &py) {// || (py.rotations % 6 != 0)) {
		val++;
	}
	if((py.rotations % 6) != 0) {
		val++;
	}
	if(rear.leftG != &po) {// || (po.rotations % 6 != 0)) {
		val++;
	}
	if((po.rotations % 6) != 0) {
		val++;
	}
	return (val / 36);
}

int opp(int x) {
	switch(x) {
		case 0:
			return 3;
		case 1:
			return 4;
		case 2:
			return 5;
		case 3:
			return 0;
		case 4:
			return 1;
		case 5:
			return 2;
		default:
			return -1;
	}
}

string oppS(string m) {
	if(m.length() == 1) {
		return (m+ "'");
	} else {
		return (m.substr(0,1));
	}
}

bool ball::validMove(string m) {
	string moves[6] = {"F", "R", "U", "F'", "R'", "U'"};
	if(prevMove.size() < 1) {
		return true;
	} else {
		if(prevMove[prevMove.size()-1] == oppS(m)) {
			return false;
		} else {
			if(prevMove.size() > 11) {
				for(int i = 0; i < 12; i++) {
					if(prevMove[i] != m) {
						return true;
					}
				}
				return false;
			}
			return true;
		}
	}
}

void ball::takeMove(int i) {
	switch(i) {
		case 0:
			rotateFrontR();
			break;
		case 1:
			rotateRightR();
			break;
		case 2:
			rotateTopR();
			break;
		case 3:
			rotateFrontL();
			break;
		case 4:
			rotateRightL();
			break;
		case 5:
			rotateTopL();
			break;
		default:
			break;
	}
}

void ball::randMoves(int n) {
	string moves[6] = {"F", "R", "U", "F'", "R'", "U'"};
	srand(time(NULL));
	vector<int> moveList;
	for(int i = 0; i < n; i++) {
		int rando = rand() % 6;
		bool accept = true;
		if(i > 0) {
			if(opp(rando) == moveList[i-1]) {
				accept = false;
			}
		}
		if(i > 11) {
			bool cont = true;
			for(int j = i-11; j < i; j++) {
				if(moveList[j] != rando) {
					cont = false;
					break;
				}
			}
			if(cont) {
				accept = false;
			}
		}
		if(accept) {
			moveList.push_back(rando);
		} else {
			i--;
		}
	}
	for(int i = 0; i < n; i++) {
		cout << moves[moveList[i]] << " ";
		switch(moveList[i]) {
			case 0:
				rotateFrontR();
				break;
			case 1:
				rotateRightR();
				break;
			case 2:
				rotateTopR();
				break;
			case 3:
				rotateFrontL();
				break;
			case 4:
				rotateRightL();
				break;
			case 5:
				rotateTopL();
				break;
		}
	}
	nl();
	print();
}
