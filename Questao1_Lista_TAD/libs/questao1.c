#include "questao1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define matriz_L 20
#define matriz_C 30
#define GRAMA 'G'
#define RUA 'R'
#define CASA 'C'

struct pessoa
{
    char nome[50];
    int idade;
    int num_casa;
};

struct casa
{
    int numero;
    int capacidade;
    Pessoa *moradores;
    int qtr_m;
};

struct mapa
{
    char tipo;
    Casa *casa;
};

void exibir_mapa(Mapa **mapa){
    for (int i = 0; i < matriz_L; i++) {
        for (int j = 0; j < matriz_C; j++) {
            printf("%c ", mapa[i][j].tipo);
        }
        printf("\n");
    }
}

Mapa **criar_mapa(){
    Mapa **mapa = (Mapa **)malloc( matriz_L * sizeof(Mapa*));
    if (mapa == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para o mapa.\n");
        return NULL;
    }
    for (int i = 0; i < matriz_L; i++)
    {
        mapa[i] = (Mapa*)malloc(matriz_C * sizeof(Mapa));
        if (mapa[i] == NULL) {
            fprintf(stderr, "Erro ao alocar memoria para o mapa[%d].\n", i);
            for (int j = 0; j < i; j++) {
                free(mapa[j]);
            }
            free(mapa);
            return NULL;
        }
    }
    for (int i = 0; i < matriz_L; i++) {
        for (int j = 0; j < matriz_C; j++) {
            mapa[i][j].tipo = GRAMA; 
            mapa[i][j].casa = NULL;
        }
    }
    return mapa;
}

Casa *criar_casa(Mapa **mapa){
    int numero_casa;
    printf("Informe o numero da casa\n");
    scanf("%d",&numero_casa);

    if (numero_casa < 0){
        printf("Numero invalido\n");
        return criar_casa(mapa);
    }

    int isNum_Casa = 0;
    for (int i = 0; i < matriz_L; i++) {
        for (int j = 0; j < matriz_C; j++) {
            if (mapa[i][j].casa == NULL){
                continue;
            }
            if (mapa[i][j].casa->numero == numero_casa){
                isNum_Casa = 1;
            }
        }
    }

    if (isNum_Casa){
        printf("Numero informado da casa ja existe\n");
        return criar_casa(mapa);
    }
    

    Casa *casa = (Casa*)malloc(sizeof(Casa));

    if (casa == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para o mapa.\n");
        return NULL;
    }

    casa->numero = numero_casa;
    printf("Informe a capacidade da casa\n");
    scanf("%d",&casa->capacidade);
    casa->moradores = (Pessoa*)malloc(casa->capacidade * sizeof(Pessoa));
    casa->qtr_m = 0;
    
    if (casa->moradores == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para os moradores.\n");
        free(casa);
        return NULL;
    }

    return casa;
}

Pessoa *criar_pessoa(Mapa **mapa, int index_I, int index_J){
    Pessoa *pessoa = (Pessoa*)malloc(mapa[index_I][index_J].casa->capacidade * sizeof(Pessoa));
    if (pessoa == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para a pessoa.\n");
        return NULL;
    }
    return pessoa;
}

void buscar_casa_pelo_numero(Mapa **mapa, int numero_casa, int *verifyCasaNum, int *index_I, int *index_J){
    for (int i = 0; i < matriz_L; i++) {
        for (int j = 0; j < matriz_C; j++) {
            if (mapa[i][j].casa == NULL){
                continue;
            }
            if (mapa[i][j].casa->numero == numero_casa){
                *verifyCasaNum = 0;
                *index_I = i;
                *index_J = j;
            }
        }
    }
}

void inserir_casa(Mapa **mapa){
    int linha, coluna;
    printf("Informe a linha e a coluna que deseja colocar sua casa\n");
    scanf("%d %d", &linha, &coluna);
    if ((linha > matriz_L || linha < 0 ) || (coluna > matriz_C || coluna < 0)){
        printf("Essa areas nao corresponde a area do mapa\n");
        return;
    }
    if(mapa[linha][coluna].tipo == RUA){
        printf("Essa posicao nao pode colocar uma casa, pois tem uma rua\n");
    }
    mapa[linha][coluna].tipo = CASA;
    mapa[linha][coluna].casa = criar_casa(mapa);

    printf("Casa inserida com sucesso\n");
    exibir_mapa(mapa);
}

void adicionar_morador(Mapa **mapa){
    int numero_casa;
    printf("Informe o numero da casa\n");
    scanf("%d",&numero_casa);

    if (numero_casa < 0){
        printf("Numero invalido\n");
        criar_casa(mapa);
        return;
    }

    int verifyCasaNum = 1, index_I, index_J;
    buscar_casa_pelo_numero(mapa, numero_casa, &verifyCasaNum, &index_I, &index_J);

    if (verifyCasaNum){
        printf("Casa nao encontrada\n");
        adicionar_morador(mapa);
        return;
    }

    if (mapa[index_I][index_J].casa->qtr_m >= mapa[index_I][index_J].casa->capacidade){
        printf("Essa casa esta cheia\n");
        adicionar_morador(mapa);
        return;
    }

    if (mapa[index_I][index_J].casa->moradores == NULL) {
        criar_pessoa(mapa, index_I, index_J);
        return;
    }

    printf("Informe o nome do morador\n");
    scanf(" %[^\n]s", mapa[index_I][index_J].casa->moradores[
        mapa[index_I][index_J].casa->qtr_m
    ].nome);
    printf("Informe a idade do morador\n");
    scanf("%d",&mapa[index_I][index_J].casa->moradores[
        mapa[index_I][index_J].casa->qtr_m
    ].idade);
    mapa[index_I][index_J].casa->moradores[
        mapa[index_I][index_J].casa->qtr_m
    ].num_casa = numero_casa;
    mapa[index_I][index_J].casa->qtr_m++;

    printf("Morador adicionado com sucesso\n");
    exibir_mapa(mapa);
}

void remover_morador(Mapa **mapa){
    int numero_casa;
    printf("Informe o numero da casa\n");
    scanf("%d",&numero_casa);

    if (numero_casa < 0){
        printf("Numero invalido\n");
        criar_casa(mapa);
        return;
    }

    int verifyCasaNum = 1, index_I, index_J;
    buscar_casa_pelo_numero(mapa, numero_casa, &verifyCasaNum, &index_I, &index_J);

    if (verifyCasaNum){
        printf("Casa nao encontrada\n");
        adicionar_morador(mapa);
        return;
    }

    if (mapa[index_I][index_J].casa->qtr_m == 0){
        printf("Essa casa nao tem moradores\n");
        return;
    }

    char nome[50];
    printf("Informe o nome do morador que deseja remover\n");
    scanf(" %[^\n]s", nome);

    int found_pessoa = 0;

    for (int i = 0; i < mapa[index_I][index_J].casa->qtr_m; i++)
    {
        if (strcmp(mapa[index_I][index_J].casa->moradores[i].nome, nome) == 0){
            found_pessoa = 1;
            for (int j = i; j < mapa[index_I][index_J].casa->qtr_m - 1; j++)
            {
                mapa[index_I][index_J].casa->moradores[j] = mapa[index_I][index_J].casa->moradores[j + 1];
            }
            mapa[index_I][index_J].casa->qtr_m--;
            printf("Morador removido com sucesso\n");
            break;
        }
    }
    if (!found_pessoa){
        printf("Morador nao encontrado\n");
        return;
    }
    exibir_mapa(mapa);
}

void remover_casa(Mapa **mapa){
    int numero_casa;
    printf("Informe o numero da casa\n");
    scanf("%d",&numero_casa);

    if (numero_casa < 0){
        printf("Numero invalido\n");
        criar_casa(mapa);
        return;
    }

    int verifyCasaNum = 1, index_I, index_J;
    buscar_casa_pelo_numero(mapa, numero_casa, &verifyCasaNum, &index_I, &index_J);

    if (verifyCasaNum){
        printf("Casa nao encontrada\n");
        adicionar_morador(mapa);
        return;
    }

    free(mapa[index_I][index_J].casa->moradores);
    free(mapa[index_I][index_J].casa);
    mapa[index_I][index_J].casa = NULL;
    mapa[index_I][index_J].tipo = GRAMA;

    printf("Casa removida com sucesso\n");
    exibir_mapa(mapa);
}

void colocar_rua_grama(Mapa **mapa){
    int linha, coluna;
    printf("Informe a linha e a coluna para colocar rua ou grama\n");
    scanf("%d %d", &linha, &coluna);

    if (linha < 0 || linha >= matriz_L || coluna < 0 || coluna >= matriz_C){
        printf("Posicao invalida\n");
        return;
    }

    if (mapa[linha][coluna].casa != NULL){
        printf("Ja existe uma casa nessa posicao\n");
        return;
    }

    mapa[linha][coluna].tipo = (mapa[linha][coluna].tipo == RUA) ? GRAMA : RUA;
    exibir_mapa(mapa);
}

void liberar_mapa(Mapa **mapa){
    for (int i = 0; i < matriz_L; i++) {
        for (int j = 0; j < matriz_C; j++) {
            if (mapa[i][j].casa != NULL) {
                free(mapa[i][j].casa->moradores);
                free(mapa[i][j].casa);
            }
        }
        free(mapa[i]);
    }
    free(mapa);
}

void menu(){
    printf("Menu:\n");
    printf("1. Inserir casa\n");
    printf("2. Adicionar morador\n");
    printf("3. Remover morador\n");
    printf("4. Remover casa\n");
    printf("5. Colocar rua ou grama\n");
    printf("6. Sair\n");
}