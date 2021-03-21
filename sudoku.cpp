#include <iostream>
#include <string>
using namespace std;

struct Square {
	bool mozliwosci[10];
	int ile_mozliwosci;
	int wynik;
};

int error = 0;
int licznik = 1;

void SetConstraint(Square S[10][10], int x, int y, int v) {
	S[x][y].mozliwosci[v] = false;
	S[x][y].ile_mozliwosci--;
	if (S[x][y].ile_mozliwosci == 0) {
		error = 1;
	}
}

int FindResult(bool w[10]) {
	for (int i = 1; i < 10; i++)
		if (w[i] == true)
			return i;
	return 0;
}

void SetResult(Square S[10][10], int x, int y, int v) {
	for (int i = 1; i < 10; i++)
		S[x][y].mozliwosci[i] = false;
	S[x][y].mozliwosci[v] = true;
	S[x][y].ile_mozliwosci = 1;
	S[x][y].wynik = v;
}

void ConstraintPropagation(Square S[10][10], int x, int y, int v) {

	//if (error == 1) return;

	SetResult(S, x, y, v);

	//dla wiersza

	for (int i = 1; i < 10; i++) {
		if (i != y) {
			if (S[x][i].mozliwosci[v] == true) {

				SetConstraint(S, x, i, v);

				if (error == 1) return;

				if (S[x][i].ile_mozliwosci == 1)
					ConstraintPropagation(S, x, i, FindResult(S[x][i].mozliwosci));

				if (error == 1) return;
			}
		}
	}

	//dla kolumny

	for (int i = 1; i < 10; i++) {
		if (i != x) {
			if (S[i][y].mozliwosci[v] == true) {

				SetConstraint(S, i, y, v);

				if (error == 1) return;

				if (S[i][y].ile_mozliwosci == 1)
					ConstraintPropagation(S, i, y, FindResult(S[i][y].mozliwosci));

				if (error == 1) return;
			}
		}
	}

	//dla kwadratu

	for (int i = (((x - 1) / 3) * 3) + 1; i < (((x - 1) / 3) * 3) + 4; i++) {
		for (int j = (((y - 1) / 3) * 3) + 1; j < (((y - 1) / 3) * 3) + 4; j++) {
			if ((i != x) && (j != y)) {
				if (S[i][j].mozliwosci[v] == true) {

					SetConstraint(S, i, j, v);

					if (error == 1) return;

					if (S[i][j].ile_mozliwosci == 1)
						ConstraintPropagation(S, i, j, FindResult(S[i][j].mozliwosci));

					if (error == 1) return;
				}
			}
		}
	}
}

//znajduje kwadracik, a którym jest najmniej mo¿liwoœci wstawienia cyfry

void FindMinPoss(Square S[10][10], int &x, int &y, int &minimum) {
	minimum = 9;
	for (int i = 1; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			if ((S[i][j].ile_mozliwosci < minimum) && (S[i][j].ile_mozliwosci > 1)) {
				minimum = S[i][j].ile_mozliwosci;
				x = i;
				y = j;
			}
		}
	}
}

bool IsSolved(Square S[10][10]) {
	int IsIt = 0;
	for (int i = 1; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			if (S[i][j].wynik != 0)IsIt++;
		}
	}
	if (IsIt == 81)return true;
	else return false;
}

void Solve(Square S[10][10]) {
	if (IsSolved(S) == true)return;
	int x, y, ile_moz;
	FindMinPoss(S, x, y, ile_moz);

	Square S0[10][10];

	for (int i = 1; i < 10; i++) {

		if (S[x][y].mozliwosci[i] == true) {

			//tworzenie kopii oryginalnej tablicy sudoku
			for (int j = 1; j < 10; j++) {
				for (int k = 1; k < 10; k++) {
					S0[j][k] = S[j][k];
				}
			}

			licznik++;

			ConstraintPropagation(S0, x, y, i);

			if (error == 0) {
				if (IsSolved(S0) == false) {
					Solve(S0);
					if (IsSolved(S0) == true)
						break;
				}
				else {
					break;
				}
			}
			else {
				error = 0;
				ile_moz--;
				S[x][y].ile_mozliwosci--;
				S[x][y].mozliwosci[i] = false;
			}
		}
	}
	if (ile_moz != 0) {
		for (int j = 1; j < 10; j++) {
			for (int k = 1; k < 10; k++) {
				S[j][k] = S0[j][k];
			}
		}
	}
}

void Initialize(Square S[10][10]) {
	for (int i = 1; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			for (int k = 1; k < 10; k++) {
				S[i][j].mozliwosci[k] = true;
			}
			S[i][j].ile_mozliwosci = 9;
			S[i][j].wynik = 0;
		}
	}
}

void Read(Square S[10][10]) {

	string s;
	cin >> s;
	int ss = 0;

	for (int i = 1; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			if ((s[ss] > 48) && (s[ss] < 58))
				ConstraintPropagation(S, i, j, s[ss] - 48);
			ss++;
		}
	}
}

void Write(Square S[10][10]) {
	for (int i = 1; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			for (int k = 1; k < 10; k++) {
				if (S[i][j].mozliwosci[k] == true)
					cout << k;
			}
			cout << ",";
		}
		cout << endl;
	}
}

int main() {

	Square Sudoku[10][10];

	while (1) {
		Initialize(Sudoku);
		Read(Sudoku);
		Solve(Sudoku);
		Write(Sudoku);
		cout << "Ilosc iteracji: "<<licznik << endl << endl;
		licznik = 1;
	}

	system("pause");
	return 0;
}