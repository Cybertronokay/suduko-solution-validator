#include <iostream>
#include <fstream>

#define SIZE 9

int sudoku[SIZE][SIZE];
int valid[27] = {0};

void check_row(int row) {
    int nums[10] = {0};
    for (int i = 0; i < SIZE; ++i) {
        int num = sudoku[row][i];
        if (num < 1 || num > 9 || nums[num]) return;
        nums[num] = 1;
    }
    valid[row] = 1;
}

void check_col(int col) {
    int nums[10] = {0};
    for (int i = 0; i < SIZE; ++i) {
        int num = sudoku[i][col];
        if (num < 1 || num > 9 || nums[num]) return;
        nums[num] = 1;
    }
    valid[9 + col] = 1;
}

void check_subgrid(int row, int col) {
    int nums[10] = {0};
    for (int i = row; i < row + 3; ++i) {
        for (int j = col; j < col + 3; ++j) {
            int num = sudoku[i][j];
            if (num < 1 || num > 9 || nums[num]) return;
            nums[num] = 1;
        }
    }
    int index = 18 + (row / 3) * 3 + (col / 3);
    valid[index] = 1;
}

int main() {
    std::ifstream file("input.txt");
    if (!file) {
        std::cout << "Invalid Sudoku solution\n";
        return 0;
    }

    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            file >> sudoku[i][j];

    for (int i = 0; i < SIZE; ++i) {
        check_row(i);
        check_col(i);
    }

    for (int i = 0; i < SIZE; i += 3)
        for (int j = 0; j < SIZE; j += 3)
            check_subgrid(i, j);

    for (int i = 0; i < 27; ++i) {
        if (valid[i] != 1) {
            std::cout << "Invalid Sudoku solution\n";
            return 0;
        }
    }

    std::cout << "Valid Sudoku solution\n";
    return 0;
}
