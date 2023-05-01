#include <iostream>
#include <fstream>

using namespace std;

void search(char* T, const int TROWS, const int TCOLS, char* P, const int PROWS, const int PCOLS);

int main()
{
	const int TROWS = 22;
	const int TCOLS = 13;
	const int PROWS = 3;
	const int PCOLS = PROWS;

	char* T = new char[TROWS * TCOLS];
	char* P = new char[PROWS * PCOLS];

	ifstream TFile;
	TFile.open("T.txt");
	int i = 0;
	while (!TFile.eof()) {
		char* temp = new char;
		*temp = TFile.get();
		if (*temp == '\t') {
			i++;
		}
		else if (*temp == '\n') {
			i++;
		}
		else if ((int)(*temp) >= 65 && (int)(*temp) <= 90) {
			T[i] = *temp;
		}
	}
	TFile.close();

	ifstream PFile;
	PFile.open("P.txt");
	i = 0;
	while (!PFile.eof()) {
		char* temp = new char;
		*temp = PFile.get();
		if (*temp == '\t') {
			i++;
		}
		else if (*temp == '\n') {
			i++;
		}
		else if ((int)(*temp) >= 65 && (int)(*temp) <= 90) {
			P[i] = *temp;
		}
	}
	PFile.close();
	search(T, TROWS, TCOLS, P, PROWS, PCOLS);
}

void search(char* T, const int TROWS, const int TCOLS, char* P, const int PROWS, const int PCOLS)
{
	int m = PROWS * PCOLS;
	int n = TROWS * TCOLS;

	int s = 0;
	int prevS = -1;
	bool firstS = false;
	int firstShift = -1;
	int shiftCount = 0;

	while (s <= (TROWS * TCOLS) - PROWS - (TCOLS * (PROWS - 1)))
	{
		if ((floor(s / TCOLS) + 1) * TCOLS < s + PCOLS) {
			s += PROWS - 1;
		}
		//if (s - (floor(s / TCOLS) * TCOLS) + PROWS >= TCOLS) {
		//	s += PROWS - 1;
		//}

		int j = m - 1;
		int k = 0;
		int count = 0;
		//cout << s << endl;
		while (j >= 0 && P[j] == T[(s + (PROWS - 1) + ((PCOLS - 1) * TCOLS)) - k - count]) {
			//cout << P[j] << " " << T[(s + (PROWS - 1) + ((PCOLS - 1) * TCOLS)) - k - count] << endl;
			count++;
			j--;
			if (count == PROWS) {
				k += TCOLS;
				count = 0;
			}
		}
		if (j < 0)
		{
			if (firstS == false) {
				firstShift = s;
			}
			firstS = true;
			shiftCount++;
			T[s] = NULL;

			if (prevS != -1 && (s - (floor(s / TCOLS) * TCOLS) > prevS - (floor(prevS / TCOLS) * TCOLS)) && (s - (floor(s / TCOLS) * TCOLS) <= prevS - (floor(prevS / TCOLS) * TCOLS) + PROWS)) {
				if (firstS == true) {

				}
			}
			prevS = s;
			s += (TCOLS * PCOLS) + 1;
			//s += (TCOLS * PCOLS) - (PCOLS - 1) + 1;
		}
		else {
			if (prevS != -1 && (s - (floor(s / TCOLS) * TCOLS) > prevS - (floor(prevS / TCOLS) * TCOLS)) && (s - (floor(s / TCOLS) * TCOLS) < prevS - (floor(prevS / TCOLS) * TCOLS) + PROWS)) {
				//cout << s << endl;
				int rowOfMismatch = floor(j / PCOLS);
				int lastOcc = -1;
				for (int i = 0, n = 0; i < PCOLS; i++, n++) {
					if (T[s + j] == P[rowOfMismatch * PCOLS + n]) {
						lastOcc = n;
					}
				}
				if (s + PCOLS >= TCOLS - 1) {
					//if ((s - (floor(s / TCOLS) * TCOLS)) + PCOLS > TCOLS) {
					s += 1;
				}
				else {
					if (lastOcc > 1) {
						cout << "p" << endl;
						s += lastOcc;
					}
					else {
						cout << "q" << endl;
						s += 1;
					}
				}
			}
			else if (shiftCount > 0) {
				//cout <<"s2 "<< s << endl;
				if (shiftCount > 1) {
					cout << "Pattern occurs at shift = " << floor(firstShift / TCOLS) << "," << firstShift - (floor(firstShift / TCOLS) * TCOLS) << endl;
				}

				s = firstShift + 1;

				firstS = false;
				shiftCount = 0;
				firstShift = -1;
				prevS = -1;
			}
			else {
				int rowOfMismatch = floor(j / PCOLS);
				int lastOcc = -1;
				for (int i = 0, n = 0; i < PCOLS; i++, n++) {
					if (T[s + j] == P[rowOfMismatch * PCOLS + n]) {
						lastOcc = n;
					}
				}
				//if ((s - (floor(s / TCOLS) * TCOLS)) + PCOLS > TCOLS) {
				if (s + PCOLS >= TCOLS - 1) {
					s += 1;
				}
				else {
					//if(lastOcc > 1)
					if (lastOcc > 1) {
						s += lastOcc;
					}
					else {
						s += 1;
					}
				}

			}
		}
	}
	if (shiftCount > 1) { //for the occurence on the lowest row
		cout << "Pattern occurs at shift = " << floor(firstShift / TCOLS) << "," << firstShift - (floor(firstShift / TCOLS) * TCOLS) << endl;
	}
}