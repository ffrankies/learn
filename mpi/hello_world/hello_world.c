#include "hello_world.h"

int main(int argc, char* argv[]) {

    int numtasks, taskid, hostnamelen;
    char host[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Get_processor_name(host, &hostnamelen);
    
    printf("Hello World! I'm task %d, running on host %s\n", taskid, host);

    if (taskid == MASTER_TASK) {
        printf("I'm the master task. There are %d tasks running.\n", numtasks);
    }

    MPI_Finalize();

}