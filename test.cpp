#include "gearball.h"
#include "astar.h"
#include <fstream>

using namespace std;

int main() {
	ofstream outFile;
	outFile.open("logfile");
	vector<int> avgs;
	for(int i = 5; i < 20; i++) {
		int count = 0;
		for(int j = 0; j < 5; j++) {
			cout << "Iteration " << j+1 << " of " << j << " random moves." << endl;
			outFile << "Iteration " << j+1 << " of " << i << " rotations." << endl;
			ball b;
			b.randMoves(i);
			cout << "Moves to randomize: ";
			outFile << "Moves to randomize: ";
			printMoves(b.prevMove);
			for(int k = 0; k < b.prevMove.size(); k++) {
				outFile << b.prevMove[k] << " ";
			}
			outFile << endl;
			b = aStar(b);
			cout << "Moves to solve: ";
			outFile << "Moves to solve: ";
			printMoves(b.prevMove);
			for(int k = 0; k < b.prevMove.size(); k++) {
				outFile << b.prevMove[k] << " ";
			}
			outFile << endl;
			count += NODE_COUNT;
			cout << "NODE COUNT: " << NODE_COUNT << endl;
			outFile << "NODE COUNT: " << NODE_COUNT << endl;
		}
		avgs.push_back(count / 5);
		cout << "AVG for " << i << ": " << count / 5 << endl;
		outFile << "AVG for " << i << ": " << count / 5 << endl;

	}
	cout << "DONE" << endl;
	outFile << "DONE" << endl;
	outFile.close();
}

