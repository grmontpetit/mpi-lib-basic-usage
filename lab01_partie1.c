#include <stdio.h>
#include "lab01_partie1.h"
#include "mpi.h"
#include <unistd.h>
#include <stdlib.h>
//#include <iostream>

void resoudreProbUn(int valeur, int alteration) {

    int j, k, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (k = 0; k <= alteration; k++) {
        for (j = 0; j < taille_matrice; j++) {
            // Lorsque k est egal a zero, on instancie la matrice 1
            if (k == 0) {
                matrice[rank][j] = valeur;
            }
            //~ // Lorsque k n'est pas egal a 0, on calcule matrice2
            // avec la matrice
            else {
                usleep(1000);
                matrice2[j] = matrice[rank][j] + (rank + j) * k;
                matrice[rank][j] = matrice2[j];

            }
        }
    }				// Fin du premier for
    MPI_Gather(matrice2, taille_matrice, MPI_INT, matrice, taille_matrice,
    MPI_INT, 0, MPI_COMM_WORLD);
}

void resoudreProbDeux(int valeur, int alteration) {

    int rank, j, k;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (k = 0; k <= alteration; k++) {
        for (j = 0; j < taille_matrice; j++) {
            // Lorsque k est egal a zero, on instancie la matrice 1
            if (k == 0) {
                matrice[rank][j] = valeur;
            }
            // Lorsque k n'est pas egal a 0 et que c'est la 1re
            // colonne
            else if (j == 0) {
                usleep(1000);
                matrice2[j] = matrice[rank][j] + (rank * k);
                matrice[rank][j] = matrice2[j];
            }
            // Lorsque k n'est pas egal a 0 et que c'est autre
            // que la 1re colonne
            else {
                usleep(1000);
                matrice2[j] = matrice[rank][j] + matrice[rank][j - 1] * k;
                matrice[rank][j] = matrice2[j];
            }
        }
    }
    MPI_Gather(matrice2, taille_matrice, MPI_INT, matrice, taille_matrice,
    MPI_INT, 0, MPI_COMM_WORLD);
}

void afficherMatrice() {
    int i, j, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {

        for (i = 0; i < taille_matrice; i++) {
            for (j = 0; j < taille_matrice; j++) {
                printf("%d ", matrice[i][j]);
            }
            printf("\n");
        }
    }

}

int main(int argc, char *argv[]) {
    int err;
    err = MPI_Init(&argc, &argv);
    if (err < 0)
        exit(1);
    int probleme = 0;
    int alteration = 0;
    int valeur = 0;
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc != 4) {
        printf(
                "Utilisation: lab01_partie1 noProbbleme nbAlterations valeurInitiale");
        err = MPI_Finalize();
        return 0;
    }

    probleme = atoi(argv[1]);
    alteration = atoi(argv[2]);
    valeur = atoi(argv[3]);

    if (probleme == 1) {
        if (rank == 0)
            printf("Solution au probleme no 1: \n");
        resoudreProbUn(valeur, alteration);

        afficherMatrice();
        if (rank == 0)
            printf("probleme1 resolu");

    } else if (probleme == 2) {
        if (rank == 0)
            printf("Solution au probleme no 2: \n");
        resoudreProbDeux(valeur, alteration);
        afficherMatrice();
    } else {
        printf("Aucun probleme selectionne, le programme se termine\n");
    }

    err = MPI_Finalize();
    return 0;
}
