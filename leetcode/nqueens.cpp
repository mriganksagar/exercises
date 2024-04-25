#include<vector>
#include<string>
using namespace std;


class Solution {
public:
    vector<bool> columns;
    vector<bool> rows;
    vector<bool> forwardDiagonal;
    vector<bool> backwardDiagonal;

    bool isColumnTaken(int c){
        return columns[c];
    } 
    bool isRowTaken(int r){
        return rows[r];
    }
    bool isForwardTaken(int r, int c){
        return forwardDiagonal[r+c];
    }
    bool isBackwardTaken(int r, int c, int n){
        return backwardDiagonal[c-r+n-1];
    }
    bool isTaken(int r, int c, int n){
        return isColumnTaken(c) || isRowTaken(r) || isForwardTaken(r, c) || isBackwardTaken(r, c, n);
    }
    void markColumn(int c, bool value = true){
        columns[c] = value;
    }
    void markRow(int r, bool value = true){
        rows[r] = value; 
    }
    void markForward(int r, int c, bool value = true){
        forwardDiagonal[r+c] = value;
    }
    void markBackward(int r, int c, int n, bool value = true){
        backwardDiagonal[c-r+n-1] = value;
    }

    void mark(int r, int c, int n, bool value = true){
        markColumn(c, value);
        markRow(r, value);
        markForward(r, c, value);
        markBackward(r, c, n, value);
    }


    void solveNQueen(int r, int n, vector<string>& board, vector<vector<string>>& result){
        string row;
        for(int c = 0; c<n; c++){
            if(!isTaken(r, c, n)){
                mark(r, c, n);
                row+="Q";
                for(int x= c+1; x< n; x++) row+=".";
                board.push_back(row);
                if(r == n-1){
                    //last row is pushed
                    result.push_back(board);
                }
                else solveNQueen(r+1, n, board, result);
                // backtrack
                mark(r,c,n, false);
                row = row.substr(0, c);
                board.pop_back();
            }
            row+=".";
        }
    }

    
    vector<vector<string>> solveNQueens(int n) {
        columns.resize(n, false);
        rows.resize(n, false);
        forwardDiagonal.resize(2*n-1, false);
        backwardDiagonal.resize(2*n-1, false);
        vector<string> board; 
        vector<vector<string>> result;
        solveNQueen(0, n, board, result);
        return result;
    }
};


// i was trying to do iteratively, but recrusion is the saviour it seems, easy peesy
// vector<vector<string>> solveNQueensHelper(int n){
//         vector<vector<string>> result;
//         vector<string> chessboard;
//         for(int r = 0; r < n; r++){
//             string s = "";
//             for(int c = 0; c < n; c++){
//                 if(!isTaken(r, c, n)){
//                     mark(r,c,n);
//                     s+= "Q";
//                     chessboard.push_back(s);
//                     break;
//                 }
//                 s+=".";
//             }
//             // traceback
//         }
//     }