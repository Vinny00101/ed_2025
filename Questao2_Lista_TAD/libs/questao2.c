#include "questao2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aluno
{
    char nome[40];
    int idade;
    char matricula[16];
};
struct professor
{
    char nome[40];
    char disciplina[30];
    int id;
};
struct sala
{
    char codigo[10];
    int capacidade;
    int qtd_alunos;
    Aluno *alunos;
};
struct escola
{
    char nome[50];
    char municipio[40];
    int qtd_professores;
    Professor *professores;
    int qtd_salas;
    Sala *salas;
};

Professor* criar_professor(const char *nome, const char *disciplina, int id){
    Professor *prof = (Professor *)malloc(sizeof(Professor));
    if(prof == NULL){
        printf("Erro ao tentar alocar");
        return NULL;
    }
    snprintf(prof->nome, sizeof(prof->nome), "%s", nome);
    snprintf(prof->disciplina, sizeof(prof->disciplina), "%s", disciplina);
    prof->id = id;

    return prof;
}

Escola* criar_escola(const char *nome, const char *municipio){
    Escola *nome_escola = (Escola *)malloc(sizeof(Escola));
    if(nome_escola == NULL){
        printf("Erro ao tentar alocar");
        return NULL;
    }
    snprintf(nome_escola->nome, sizeof(nome_escola->nome), "%s", nome);
    snprintf(nome_escola->municipio, sizeof(nome_escola->municipio), "%s", municipio);
    nome_escola->qtd_professores = 0;
    nome_escola->professores = NULL;
    nome_escola->qtd_salas = 0;
    nome_escola->salas = NULL;
    return nome_escola;
}

void cadastrar_escola(Escola *escolas, int *qtd_escolas){
    char nome[50];
    char municipio[40];

    printf("Digite o nome da escola: ");
    scanf(" %[^\n]", nome);
    printf("Digite o município da escola: ");
    scanf(" %[^\n]", municipio);

    Escola *nova_escola = criar_escola(nome, municipio);

    if(nova_escola == NULL){
        printf("Erro ao criar a nova escola.\n");
        free(nova_escola);
        return;
    }
    escolas = (Escola *)realloc(escolas, (*qtd_escolas + 1) * sizeof(Escola));

    if(escolas == NULL){
        printf("Erro ao alocar memória para a lista de escolas.\n");
        free(nova_escola);
        return;
    }

    escolas[*qtd_escolas] = *nova_escola;
    (*qtd_escolas)++;
    free(nova_escola);
    printf("Escola cadastrada com sucesso!\n");

}

void listar_escolas(Escola *escolas, int qtd_escolas){
    if (qtd_escolas == 0){
        printf("Nenhuma escola cadastrada.\n");
        return;
    }
    for (int i = 0; i < qtd_escolas; i++){
        printf("Escola %d:\n", i + 1);
        printf("Nome: %s\n", escolas[i].nome);
        printf("Município: %s\n", escolas[i].municipio);
        printf("Quantidade de Professores: %d\n", escolas[i].qtd_professores);
        printf("Quantidade de Salas: %d\n", escolas[i].qtd_salas);
        printf("-------------------------\n");
    }
}

void cadastrar_professor(Escola *escolas, int qtd_escolas){
    char nome_escola[50];
    printf("Informe o nome da escola para colocar o professor\n");
    scanf(" %[^\n]", nome_escola);

    int found = 0, index;
    for (int i = 0; i < qtd_escolas; i++)
    {
        if(strcmp(escolas[i].nome, nome_escola) == 0){
            found = 1;
            index = i;
        }
    }

    if (!found){
        printf("Escola nao encontrada\n");
        cadastrar_professor(escolas, qtd_escolas);
        return;
    }
    
    char nome[40];
    char disciplina[30];
    int id;

    printf("Informe o id do professor\n");
    scanf("%d",&id);

    int found = 0;
    for (int i = 0; i < escolas[index].qtd_professores; i++)
    {
        if (escolas[index].professores->id == id )
        {
            found = 1;
        }
    }
    
    if(found){
        printf("Id ja usado por um professor\n");
        cadastrar_professor(escolas, qtd_escolas);
        return;
    }

    printf("Digite o nome da escola: \n");
    scanf(" %[^\n]", nome);
    printf("Digite o nome da disciplina da escola: \n");
    scanf(" %[^\n]", disciplina);

    Professor *prof = criar_professor(nome, disciplina, id);

    if(prof == NULL){
        printf("Erro ao criar o novo professor.\n");
        free(prof);
        return;
    }

    escolas[index].professores = (Professor *)realloc(escolas[index].professores, (escolas[index].qtd_professores + 1) * sizeof(Professor));

    if(escolas[index].professores == NULL){
        printf("Erro ao alocar memória para a lista de professores.\n");
        free(prof);
        return;
    }

    escolas[index].professores[escolas[index].qtd_professores++] = *prof;
    printf("Professor cadastrado com sucesso!\n");
    free(prof);
}

void cadastrar_sala(Escola *escolas, int qtd_escolas){

}
void cadastrar_aluno(Escola *escolas, int qtd_escolas){

}
void remover_aluno(Escola *escolas, int qtd_escolas){

}
void mover_aluno(Escola *escolas, int qtd_escolas){

}
void listar_professores(Escola *escolas, int qtd_escolas){

}
void listar_salas_alunos(Escola *escolas, int qtd_escolas){

}
void liberar_memoria(Escola *escolas, int qtd_escolas){
    
}

void menu(){
    printf("1. Cadastrar escola\n");
    printf("2. Listar escolas\n");
    printf("3. Cadastrar professor\n");
    printf("4. Cadastrar sala\n");
    printf("5. Cadastrar aluno\n");
    printf("6. Remover aluno\n");
    printf("7. Mover aluno\n");
    printf("8. Listar professores\n");
    printf("9. Listar salas e alunos\n");
    printf("10. Sair\n");
}