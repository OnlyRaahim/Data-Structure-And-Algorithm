
#include <bits/stdc++.h>
using namespace std;

bool searchWord(vector<vector<char>>& board, string word,
                int r, int c, int index) {

    
    if (index == word.length()) {
        return true;
    }

    
    if (r < 0 || c < 0 || r >= board.size() || c >= board[0].size()) {
        return false;
    }

    
    if (board[r][c] != word[index]) {
        return false;
    }

    
    char temp = board[r][c];
    board[r][c] = '#';

    
    bool found =
        searchWord(board, word, r + 1, c, index + 1) ||
        searchWord(board, word, r - 1, c, index + 1) ||
        searchWord(board, word, r, c + 1, index + 1) ||
        searchWord(board, word, r, c - 1, index + 1);

    
    board[r][c] = temp;

    return found;
}

int main() {
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };

    string word = "ABCCED";

    bool found = false;

    for (int r = 0; r < board.size(); r++) {
        for (int c = 0; c < board[0].size(); c++) {
            if (searchWord(board, word, r, c, 0)) {
                found = true;
                break;
            }
        }

        if (found) {
            break;
        }
    }

    cout << (found ? "true" : "false") << endl;

    return 0;
}
