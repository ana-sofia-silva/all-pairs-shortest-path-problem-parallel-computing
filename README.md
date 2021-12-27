# All-Pairs-Shortest-Path-Problem-Parallel-Computing
The problem consists in determining all shortest paths between pairs of nodes in a given graph. 

<h1> Execution </h1>

To execute the program I can compile the main file with the command $ make followed by $ make
runTestX. I defined a Make file in which I created a set of tests, on my personal computer ( $ make
runTestHome) and another one using the lab ( $ make runTestLab) . The execution of the program
is processed bympicc -np P – hostfile ./hostfile –map-by node fox < ./matrix examples/inputX. Let P
be the number of processes, fox the executable, hostfile defines the slots and inputX the file with
the matrix used as input.
