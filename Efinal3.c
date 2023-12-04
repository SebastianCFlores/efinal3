#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_size < 2) {
        fprintf(stderr, "Este programa requiere al menos 2 procesos.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int mi_mensaje = world_rank;

    MPI_Sendrecv(&mi_mensaje, 1, MPI_INT, (world_rank + 1) % world_size, 0,
                 &mi_mensaje, 1, MPI_INT, (world_rank - 1 + world_size) % world_size, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Proceso %d: Recibí el mensaje %d de mi vecino.\n", world_rank, mi_mensaje);

    MPI_Finalize();

    return 0;
}
