/**
 * Function to print elements in a two-dimensional array.
 *
 * Two-dimensional array to print.
 */

void printMatrix(int **matrix, int dim){

    int row, col;

    for (row = 0; row < dim; row++){
        for ( col = 0; col < dim; col++){
            printf("%d ", matrix[row][col]);
        }
        printf("\n");
    }
}