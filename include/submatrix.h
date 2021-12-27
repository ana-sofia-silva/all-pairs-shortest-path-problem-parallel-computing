/* Submatrix Creation */

int i, j;
int index_i, index_j;

void submatrix(int **m, GRID *grid, int **matrixAux, int dim){
    for (i = 0; i < dim; i++){
        for (j = 0; j < dim; j++){
            index_i = grid->my_row * dim + i;
            index_j = grid->my_col * dim + j;
            matrixAux[i][j] = m[index_i][index_j];
        }
    }
}

/**
 * We want to copy matrix A to B so we have D_A X D_B while A=B because they are quadratic
 * */

int **matrixCopy(int **m, int dim){
    
    // dim : row/colomn count

    int **dst;
    int i, j;

    memoryAllocation(&dst, dim);

    for (i = 0; i < dim; i++){ /* Row - count */
        for (j = 0; j < dim; j++){ /* Column - count */
              dst[i][j] = m[i][j];
       }
    }
    return dst;
}
