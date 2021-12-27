#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include "./lib/struct.h"
#include "./include/foxalgorithm.h"
#include "./include/printmatrix.h"
#include "./include/matrixrequirements.h"
#include "./include/gridsetup.h"
#include "./include/submatrix.h"

#define MAX 99999


/* Main */
int main(int argc, char *argv[]){

    GRID grid; // My grid

    int **matrixInit;
    int **matrixA;
    int **matrixB;
    int **matrixC;
    int **matrixEnd;
    
    int num_procs, rank, req = 0;
    int matrix_dim, submatrix_dim;
    int i, j, k;
    double t1, t2, interval,interval_mil;

    int firstRank = 0;

    /* MPI initialization */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    /* Checks whether the input matrix has a valid dimension */

    if (rank == firstRank){
        scanf("%d", &matrix_dim);
        if (matrixValidation(num_procs, matrix_dim) == -1)
            req = -1;
    }

    
    /** @brief We must broadcasts a message from the process 
    * with rank root to all other processes of the group with the
    * result of the matrix validation
    *
    * */
    MPI_Bcast(&req, 1, MPI_INT, 0, MPI_COMM_WORLD);

    /* If the matrix requeriments are not met we terminate the program */
    if (req == -1){
        MPI_Finalize();
        return 0;
    }

    setupGrid(&grid);

    /*Broad cast the matrix dimension to all other processes */
    MPI_Bcast(&matrix_dim, 1, MPI_INT, 0, MPI_COMM_WORLD);

    /* Alocarion of memory - pass matrix and its dimension */
    memoryAllocation(&matrixInit, matrix_dim);

    if (rank == firstRank){
        for (i = 0; i < matrix_dim; i++){
            for (j = 0; j < matrix_dim; j++){
                int temp;
                scanf("%d", &temp);
                if (i != j && temp == 0){
                    matrixInit[i][j] = MAX;
                }
                else{
                    matrixInit[i][j] = temp;
                }
            }
        } 
    }

    /* New broadcast with matrix*/
    MPI_Bcast(&(matrixInit[0][0]), matrix_dim * matrix_dim, MPI_INT, 0, MPI_COMM_WORLD);

    /* Memory allocation for all matrix involved */
    submatrix_dim = matrix_dim / grid.q;

    memoryAllocation(&matrixA, submatrix_dim);
    memoryAllocation(&matrixB, submatrix_dim);
    memoryAllocation(&matrixC, submatrix_dim);
    
    submatrix(matrixInit, &grid, matrixA, submatrix_dim);

    /* Copy of the matrix A to matrix B */
    matrixB = matrixCopy(matrixA, submatrix_dim);

    for (i = 0; i < submatrix_dim; i++){
        for (j = 0; j < submatrix_dim; j++){
            matrixC[i][j] = MAX;
        }
    }

    /** @brief 
     * Blocks the program until all processes in the communicator have 
     * reached this routine so we can start counting the elapsed time.
     *
    */
    MPI_Barrier(MPI_COMM_WORLD);
    /**
     * @brief Starts counting the time t2-t1
     * 
     */
    t1 = MPI_Wtime();

    /* Fox's Algorithm Initialization: we pass it the grid, the 3
    * matrices and the the dimension of the submatrix
    */
    for (i = 1; i < log2(matrix_dim - 1); i *= 2){
        FoxAlgorithm(&grid, matrixA, matrixB, matrixC, submatrix_dim);
        matrixA = matrixCopy(matrixC, submatrix_dim);
        matrixB = matrixCopy(matrixC, submatrix_dim);
    }

    /* Memory allocation */
    memoryAllocation(&matrixEnd, submatrix_dim);

    if (rank != firstRank)
        MPI_Send(&(matrixC[0][0]), submatrix_dim * submatrix_dim, MPI_INT, 0, 0, MPI_COMM_WORLD);
    else{
        for (i = 0; i < submatrix_dim; i++){
            for ( j = 0; j < submatrix_dim; j++){
                if (matrixC[i][j] == MAX)
                    matrixInit[i][j] = 0;
                else
                    matrixInit[i][j] = matrixC[i][j];
            }
        }

        for (i = 1; i < num_procs; i++){

            MPI_Recv(&(matrixEnd[0][0]), submatrix_dim * submatrix_dim, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            int r = i / grid.q;
            int c = i % grid.q;

            for ( k = 0; k < submatrix_dim; k++){
                for (j = 0; j < submatrix_dim; j++){
                    if (matrixEnd[k][j] == MAX)
                        matrixInit[r * submatrix_dim + k][c * submatrix_dim + j] = 0;
                    else
                        matrixInit[r * submatrix_dim + k][c * submatrix_dim + j] = matrixEnd[k][j];
                }
            }
        }
    } /* Fox's Algorithm Termination */

    /*Barrier: waiting on all the processes to t2*/
    MPI_Barrier(MPI_COMM_WORLD);
    t2 = MPI_Wtime();

    if (rank == firstRank){
        interval = t2 - t1;
        interval_mil = interval * 1000;
        printf("The elapsed time was %lf milliseconds\n", interval_mil);
        /* Calls printMatrix*/
        printMatrix(matrixInit, matrix_dim);
    }

    /*Termination*/
    MPI_Finalize();
    return 0;
}
