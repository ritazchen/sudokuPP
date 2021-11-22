//Sudoku utilizando threads backtracking

#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define N 16
#define nSubmatriz 4 //raiz quadrada de N

/*
int grid[N][N] = {
    {6,5,0,8,7,3,0,9,0},
    {0,0,3,2,5,0,0,0,8},
    {9,8,0,1,0,4,3,5,7},
    {1,0,5,0,0,0,0,0,0},
    {4,0,0,0,0,0,0,0,2},
    {0,0,0,0,0,0,5,0,3},
    {5,7,8,3,0,1,0,2,6},
    {2,0,0,0,4,8,9,0,0},
    {0,9,0,6,2,5,0,8,1}
};

int grid[N][N] = {
	{3,0,6,5,0,8,4,0,0},
	{5,2,0,0,0,0,0,0,0},
	{0,8,7,0,0,0,0,3,1},
	{0,0,3,0,1,0,0,8,0},
	{9,0,0,8,6,3,0,0,5},
	{0,5,0,0,9,0,6,0,0},
	{1,3,0,0,0,0,2,5,0},
	{0,0,0,0,0,0,0,7,4},
	{0,0,5,2,0,6,3,0,0} 
};

int grid[N][N] = {
    1,3,0,0,6,0,0,2,5, 
    0,0,0,0,5,0,0,0,0, 
    0,0,6,1,0,7,9,0,0, 
    0,0,5,6,3,9,4,0,0, 
    0,0,0,0,0,0,0,0,0,
    9,0,2,0,4,0,3,0,7, 
    0,5,0,8,0,3,0,7,0, 
    0,0,7,0,0,0,8,0,0, 
    4,0,0,0,0,0,0,0,6
};

int grid[N][N] = {
    8,0,0,0,0,0,0,0,0,
    0,0,3,6,0,0,0,0,0,
    0,7,0,0,9,0,2,0,0,
    0,5,0,0,0,7,0,0,0,
    0,0,0,0,4,5,7,0,0,
    0,0,0,1,0,0,0,3,0,
    0,0,1,0,0,0,0,6,8,
    0,0,8,5,0,0,0,1,0,
    0,9,0,0,0,0,4,0,0
};
*/
int grid[N][N] = {
	{0,0,0,0,6,7,0,15,0,0,10,0,9,0,0,0},
	{0,14,10,13,0,0,11,9,1,12,0,6,0,5,0,0},
	{16,0,0,9,0,0,1,4,3,13,14,11,10,0,8,0},
	{0,12,0,5,2,0,0,0,0,0,15,0,1,0,0,11},
	{11,0,0,0,9,0,0,0,12,0,0,0,5,0,13,7},
	{5,4,14,0,11,15,6,13,0,0,0,10,0,0,0,0},
	{0,0,0,15,7,5,0,0,2,0,9,0,0,12,0,14},
	{9,0,0,0,0,1,10,0,0,0,0,13,0,0,0,15},
	{0,10,0,0,0,16,0,0,0,0,0,3,2,0,15,8},
	{0,0,0,14,0,0,0,6,0,11,0,9,13,0,7,1},
	{15,0,0,11,0,2,0,14,0,0,7,0,0,0,0,5},
	{0,0,12,0,1,0,0,0,0,0,0,0,14,0,0,9},
	{12,0,13,8,16,10,0,11,0,1,2,0,0,0,0,0},
	{0,0,0,3,0,6,0,0,0,8,0,12,0,0,0,0},
	{14,0,0,4,0,0,12,0,15,16,13,0,8,0,11,0},
	{0,0,15,0,0,4,0,0,6,3,0,0,0,0,2,13}
};

int vetorPossiveis[N], contVetorPossiveis = 0;
int contadorRecursao[N];
int grids[N][N][N];
int solucao = 0;
float tempoFinal = -1;
clock_t tempo;
pthread_mutex_t mutex;

/* void print_sudoku()
{
    int i,j;
    for(i=0;i<N;i++) {
        for(j=0;j<N;j++) {
            printf("%d ",grid[i][j]);
            if(j == 2 || j == 5) {
                printf("| ");
            }
        }
        printf("\n");
        if(i == 2 || i == 5){
            printf("---------------------\n");
        }
    }
    printf("\n");
} */

void print_sudoku()
{
    int i,j;
    for(i=0;i<N;i++) {
        for(j=0;j<N;j++) {
            printf("%d ",grid[i][j]);
            if(j == 3 || j == 7 || j == 11) {
                printf("\t| ");
            }
        }
        printf("\n");
        if(i == 3 || i == 7 || i == 11){
            printf("------------------------------------------------------------\n");
        }
    }
    printf("\n");
}

void print_grids(int id)
{
    int i,j;
    for(i=0;i<N;i++) {
        for(j=0;j<N;j++) {
            printf("%d ",grids[id][i][j]);
            if(j == 3 || j == 7 || j == 11) {
                printf("\t| ");
            }
        }
        printf("\n");
        if(i == 3 || i == 7 || i == 11){
            printf("------------------------------------------------------------\n");
        }
    }
    printf("\n");
}

int number_unassigned(int *row, int *col)
{
    int num_unassign = 0;
    int i,j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if(grid[i][j] == 0)
            {
                *row = i;
                *col = j;
                num_unassign = 1;
                return num_unassign;
            }
        }
    }
    return num_unassign;
}

int is_safe(int n, int r, int c)
{
    int i,j;

    for(i=0;i<N;i++)
    {
        if(grid[r][i] == n)
            return 0; 
    }

    for(i=0;i<N;i++)
    {
        if(grid[i][c] == n)
            return 0;
    }

    int row_start = (r/nSubmatriz)*nSubmatriz;
    int col_start = (c/nSubmatriz)*nSubmatriz;
    for(i=row_start;i<row_start+nSubmatriz;i++)
    {
        for(j=col_start;j<col_start+nSubmatriz;j++)
        {
            if(grid[i][j]==n)
                return 0;
        }
    }
    return 1;
}

int check_first_position_unassigned() {
    int row, col, n, i, j, k;
    
    //procura a primeira célula vazia da matriz e retorna a posição (row,col) para adicionar um número nessa posição
    if(number_unassigned(&row, &col) == 0)
        return 1;

    //como a célula[row][col] é vazia, vamos ver quais são as possibilidades de numeros para colocar nessa posição
    for(i=1;i<=N;i++)
    {
        //verifica se é possível colocar o número i dentro daquela posição sem quebrar as restrições
        if(is_safe(i, row, col))
        {
            //vetorPossiveis guarda os números possíveis pra colocar naquela célula vazia
            vetorPossiveis[contVetorPossiveis] = i;
            contVetorPossiveis++; //incrementa o tamanho do vetor de números possíveis
        }
    }

    if(contVetorPossiveis > 0) {
        //faz (contVetorPossiveis) copias da grid inicial
        for(i = 0; i < contVetorPossiveis; i++){
            for(j = 0; j < N; j++) {
                for(k = 0; k < N; k++) {
                    grids[i][j][k] = grid[j][k];
                }
            }
            grids[i][row][col] = vetorPossiveis[i]; //coloca o número da possibilidade naquela posição em braco
        }
    }
    return 0;
}

int number_unassigned_solve(int *row, int *col, int id)
{
    int num_unassign = 0;
    int i,j;

    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if(grids[id][i][j] == 0)
            {
                *row = i;
                *col = j;
                num_unassign = 1;
                return num_unassign;
            }
        }
    }
    return num_unassign;
}

int is_safe_solve(int n, int r, int c, int id)
{
    int i,j;

    for(i=0;i<N;i++)
    {
        if(grids[id][r][i] == n)
            return 0; 
    }

    for(i=0;i<N;i++)
    {
        if(grids[id][i][c] == n)
            return 0;
    }

    int row_start = (r/nSubmatriz)*nSubmatriz;
    int col_start = (c/nSubmatriz)*nSubmatriz;
    for(i=row_start;i<row_start+nSubmatriz;i++)
    {
        for(j=col_start;j<col_start+nSubmatriz;j++)
        {
            if(grids[id][i][j]==n)
                return 0;
        }
    }
    return 1;
}

void* solve_sudoku(void* args)
{
    if(solucao) {
        return (void*)1;
    }

    int row, col, i, j, k;
    int* current_thread = (int*) args;
    contadorRecursao[*current_thread]++;

    if(number_unassigned_solve(&row, &col, *current_thread) == 0) {
        pthread_mutex_lock(&mutex);
        solucao = *current_thread;
        tempoFinal = (float)((clock() - tempo)*1.0 / CLOCKS_PER_SEC);
        pthread_mutex_unlock(&mutex);
        return (void*)1;
    }

    for(i=1;i<=N;i++)
    {
        if(is_safe_solve(i, row, col, *current_thread))
        {
            grids[*current_thread][row][col] = i;

            if(solve_sudoku(args))
                return (void*)1;

            grids[*current_thread][row][col]=0;
        }
    }
    return (void*)0;
}

int main() {
    printf("---Sudoku  Inicial---\n\n");
    print_sudoku();

    int i; 
    //inicializa o vetor de números possíveis para a primeira posição em branco (com valor 0) e o contador como 1
    for(i = 0; i < N; i++) {
        vetorPossiveis[i] = 0;
        contadorRecursao[i] = 1;
    }
    
    tempo = clock();

    check_first_position_unassigned();

    if(contVetorPossiveis > 0) {
        //cria (contVetorPossiveis) threads para resolver cada copia da matriz possível
        pthread_t thread[contVetorPossiveis];
        int current_thread[contVetorPossiveis];
        pthread_mutex_init(&mutex, NULL);

        for(i = 0; i < contVetorPossiveis; i++) {
            current_thread[i] = i;
            pthread_create(&thread[i], NULL, solve_sudoku, (void*)&current_thread[i]);
        }

        for(i = 0; i < contVetorPossiveis; i++) {
            pthread_join(thread[i], NULL);
        }
        pthread_mutex_destroy(&mutex);
    }

    printf("vetor de possiveis:\n");
    for(i = 0; i < contVetorPossiveis; i++) {
        printf("%d ", vetorPossiveis[i]);
    }
    if(tempoFinal > 0) {
        printf("\n--Sudoku  Resolvido! --\n");
        printf("* Tempo de execução: %.5f s\n", tempoFinal);
        printf("Contador = %d\n", contadorRecursao[solucao]);
        print_grids(solucao);
        printf("\n");
    }
    else {
        printf("\nSem solução para o sudoku\n");
    }

    return 0;
}
