typedef struct {
    /**
     * @brief Defines the total number of processors
     * 
     */
    int       procs;
    /**
     * @brief Defines the communicator for entire grid
     * 
     */
    MPI_Comm  comm;
    /**
     * @brief Defines the communicator for the row
     * 
     */
    MPI_Comm  row_comm;
    /**
     * @brief Defines the communicator for entire column
     * 
     */
    MPI_Comm  col_comm;
    /**
     * @brief Defines the order of the grid
     * 
     */
    int       q;
    /**
     * @brief Defines the grid row for the processor
     * 
     */
    int       my_row;
    /** 
     * @brief Defines the grid column for the processor
     * 
     */
    int       my_col;
    /** 
     * @brief Defines the rank that the processor has on the grid communicator
     * 
     */
    int       myRank;
} GRID;

/* Struct of the grid: all the information we pass such number of processes, communicators, colomns, rows and rank */