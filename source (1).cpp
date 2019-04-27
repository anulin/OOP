#include <fstream>
#include <vector>
#include <iostream>
#include <queue>
#include <set>
const int PuzzleSize = 4;
using namespace std;


template <int PSIZE>
class Puzzle {
public:
	short curDist;
	short heurDist;
	short posOfZero;
	Puzzle() {
		puzzle.resize(PSIZE * PSIZE);
	}
	Puzzle(const Puzzle& puzzleTemp,
		char lMove, short cDist,
		short hDist, short pOfZero) :
		lastMove(lMove), curDist(cDist), heurDist(hDist), posOfZero(pOfZero) {
		puzzle.resize(PSIZE * PSIZE);
		for (short i = 0; i < PSIZE * PSIZE; ++i) {
			puzzle[i] = puzzleTemp[i];
		}
	}
	void incrCurDist() {
		curDist++;
	}
	short getCurDist() {
		return curDist;
	}
	char getLastMove() {
		return lastMove;
	}

	short& operator[] (short ind) {
		return puzzle[ind];
	}
	const short operator[] (short ind) const {
		return puzzle[ind];
	}
	bool compBySumDist(const Puzzle& puzz) const {
		if (curDist + heurDist == puzz.curDist + puzz.heurDist) {
			return heurDist > puzz.heurDist;
		}
		else {
			return curDist + heurDist > puzz.curDist + puzz.heurDist;
		}
	}
	bool isSolved() {
		for (short i = 0; i < PSIZE * PSIZE - 1; ++i) {
			if (puzzle[i] != i + 1) {
				return false;
			}
		}
		return true;
	}
	bool compByOrder(const Puzzle& puzz) const {
		for (short i = 0; i < PSIZE * PSIZE; ++i) {
			if (puzzle[i] < puzz[i]) {
				return true;
			}
			if (puzzle[i] > puzz[i]) {
				return false;
			}
		}
		return false;
	}
	template <int SIZE>
	friend std::istream& operator>> (std::istream& input, Puzzle<SIZE>& puzz);
	template <int SIZE>
	friend std::ostream& operator<< (std::ostream& output,
		const Puzzle<SIZE>& puzz);

	vector<Puzzle> GetNextState() {

	    vector<Puzzle> vectr;
		moveZeroLeft(vectr);
		moveZeroUp(vectr);
		moveZeroRight(vectr);
		moveZeroDown(vectr);
		return vectr;
	}

private:

	std::vector<short> puzzle;
	char lastMove;

	void moveZeroUp(vector<Puzzle> &vectr) {
		Puzzle<PSIZE> tmpPuzz;
		if (getLastMove() != 'U') {
			if (posOfZero / PSIZE > 0) {
				tmpPuzz = *this;
				tmpPuzz[posOfZero] = tmpPuzz[posOfZero - PSIZE];
				tmpPuzz[posOfZero - PSIZE] = 0;
				tmpPuzz.incrCurDist();
				tmpPuzz.lastMove='D';
				vectr.push_back(tmpPuzz);

			}
		}
	}
	void moveZeroDown(vector<Puzzle> &vectr) {
		Puzzle<PSIZE> tmpPuzz;
		if (getLastMove() != 'D') {
			if (posOfZero / PSIZE < PSIZE - 1) {
				tmpPuzz = *this;
				tmpPuzz[posOfZero] = tmpPuzz[posOfZero + PSIZE];
				tmpPuzz[posOfZero + PSIZE] = 0;
				tmpPuzz.incrCurDist();
				tmpPuzz.lastMove='U';
				vectr.push_back(tmpPuzz);

			}
		}
	}
	void moveZeroRight(vector<Puzzle> &vectr) {
		Puzzle<PSIZE> tmpPuzz;
		if (getLastMove() != 'R') {
			if (posOfZero % PSIZE < PSIZE - 1) {
				tmpPuzz = *this;
				tmpPuzz[posOfZero] = tmpPuzz[posOfZero + 1];
				tmpPuzz[posOfZero + 1] = 0;
				tmpPuzz.incrCurDist();
				tmpPuzz.lastMove='L';
				vectr.push_back(tmpPuzz);

			}
		}
	}
	void moveZeroLeft(vector<Puzzle> &vectr) {
		Puzzle<PSIZE> tmpPuzz;
		if (getLastMove() != 'L') {
			if (posOfZero % PSIZE > 0) {
				tmpPuzz = *this;
				tmpPuzz[posOfZero] = tmpPuzz[posOfZero - 1];
				tmpPuzz[posOfZero - 1] = 0;
				tmpPuzz.incrCurDist();
				tmpPuzz.lastMove='R';
				vectr.push_back(tmpPuzz);
			}
		}
	}

};

template <int PSIZE>
std::istream& operator>> (std::istream& input, Puzzle<PSIZE>& puzz) {
	for (short i = 0; i < PSIZE * PSIZE; ++i) {
		input >> puzz[i];
	}
	puzz.lastMove = 0;
	puzz.curDist = 0;
	for (short i = 0; i < PSIZE * PSIZE; ++i) {
		if (puzz[i] == 0) {
			puzz.posOfZero = i;
			break;
		}
	}
	return input;
}

template <int PSIZE>
std::ostream& operator<< (std::ostream& output, const Puzzle<PSIZE>& puzz) {
	for (short i = 0; i < PSIZE * PSIZE; ++i) {
		output << puzz[i] << " ";
		if ((i + 1) % PSIZE == 0) {
			output << "\n";
		}
	}
	return output;
}

template <int PSIZE>
struct PuzzleSolver {
	bool solvePuzzle(std::ifstream& fIn, short hDist(const Puzzle<PSIZE>&)) {
		fIn >> startPuzzle;
		heurDist = hDist;
		vector<Puzzle<PSIZE>> vectr;
		priorQueue = std::priority_queue<Puzzle<PSIZE>, std::deque<Puzzle<PSIZE>>, CompBySumDist>();
		coveredVert.clear();
		priorQueue.emplace(startPuzzle, '0', 0, hDist(startPuzzle), startPuzzle.posOfZero);
		if (hDist(startPuzzle) >= 0 && !isSolvable()) {
			return false;
		}
		while (!priorQueue.empty()) {
			curPuzzle = priorQueue.top();
			posOfZero = curPuzzle.posOfZero;
			priorQueue.pop();
			if (curPuzzle.isSolved()) {
				traceMovements();
				break;
			}
			//std::cout << curPuzzle << " " << cornerTiles(curPuzzle) << "\n";
			/*if (counter % 5 == 0) {
				std::cout << coveredVert.size() << " " << priorQueue.size() << "\n";
				int i;
				std::cin >> i;
				//std::cout << curPuzzle.heurDist + curPuzzle.curDist << "   " << curPuzzle.curDist << " " << curPuzzle.heurDist << "\n";
			}*/
			vectr=curPuzzle.GetNextState();
			for(int i=0; i<vectr.size();i++){
			    if (coveredVert.find(vectr[i]) == coveredVert.end()) {
                    if(vectr[i].getLastMove()=='D')
                        priorQueue.emplace(vectr[i], 'D', vectr[i].getCurDist(),
                            heurDist(vectr[i]), posOfZero - PSIZE);
                    else if(vectr[i].getLastMove()=='U')
                        priorQueue.emplace(vectr[i], 'U', vectr[i].getCurDist(),
                            heurDist(vectr[i]), posOfZero + PSIZE);
                    else if(vectr[i].getLastMove()=='L')
                        priorQueue.emplace(vectr[i], 'L', vectr[i].getCurDist(),
                            heurDist(vectr[i]), posOfZero + 1);
                    else
                        priorQueue.emplace(vectr[i], 'R', vectr[i].getCurDist(),
                            heurDist(vectr[i]), posOfZero - 1);
				}

			}
			coveredVert.insert(curPuzzle);
		}
		return true;
	}

	void printSolution(std::ofstream& fOut) {
		if (isSolvable()) {
			fOut << minDist << "\n";
			for (short i = reqMovements.size(); i > 0; --i) {
				fOut << reqMovements[i - 1];
			}
		}
		else {
			fOut << "-1";
		}
		fOut << "\n";
	}
private:
	class CompBySumDist {
	public:
		bool operator() (const Puzzle<PSIZE>& firstPuzz, const Puzzle<PSIZE>& secondPuzz) {
			return firstPuzz.compBySumDist(secondPuzz);
		}
	};

	class CompByOrder {
	public:
		bool operator() (const Puzzle<PSIZE>& firstPuzz, const Puzzle<PSIZE>& secondPuzz) {
			return firstPuzz.compByOrder(secondPuzz);
		}
	};

	short(*heurDist)(const Puzzle<PSIZE>&);
	Puzzle<PSIZE> startPuzzle;
	priority_queue<Puzzle<PSIZE>, std::deque<Puzzle<PSIZE>>, CompBySumDist> priorQueue;
	set<Puzzle<PSIZE>, CompByOrder> coveredVert;
	vector<char> reqMovements;
	short minDist;
	Puzzle<PSIZE> tmpPuzz;
	short posOfZero;
	Puzzle<PSIZE> curPuzzle;
	short prevPosOfZero;
	short curPosOfZero;

	short isSolvable() {
		short amOfInv = 0;
		for (short i = 0; i < PSIZE * PSIZE; ++i) {
			for (short j = i + 1; j < PSIZE * PSIZE; ++j) {
				if ((i < j) && ((startPuzzle[i] > startPuzzle[j] &&
					startPuzzle[j] != 0))) {
					amOfInv++;
				}
			}
			if (startPuzzle[i] == 0 && PSIZE % 2 == 0) {
				amOfInv += (i / 4 + 1);
			}
		}
		return (amOfInv + 1) % 2;
	}

	void traceMovements() {
		reqMovements.clear();
		minDist = curPuzzle.getCurDist();
		while (curPuzzle.getCurDist() > 0) {
			tmpPuzz = curPuzzle;
			for (short i = 0; i < PSIZE * PSIZE; ++i) {
				if (curPuzzle[i] == 0) {
					posOfZero = i;
					break;
				}
			}
			reqMovements.push_back(curPuzzle.getLastMove());
			switch (curPuzzle.getLastMove()) {
			case 'D':
				tmpPuzz[posOfZero] = tmpPuzz[posOfZero + PSIZE];
				tmpPuzz[posOfZero + PSIZE] = 0;
				break;
			case 'U':
				tmpPuzz[posOfZero] = tmpPuzz[posOfZero - PSIZE];
				tmpPuzz[posOfZero - PSIZE] = 0;
				break;
			case 'L':
				tmpPuzz[posOfZero] = tmpPuzz[posOfZero - 1];
				tmpPuzz[posOfZero - 1] = 0;
				break;
			default:
				tmpPuzz[posOfZero] = tmpPuzz[posOfZero + 1];
				tmpPuzz[posOfZero + 1] = 0;
				break;
			}
			curPuzzle = *(coveredVert.find(tmpPuzz));
		}
	}

};

template <int PSIZE>
short linearAndPillarConflict(const Puzzle<PSIZE>& puzzle) {
	short distance = 0;
	for (short i = 0; i < PSIZE * PSIZE; ++i) {
		for (short j = i + 1; j < i / PSIZE + PSIZE; ++j) {
			if (puzzle[j] != 0 && puzzle[i] > puzzle[j] &&
				(puzzle[i] - 1) / PSIZE == i / PSIZE &&
				(puzzle[j] - 1) / PSIZE == j / PSIZE) {
				distance += 2;
			}
		}
		for (short j = i / PSIZE; j < PSIZE; ++j) {
			if (puzzle[j * PSIZE + i % PSIZE] != 0 && puzzle[i] > puzzle[j * PSIZE + i % PSIZE] &&
				(puzzle[i] - 1) % PSIZE == i % PSIZE &&
				(puzzle[j * PSIZE + i % PSIZE] - 1) % PSIZE == (j * PSIZE + i % PSIZE) % PSIZE) {
				distance += 2;
			}
		}
	}
	return distance;
}


template <int PSIZE>
short manhattanDistance(const Puzzle<PSIZE>& puzzle) {
	short distance = 0;
	short xDif;
	short yDif;
	for (short i = 1; i < PSIZE * PSIZE + 1; ++i) {
		if (puzzle[i - 1] == 0) {
			++i;
			if (i >= PSIZE * PSIZE + 1) {
				break;
			}
		}
		xDif = abs((i - 1) % PSIZE - (puzzle[i - 1] - 1) % PSIZE);
		yDif = abs((i - 1) / PSIZE - (puzzle[i - 1] - 1) / PSIZE);
		distance += xDif;
		distance += yDif;
	}
	return distance;
}

template <int PSIZE>
short heurDistance(const Puzzle<PSIZE>& puzzle) {
	return manhattanDistance(puzzle) + linearAndPillarConflict(puzzle)/* + cornerTiles(puzzle)*/;
}

int main() {
	std::ifstream fIn;
	fIn.open("input.txt");
	PuzzleSolver<PuzzleSize> puzzleSolver;
	std::ofstream fOut;
	fOut.open("output.txt", std::ios::out);
	puzzleSolver.solvePuzzle(fIn, &heurDistance);
	puzzleSolver.printSolution(fOut);
	fIn.close();
	fOut.close();
	return 0;
}
