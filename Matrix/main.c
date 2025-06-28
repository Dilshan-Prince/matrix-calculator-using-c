#include <stdio.h>
#include <stdlib.h>

#define MAX 5

// ===== Matrix Utilities =====
int** allocateMatrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
        matrix[i] = (int *)malloc(cols * sizeof(int));
    return matrix;
}

void freeMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);
}

void inputMatrix(int **matrix, int rows, int cols, char name) {
    printf("Enter elements of Matrix %c (%dx%d):\n", name, rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            printf("%c[%d][%d]: ", name, i, j);
            scanf("%d", &matrix[i][j]);
        }
}

void displayMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d\t", matrix[i][j]);
        printf("\n");
    }
}

void displayMatrixDouble(double **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%.2f\t", matrix[i][j]);
        printf("\n");
    }
}

void freeMatrixDouble(double **matrix, int rows) {
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);
}

// ===== Matrix Operations =====
int** addMatrices(int **A, int **B, int rows, int cols) {
    int **res = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res[i][j] = A[i][j] + B[i][j];
    return res;
}

int** subtractMatrices(int **A, int **B, int rows, int cols) {
    int **res = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res[i][j] = A[i][j] - B[i][j];
    return res;
}

int** multiplyMatrices(int **A, int **B, int rA, int cA, int cB) {
    int **res = allocateMatrix(rA, cB);
    for (int i = 0; i < rA; i++)
        for (int j = 0; j < cB; j++) {
            res[i][j] = 0;
            for (int k = 0; k < cA; k++)
                res[i][j] += A[i][k] * B[k][j];
        }
    return res;
}

int** transposeMatrix(int **M, int rows, int cols) {
    int **res = allocateMatrix(cols, rows);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res[j][i] = M[i][j];
    return res;
}

double determinant3x3(int **M) {
    return M[0][0]*(M[1][1]*M[2][2]-M[1][2]*M[2][1])
         - M[0][1]*(M[1][0]*M[2][2]-M[1][2]*M[2][0])
         + M[0][2]*(M[1][0]*M[2][1]-M[1][1]*M[2][0]);
}

double** inverse2x2(int **M) {
    int det = M[0][0]*M[1][1] - M[0][1]*M[1][0];
    if (det == 0) return NULL;
    double **inv = (double **)malloc(2 * sizeof(double *));
    for (int i = 0; i < 2; i++)
        inv[i] = (double *)malloc(2 * sizeof(double));
    inv[0][0] =  M[1][1] / (double)det;
    inv[0][1] = -M[0][1] / (double)det;
    inv[1][0] = -M[1][0] / (double)det;
    inv[1][1] =  M[0][0] / (double)det;
    return inv;
}

double** inverse3x3(int **M) {
    double det = determinant3x3(M);
    if (det == 0) return NULL;

    double **inv = (double **)malloc(3 * sizeof(double *));
    for (int i = 0; i < 3; i++)
        inv[i] = (double *)malloc(3 * sizeof(double));

    inv[0][0] =  (M[1][1]*M[2][2] - M[1][2]*M[2][1]) / det;
    inv[0][1] = -(M[0][1]*M[2][2] - M[0][2]*M[2][1]) / det;
    inv[0][2] =  (M[0][1]*M[1][2] - M[0][2]*M[1][1]) / det;

    inv[1][0] = -(M[1][0]*M[2][2] - M[1][2]*M[2][0]) / det;
    inv[1][1] =  (M[0][0]*M[2][2] - M[0][2]*M[2][0]) / det;
    inv[1][2] = -(M[0][0]*M[1][2] - M[0][2]*M[1][0]) / det;

    inv[2][0] =  (M[1][0]*M[2][1] - M[1][1]*M[2][0]) / det;
    inv[2][1] = -(M[0][0]*M[2][1] - M[0][1]*M[2][0]) / det;
    inv[2][2] =  (M[0][0]*M[1][1] - M[0][1]*M[1][0]) / det;

    return inv;
}

// ===== Main Program =====
int main() {
    int repeatAll = 1;

    while (repeatAll) {
        int matrixCount;
        printf("How many matrices do you want to use? (Maximum 3 Matrices): ");
        scanf("%d", &matrixCount);
        if (matrixCount < 1 || matrixCount > 3) {
            printf("Invalid matrix count.\n");
            continue;
        }

        int **A = NULL, **B = NULL, **C = NULL;
        int rA = 0, cA = 0, rB = 0, cB = 0, rC = 0, cC = 0;

        // Input Matrix A
        printf("Matrix A:\nEnter rows and cols (max 5x5): ");
        scanf("%d %d", &rA, &cA);
        if (rA > MAX || cA > MAX) { printf("Exceeded size.\n"); continue; }
        A = allocateMatrix(rA, cA);
        inputMatrix(A, rA, cA, 'A');

        if (matrixCount >= 2) {
            printf("Matrix B:\nEnter rows and cols (max 5x5): ");
            scanf("%d %d", &rB, &cB);
            if (rB > MAX || cB > MAX) { freeMatrix(A, rA); continue; }
            B = allocateMatrix(rB, cB);
            inputMatrix(B, rB, cB, 'B');
        }

        if (matrixCount == 3) {
            printf("Matrix C:\nEnter rows and cols (max 5x5): ");
            scanf("%d %d", &rC, &cC);
            if (rC > MAX || cC > MAX) { freeMatrix(A, rA); if (B) freeMatrix(B, rB); continue; }
            C = allocateMatrix(rC, cC);
            inputMatrix(C, rC, cC, 'C');
        }

        printf("\nMatrix A:\n"); displayMatrix(A, rA, cA);
        if (matrixCount >= 2) { printf("\nMatrix B:\n"); displayMatrix(B, rB, cB); }
        if (matrixCount == 3) { printf("\nMatrix C:\n"); displayMatrix(C, rC, cC); }

        int repeatMenu = 1;
        while (repeatMenu) {
            printf("\n--- Matrix Operations ---\n");
            if (matrixCount == 1) {
                printf("4. Inverse\n5. Transpose\n");
            } else {
                printf("1. Addition\n2. Subtraction\n3. Multiplication\n4. Inverse\n5. Transpose\n");
            }
            printf("Enter your choice: ");
            int choice;
            scanf("%d", &choice);

            int **M = A, rows = rA, cols = cA;

            if (choice == 4 || choice == 5) {
                if (matrixCount > 1) {
                    char target;
                    printf("Which matrix? ");
                    if (matrixCount == 2) printf("(A or B): ");
                    else printf("(A, B, or C): ");
                    scanf(" %c", &target);
                    if (target == 'A') { M = A; rows = rA; cols = cA; }
                    else if (target == 'B') { M = B; rows = rB; cols = cB; }
                    else if (target == 'C' && matrixCount == 3) { M = C; rows = rC; cols = cC; }
                    else { printf("Invalid selection.\n"); continue; }
                }

                if (choice == 4) {
                    if (rows != cols || (rows != 2 && rows != 3)) {
                        printf("Only 2x2 or 3x3 supported for inverse.\n");
                    } else {
                        double **inv = (rows == 2) ? inverse2x2(M) : inverse3x3(M);
                        if (inv == NULL) printf("Matrix is singular.\n");
                        else {
                            printf("\nInverse Matrix:\n");
                            displayMatrixDouble(inv, rows, cols);
                            freeMatrixDouble(inv, rows);
                        }
                    }
                } else {
                    int **trans = transposeMatrix(M, rows, cols);
                    printf("\nTranspose Matrix:\n");
                    displayMatrix(trans, cols, rows);
                    freeMatrix(trans, cols);
                }
            }

            else if (matrixCount < 2) {
                printf("Operation needs at least 2 matrices.\n");
            } else {
                int **result = NULL;
                if (choice == 1) {
                    if (rA == rB && cA == cB) {
                        result = addMatrices(A, B, rA, cA);
                        if (matrixCount == 3 && rB == rC && cB == cC) {
                            int **temp = result;
                            result = addMatrices(result, C, rC, cC);
                            freeMatrix(temp, rA);
                        }
                        printf("\nResult:\n"); displayMatrix(result, rA, cA); freeMatrix(result, rA);
                    } else printf("Dimension mismatch.\n");
                } else if (choice == 2) {
                    if (rA == rB && cA == cB) {
                        result = subtractMatrices(A, B, rA, cA);
                        if (matrixCount == 3 && rB == rC && cB == cC) {
                            int **temp = result;
                            result = subtractMatrices(result, C, rC, cC);
                            freeMatrix(temp, rA);
                        }
                        printf("\nResult:\n"); displayMatrix(result, rA, cA); freeMatrix(result, rA);
                    } else printf("Dimension mismatch.\n");
                } else if (choice == 3) {
                    if (cA == rB) {
                        result = multiplyMatrices(A, B, rA, cA, cB);
                        if (matrixCount == 3 && cB == rC) {
                            int **temp = result;
                            result = multiplyMatrices(result, C, rA, cB, cC);
                            freeMatrix(temp, rA);
                        }
                        printf("\nResult:\n");
                        displayMatrix(result, rA, (matrixCount == 3) ? cC : cB);
                        freeMatrix(result, rA);
                    } else printf("Dimension mismatch.\n");
                } else printf("Invalid operation.\n");
            }

            printf("\n1. Do another calculation\n2. Redefine matrices\n3. Exit\nChoose: ");
            int next;
            scanf("%d", &next);
            if (next == 1) continue;
            else if (next == 2) repeatMenu = 0;
            else { repeatMenu = 0; repeatAll = 0; }
        }

        freeMatrix(A, rA);
        if (B) freeMatrix(B, rB);
        if (C) freeMatrix(C, rC);
    }

    printf("\nThanks for using Matrix Calculator!\n");
    return 0;
}
