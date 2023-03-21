#include <iostream>
#include <vector>
#include <thread>

using namespace std;

double determinant(const vector<vector<double>>& matrix);

int main() {
    // Example usage
    vector<vector<double>> matrix = {
        {9, 8, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    double det = determinant(matrix);
    cout << "Determinant: " << det << endl;
    return 0;
}

double submatrix_determinant(const vector<vector<double>>& matrix, int row, int col) {
    int size = matrix.size() - 1;
    vector<vector<double>> submatrix(size, vector<double>(size));
    for (int i = 0, r = 0; i <= size; i++, r++) {
        if (i == row) {
            r--;
            continue;
        }
        for (int j = 0, c = 0; j <= size; j++, c++) {
            if (j == col) {
                c--;
                continue;
            }
            submatrix[r][c] = matrix[i][j];
        }
    }
    return determinant(submatrix);
}

double determinant(const vector<vector<double>>& matrix) {
    int size = matrix.size();
    if (size == 1) {
        return matrix[0][0];
    }
    if (size == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    double det = 0;
    vector<thread> threads;
    for (int j = 0; j < size; j++) {
        threads.emplace_back([j, &matrix, &det]() {
            double sub_det = submatrix_determinant(matrix, 0, j);
            det += matrix[0][j] * sub_det * ((j % 2 == 0) ? 1 : -1);
        });
    }
    for (auto& t : threads) {
        t.join();
    }
    return det;
}
