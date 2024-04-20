#include<vector>
using namespace std;

class Solution {
public:
    bool possible(vector<vector<char>>& board, char value , int row, int column){
        //checks the row and column
        for(int i = 0; i< 9; i++){
            if(board[row][i] == value) return false;
            if(board[i][column] == value) return false;
        }
        // checks the square
        int col1, col2, row1, row2;
        col1 = (column/3)*3;
        col2 = col1+2;
        row1 = (row/3)*3;
        row2 = row1+2;

        for(int r = row1; r <= row2; r++){
            for(int c = col1; c<=col2; c++){
                if(board[r][c] == value) return false;
            }
        }
        return true;
    }

    bool solveSudoku(vector<vector<char>>& board) {
        for(int row = 0; row<9; row++ ){
            for(int col = 0; col < 9; col++){
                if(board[row][col] == '.'){
                    for(char value = '1'; value <= '9'; value++){
                        if(possible(board, value, row, col)){
                            board[row][col] = value;
                            if(solveSudoku(board)) return true;
                            board[row][col] = '.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    // lets optimsize it a bit

    bool solveSudokuNext(vector<vector<char>>& board, int row, int column){
        if(column < 8 ) return solveSudokuOptimised(board, row, column+1);
        else if(row < 8) return solveSudokuOptimised(board, row+1, 0);
        else return true;
    }

    bool solveSudokuOptimised(vector<vector<char>>& board, int row = 0, int column = 0) {
        if(board[row][column] != '.') return solveSudokuNext(board, row, column);

        for(char value = '1'; value <= '9'; value++){
            if(possible(board, value, row, column)){
                board[row][column] = value;
                if(solveSudokuNext(board, row, column)) return true;
                board[row][column] = '.';
            }
        }
        return false;
    }
};