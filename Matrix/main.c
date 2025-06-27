#include <stdio.h>
#include <stdlib.h>

// === Utility Functions ===

int** allocateMatrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
        matrix[i] = (int *)malloc(cols * sizeof(int));
    return matrix;
}

void inputMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i, j);
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

void freeMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);
}

// === Matrix Operations ===

int** addMatrices(int **A, int **B, int rows, int cols) {
    int **result = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = A[i][j] + B[i][j];
    return result;
}

int** subtractMatrices(int **A, int **B, int rows, int cols) {
    int **result = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = A[i][j] - B[i][j];
    return result;
}

int** multiplyMatrices(int **A, int **B, int rowsA, int colsA, int colsB) {
    int **result = allocateMatrix(rowsA, colsB);
    for (int i = 0; i < rowsA; i++)
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;
            for (int k = 0; k < colsA; k++)
                result[i][j] += A[i][k] * B[k][j];
        }
    return result;
}

int** transposeMatrix(int **A, int rows, int cols) {
    int **transpose = allocateMatrix(cols, rows);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            transpose[j][i] = A[i][j];
    return transpose;
}

// Inverse (2x2 only)
double** inverseMatrix2x2(int **A) {
    int det = A[0][0]*A[1][1] - A[0][1]*A[1][0];
    if (det == 0) return NULL;

    double **inv = (double **)malloc(2 * sizeof(double *));
    for (int i = 0; i < 2; i++)
        inv[i] = (double *)malloc(2 * sizeof(double));

    inv[0][0] =  A[1][1] / (double)det;
    inv[0][1] = -A[0][1] / (double)det;
    inv[1][0] = -A[1][0] / (double)det;
    inv[1][1] =  A[0][0] / (double)det;

    return inv;
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

// === Main Program ===

int main() {
    int rows1, cols1, rows2, cols2;

    printf("Enter rows and columns of Matrix A: ");
    scanf("%d %d", &rows1, &cols1);
    int **A = allocateMatrix(rows1, cols1);
    printf("Matrix A:\n");
    inputMatrix(A, rows1, cols1);

    printf("Enter rows and columns of Matrix B: ");
    scanf("%d %d", &rows2, &cols2);
    int **B = allocateMatrix(rows2, cols2);
    printf("Matrix B:\n");
    inputMatrix(B, rows2, cols2);

    printf("\nMatrix A:\n");
    displayMatrix(A, rows1, cols1);

    printf("\nMatrix B:\n");
    displayMatrix(B, rows2, cols2);


    printf("\n--- Matrix Operations ---\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Inverse (2x2 Only)\n");
    printf("5. Transpose\n");
    printf("Enter your choice: ");

    int choice;
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            if (rows1 == rows2 && cols1 == cols2) {
                int **sum = addMatrices(A, B, rows1, cols1);
                printf("\nA + B:\n");
                displayMatrix(sum, rows1, cols1);
                freeMatrix(sum, rows1);
            } else {
                printf("Addition not possible: dimension mismatch.\n");
            }
            break;

        case 2:
            if (rows1 == rows2 && cols1 == cols2) {
                int **diff = subtractMatrices(A, B, rows1, cols1);
                printf("\nA - B:\n");
                displayMatrix(diff, rows1, cols1);
                freeMatrix(diff, rows1);
            } else {
                printf("Subtraction not possible: dimension mismatch.\n");
            }
            break;

        case 3:
            if (cols1 == rows2) {
                int **prod = multiplyMatrices(A, B, rows1, cols1, cols2);
                printf("\nA x B:\n");
                displayMatrix(prod, rows1, cols2);
                freeMatrix(prod, rows1);
            } else {
                printf("Multiplication not possible: A's columns != B's rows.\n");
            }
            break;

        case 4: {
            int matrixChoice;
            printf("Inverse of which matrix? (1 for A, 2 for B): ");
            scanf("%d", &matrixChoice);

            int **target = (matrixChoice == 1) ? A : B;
            int rows = (matrixChoice == 1) ? rows1 : rows2;
            int cols = (matrixChoice == 1) ? cols1 : cols2;

            if (rows == 2 && cols == 2) {
                double **inv = inverseMatrix2x2(target);
                if (inv == NULL) {
                    printf("Matrix is singular, inverse doesn't exist.\n");
                } else {
                    printf("\nInverse:\n");
                    displayMatrixDouble(inv, 2, 2);
                    freeMatrixDouble(inv, 2);
                }
            } else {
                printf("Inverse implemented only for 2x2 matrices.\n");
            }
            break;
        }

        case 5: {
            int matrixChoice;
            printf("Transpose of which matrix? (1 for A, 2 for B): ");
            scanf("%d", &matrixChoice);

            int **target = (matrixChoice == 1) ? A : B;
            int rows = (matrixChoice == 1) ? rows1 : rows2;
            int cols = (matrixChoice == 1) ? cols1 : cols2;

            int **trans = transposeMatrix(target, rows, cols);
            printf("\nTranspose:\n");
            displayMatrix(trans, cols, rows);
            freeMatrix(trans, cols);
            break;
        }

        default:
            printf("Invalid choice.\n");
    }

    freeMatrix(A, rows1);
    freeMatrix(B, rows2);

    return 0;
}
