#include <iostream>
#include <vector>
#include "gearball.h"
#include "astar.h"

using namespace std;

void printMenu() {
        cout << "Commands:" << endl;
        cout << "0:\tQuit" << endl;
        cout << "1:\tPrint GearBall" << endl;
        cout << "2:\tRandom Rotations" << endl;
        cout << "3:\tRotate a side" << endl;
        cout << "4:\tHeuristic evaluation" << endl;
	cout << "5:\tSolve using a*" << endl;
        cout << "6:\tPrint Menu" << endl;
}

void printRotations() {
        cout << "1:\tRotate Front & Back Right" << endl;
        cout << "2:\tRotate Top & Bottom Right" << endl;
        cout << "3:\tRotate Right & Left Right" << endl;
        cout << "4:\tRotate Front & Back Left" << endl;
        cout << "5:\tRotate Top & Bottom Left" << endl;
        cout << "6:\tRotate Right & Left Left" << endl;
}

int main() {
        ball b;
        int input = 9;
        while(input != 0) {
                switch(input) {
                        case 1:
                                b.print();
                                break;
                        case 2:
                                int n;
                                cout << "How many moves? ";
                                cin >> n;
                                b.randMoves(n);
                                break;
                        case 3:
                                int y;
                                printRotations();
                                cout << "Command: ";
                                cin >> y;
                                switch(y) {
                                        case 1:
                                                b.rotateFrontR();
                                                b.print();
                                                break;
                                        case 2:
                                                b.rotateTopR();
                                                b.print();
                                                break;
                                        case 3:
                                                b.rotateRightR();
                                                b.print();
                                                break;
                                        case 4:
                                                b.rotateFrontL();
                                                b.print();
                                                break;
                                        case 5:
                                                b.rotateTopL();
                                                b.print();
                                                break;
                                        case 6:
                                                b.rotateRightL();
                                                b.print();
                                                break;
                                        default:
                                                printMenu();
                                                break;
                                }
                        case 4:
                                cout << b.estimate() << endl;
				break;
			case 5:
				{
				b = aStar(b);
				printMoves(b.prevMove);
				}
				break;
                        default:
                                printMenu();
                                break;
                }
        cout << "Command: ";
        cin >> input;
        }
}
