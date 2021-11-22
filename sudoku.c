//Sudoku sequencial backtracking

#include <stdio.h>
#include <time.h>

int contador = 0;

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

int number_unassigned(int *row, int *col)
{
/*
Verifica se existe pelo menos uma posição que não esteja preenchida. caso seja encontrada, 
a função vai alterar os valores da linha e da coluna e voltar para a função que a chamou
*/
    int i,j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if(grid[i][j] == 0)
            {
                //troca os valores de row e col se encontrar uma posição vazia
                *row = i;
                *col = j;
                return 1;
            }
        }
    }
    return 0;
}

int is_safe(int n, int row, int col)
{
/*
Verifica se o número pode ser colocado na posição grid[r][c] ou não,
retornará 1 se o número não estiver na linha r, coluna c e na submatriz analisada
*/
    int i,j;

    //verifica se o número está na linha. se sim, retorna 0 (not safe)
    for(i=0;i<N;i++)
    {
        if(grid[row][i] == n)
            return 0; 
    }

    //verifica se o número está na coluna. se sim, retorna 0 (not safe)
    for(i=0;i<N;i++)
    {
        if(grid[i][col] == n)
            return 0;
    }

    //verifica se o número está na submatriz (nSubmatriz)x(nSubmatriz). se sim, retorna 0 (not safe)
    int row_start = (row/nSubmatriz)*nSubmatriz;
    int col_start = (col/nSubmatriz)*nSubmatriz;
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

int solve_sudoku()
{
    //print_sudoku();
    int row, col;
    contador++;

    //os endereços de row e col são passadas por referência para que, caso seja encontrado uma posição vazia,
    //a função alterará os valores da coluna e linha
    if(number_unassigned(&row, &col) == 0) //se todas as posições já estiverem diferentes de 0, o sudoku está resolvido
        return 1;

    int n,i;

    for(i=1;i<=N;i++)
    {
        //verifica se o número i pode ser colocado na posição grid[row][col], se sim, substitui e chama a recursão
        if(is_safe(i, row, col))
        {
            grid[row][col] = i;

            // backtracking
            if(solve_sudoku())
                return 1;

            //se a solução não der certo ao atribuir o número i na posição da grid[row][col], coloca 0 novamente na posição
            grid[row][col]=0;
        }
    }
    return 0;
}

int main() {
    printf("---Sudoku  Inicial---\n\n");
    print_sudoku();

    clock_t tempo = clock();
    if (solve_sudoku()) {
        float tempoFinal = (float)((clock() - tempo)*1.0 / CLOCKS_PER_SEC);
        printf("\n--Sudoku  Resolvido--\n");
        printf("* Tempo de execução: %.5f s\n", tempoFinal);
        printf("* A funcao de solve foi chamada %d vezes.\n\n", contador);
        print_sudoku();
    } else {
        printf("\nSem solução para o sudoku proposto\n");
    }

    return 0;
}
