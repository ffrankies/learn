hello_world: ./hello_world/hello_world.c ./hello_world/hello_world.h
	mpicc ./hello_world/hello_world.c -o ./hello_world/hello_world.o
	mpirun -np 8 ./hello_world/hello_world.o
	rm ./hello_world/hello_world.o

blocking: ./blocking/blocking.c ./blocking/blocking.h
	mpicc ./blocking/blocking.c -o ./blocking/blocking.o
	mpirun -np 8 ./blocking/blocking.o
	rm ./blocking/blocking.o