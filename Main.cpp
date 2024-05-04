#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
using namespace std;
char world[20][40];
const int PlayerCnt = 10;
char Source[PlayerCnt] = {'M', '%', '@', 'V', 'H', 'A', 'S', 'D', 'W', 'O'};
int MobX[PlayerCnt];
int MobY[PlayerCnt];
bool Alive[PlayerCnt];
bool Evil[PlayerCnt];
bool played = 0, Killing;
int CrewLeft, ImposterLeft;
bool Restart = 0, Reported;
string str;
void load() {
	srand(time(0));
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 40; j++) {
			if (i == 0 || i == 19 || j == 0 || j == 39) {
				world[i][j] = '#';
			} else world[i][j] = ' ';
		}
	}
	for (int i = 0; i < PlayerCnt; i++) {
		Evil[i] = 0;
		Alive[i] = 1;
		MobX[i] = rand() % 36 + 1;
		MobY[i] = rand() % 16 + 1;
	}
	for (int i = 0; i < 3; i++)Evil[rand() % PlayerCnt] = 1;
}

void Report(int num) {
	system("cls");
	cout << "No." << num << " made a emergency meeting" << endl;
	cout << "Conversation is going to start" << endl;
	cout << "_______________________________" << endl;
	srand(time(0));
	int cnt = rand() % 10 + 3, r = rand() % 20 * 100;
	for (int i = 0; i < cnt; i++) {
		cout << "No." << rand() % 9 + 1 << " : ";
		if (rand() % 2 == 0) {
			if (rand() % 2 == 0) {
				cout << "Why someone called a report again?!" << endl;
			} else {
				cout << "Darn!" << endl;
			}
		} else {
			if (rand() % 2 == 0) {
				cout << "He's lying!" << endl;
			} else {
				cout << "I think I know who's the imposter" << endl;
			}
		}
		Sleep(r);
		r = rand() % 20 * 100;
	}
	system("cls");
	cout << "Voting" << endl;
	cout << "_________________________" << endl;
	for (int i = 0; i < 9; i++) {
		cout << "No." << i + 1 << " has voted" << endl;
		r = rand() % 20 * 100;
		Sleep(r);
	}
	cin >> cnt;
	if (rand() % 5 == 0) {
		cout << "No." << cnt << " was thrown out of the ship" << endl;
		Alive[cnt - 1] = 0;
	} else {
		cnt = rand() % 10 + 1;
		cout << "No." << cnt << " was thrown out of the ship" << endl;
		Alive[cnt - 1] = 0;
	}
	Sleep(3000);
}
void TryMove() {
	char key;
	key = 0;
	Killing = 0;
	if (_kbhit() && Alive[9] == 1) {
		key = getch();
		if (key == 'w' && MobY[PlayerCnt - 1] < 18)MobY[PlayerCnt - 1]++;
		if (key == 's' && MobY[PlayerCnt - 1] > 1)MobY[PlayerCnt - 1]--;
		if (key == 'a' && MobX[PlayerCnt - 1] > 1)MobX[PlayerCnt - 1]--;
		if (key == 'd' && MobX[PlayerCnt - 1] < 38)MobX[PlayerCnt - 1]++;
		if (key == 'r' && Reported == 0)Report(10);
		if (key == ' ' && Alive[9] == 0)Restart = 1;
	}
}
void Kill() {
	srand(time(0));
	for (int i = 0; i < 9; i++) {
		for (int j = i + 1; j < 10; j++) {
			if (MobX[i] == MobX[j] && MobY[i] == MobY[j] && rand() % 2 == 0) {
				if (Evil[i] == 1 && rand() % 2 == 0 && Alive[i] == 1) {
					Alive[j] = 0;
					Source[j] = 'X';
				}
				if (Evil[j] == 1 && Alive[j] == 1) {
					if (j == 10 && Killing == 1) {
						Alive[i] = 0;
						Source[i] = 'X';
					} else if (rand() % 2 == 0) {
						Alive[i] = 0;
						Source[i] = 'X';
					}
				}
			}
		}
	}
	if (Alive[9] == 0)Source[9] = 'X';
}
void BodyReport() {
	srand(time(0));
	int cnt = rand() % 10 + 3, r = rand() % 20 * 100;
	for (int i = 0; i < 9; i++) {
		for (int j = i + 1; j < 10; j++) {
			if (MobX[j] == MobX[i] && MobY[j] == MobY[i]) {
				if (Source[i] == 'X' && Evil[j] == 0) {
					Source[i] = '+';
					system("cls");
					cout << "No." << j << " found the dead body of No." << i << "!" << endl;
					cout << "Conversation is going to start" << endl;
					int r = 100;
					cout << "____________________________________" << endl;
					Sleep(1000);
					for (int i = 0; i < cnt; i++) {
						cout << "No." << rand() % 9 + 1 << " : ";
						if (rand() % 2 == 0) {
							if (rand() % 2 == 0) {
								cout << "I'm not doing anything!";
							} else {
								if (rand() % 2 == 0) {
									cout << "What's our disicion?";
								} else {
									cout << "I have no idea...";
								}
							}
						} else {
							if (rand() % 2 == 0) {
								cout << "I guess No." << rand() % 10 + 1 << " is the imposter!";
							} else {
								if (rand() % 2 == 0) {
									cout << "Vote No." << rand() % 10 + 1 << "! I saw him killing No." << rand() % 10 + 1;
								} else {
									cout << "So which crew should we pick?";
								}

							}
						}
						// cout<<"";
						cout << endl;
						Sleep(r);
						r = rand() % 20 * 100;
					}
					cout << "Your turn:" << endl;
					str = "1";
					getline(cin, str);
					if (rand() % 2 == 0) {
						cout << "No." << rand() % 10 + 1 << " : " << "Hmmmm, I agree with you";
					}
					system("cls");
					cout << endl << endl << "Press any key to vote" << endl;
					for (int i = 0; i < 9; i++) {
						cout << "No." << i + 1 << " has voted" << endl;
						r = rand() % 20 * 100;
						Sleep(r);
					}
					cin >> cnt;
					if (rand() % 5 == 0) {
						cout << "No." << cnt << " was thrown out of the ship" << endl;
						Alive[cnt - 1] = 0;
						Source[i] = '+';
					} else {
						cnt = rand() % 10 + 1;
						cout << "No." << cnt << " was thrown out of the ship" << endl;
						Alive[cnt - 1] = 0;
						Source[i] = '+';
					}
					//MobX[9]++;\]
					Sleep(3000);
				}
				if (Source[j] == 'X' && Evil[i] == 0) {
					Source[j] = '+';
					system("cls");
					cout << "No." << i << " found the dead body of No." << j << "!" << endl;
					cout << "Conversation is going to start" << endl;
					int r = 100;
					cout << "____________________________________" << endl;
					Sleep(1000);
					for (int i = 0; i < cnt; i++) {
						cout << "No." << rand() % 9 + 1 << " : ";
						if (rand() % 2 == 0) {
							if (rand() % 2 == 0) {
								cout << "I'm not doing anything!";
							} else {
								if (rand() % 2 == 0) {
									cout << "What's our disicion?";
								} else {
									cout << "I have no idea...";
								}
							}
						} else {
							if (rand() % 2 == 0) {
								cout << "I guess No." << rand() % 10 + 1 << " is the imposter!";
							} else {
								if (rand() % 2 == 0) {
									cout << "Vote No." << rand() % 10 + 1 << "! I saw him killing No." << rand() % 10 + 1;
								} else {
									cout << "So which crew should we pick?";
								}

							}
						}
						// cout<<"";
						cout << endl;
						Sleep(r);
						r = rand() % 20 * 100;
					}
					cout << "Your turn:" << endl;
					str = "1";
					getline(cin, str);
					if (rand() % 2 == 0) {
						cout << "No." << rand() % 10 + 1 << " : " << "Hmmmm, I agree with you";
					}
					system("cls");
					cout << endl << endl << "Press any key to vote" << endl;
					for (int i = 0; i < 9; i++) {
						cout << "No." << i + 1 << " has voted" << endl;
						r = rand() % 20 * 100;
						Sleep(r);
					}
					cin >> cnt;
					if (rand() % 5 == 0) {
						cout << "No." << cnt << " was thrown out of the ship" << endl;
						Alive[cnt - 1] = 0;
						Source[j] = '+';
					} else {
						cnt = rand() % 10 + 1;
						cout << "No." << cnt << " was thrown out of the ship" << endl;
						Alive[cnt - 1] = 0;
						Source[j] = '+';
					}
					//MobX[9]++;\]
					Sleep(3000);
				}
			}
		}

	}
}
void MobUpdate() {
	TryMove();
	srand(time(0));
	if (rand() % 30 == 0) {
		Report(rand() % 10 + 1);
	}
	for (int i = 0; i < PlayerCnt - 1; i++) {
		if (Alive[i] == 1) {
			if (rand() % 3 == 0)MobX[i] += rand() % 3 - 1;
			if (rand() % 3 == 0)MobY[i] += rand() % 3 - 1;
		}
		if (MobX[i] < 1)MobX[i] = 1;
		if (MobX[i] > 38)MobX[i] = 38;
		if (MobY[i] < 1)MobY[i] = 1;
		if (MobY[i] > 18)MobY[i] = 18;
	}
	Kill();
	BodyReport();
}
void CheckAlive() {
	CrewLeft = 0;
	for (int i = 0; i < 10; i++) {
		if (Source[i] != 'X')CrewLeft++;
	}
	ImposterLeft = 0;
	for (int i = 0; i < 10; i++) {
		if (Evil[i] == 1 && Source[i] != 'X')ImposterLeft++;
	}
}
void ScreenUpdate() {
	MobUpdate();
	system("cls");
	bool x = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 40; j++) {
			//cout<<world[i][j];
			x = 0;
			for (int k = 0; k < PlayerCnt; k++) {
				if (MobX[k] == j && 19 - MobY[k] == i) {
					x = 1;
					cout << Source[k];
					break;
				}
			}
			if (x == 0)cout << world[i][j];
		}
		cout << endl;
	}
	CheckAlive();
	cout << "Crews left: " << CrewLeft << "\tImposters left: " << ImposterLeft << endl;
	if (Evil[9] == 1)cout << "You're the imposter No.10" << endl;
	else cout << "You're the crew No.10" << endl;
	if (Alive[9] == 0) {
		char key;
		cout << "You're Dead" << endl << "Press space bar to restart";
	} else if (Reported == 0)cout << "You can Press R to report once" << endl;
	Sleep(200);
}
int main() {
	//{'M','%','@','V','H','A','S','D','W','O'}
	Restart = 0;
	Reported = 0;
	Source[0] = '1';
	Source[1] = '2';
	Source[2] = '3';
	Source[3] = '4';
	Source[4] = '5';
	Source[5] = '6';
	Source[6] = '7';
	Source[7] = '8';
	Source[8] = '9';
	Source[9] = 'O';
	system("cls");
	played = 1;
	load();
	//CrewLeft>3&&Evil[9]==1||ImposterLeft>0&&Evil[9]==0
	while (1) {
		ScreenUpdate();
		if (Restart == 1) {
			system("cls");
			cout << "Creating new game..." << endl << "Press any key to continue" << endl;
			load();
			getch();
			main();
		}
	}
	if (Evil[9] == 1)cout << "Imposter won!";
	else cout << "crew won!";
	cout << endl << "Press any key to restart" << endl << endl;
	getch();
	main();
}
