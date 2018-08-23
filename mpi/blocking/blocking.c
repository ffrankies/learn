#include "blocking.h"

int main(int argc, char* argv[]) {

    int numtasks, taskid, hostnamelen, received_msg;
    MPI_Request request;
    MPI_Status status;
    char host[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Get_processor_name(host, &hostnamelen);

    if (taskid == MASTER_TASK) {
        printf("I'm the master task. There are %d tasks running.\n", numtasks);
    }

    int partner;

    if (taskid < numtasks/2) {
        partner = numtasks/2 + taskid;
    } else {
        partner = taskid - numtasks/2;
    }

    MPI_Isend(&taskid, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &request);
    MPI_Recv(&received_msg, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);

    MPI_Waitall(1, &request, &status);

    printf("I'm task %d, my partner is %d, received message from %d.\n", taskid, partner, received_msg);
    
    MPI_Finalize();

}
