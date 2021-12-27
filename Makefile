EXE := fox
RP := mpirun
CC := mpicc

.PHONY: all compile clean run runTestHome runTestLab

# Compile and run all

all: compile

compile:
	$(CC) main.c -o fox -lm

#run: compile 
# $(RP) -np 4 --oversubscribe ./$(EXE) < input6

runTestHome: compile
	$(RP) -np 1 --oversubscribe ./$(EXE) < ./matrix_examples/input6
	$(RP) -np 1 --oversubscribe ./$(EXE) < ./matrix_examples/input300
	$(RP) -np 1 --oversubscribe ./$(EXE) < ./matrix_examples/input600
	$(RP) -np 1 --oversubscribe ./$(EXE) < ./matrix_examples/input900
	$(RP) -np 1 --oversubscribe ./$(EXE) < ./matrix_examples/input1200

	$(RP) -np 4 --oversubscribe ./$(EXE) < ./matrix_examples/input6
	$(RP) -np 4 --oversubscribe ./$(EXE) < ./matrix_examples/input300
	$(RP) -np 4 --oversubscribe ./$(EXE) < ./matrix_examples/input600
	$(RP) -np 4 --oversubscribe ./$(EXE) < ./matrix_examples/input900
	$(RP) -np 4 --oversubscribe ./$(EXE) < ./matrix_examples/input1200

	$(RP) -np 4 --oversubscribe ./$(EXE) < ./matrix_examples/input6
	$(RP) -np 4 --oversubscribe ./$(EXE) < ./matrix_examples/input300
	$(RP) -np 4 --oversubscribe ./$(EXE) < ./matrix_examples/input600
	$(RP) -np 4 --oversubscribe ./$(EXE) < ./matrix_examples/input900
	$(RP) -np 4 --oversubscribe ./$(EXE) < ./matrix_examples/input1200

	$(RP) -np 9 --oversubscribe ./$(EXE) < ./matrix_examples/input6
	$(RP) -np 9 --oversubscribe ./$(EXE) < ./matrix_examples/input300
	$(RP) -np 9 --oversubscribe ./$(EXE) < ./matrix_examples/input600
	$(RP) -np 9 --oversubscribe ./$(EXE) < ./matrix_examples/input900
	$(RP) -np 9 --oversubscribe ./$(EXE) < ./matrix_examples/input1200

	$(RP) -np 16 --oversubscribe ./$(EXE) < ./matrix_examples/input6
	$(RP) -np 16 --oversubscribe ./$(EXE) < ./matrix_examples/input300
	$(RP) -np 16 --oversubscribe ./$(EXE) < ./matrix_examples/input600
	$(RP) -np 16 --oversubscribe ./$(EXE) < ./matrix_examples/input900
	$(RP) -np 16 --oversubscribe ./$(EXE) < ./matrix_examples/input1200


runTestLab: compile
	$(RP) -np 4 --hostfile ./hostfile --map-by node ./$(EXE) < ./matrix_examples/input6
	$(RP) -np 4 --hostfile ./hostfile --map-by node ./$(EXE) < ./matrix_examples/input300
	$(RP) -np 4 --hostfile ./hostfile --map-by node ./$(EXE) < ./matrix_examples/input600
	$(RP) -np 4 --hostfile ./hostfile --map-by node ./$(EXE) < ./matrix_examples/input900
	$(RP) -np 4 --hostfile ./hostfile --map-by node ./$(EXE) < ./matrix_examples/input1200


	$(RP) -np 9 --hostfile ./hostfile --map-by node ./$(EXE) < ./matrix_examples/input6
	$(RP) -np 9 --hostfile ./hostfile --map-by node ./$(EXE) < ./matrix_examples/input300
	$(RP) -np 9 --hostfile ./hostfile --map-by node ./$(EXE) < ./matrix_examples/input600
	$(RP) -np 9 --hostfile ./hostfile --map-by node ./$(EXE) < ./matrix_examples/input900
	$(RP) -np 9 --hostfile ./hostfile --map-by node ./$(EXE) < ./matrix_examples/input1200

	$(RP) -np 16 --hostfile ./hostfile --map-by node ./$(EXE) < ./matrix_examples/input6
	$(RP) -np 16 --hostfile ./hostfile --map-by node ./$(EXE) < ./matrix_examples/input300
	$(RP) -np 16 --hostfile ./hostfile --map-by node ./$(EXE) < ./matrix_examples/input600
	$(RP) -np 16 --hostfile ./hostfile --map-by node ./$(EXE) < ./matrix_examples/input900
	$(RP) -np 16 --hostfile ./hostfile --map-by node ./$(EXE) < ./matrix_examples/input1200
