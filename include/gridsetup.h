
/*
*
* Grid setup according to the book "mpi guide"
*
*/

void *setupGrid(GRID *grid){

    int old_rank;
    int dimensions[2];
    int periods[2];
    int coordinates[2], varying_cordinates[2];

    /* Setup the global Grid Information */

    MPI_Comm_size(MPI_COMM_WORLD, &(grid->procs));
    MPI_Comm_size(MPI_COMM_WORLD, &old_rank);


    grid->q = (int)sqrt((double)grid->procs);
    dimensions[0] = dimensions[1] = grid->q;
    periods[0] = periods[1] = 1;

    /* Makes a new communicator to which topology information has been attached */
    MPI_Cart_create(MPI_COMM_WORLD, 2, dimensions, periods, 1, &(grid->comm));

    MPI_Comm_rank(grid->comm, &(grid->myRank));

    /* Determines process coords in cartesian topology given rank in group */
    MPI_Cart_coords(grid->comm, grid->myRank, 2, coordinates);

    grid->my_row = coordinates[0];
    grid->my_col = coordinates[1];

    /* Setup up row and column communicators */
    varying_cordinates[0] = 0; varying_cordinates[1] = 1;

    /* Partitions a communicator into subgroups which form 
    *lower-dimensionsensional cartesian subgrids */
    MPI_Cart_sub(grid->comm, varying_cordinates, &(grid->row_comm));

    // COLUMN_COMM_WORLD
    varying_cordinates[0] = 1; varying_cordinates[1] = 0;

    MPI_Cart_sub(grid->comm, varying_cordinates, &(grid->col_comm));

} /* Setup grid */
