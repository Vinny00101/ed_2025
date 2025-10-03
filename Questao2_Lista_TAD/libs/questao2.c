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

// --- Funções de criação ---
Professor* criar_professor(const char *nome, const char *disciplina, int id){
    Professor *prof = (Professor *)malloc(sizeof(Professor));
    if(!prof){
        printf("Erro ao tentar alocar\n");
        return NULL;
    }
    snprintf(prof->nome, sizeof(prof->nome), "%s", nome);
    snprintf(prof->disciplina, sizeof(prof->disciplina), "%s", disciplina);
    prof->id = id;
    return prof;
}

Escola* criar_escola(const char *nome, const char *municipio){
    Escola *nome_escola = (Escola *)malloc(sizeof(Escola));
    if(!nome_escola){
        printf("Erro ao tentar alocar\n");
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

// --- Funções principais ---
void cadastrar_escola(Escola **escolas, int *qtd_escolas){
    char nome[50];
    char municipio[40];

    printf("Digite o nome da escola: ");
    scanf(" %[^\n]", nome);
    printf("Digite o município da escola: ");
    scanf(" %[^\n]", municipio);

    // Verifica duplicidade
    for(int i=0;i<*qtd_escolas;i++){
        if(strcmp((*escolas)[i].nome, nome)==0){
            printf("Escola já cadastrada!\n");
            return;
        }
    }

    Escola *nova_escola = criar_escola(nome, municipio);
    if(!nova_escola){
        printf("Erro ao criar a nova escola.\n");
        return;
    }

    *escolas = (Escola *)realloc(*escolas, (*qtd_escolas + 1) * sizeof(Escola));
    if(!*escolas){
        printf("Erro ao alocar memória para a lista de escolas.\n");
        free(nova_escola);
        return;
    }

    (*escolas)[*qtd_escolas] = *nova_escola;
    (*qtd_escolas)++;
    free(nova_escola);
    printf("Escola cadastrada com sucesso!\n");
}

void listar_escolas(Escola *escolas, int qtd_escolas){
    if(qtd_escolas == 0){
        printf("Nenhuma escola cadastrada.\n");
        return;
    }
    for(int i=0;i<qtd_escolas;i++){
        printf("Escola %d:\n", i+1);
        printf("Nome: %s\n", escolas[i].nome);
        printf("Município: %s\n", escolas[i].municipio);
        printf("Quantidade de Professores: %d\n", escolas[i].qtd_professores);
        printf("Quantidade de Salas: %d\n", escolas[i].qtd_salas);
        printf("-------------------------\n");
    }
}

void cadastrar_professor(Escola *escolas, int qtd_escolas){
    char nome_escola[50];
    printf("Informe o nome da escola para cadastrar o professor: ");
    scanf(" %[^\n]", nome_escola);

    int found = 0, index = -1;
    for(int i=0;i<qtd_escolas;i++){
        if(strcmp(escolas[i].nome,nome_escola)==0){
            found = 1;
            index = i;
            break;
        }
    }

    if(!found){
        printf("Escola não encontrada.\n");
        return;
    }

    int id;
    char nome[40];
    char disciplina[30];

    printf("Informe o id do professor: ");
    scanf("%d",&id);

    for(int i=0;i<escolas[index].qtd_professores;i++){
        if(escolas[index].professores[i].id == id){
            printf("Id já usado por outro professor.\n");
            return;
        }
    }

    printf("Informe o nome do professor: ");
    scanf(" %[^\n]", nome);
    printf("Informe a disciplina: ");
    scanf(" %[^\n]", disciplina);

    Professor *prof = criar_professor(nome, disciplina, id);
    if(!prof){
        printf("Erro ao criar o professor.\n");
        return;
    }

    escolas[index].professores = (Professor *)realloc(escolas[index].professores, (escolas[index].qtd_professores+1)*sizeof(Professor));
    if(!escolas[index].professores){
        printf("Erro ao alocar memória para professores.\n");
        free(prof);
        return;
    }

    escolas[index].professores[escolas[index].qtd_professores++] = *prof;
    free(prof);
    printf("Professor cadastrado com sucesso!\n");
}

void cadastrar_sala(Escola *escolas, int qtd_escolas){
    char nome_escola[50];
    printf("Informe o nome da escola para cadastrar a sala: ");
    scanf(" %[^\n]", nome_escola);

    int found = 0, index = -1;
    for(int i=0;i<qtd_escolas;i++){
        if(strcmp(escolas[i].nome,nome_escola)==0){
            found = 1;
            index = i;
            break;
        }
    }
    if(!found){
        printf("Escola não encontrada.\n");
        return;
    }

    char codigo[10];
    int capacidade;

    printf("Informe o código da sala: ");
    scanf(" %[^\n]", codigo);

    // Verifica duplicidade
    for(int i=0;i<escolas[index].qtd_salas;i++){
        if(strcmp(escolas[index].salas[i].codigo, codigo)==0){
            printf("Sala já cadastrada com este código.\n");
            return;
        }
    }

    printf("Informe a capacidade da sala: ");
    scanf("%d",&capacidade);

    Sala nova_sala;
    snprintf(nova_sala.codigo,sizeof(nova_sala.codigo),"%s",codigo);
    nova_sala.capacidade = capacidade;
    nova_sala.qtd_alunos = 0;
    nova_sala.alunos = NULL;

    escolas[index].salas = (Sala *)realloc(escolas[index].salas,(escolas[index].qtd_salas+1)*sizeof(Sala));
    if(!escolas[index].salas){
        printf("Erro ao alocar memória para salas.\n");
        return;
    }

    escolas[index].salas[escolas[index].qtd_salas++] = nova_sala;
    printf("Sala cadastrada com sucesso!\n");
}

void cadastrar_aluno(Escola *escolas, int qtd_escolas){
    char nome_escola[50];
    printf("Informe o nome da escola: ");
    scanf(" %[^\n]", nome_escola);

    int found = 0, index = -1;
    for(int i=0;i<qtd_escolas;i++){
        if(strcmp(escolas[i].nome,nome_escola)==0){
            found = 1;
            index = i;
            break;
        }
    }
    if(!found){
        printf("Escola não encontrada.\n");
        return;
    }

    char codigo_sala[10];
    printf("Informe o código da sala: ");
    scanf(" %[^\n]", codigo_sala);

    int sala_index = -1;
    for(int i=0;i<escolas[index].qtd_salas;i++){
        if(strcmp(escolas[index].salas[i].codigo,codigo_sala)==0){
            sala_index = i;
            break;
        }
    }
    if(sala_index == -1){
        printf("Sala não encontrada.\n");
        return;
    }

    if(escolas[index].salas[sala_index].qtd_alunos >= escolas[index].salas[sala_index].capacidade){
        printf("Sala cheia.\n");
        return;
    }

    Aluno novo_aluno;
    printf("Informe o nome do aluno: ");
    scanf(" %[^\n]", novo_aluno.nome);
    printf("Informe a idade do aluno: ");
    scanf("%d",&novo_aluno.idade);
    printf("Informe a matrícula do aluno: ");
    scanf(" %[^\n]", novo_aluno.matricula);

    // Verifica duplicidade de matrícula
    for(int i=0;i<escolas[index].qtd_salas;i++){
        for(int j=0;j<escolas[index].salas[i].qtd_alunos;j++){
            if(strcmp(escolas[index].salas[i].alunos[j].matricula, novo_aluno.matricula)==0){
                printf("Matrícula já cadastrada em outra sala.\n");
                return;
            }
        }
    }

    Sala *sala = &escolas[index].salas[sala_index];
    sala->alunos = (Aluno *)realloc(sala->alunos, (sala->qtd_alunos+1)*sizeof(Aluno));
    sala->alunos[sala->qtd_alunos++] = novo_aluno;

    printf("Aluno cadastrado com sucesso!\n");
}

void remover_aluno(Escola *escolas, int qtd_escolas){
    char nome_escola[50];
    printf("Informe o nome da escola: ");
    scanf(" %[^\n]", nome_escola);

    int found = 0, index = -1;
    for(int i=0;i<qtd_escolas;i++){
        if(strcmp(escolas[i].nome,nome_escola)==0){
            found = 1;
            index = i;
            break;
        }
    }
    if(!found){
        printf("Escola não encontrada.\n");
        return;
    }

    char codigo_sala[10];
    printf("Informe o código da sala: ");
    scanf(" %[^\n]", codigo_sala);

    int sala_index = -1;
    for(int i=0;i<escolas[index].qtd_salas;i++){
        if(strcmp(escolas[index].salas[i].codigo,codigo_sala)==0){
            sala_index = i;
            break;
        }
    }
    if(sala_index == -1){
        printf("Sala não encontrada.\n");
        return;
    }

    char matricula[16];
    printf("Informe a matrícula do aluno a remover: ");
    scanf(" %[^\n]", matricula);

    Sala *sala = &escolas[index].salas[sala_index];
    int aluno_index = -1;
    for(int i=0;i<sala->qtd_alunos;i++){
        if(strcmp(sala->alunos[i].matricula, matricula)==0){
            aluno_index = i;
            break;
        }
    }
    if(aluno_index == -1){
        printf("Aluno não encontrado.\n");
        return;
    }

    // Compacta o vetor
    for(int i=aluno_index;i<sala->qtd_alunos-1;i++){
        sala->alunos[i] = sala->alunos[i+1];
    }
    sala->qtd_alunos--;
    sala->alunos = (Aluno *)realloc(sala->alunos, sala->qtd_alunos * sizeof(Aluno));
    printf("Aluno removido com sucesso.\n");
}

void mover_aluno(Escola *escolas, int qtd_escolas){
    char nome_escola[50];
    printf("Informe o nome da escola: ");
    scanf(" %[^\n]", nome_escola);

    int found = 0, index = -1;
    for(int i=0;i<qtd_escolas;i++){
        if(strcmp(escolas[i].nome,nome_escola)==0){
            found = 1;
            index = i;
            break;
        }
    }
    if(!found){
        printf("Escola não encontrada.\n");
        return;
    }

    char matricula[16];
    printf("Informe a matrícula do aluno a mover: ");
    scanf(" %[^\n]", matricula);

    int sala_origem = -1, aluno_index = -1;
    for(int i=0;i<escolas[index].qtd_salas;i++){
        for(int j=0;j<escolas[index].salas[i].qtd_alunos;j++){
            if(strcmp(escolas[index].salas[i].alunos[j].matricula, matricula)==0){
                sala_origem = i;
                aluno_index = j;
                break;
            }
        }
        if(sala_origem != -1) break;
    }
    if(sala_origem == -1){
        printf("Aluno não encontrado.\n");
        return;
    }

    char codigo_dest[10];
    printf("Informe o código da sala destino: ");
    scanf(" %[^\n]", codigo_dest);

    int sala_dest = -1;
    for(int i=0;i<escolas[index].qtd_salas;i++){
        if(strcmp(escolas[index].salas[i].codigo, codigo_dest)==0){
            sala_dest = i;
            break;
        }
    }
    if(sala_dest == -1){
        printf("Sala destino não encontrada.\n");
        return;
    }

    Sala *orig = &escolas[index].salas[sala_origem];
    Sala *dest = &escolas[index].salas[sala_dest];

    if(dest->qtd_alunos >= dest->capacidade){
        printf("Sala destino cheia.\n");
        return;
    }

    // Mover aluno
    dest->alunos = (Aluno *)realloc(dest->alunos, (dest->qtd_alunos+1)*sizeof(Aluno));
    dest->alunos[dest->qtd_alunos++] = orig->alunos[aluno_index];

    // Remover da origem
    for(int i=aluno_index;i<orig->qtd_alunos-1;i++){
        orig->alunos[i] = orig->alunos[i+1];
    }
    orig->qtd_alunos--;
    orig->alunos = (Aluno *)realloc(orig->alunos, orig->qtd_alunos*sizeof(Aluno));

    printf("Aluno movido com sucesso.\n");
}

void listar_professores(Escola *escolas, int qtd_escolas){
    char nome_escola[50];
    printf("Informe o nome da escola: ");
    scanf(" %[^\n]", nome_escola);

    int found = 0, index = -1;
    for(int i=0;i<qtd_escolas;i++){
        if(strcmp(escolas[i].nome,nome_escola)==0){
            found = 1;
            index = i;
            break;
        }
    }
    if(!found){
        printf("Escola não encontrada.\n");
        return;
    }

    if(escolas[index].qtd_professores == 0){
        printf("Nenhum professor cadastrado.\n");
        return;
    }

    for(int i=0;i<escolas[index].qtd_professores;i++){
        printf("Nome: %s, Disciplina: %s, Id: %d\n",
               escolas[index].professores[i].nome,
               escolas[index].professores[i].disciplina,
               escolas[index].professores[i].id);
    }
}

void listar_salas_alunos(Escola *escolas, int qtd_escolas){
    char nome_escola[50];
    printf("Informe o nome da escola: ");
    scanf(" %[^\n]", nome_escola);

    int found = 0, index = -1;
    for(int i=0;i<qtd_escolas;i++){
        if(strcmp(escolas[i].nome,nome_escola)==0){
            found = 1;
            index = i;
            break;
        }
    }
    if(!found){
        printf("Escola não encontrada.\n");
        return;
    }

    if(escolas[index].qtd_salas == 0){
        printf("Nenhuma sala cadastrada.\n");
        return;
    }

    for(int i=0;i<escolas[index].qtd_salas;i++){
        Sala *sala = &escolas[index].salas[i];
        printf("Sala %s (Capacidade: %d, Alunos: %d):\n",
               sala->codigo, sala->capacidade, sala->qtd_alunos);
        for(int j=0;j<sala->qtd_alunos;j++){
            printf("  Nome: %s, Idade: %d, Matrícula: %s\n",
                   sala->alunos[j].nome,
                   sala->alunos[j].idade,
                   sala->alunos[j].matricula);
        }
        printf("-------------------------\n");
    }
}

void liberar_memoria(Escola *escolas, int qtd_escolas){
    for(int i=0;i<qtd_escolas;i++){
        for(int j=0;j<escolas[i].qtd_salas;j++){
            free(escolas[i].salas[j].alunos);
        }
        free(escolas[i].salas);
        free(escolas[i].professores);
    }
    free(escolas);
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