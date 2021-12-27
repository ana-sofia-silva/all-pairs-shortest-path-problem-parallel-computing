/** @brief Matrix validation - First Step 
*
* Reads the number of vertices from the input and stores it, along with the submatrix size.
* Returns 1 if it succeeds, otherwise returns -1.
*
* We know that given matrices of size NxN and P processors, there must exist an integer Q such that P = Q*Q and N mod Q = 0, otherwise the algorithm cannot be applied. 
*
*
*/

int matrixValidation(int num_procs, int matrix_dim){

    int mod; 
    int q;

    mod = matrix_dim % (int)sqrt(num_procs); // mod 0
    
    if ( mod != 0){
        printf("ERROR - for:\n"
			" number of processes:  %d\n" 
			" matrix size:  %d\n"
			"The calculated submatrix's size"
			" cannot be used for Fox's algorithm\n", num_procs, matrix_dim);
        printf("\n");
        return -1;
    }
    else{
        return 1;
    }
}

/* Observation: Use of operator && (and) does not satisfies the condition, use || (or) */