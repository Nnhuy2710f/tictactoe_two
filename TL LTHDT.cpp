#include <iostream> // thu vien ho tro nhap xuat 
#include <stdexcept> //thu vien ho tro kiem tra cac nuoc di loi 
#include <ctime> // thu vien ho tro tao ra cac buoc di ngau nhien cua computer
#include <cstdlib> //thu vien ho tro tao ra cac thanh phan an phim 
#include <bits/stdc++.h> // thu vien cung cap cac thu vien phuc vu cho chuc nang duyet xau cua chuong trinh
#include <windows.h> // thu vien ho tro color
using namespace std;
// Xay dung class Board de thiet ke khung cua tro choi
class Board {
    char arr[3][3]; // Khoi tao mang 2 chieu kiem soat board game
public:
	// Khoi tao Board game
    Board() {
        clearBoard();
    }
    // Ham bo tro thiet ke va quan ly su thay doi cua tro choi
    // Ham clearBoard su dung de xoa noi dung cua bang choi bang cach gan moi o cua bang thanh dau gach ngang (“-”). 
    void clearBoard() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                arr[i][j] = '-';
            }
        }
    }
    // Ham displayBoard su dung de in ra noi dung cua bang choi, hien thi bang duoi dang 3x3 voi cac dau gach ngang va cac ky tu (X, O hoac -) tuong ung
    void display_Board() {
    	cout << '\n';
    	cout << "  -------------------------------------------" << '\n';
    	for (int i = 0; i < 3; ++i) {
        	cout << "  | ";
        	for (int j = 0; j < 3; ++j) {
            	cout << arr[i][j] << "           | ";
        	}
        	cout << '\n';
        	cout << "  -------------------------------------------" << '\n';
        	           
    	}
    	
	}
	// Ham checkWinner duoc su dung de kiem tra xem nguoi chien thang sau moi luot danh
    char checkWinner() {
        for (int i = 0; i < 3; ++i) {
            if (arr[i][0] != '-' && arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2]) {
                return arr[i][0];
            }
        }
        for (int i = 0; i < 3; ++i) {
            if (arr[0][i] != '-' && arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i]) {
                return arr[0][i];
            }
        }
        if (arr[0][0] != '-' && arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2]) {
            return arr[0][0];
        }
        if (arr[0][2] != '-' && arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0]) {
            return arr[0][2];
        }
        return '-';
    }
    	//Ham symbol duoc su dung de danh dau mot ky tu vao o cua bang voi vi tri duoc chi dinh boi hang row va cot col
    bool symbol(int row, int col, char symbol) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || arr[row][col] != '-') {
            return false;
        }
        arr[row][col] = symbol;
        return true;
    }
	// check_full duoc su dung de kiem tra xem bang da day chua
    bool check_full() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (arr[i][j] == '-') {
                    return false;
                }
}
        }
        return true;
    }
};
// Xay dung class Player de xac dinh nguoi choi la human hoac computer
class Player {
protected:
    char symbol;
public:
	// Khoi tao
    Player(char m) : symbol(m) {} 
    virtual void makeMove(Board& board) = 0;// Ham ao duoc trien khai trong cac lop con de thuc hien cac nuoc di cua nguoi choi
};
// Xay dung class HumanPlayer ke thua tu lop Player
class HumanPlayer : public Player {
public:
	// Khoi tao
    HumanPlayer(char t) : Player(t) {}
    // Ham bo tro
    //  Ham makeMove yeu cau nguoi choi nhap 1-9 tuong ung cac vi tri tren bang de danh dau. No kiem tra tinh hop le cua nuoc di 
    void makeMove(Board& board) override { 
        int pos;
        while (true) {
        cout << "Enter your move (1 -> 9): ";
        if (!(cin >> pos)) { 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input, Please enter a number." << endl;
            continue; 
        }
        if (pos < 1 || pos > 9) { 
            cout << "Invalid move, Please enter a number from 1 to 9." << endl;
            continue; 
        }
        int row = (pos - 1) / 3;
        int col = (pos - 1) % 3;
        if (!board.symbol(row, col, symbol)) { 
          	cout << "This position is already taken. Please choose another one." << endl;
            continue; 
        }
        	break; 
    	}
    }
};
//***Xay dung class ComputerPlayer ke thua tu lop Player***//
class ComputerPlayer : public Player {
public:
	// Khoi tao
    ComputerPlayer(char t) : Player(t) {}
    // Ham bo tro
    // Ham makeMove tao ra mot nuoc di ngau nhien cho nguoi choi may tinh bang cach chon mot hang va cot ngau nhien tren bang va dat ky tu vao o do
	 
    void makeMove(Board& board) override {
        int row, col;
        do {
            row = rand() % 3;
            col = rand() % 3;
        } while (!board.symbol(row, col, symbol));
    }
};
//***Xay dung class Game de quan ly che do cua game***//
class Game {
    Board board;
    Player* player1;
    Player* player2;
    // ham bo tro 
    // tinh turn player1 va player2
    void switchPlayers(Player*& current) {
        if (current == player1) {
            current = player2;
        } else {
            current = player1;
        }
    }

public:
	// Khoi tao
    Game(Player* p1, Player* p2) : player1(p1), player2(p2) {}
	// Ham bo tro
	// Ham play dieu khien luot choi cua tro choi Tic Tac Toe.
    void play() {
        Player* current = player1;
        while (1) {
        	Set_colorGame(1);
            cout << "Tic Tac Toe ";
			
			cout << "3x3" << endl;Set_colorGame(7);
            board.display_Board();
            cout << endl;

            try {
                current->makeMove(board);
			} 
			catch (const invalid_argument& e) {
                cerr << "Error: " << e.what() << endl;
                continue;
            }

            char winner = board.checkWinner();
            if (winner != '-') {
            	Set_colorGame(3);
                cout << "Winner is: " << winner << endl;Set_colorGame(7);
                board.display_Board();
                break;
            } else if (board.check_full()) {
            	Set_colorGame(3);
                cout << "TIE!" << endl;Set_colorGame(7);
                board.display_Board(); 
                break;
            }
			
            switchPlayers(current);
        }
    }
    // xay dung color chu trong class Game
    void Set_colorGame(int color) {
    	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    	SetConsoleTextAttribute(hConsole, color);
	}
};

void Menu() {
    cout << "-----------[X] Tic Tac Toe Game [O]------------" << endl;
    cout << "|           1. Play against Computer          |" << endl;
    cout << "|           2. Play with a Friend             |" << endl;
    cout << "|           3. Computer vs Computer           |" << endl;
    cout << "|           4. How to play                    |" << endl;
    cout << "|           5. Game information               |" << endl;
    cout << "|           6. Exit Game                      |" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << endl;
}

int main() {
    srand(time(NULL));
    char choice; // tao ra bien de lua chon cac muc trong menu gameplay
    while (1) {
    	Menu();
    	
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case '1': {
            	cout << "Human vs Computer"<< endl;
            	char mark1, mark2;
            	bool checkSymbol1 = true;
            	bool checkSymbol2 = true;
				cout << "Player 1(X/O): ";
				cin >> mark1;
            	while (checkSymbol1){
            		if(mark1 != 'X' && mark1 != 'O'){
            			cout << "Invalid symbol! Please select again! Player 1: ";
            			cin >> mark1;
					} else {
						break;
					} 
				}
				cout << "Player 2(X/O): ";
				cin >> mark2;
				while (checkSymbol2){
            		if(mark2 != 'X' && mark2 != 'O' || mark2 == mark1){
            			cout << "Invalid symbol! Please select again! Player 2: ";
            			cin >> mark2;
					} else {
						break;
					} 
				}
            	if (mark1 == 'X' && mark2 == 'O'){
            		HumanPlayer player1('X');
                	ComputerPlayer player2('O');
                	Game game(&player1, &player2);
                	game.play();
				} else if (mark1 == 'O' && mark2 == 'X'){
					HumanPlayer player1('O');
                	ComputerPlayer player2('X');
                	Game game(&player2, &player1);
                	game.play();
				} 
                break;
            }
            case '2': {
            	cout << "Human1 vs Human2"<< endl;
                char mark1, mark2;
            	bool checkSymbol1 = true;
            	bool checkSymbol2 = true;
				cout << "Player 1(X/O): ";
cin >> mark1;
            	while (checkSymbol1){
            		if(mark1 != 'X' && mark1 != 'O'){
            			cout << "Invalid symbol! Please select again! Player 1: ";
            			cin >> mark1;
					} else {
						break;
					} 
				}
				cout << "Player 2(X/O): ";
				cin >> mark2;
				while (checkSymbol2){
            		if(mark2 != 'X' && mark2 != 'O' || mark2 == mark1){
            			cout << "Invalid symbol! Please select again! Player 2: ";
            			cin >> mark2;
					} else {
						break;
					} 
				}
            	if (mark1 == 'X' && mark2 == 'O'){
            		HumanPlayer player1('X');
                	HumanPlayer player2('O');
                	Game game(&player1, &player2);
                	game.play();
				} else if (mark1 == 'O' && mark2 == 'X'){
					HumanPlayer player1('O');
                	HumanPlayer player2('X');
                	Game game(&player2, &player1);
                	game.play();
				} 
                break;
            }
            case '3':{
            	cout << "Computer1 vs Computer2" << endl;
            	char mark1, mark2;
            	bool checkSymbol1 = true;
            	bool checkSymbol2 = true;
				cout << "Player 1(X/O): ";
				cin >> mark1;
            	while (checkSymbol1){
            		if(mark1 != 'X' && mark1 != 'O'){
            			cout << "Invalid symbol! Please select again! Player 1: ";
            			cin >> mark1;
					} else {
						break;
					} 
				}
				cout << "Player 2(X/O): ";
				cin >> mark2;
				while (checkSymbol2){
            		if(mark2 != 'X' && mark2 != 'O' || mark2 == mark1){
            			cout << "Invalid symbol! Please select again! Player 2: ";
            			cin >> mark2;
					} else {
						break;
					} 
				}
            	if (mark1 == 'X' && mark2 == 'O'){
            		ComputerPlayer player1('X');
                	ComputerPlayer player2('O');
                	Game game(&player1, &player2);
                	game.play();
				} else if (mark1 == 'O' && mark2 == 'X'){
					ComputerPlayer player1('O');
                	ComputerPlayer player2('X');
                	Game game(&player2, &player1);
                	game.play();
				} 
				break;
			}
            case '4':
                cout << "---------------How to play---------------" << endl;
            	cout << "|     *Type 1 -> 9 to tick the box      |" << endl;
            	cout << "|           on the board game           |" << endl;
            	cout << "|     *The winner is the one who gets   |" << endl;
            	cout << "|    three X's in a row in the board    |" << endl;
            	cout << "-----------------------------------------" << endl;
            	cout << endl;
                break;
            case '5':{
				cout << "---------------The game created by---------------" << endl;
            	cout << "|                Group: TWO                     |" << endl;
            	cout << "|         Contact for more information:         |" << endl;
                cout << "|        4901104007@student.hcmue.edu.vn        |" << endl;
            	cout << "|     or 4901104114@student.hcmue.edu.vn        |" << endl;
            	cout << "|     or 4901104175@student.hcmue.edu.vn        |" << endl;
            	cout << "|     or 4901104181@student.hcmue.edu.vn        |" << endl;
            	cout << "-------------------------------------------------" << endl;
            	cout << endl;
            	break;
			}
            case '6':{
            	cout << "--------------------Exit--------------------" << endl;
            	cout << "|         Exited game successfully!        |" << endl;
                cout << "|         Thank you and see you again      |" << endl;
                cout << "============================================" << endl;
                return 0;
				break;
			}
            default:
            	cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}

