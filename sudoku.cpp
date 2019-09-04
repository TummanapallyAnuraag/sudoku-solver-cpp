#include <bits/stdc++.h>
using namespace std;
int sudoku[9][9];

bool find_zero_elem(int *r, int *c){
    for(int row = 0;row < 9; row++){
        for(int col = 0;col < 9; col++){
            if(sudoku[row][col] == 0){
                *r = row;
                *c = col;
                return true;
            }
        }
    }
    return false;
}

void find_valid_invalid(int r, int c, int* is_valid){
    int rows[3], cols[3];
    for(int col = 0; col < 9; col++){
        // check the row
        if(sudoku[r][col] != 0){
            is_valid[ sudoku[r][col] ] = 0;
        }
    }
    for(int row = 0; row < 9; row++){
        // check the column
        if(sudoku[row][c] != 0){
            is_valid[ sudoku[row][c] ] = 0;
        }
    }
    switch(r){
        case 0:case 1:case 2:
            rows[0] = 0;rows[1] = 1;rows[2] = 2;break;
        case 3:case 4:case 5:
            rows[0] = 3;rows[1] = 4;rows[2] = 5;break;
        case 6: case 7: case 8:
            rows[0] = 6;rows[1] = 7;rows[2] = 8;break;
    }
    switch(c){
        case 0:case 1:case 2:
            cols[0] = 0;cols[1] = 1;cols[2] = 2;break;
        case 3:case 4:case 5:
            cols[0] = 3;cols[1] = 4;cols[2] = 5;break;
        case 6: case 7: case 8:
            cols[0] = 6;cols[1] = 7;cols[2] = 8;break;
    }
    for(int i = 0; i<3;i++){
        for(int j=0;j<3;j++){
            // check the 3x3 block
            if(sudoku[rows[i]][cols[j]] != 0){
                is_valid[ sudoku[rows[i]][cols[j]] ] = 0;
            }
        }
    }
}

bool backtrack_algo(int nz_elem){
    int r, c, entry, is_valid[10] = {1,1,1,1,1,1,1,1,1,1};
    int prev_sudoku[9][9];
    // take a backup, for back tracking
    for(int i = 0;i < 9;i++){
        for(int j = 0; j < 9;j++){
            prev_sudoku[i][j] = sudoku[i][j];
        }
    }
    /* find the top, left most 0 element */
    if(!find_zero_elem(&r, &c)){
        // sudoku is already solved!
        return true;
    }
    find_valid_invalid(r, c, is_valid);
    for(entry = 1;entry <=9; entry++){
        if(is_valid[entry]){
            sudoku[r][c] = entry;
            if(nz_elem == 81){
                // we are done
                cout << "sudoku solved, hurray!" << endl;
                return true;
            }else if(backtrack_algo(nz_elem+1)){
                // no problems, so okay
                return true;
            }else{
                // backtrack
                for(int i = 0;i < 9;i++){
                    for(int j = 0; j < 9;j++){
                        sudoku[i][j] = prev_sudoku[i][j];
                    }
                }
            }
        }else{
            // cout << nz_elem << ": " << entry << " is not valid" << endl;
        }
    }
    if(entry > 9){
        // none of them are successful, so return false.
        return false;
    }
    return true;
}

int main(){
    int nz_elem = 0;
    for(int r = 0;r < 9;r++){
        for(int c = 0; c < 9;c++){
            cin >> sudoku[r][c];
            if(sudoku[r][c])
                nz_elem++;
        }
    }
    if(backtrack_algo(nz_elem)){
        string ch;
        for(int r = 0;r < 9;r++){
            for(int c = 0; c < 9;c++){
                if(c == 2 || c == 5)
                    ch = " | ";
                else
                    ch = " ";
                cout << sudoku[r][c] << ch;
            }
            if(r == 2 || r == 5)
                cout << endl << "- - - - - - - - - - -";
            cout << endl;
        }
    }
    return 0;
}
