#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>


int minDistance(double dist[], bool sptSet[], int n)
{
    //calculez distanta minima
    int min = INT_MAX, min_index, i;
    for (i = 0; i < n; i++)
    {
        if (sptSet[i] == false && dist[i] <= min)
            min = dist[i], min_index = i;
    }
    return min_index;
}

void dijkstra(double **M, int src, int n, int id_magazin, int *magazin, int *path, double *suma)
{
    int i, j;
    double dist[1000];
    // in dist retin distantele de la sursa la toate nodurile
    bool sptSet[1000];
    // vectorul de vizite
    for (i = 0; i < n; i++)
    {
        path[i] = src;
        dist[i] = INT_MAX, sptSet[i] = false;
    }
    dist[src] = 0;
    for (i = 0; i < n; i++)
    {
        int u = minDistance(dist, sptSet, n);
        // calculez nodul cel mai apropiat
        sptSet[u] = true;
        for (j = 0; j < n && sptSet[id_magazin] == false; j++)
        {
            if (!sptSet[j] && M[u][j] && dist[u] != INT_MAX && dist[u] + M[u][j] < dist[j])
            {
                path[j] = u;
                dist[j] = dist[u] + M[u][j];
            }
        }
    }
    *suma = *suma + dist[id_magazin];
    printf("%.1lf", dist[id_magazin]);
}

void print_path(int src, int dst, int *path)
{
    if (src != dst)
    {
        print_path(path[src], dst, path);
        printf(" %d", src);
    }
}
void print_path_first(int src, int dst, int *path, int *nr_drum, int *drum)
{
    if (src != dst)
    {
        print_path_first(path[src], dst, path, nr_drum, drum);
        *nr_drum = *nr_drum + 1;
        drum[*nr_drum] = src;
    }
}


void DFS(int i, int n, double **M, int *visited, int *depo, int d, int parc2)
{
    int j, ok = 0, k;
    visited[i] = visited[i] + 1;
    for (j = 0; j < n; j++)
    {
        ok = 0;
        for (k = 0; k < d; k++)
        {
            if (j == depo[k])
            {
                ok = 1;
            }
        }
        if (visited[j] == 0 && M[i][j] != 0 && ok == 0 && parc2 == 0)
            DFS(j, n, M, visited, depo, d, parc2);
        if (visited[j] == 1 && M[i][j] != 0 && ok == 0 && parc2 == 1)
            DFS(j, n, M, visited, depo, d, parc2);
    }
}

void InvMatrix(double **M, int n)
{
    double invM[50][50];
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            invM[j][i] = M[i][j];
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            M[i][j] = invM[i][j];
        }
    }
}

void DFS2(int i, int n, double **M, int *visited, int *depo, int d, double *suma, int *last, int parc)
{
    int j, ok = 0;
    visited[i] = visited[i] + 1;
    if (parc == 1 && M[i][*last] != 0)
    {
        *suma = *suma + M[i][*last];
        return;
    }
    for (j = 0; j < n; j++)
    {
        ok = 0;
        int k;
        for (k = 0; k < d; k++)
        {
            if (j == depo[k])
            {
                ok = 1;
            }
        }
        //pentru prima parcurgere
        if (visited[j] == 0 && M[i][j] != 0 && ok == 0 && parc == 0)
        {
            *suma = *suma + M[i][j];
            //adaug in suma costul drumului
            *last = j;
            //retin ultimul nod vizitat
            DFS2(j, n, M, visited, depo, d, suma, last, parc);
        }
        //pentru a doua parcurgere
        if (visited[j] == 0 && M[i][j] != 0 && parc == 1)
        {
            *suma = *suma + M[i][j];
            *last = j;
            //daca am ajuns la nodul sursa, ma opresc
            if (j == *last)
            {
                return;
            }
            DFS2(j, n, M, visited, depo, d, suma, last, parc);
        }
    }
}

int main()
{
    int n, m, d, u, v, i, j, *depo, nr, src, nr_magazine, k, *magazin, ok;
    // n=nr noduri; m=nr arce; d=nr depozite graf
    // u,v=id noduri; w=costul parcurgerii drumului dintre acestea
    // i,j,k= indexi; *depo=sirul depozitelor; nr=
    // src=sursa             ;ok= variabila cu care verific diverse conditii
    //*magazin=sirul magazinelor/clientilor
    double *suma, w;
    //*suma= costul total al traseului de la task 1
    char string[100];
    // in string retin id-ul task-ului
    suma = (double *)malloc(sizeof(double));
    *suma = 0;
    // aloc dinamic variabila suma si o initializez cu 0
    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%d", &d);
    double **M = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++)
    {
        M[i] = (double *)malloc(n * sizeof(double));
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            M[i][j] = 0;
        }
    }
    for (i = 0; i < m; i++)
    {
        scanf("%d", &u);
        scanf("%d", &v);
        scanf("%lf", &w);
        M[u][v] = w;
    }
    // am alocat dinamic matricea de adiacenta si am retinut in
    // aceasta datele grafului
    depo = (int *)malloc(d * sizeof(int));
    for (i = 0; i < d; i++)
    {
        scanf("%d", &depo[i]);
    }
    // am alocat dinamic variabila depo si am retinut datele de intrare
    scanf("%d", &nr);
    int count;
    for (count = 0; count < nr; count++)
    {
        *suma = 0;
        scanf("%s", string);
        // string=id
        if (strcmp(string, "e1") == 0)
        {
            scanf("%d", &src);
            // src=depozitul de la care plecam
            scanf("%d", &nr_magazine);
            // numarul de magazine la care vrem sa ajungem
            magazin = (int *)malloc(nr_magazine * sizeof(int));
            // vectorul de magazine
            for (i = 0; i < nr_magazine; i++)
            {
                scanf("%d", &magazin[i]);
                // iau de la tastatura magazinul i
                printf("%d\n", magazin[i]);
                int *drum;
                // retin dumul cel mai scurt de la sursa la magazin[i]
                int *path;
                // retin drumul cel mai scurt
                int *nr_drum;
                // nr_drum= lungimea drumului
                nr_drum = (int *)malloc(sizeof(int));
                drum = (int *)malloc(n * sizeof(int));
                path = (int *)malloc(n * sizeof(int));
                *nr_drum = 0;
                dijkstra(M, src, n, magazin[i], magazin, path, suma);
                printf(" ");
                drum[0] = src;
                // pentru ca plec de la sursa
                print_path_first(magazin[i], src, path, nr_drum, drum);
                dijkstra(M, magazin[i], n, src, magazin, path, suma);
                printf("\n");
                for (j = 0; j < *nr_drum + 1; j++)
                {
                    if (j == *nr_drum)
                    {
                        printf("%d", drum[j]);
                    }
                    else
                    {
                        printf("%d ", drum[j]);
                    }
                }
                // printez drumul de la sursa la magazin[i]
                print_path(src, magazin[i], path);
                // printez drumul de la magazin[i] la sursa
                printf("\n");
                free(drum);
                free(path);
                free(nr_drum);
            }
            free(magazin);
            printf("%.1lf", *suma);
            if (count < nr - 1)
            {
                printf("\n");
            }
        }
        if (strcmp(string, "e2") == 0 || strcmp(string, "e3") == 0)
        {
            double **M_initial = (double **)malloc(n * sizeof(double *));
            for (j = 0; j < n; j++)
            {
                M_initial[j] = (double *)malloc(n * sizeof(double));
            }
            // retin matricea initiala intr-o alta matrice, M_initial,
            // deoarece urmeaza sa inversez matricea
            int graf[1000], nr_conex = 1;
            for (j = 0; j < n; j++)
            {
                graf[j] = 0;
            }
            for (j = 0; j < d; j++)
            {
                graf[depo[j]] = -1;
            }
            // nu am voie sa trec prin depozite
            int nod = 0;
            for (j = 0; j < d; j++)
            {
                if (depo[j] == nod)
                {
                    nod++;
                }
            }
            // numar cate noduri pot vizita, inafara de depozite
            int start = nod;
            for (nod = start; nod < n; nod++)
            {
                int *visited;
                int parc2 = 0;
                // cu variavila parc2 (de la parcurgerea numarul 2)
                // voi verifica daca ma aflu la prima sau a doua parcurgere
                // cu algoritmul DFS
                visited = (int *)malloc(n * sizeof(int));
                for (j = 0; j < n; j++)
                {
                    visited[j] = 0;
                }
                // initial nu am niciun nod vizitat
                for (j = 0; j < n; j++)
                {
                    for (k = 0; k < n; k++)
                    {
                        M_initial[j][k] = M[j][k];
                    }
                }
                // salvez matricea initiala
                DFS(nod, n, M, visited, depo, d, parc2);
                InvMatrix(M, n);
                parc2 = 1;
                // am facut prima parcurgere, deci sunt la cea de a doua parcurgere
                DFS(nod, n, M, visited, depo, d, parc2);
                for (j = 0; j < n; j++)
                {
                    if (visited[j] == 2)
                    {
                        graf[j] = nr_conex;
                    }
                }
                // in vectorul graf retin componentele conexe,
                // iar prin variabile nr_conex, numar cate componente
                // conexe am
                // exemplu: daca am un graf cu 8 noduri si am 2 componente
                // conexe (1,2,6 si 3,5,7), si 0 nod depozit vectorul graf va arata
                // in felul urmator: -1 1 1 2 0 2 1 2
                // indici:            0 1 2 3 4 5 6 7
                ok = 0;
                // cu ok verific daca mai sunt noduri de cautat
                for (j = 0; j < n; j++)
                {
                    if (graf[j] == 0)
                    {
                        ok = 1;
                        nod = j - 1;
                        break;
                        // mai am de cautat
                    }
                }
                if (ok == 0)
                {
                    nod = n + 1;
                }
                if (ok == 1)
                {
                    nr_conex++;
                }
                free(visited);
            }
            if (strcmp(string, "e2") == 0)
            {
                printf("%d\n", nr_conex);
                for (j = 0; j < nr_conex; j++)
                {
                    ok = 0;
                    for (k = 0; k < n; k++)
                    {
                        if (graf[k] == j + 1)
                        {
                            if (ok == 1)
                            {
                                printf(" %d", k);
                            }
                            if (ok == 0)
                            {
                                printf("%d", k);
                            }
                            ok = 1;
                        }
                    }
                    if (j < nr_conex - 1)
                    {
                        printf("\n");
                    }
                }
            }
            int nr_nod, elimin;
            if (strcmp(string, "e3") == 0)
            {
                scanf("%d", &start);
                for (j = 0; j < start; j++)
                {
                    int t;
                    double sumM = 99999;
                    int *conex = calloc(n, sizeof(int));
                    for (k = 0; k < n; k++)
                    {
                        conex[k] = -1;
                    }
                    scanf("%d", &nr_nod);
                    //nr_nod= numarul de noduri care trebuiesc parcurse
                    for (k = 0; k < nr_nod; k++)
                    {
                        scanf("%d", &elimin);
                        conex[elimin] = 1;
                    }

                    for (t = 0; t < d; t++)
                    {
                        nod = depo[t];
                        double **M2 = (double **)malloc(n * sizeof(double *));
                        for (i = 0; i < n; i++)
                        {
                            M2[i] = (double *)malloc(n * sizeof(double));
                        }

                        for (i = 0; i < n; i++)
                        {
                            for (k = 0; k < n; k++)
                            {
                                M2[i][k] = M_initial[i][k];
                            }
                        }

                        for (k = 0; k < d; k++)
                        {
                            conex[depo[k]] = 1;
                        }
                        for (k = 0; k < n; k++)
                        {
                            if (conex[k] == -1)
                            {
                                for (i = 0; i < n; i++)
                                {
                                    M2[k][i] = 0;
                                    M2[i][k] = 0;
                                }
                            }
                        }
                        int *visited = malloc(n * sizeof(int));
                        *suma = 0;
                        for (i = 0; i < n; i++)
                        {
                            visited[i] = 0;
                        }
                        int last = 0;
                        int parc = 0;
                        //last= ultimul nod vizitat
                        //parc (de la parcurgere), tine cont daca e prima sau
                        // a doua parcurgere

                        DFS2(nod, n, M2, visited, depo, d, suma, &last, parc);
                        int aux = nod;
                        nod = last;
                        last = aux;
                        //acum fac parcurgerea de la ultimul nod vizitat la sursa
                        for (i = 0; i < n; i++)
                        {
                            visited[i] = 0;
                        }
                        parc = 1;

                        DFS2(nod, n, M2, visited, depo, d, suma, &last, parc);
                        if (last != aux)
                        {
                            *suma = *suma + M[aux][last];
                        }
                        //daca functia nu a adaugat si drumul de la last la sursa
                        //il adaug manual in main
                        if (*suma < sumM)
                            sumM = *suma;
                        free(visited);
                        for (i = 0; i < n; i++)
                        {
                            free(M2[i]);
                        }
                        free(M2);
                    }
                    free(conex);
                    printf("%.1lf", sumM);
                    if (j < start - 1)
                        printf("\n");
                }
            }
            for (i = 0; i < n; i++)
            {
                free(M_initial[i]);
            }
            free(M_initial);
        }
    }
    free(suma);
    for (i = 0; i < n; i++)
    {
        free(M[i]);
    }
    free(M);
    free(depo);
    return 0;
}