

#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <cctype>
#include <ctime>
#include <cstdlib>

using namespace std;

class Object {
private:
	int r;
	int c;
	string name;
	bool treasure;
	bool hidden = true;
	int Cashinvalue;
	bool cashedout = false;
	bool obtained = false;
public:
	Object(int ro, int co, string na, bool t, int v) {
		r = ro;
		c = co;
		name = na;
		treasure = t;
		Cashinvalue = v;
	}

	int getRow() {
		return r;
	}
	int getCol() {
		return c;
	}

	string getName() {
		return name;
	}

	bool isTreasure() {
		return treasure;
	}

	bool isHidden() {
		return hidden;
	}

	bool isObtained() {
		return obtained;
	}


	void reveal() {
		hidden = false;
	}

	void obtain() {
		obtained = true;
	}

	void hide() {
		hidden = true;
	}

	void cashout() {
		cashedout = true;
	}
	string getname() {
		return name;
	}

	int getvalue() {
		return Cashinvalue;
	}
};

class Grid {
private:
	int rows;
	int cols;
	vector<vector<char>> grid;
	vector<Object> objects;
	string Objectnames[6]{ "Aquaman's Trident: A mythical object said to be belonged to the king of the ocean", "Shrimp Fossil: It has been preserved for millions of years beneath the ocean", "Pirate Skull: The skull of a pirate who met his fate while searching for treasure", "Shipwreck : remains of a ship deep in the sea", "Compass: An old compass that points an unknown direction", "Old Treasure map: A torn map hinting to a long lost treasure" };
	//string ObjectInformaiton[6]{};


public:
	Grid(int r, int c) {
		rows = r;
		cols = c;
		grid = vector<vector<char>>(rows, vector<char>(cols, '.'));
	}



	void printGrid(int Sr, int Sc) {
		//Function below makes the full grid
		for (int i = 0; i < grid.size(); i++) {

			for (int j = 0; j < grid[i].size(); j++) {


				if (i == 0 && grid[i][j] == '.') {
					grid[i][j] = '~';
				}
				if (j == 0 || j == 11) {
					grid[i][j] = '#';
				}
				if (i == 10) {
					grid[i][j] = '#';

				}
			}
		}

		int camleft = Sr - 2;
		int camup = Sc - 2;

		if (camleft < 0) {
			camleft = 0;
		}
		if (camup < 0) {
			camup = 0;
		}
		if (camleft > rows - 5) {
			camleft = rows - 5;
		}
		if (camup > cols - 5) {
			camup = cols - 5;
		}



		//Function below is used to print the grid
		for (int r = camleft; r < camleft + 5; r++) {

			for (int c = camup; c < camup + 5; c++) {

				for (int i = 0; i < objects.size(); i++) {

					if (objects[i].getRow() == r && objects[i].getCol() == c && !objects[i].isObtained() && grid[r][c] != '@') {
						if (objects[i].isTreasure()) {
							grid[r][c] = '$';
						}
						else {
							grid[r][c] = '!';
						}
					}


				}

				cout << grid[r][c] << " ";

			}

			cout << "\n";
		}
	}
	/*
	void printGrid() {
		//Function below makes the full grid
		for (int i = 0; i < grid.size(); i++) {

			for (int j = 0; j < grid[i].size(); j++) {


				if (i == 0 && grid[i][j] == '.') {
					grid[i][j] = '~';
				}
				if (j == 0 || j == 11) {
					grid[i][j] = '#';
				}
				if (i == 10) {
					grid[i][j] = '#';

				}
			}
		}

		//Function below is used to print the grid
		for (int r = 0; r < rows; r++) {

			for (int c = 0; c < cols; c++) {

				for (int i = 0; i < objects.size(); i++) {

					if (objects[i].getRow() == r && objects[i].getCol() == c && !objects[i].isObtained()) {
						if (objects[i].isTreasure()) {
							grid[r][c] = '$';
						}
						else {
							grid[r][c] = '!';
						}
					}


				}

				cout << grid[r][c] << " ";

			}

			cout << "\n";
		}
	}
	*/

	void Gridsetter(int r, int c, char v) {
		grid[r][c] = v;
	}


	char Gridgetter(int r, int c) {
		return grid[r][c];
	}

	void RandomWalls() {
		for (int i = 0; i < 5; i++) {
			int num = rand() % 4 + 2;
			int x = rand() % 9 + 1;
			int y = rand() % 10 + 1;
			int direction = rand() % 4;

			for (int j = 0; j < num; j++) {
				if (direction == 0) {
					if (y > 10) {
						break;
					}
					grid[x][y] = '*';
					y++;
				}
				else if (direction == 1) {
					if (y < 1) {
						break;
					}
					grid[x][y] = '*';
					y--;
				}
				else if (direction == 2) {
					if (x < 2) {
						break;
					}
					grid[x][y] = '*';
					x--;
				}
				else if (direction == 3) {
					if (x > 9) {
						break;
					}
					grid[x][y] = '*';
					x++;
				}
			}

		}
	}

	void randomKelp() {
		for (int i = 0; i < 2; i++) {
			int column = rand() % 10 + 1;
			grid[8][column] = '|';
			grid[9][column] = '|';

		}

	}

	void RandomTreasures() {
		int treasures = rand() % 3 + 3;

		string Treasurenames[5] = { "Diamond gem", "Gold coin", "Ruby jewel", "Rare Pearl", "Emerald" };
		int Treasurevalues[5] = { 100, 25, 50, 15, 75 };

		while (treasures > 0) {
			int x = rand() % 8 + 1;
			int y = rand() % 10 + 1;

			if (grid[x][y] == '.') {
				int random = rand() % 5;
				//grid[x][y] = '$';

				treasures--;
				objects.push_back(Object(x, y, Treasurenames[random], true, Treasurevalues[random]));

			}


		}


	}

	void RandomObjects() {
		int objectstoplace = rand() % 3 + 3;

		while (objectstoplace > 0) {
			int x = rand() % 8 + 1;
			int y = rand() % 10 + 1;
			if (grid[x][y] == '.') {
				//grid[x][y] = '!';

				int randomobject = rand() % 6;
				objectstoplace--;
				objects.push_back(Object(x, y, Objectnames[randomobject], false, 0));

			}


		}

	}


	vector<Object> inspect(int Sr, int Sc) {
		vector<Object> Treasuref;
		for (int i = 0; i < objects.size(); i++) {
			if (abs(objects[i].getRow() - Sr) <= 1 && abs(objects[i].getCol() - Sc) <= 1) {
				if (objects[i].isTreasure()) {
					if (!objects[i].isObtained()) {
						objects[i].reveal();
						objects[i].obtain();
						cout << "You collected a " << objects[i].getname() << " that is worth " << objects[i].getvalue();
						cout << endl;
						Treasuref.push_back(objects[i]);

					}
				}

				else {
					objects[i].reveal();
					cout << "You came accross a " << objects[i].getName() << endl;
					cout << endl;

				}

			}
		}
		return Treasuref;
	}

	void collect() {
		for (int i = 0; i < objects.size(); i++) {

			if (objects[i].isTreasure() && objects[i].isObtained()) {
				if (grid[objects[i].getRow()][objects[i].getCol()] != '@') {
					grid[objects[i].getRow()][objects[i].getCol()] = '.';
					objects[i].hide();
					cout << endl;
				}


			}
		}
	}

	bool isWall(int r, int c) {
		char w = grid[r][c];
		if (w == '#') {
			return true;
		}
		else if (w == '*') {
			return true;
		}
		else if (w == '|') {
			return true;
		}
		return false;
	}


	string NameofWal(int r, int c) {
		if (grid[r][c] == '*') {
			return "Coral reef";
		}
		else if (grid[r][c] == '#') {
			return "Wall";
		}
		else if (grid[r][c] == '|') {
			return "Kelp";
		}
		return "Wall";
	}
};








class Submarine {
private:
	int r;
	int c;
	int oxygen;
	vector<Object> treasuresfound;
	int totalcash;


public:
	Submarine(int ro, int co, int o) {
		r = ro;
		c = co;
		oxygen = o;
	}


	//position of submarine on the board
	//Oxygen tank 
	//treasures stored

	int getRow() const {
		return r;
	}
	int getCol() const {
		return c;
	}

	void down() {
		r++;
	}

	void up() {
		r--;
	}

	void left() {
		c--;
	}

	void right() {
		c++;
	}

	void looseoxygen() {
		oxygen -= 5;
	}

	bool outofoxygen() {
		if (oxygen <= 0) {
			return true;
		}
		return false;
	}
	void addTreasure(Object t) {
		treasuresfound.push_back(t);
	}

	vector<Object> Treasuresgotten() {
		return treasuresfound;
	}

	void Emptybag() {

		vector<Object> New;
		treasuresfound = New;

	}

	int getOxygen() {
		return oxygen;
	}

	void resetOxygen() {
		oxygen = 100;
	}
};






void game() {
	//vector<vector<char>> Grid(11, vector<char>(12, '.'));

	Grid gameboard(11, 12);
	gameboard.RandomWalls();
	gameboard.randomKelp();
	gameboard.RandomTreasures();
	gameboard.RandomObjects();
	Submarine S(0, 5, 100);
	gameboard.Gridsetter(S.getRow(), S.getCol(), '@');
	gameboard.printGrid(S.getRow(), S.getCol());
	int TotalEarnings = 0;
	//vec(Objects) total
	vector<Object> Totaltreasures;
	cout << "Oxygen: " << S.getOxygen() << "/100" << endl;



	while (!S.outofoxygen()) {
		cout << "Type; W,A,S,D to move or i to inspect: " << endl;


		string input;
		getline(cin, input);
		cout << "======================================================" << endl;

		if (input.length() != 1) {
			cout << "Enter only one letter" << endl;
			continue;
		}
		//cin >> input;
		cout << endl;

		input = tolower(input[0]);
		if (input != "i" && input != "w" && input != "s" && input != "a" && input != "d") {
			cout << "Invalid character was entered, Please enter a valid character " << endl;

		}

		if (input == "i") {

			vector<Object> foundtreasures = gameboard.inspect(S.getRow(), S.getCol());

			for (Object treasure : foundtreasures) {
				S.addTreasure(treasure);
			}

			gameboard.collect();





		}
		else if (input == "s" && (!gameboard.isWall(S.getRow() + 1, S.getCol()))) {
			gameboard.collect();
			gameboard.Gridsetter(S.getRow(), S.getCol(), '.');

			S.down();
			gameboard.Gridsetter(S.getRow(), S.getCol(), '@');
			S.looseoxygen();

		}
		else if (input == "d" && (!gameboard.isWall(S.getRow(), S.getCol() + 1))) {
			gameboard.collect();

			gameboard.Gridsetter(S.getRow(), S.getCol(), '.');
			S.right();
			gameboard.Gridsetter(S.getRow(), S.getCol(), '@');
			S.looseoxygen();

		}
		else if (input == "w" && S.getRow() > 0 && (!gameboard.isWall(S.getRow() - 1, S.getCol()))) {
			gameboard.collect();

			gameboard.Gridsetter(S.getRow(), S.getCol(), '.');

			S.up();
			gameboard.Gridsetter(S.getRow(), S.getCol(), '@');
			S.looseoxygen();

		}
		else if (input == "a" && (!gameboard.isWall(S.getRow(), S.getCol() - 1))) {
			gameboard.collect();

			gameboard.Gridsetter(S.getRow(), S.getCol(), '.');

			S.left();
			gameboard.Gridsetter(S.getRow(), S.getCol(), '@');
			S.looseoxygen();

		}
		else if (input == "w" && S.getRow() == 0) {

			cout << "Oops, you are at the surfaces. Try again:" << endl;
		}
		else {
			if (input == "s") {
				cout << "Oops, you hit a " << gameboard.NameofWal(S.getRow() + 1, S.getCol()) << "! Pick a different direction" << endl;
			}
			else if (input == "w") {
				cout << "Oops, you hit a " << gameboard.NameofWal(S.getRow() - 1, S.getCol()) << "! Pick a different direction" << endl;
			}if (input == "d") {
				cout << "Oops, you hit a " << gameboard.NameofWal(S.getRow(), S.getCol() + 1) << "! Pick a different direction" << endl;
			}if (input == "a") {
				cout << "Oops, you hit a " << gameboard.NameofWal(S.getRow(), S.getCol() - 1) << "! Pick a different direction" << endl;
			}
		}
		if (S.getRow() == 0 && S.Treasuresgotten().size() > 0) {
			vector<Object> Currenttreasures = S.Treasuresgotten();
			S.Emptybag();
			cout << "Total Treasures collected:\n";
			//cout << endl;
			int DescentEarnings = 0;
			for (int i = 0; i < Currenttreasures.size(); i++) {

				Totaltreasures.push_back(Currenttreasures[i]);
				//cout << Totaltreasures[i].getname() << " which is worth $" << Totaltreasures[i].getvalue() << "\n";
				TotalEarnings += Currenttreasures[i].getvalue();
				DescentEarnings += Currenttreasures[i].getvalue();


			}
			for (int i = 0; i < Totaltreasures.size(); i++) {
				cout << "    . A " << Totaltreasures[i].getname() << " which is worth $" << Totaltreasures[i].getvalue() << "\n";

			}
			cout << endl;
			cout << "Earnings this descent: $" << DescentEarnings << endl;

			cout << endl;
			cout << "Total Earnings: $" << TotalEarnings << endl;
			cout << endl;

		}

		gameboard.printGrid(S.getRow(), S.getCol());
		cout << endl;
		if (S.getRow() == 0) {
			S.resetOxygen();
			cout << "Your oxygen tank is full!" << endl;
		}
		cout << "Oxygen: " << S.getOxygen() << "/100" << endl;

	}

	cout << "Your oxygen tank is empty, you Lost!" << endl;
	cout << endl;
}







int main() {
	srand(time(0));
	bool playing = true;

	while (playing) {
		cout << "Main Menu:" << endl;
		cout << endl;
		cout << "1) Start Game" << endl;
		cout << "2) Exit Game" << endl;

		string input;
		getline(cin, input);

		if (input == "1") {
			game();

		}
		else if (input == "2") {
			return 0;
		}
		else {
			cout << "Enter either 1 or 2" << endl;

		}
	}




	//Submarine S(0, 4, 20);
	//gameboard.printGrid(S.getRow(), S.getCol()); Just working on initiating the submarine on the map right now






}






//quest






