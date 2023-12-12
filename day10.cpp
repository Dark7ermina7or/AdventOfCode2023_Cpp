#include <iostream>
#include <fstream>
#include <vector>
#include <string>


struct coordinates {
	int X;
	int Y;
	int fromX;
	int fromY;
	coordinates(int x, int y, int fx, int fy) : X(x), Y(y), fromX(fx), fromY(fy) {}
	coordinates(int x, int y) : X(x), Y(y) {}
};

struct pipes {
	char pipe;
	coordinates A;
	coordinates B;
	pipes(char p, coordinates a, coordinates b) : pipe(p), A(a), B(b) {}
};

std::vector<pipes> neighbors = { pipes('|',coordinates(-1,0),coordinates(1,0)),
								 pipes('-',coordinates(0,1),coordinates(0,-1)),
								 pipes('L',coordinates(-1,0),coordinates(0,1)),
								 pipes('J',coordinates(-1,0),coordinates(0,-1)),
								 pipes('7',coordinates(1,0),coordinates(0,-1)),
								 pipes('F',coordinates(1,0),coordinates(0,1)) };

std::vector<std::string> readFileToList(const std::string& filePath) {
	std::vector<std::string> lines;
	std::ifstream file(filePath);

	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			lines.push_back(line);
		}
		file.close();
	}
	else {
		std::cerr << "Unable to open file: " << filePath << std::endl;
	}

	return lines;
}

coordinates FindStart(int x, int y, std::vector<std::string> layout) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (layout[i][j] == 'S') {
				return coordinates(i, j);
			}
		}
	}
}

int main() {
	std::string filePath = "C:\\Users\\Dark7ermina7or\\Desktop\\test\\ConsoleApplication1\\Debug\\input.txt";  // Replace with the actual file path
	std::vector<std::string> lines = readFileToList(filePath);

	//add border
	for (int i = 0; i < lines.size(); ++i) {
		lines[i] = '.' + lines[i] + '.';
	}

	std::string bordertb = "";

	for (int i = 0; i < lines[0].size(); ++i) {
		bordertb += '.';
	}

	lines.insert(lines.begin(), bordertb);
	lines.push_back(bordertb);

	//get size of "array"
	int X = lines.size();
	int Y = lines[0].size();

	//std::reverse(lines.begin(), lines.end());

	coordinates startpos = FindStart(X, Y, lines);
	coordinates wayA(0, 0, startpos.X, startpos.Y), wayB(0, 0, startpos.X, startpos.Y);

	bool firstfound = false;
	coordinates firstPos(0,0,0,0);

	if (lines[startpos.X + 0][startpos.Y - 1] == '-' || lines[startpos.X + 0][startpos.Y - 1] == 'L' || lines[startpos.X + 0][startpos.Y - 1] == 'F') {
		wayA.X = startpos.X + 0;
		wayA.Y = startpos.Y - 1;
		firstfound = true;

		firstPos.X = 0;
		firstPos.Y = -1;
	}
	if (lines[startpos.X + 1][startpos.Y + 0] == '|' || lines[startpos.X + 1][startpos.Y + 0] == 'J' || lines[startpos.X + 1][startpos.Y + 0] == 'L') {
		if (firstfound) {
			wayB.X = startpos.X + 1;
			wayB.Y = startpos.Y + 0;

			firstPos.fromX = 1;
			firstPos.fromY = 0;
		}
		else {
			wayA.X = startpos.X + 1;
			wayA.Y = startpos.Y + 0;
			firstfound = true;

			firstPos.X = 1;
			firstPos.Y = 0;
		}
	}
	if (lines[startpos.X + 0][startpos.Y + 1] == '-' || lines[startpos.X + 0][startpos.Y + 1] == 'J' || lines[startpos.X + 0][startpos.Y + 1] == '7') {
		if (firstfound) {
			wayB.X = startpos.X + 0;
			wayB.Y = startpos.Y + 1;

			firstPos.fromX = 0;
			firstPos.fromY = 1;
		}
		else {
			wayA.X = startpos.X + 0;
			wayA.Y = startpos.Y + 1;
			
			firstPos.X = 0;
			firstPos.Y = 1;
		}
	}
	if (lines[startpos.X - 1][startpos.Y + 0] == '|' || lines[startpos.X - 1][startpos.Y + 0] == '7' || lines[startpos.X - 1][startpos.Y + 0] == 'F') {
		wayB.X = startpos.X - 1;
		wayB.Y = startpos.Y + 0;

		firstPos.fromX = -1;
		firstPos.fromY = 0;
	}

	std::cout << std::to_string(startpos.X) + ":" + std::to_string(startpos.Y) + "\n";
	std::cout << std::to_string(wayA.X) + ":" + std::to_string(wayA.Y) + " - " + std::to_string(wayB.X) + ":" + std::to_string(wayB.Y);

	int steps = 0;

	bool Adone, Bdone;
	coordinates toX(0, 0, 0, 0);
	int ns = neighbors.size();

	do {

		Adone = false;
		Bdone = false;

		for (int i = 0; i < ns; i++) {
			if ((lines[wayA.X][wayA.Y] == neighbors[i].pipe) && !Adone) {
				if ((wayA.fromX != wayA.X + neighbors[i].A.X) || (wayA.fromY != wayA.Y + neighbors[i].A.Y)) {
					//lines[wayA.fromX][wayA.fromY] = 'X';
					//lines[wayB.fromX][wayB.fromY] = 'X';

					toX.X = wayA.fromX;
					toX.Y = wayA.fromY;

					wayA.fromX = wayA.X;
					wayA.fromY = wayA.Y;

					wayA.X = wayA.X + neighbors[i].A.X;
					wayA.Y = wayA.Y + neighbors[i].A.Y;

					Adone = true;
					break;
				}
				if ((wayA.fromX != wayA.X + neighbors[i].B.X) || (wayA.fromY != wayA.Y + neighbors[i].B.Y)) {
					//lines[wayA.fromX][wayA.fromY] = 'X';
					//lines[wayB.fromX][wayB.fromY] = 'X';

					toX.X = wayA.fromX;
					toX.Y = wayA.fromY;

					wayA.fromX = wayA.X;
					wayA.fromY = wayA.Y;

					wayA.X = wayA.X + neighbors[i].B.X;
					wayA.Y = wayA.Y + neighbors[i].B.Y;

					Adone = true;
					break;
				}
			}
		}

		for (int i = 0; i < ns; i++) {
			if ((lines[wayB.X][wayB.Y] == neighbors[i].pipe) && !Bdone) {
				if ((wayB.fromX != wayB.X + neighbors[i].A.X) || (wayB.fromY != wayB.Y + neighbors[i].A.Y)) {
					//lines[wayA.fromX][wayA.fromY] = 'X';
					//lines[wayB.fromX][wayB.fromY] = 'X';

					toX.fromX = wayB.fromX;
					toX.fromY = wayB.fromY;

					wayB.fromX = wayB.X;
					wayB.fromY = wayB.Y;

					wayB.X = wayB.X + neighbors[i].A.X;
					wayB.Y = wayB.Y + neighbors[i].A.Y;

					Bdone = true;
					break;
				}
				if ((wayB.fromX != wayB.X + neighbors[i].B.X) || (wayB.fromY != wayB.Y + neighbors[i].B.Y)) {
					//lines[wayA.fromX][wayA.fromY] = 'X';
					//lines[wayB.fromX][wayB.fromY] = 'X';

					toX.fromX = wayB.fromX;
					toX.fromY = wayB.fromY;

					wayB.fromX = wayB.X;
					wayB.fromY = wayB.Y;

					wayB.X = wayB.X + neighbors[i].B.X;
					wayB.Y = wayB.Y + neighbors[i].B.Y;

					Bdone = true;
					break;
				}
			}
		}

		steps++;


		if (lines[toX.X][toX.Y] == 'L' || lines[toX.X][toX.Y] == 'J')
		{
			lines[toX.X][toX.Y] = 'U';
		}
		else if (lines[toX.X][toX.Y] == '7' || lines[toX.X][toX.Y] == 'F')
		{
			lines[toX.X][toX.Y] = 'D';
		}
		else if (lines[toX.X][toX.Y] == '|')
		{
			lines[toX.X][toX.Y] = 'I';
		}
		else
		{
			lines[toX.X][toX.Y] = 'X';
			//lines[toX.X][toX.Y] = 'I';
		}

		if (lines[toX.fromX][toX.fromY] == 'L' || lines[toX.fromX][toX.fromY] == 'J')
		{
			lines[toX.fromX][toX.fromY] = 'U';
		}
		else if (lines[toX.fromX][toX.fromY] == '7' || lines[toX.fromX][toX.fromY] == 'F')
		{
			lines[toX.fromX][toX.fromY] = 'D';
		}
		else if (lines[toX.fromX][toX.fromY] == '|')
		{
			lines[toX.fromX][toX.fromY] = 'I';
		}
		else
		{
			lines[toX.fromX][toX.fromY] = 'X';
			//lines[toX.fromX][toX.fromY] = 'I';
		}

		//std::cout << "\n" + std::to_string(steps) + "\n";
		//std::cout << std::to_string(wayA.X) + ":" + std::to_string(wayA.Y) + " - " + std::to_string(wayB.X) + ":" + std::to_string(wayB.Y);
	} while ((wayA.X != wayB.X) || (wayA.Y != wayB.Y));


	for (int i = 0; i < ns; i++)
	{
		if ((firstPos.X == neighbors[i].A.X && firstPos.Y == neighbors[i].A.Y && firstPos.fromX == neighbors[i].B.X && firstPos.fromY == neighbors[i].B.Y) || (firstPos.fromX == neighbors[i].A.X && firstPos.fromY == neighbors[i].A.Y && firstPos.X == neighbors[i].B.X && firstPos.Y == neighbors[i].B.Y))
		{
			lines[startpos.X][startpos.Y] = neighbors[i].pipe;

			if (lines[startpos.X][startpos.Y] == 'L' || lines[startpos.X][startpos.Y] == 'J')
			{
				lines[startpos.X][startpos.Y] = 'U';
			}
			else if (lines[startpos.X][startpos.Y] == '7' || lines[startpos.X][startpos.Y] == 'F')
			{
				lines[startpos.X][startpos.Y] = 'D';
			}
			else if (lines[startpos.X][startpos.Y] == '|')
			{
				lines[startpos.X][startpos.Y] = 'I';
			}
			else
			{
				lines[startpos.X][startpos.Y] = 'X';
				//lines[toX.fromX][toX.fromY] = 'I';
			}
		}
	}


	lines[wayA.X][wayA.Y] = 'X';
	lines[wayB.X][wayB.Y] = 'X';

	std::cout << "\n\nSteps: " + std::to_string(steps + 1);
	std::cout << "\n";

	for (int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < lines[0].size(); j++) {
			if (lines[i][j] != 'I' && lines[i][j] != 'X' && lines[i][j] != 'O' && lines[i][j] != 'U' && lines[i][j] != 'D')
			{
				lines[i][j] = ' ';
			}
			//std::cout << lines[i][j];
		}
		//std::cout << "\n";
	}

	bool inLoop = false;
	int loopSize = 0;
	int loopCross = 0;


	for (int i = 0; i < lines.size(); ++i) {
		for (int j = 0; j < lines[0].size(); ++j) {
			if ((lines[i][j] == 'U' && lines[i][j + 1] == 'U') || (lines[i][j] == 'D' && lines[i][j + 1] == 'D'))
			{
				j++;
				continue;
			}
			if ((lines[i][j] == 'U' && lines[i][j + 1] == 'D') || (lines[i][j] == 'D' && lines[i][j + 1] == 'U'))
			{
				loopCross++;
				j++;
				continue;
			}
			for (int k = j + 1; k < lines[0].size(); k++)
			{
				if (lines[i][j] == 'U' && lines[i][k] == 'X')
				{
					//j = k;
					continue;
				}
				if (lines[i][j] == 'D' && lines[i][k] == 'X')
				{
					//j = k;
					continue;
				}
				if (lines[i][j] == 'D' && lines[i][k] == 'U')
				{
					j = k;
					loopCross++;
					break;
				}
				if (lines[i][j] == 'U' && lines[i][k] == 'D')
				{
					j = k;
					loopCross++;
					break;
				}
				if (lines[i][j] == 'D' && lines[i][k] == 'D')
				{
					j = k;
					//loopCross++;
					break;
				}
				if (lines[i][j] == 'U' && lines[i][k] == 'U')
				{
					j = k;
					//loopCross++;
					break;
				}
			}
			if (lines[i][j] == 'I')
			{
				loopCross++;
				continue;
			}
			if (lines[i][j] == ' ' && (loopCross % 2 == 1))
			{
				loopSize++;
				lines[i][j] = '+';
			}
		}
	}

	std::cout << "\n\nLoop Size: " + std::to_string(loopSize);
	std::cout << "\nLoop Cross: " + std::to_string(loopCross) + "\n\n";

	for (int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < lines[0].size(); j++) {
			std::cout << lines[i][j];
		}
		std::cout << "\n";
	}
}
