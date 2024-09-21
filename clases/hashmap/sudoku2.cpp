#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<vector<string>> board = {
        {"5", "3", ".", ".", "7", ".", ".", ".", "."},
        {"6", ".", ".", "1", "9", "5", ".", ".", "."},
        {".", "9", "8", ".", ".", ".", ".", "6", "."},
        {"8", ".", ".", ".", "6", ".", ".", ".", "3"},
        {"4", ".", ".", "8", ".", "3", ".", ".", "1"},
        {"7", ".", ".", ".", "2", ".", ".", ".", "6"},
        {".", "6", ".", ".", ".", ".", "2", "8", "."},
        {".", ".", ".", "4", "1", "9", ".", ".", "5"},
        {".", ".", ".", ".", "8", ".", ".", "7", "9"}};

int main() {
    unordered_map<string, int> h;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] != "."){
                string row_key = "r"+to_string(i+1)+"v"+board[i][j];
                string col_key = "c"+to_string(j+1)+"v"+board[i][j];
                string square_key = "s"+to_string(i/3+1)+to_string(j/3+1)+"v"+board[i][j];
                if (h.find(row_key) != h.end() || h.find(col_key) != h.end() || h.find(square_key) != h.end()){
                    cout << "No es valido" << endl;
                    return 0;
                }
                h[row_key] = 1;
                h[col_key] = 1;
                h[square_key] = 1;
            }
        }
    }
    cout << "si es valido" << endl;
    return 0;
}