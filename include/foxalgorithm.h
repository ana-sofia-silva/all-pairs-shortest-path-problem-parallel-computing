
// Memory allocation
void memoryAllocation(int ***matrix, int dim);


// Matrix multiplication ( operation to multiply the values)
void matrixMultiplication(int **matrix1, int **matrix2, int **matrix3, int dim);


/* Fox's Algorithm */


void FoxAlgorithm(GRID *grid, 
                  int **matrix1,
                  int **matrix2, 
                  int **matrix3, 
                  int dim){

    // Follows the book implementation
    int step;
    int colomnsource;
    int dest;
    int bcast_root;
    int tag = 43;
    int **matrixTemp;
    
    MPI_Status status;


    /* Calculate addresses for cirular shift of B */ 
    colomnsource = (grid->my_row + 1) % grid->q;
    dest = (grid->my_row + grid->q - 1) % grid->q;


    /* Set aside storage  */
    memoryAllocation(&matrixTemp, dim);

    for ( step = 0; step < grid->q; step++){

        bcast_root = (grid->my_row + step) % grid->q;

        /* The process broadcasts */
        if (bcast_root == grid-> my_col){
            MPI_Bcast(&(matrix1[0][0]), dim * dim, MPI_INT, bcast_root, grid->row_comm);
            matrixMultiplication(matrix1, matrix2, matrix3, dim);
        }
        /* The process receives */
        else{
            MPI_Bcast(&(matrixTemp[0][0]), dim * dim, MPI_INT, bcast_root, grid->row_comm);
            matrixMultiplication(matrixTemp, matrix2, matrix3, dim);
        }


        //MPI_Sendrecv(&(matrix2[0][0]), dim * dim, MPI_INT, colomnsource, 0, grid->colComm, MPI_STATUS_IGNORE);
        MPI_Sendrecv_replace(&(matrix2[0][0]), dim * dim, MPI_INT, 
                            dest, tag, colomnsource, tag,
                            grid->col_comm,MPI_STATUS_IGNORE);

    }
}


/* Memory allocation */ 
void memoryAllocation(int ***matrix, int dim){
    /* Allocate memory of a matrix of dim X dim
    *           dim X dim = col X row 
    * The matrix will be stored contiguously in memory
    */
    int *p = (int *)malloc(dim * dim * sizeof(int *));

    // Allocate the row pointers into the memory
    (*matrix) = (int **)malloc(dim * sizeof(int *));

    // Set up pointers
    for (int i = 0; i < dim; i++){
        (*matrix)[i] = &(p[i * dim]);
    }
}


/**
 * Function to multiply two matrices
 * 
 * matrix1    First matrix
 * matrix2    Second matrix
 * matrix3    Resultant matrix to store product of both matrices.
 */

void matrixMultiplication(int **matrix1, int **matrix2, int **matrix3, int dim){
    int row, col, k;
    for (row = 0; row < dim; row++){
        for (col = 0; col < dim; col++){
            for (k = 0; k < dim; k++){
                if ((matrix1[row][k] + matrix2[k][col]) < matrix3[row][col])
                    /* Store sum of product of row of first matrix 
                    * and column of second matrix to resultant matrix.*/
                    matrix3[row][col] = matrix1[row][k] + matrix2[k][col];
            }
        }
    }
}