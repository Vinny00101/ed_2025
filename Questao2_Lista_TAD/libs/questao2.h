#ifndef QUESTAO2_H
#define QUESTAO2_H

typedef struct aluno Aluno;
typedef struct professor Professor;
typedef struct sala Sala;
typedef struct escola Escola;

Aluno* criar_aluno(const char *nome, int idade, const char *matricula);
Professor* criar_professor(const char *nome, const char *disciplina, int id);
Sala* criar_sala(const char *codigo, int capacidade);
Escola* criar_escola(const char *nome, const char *municipio);

void cadastrar_escola(Escola *escolas, int *qtd_escolas);
void listar_escolas(Escola *escolas, int qtd_escolas);
void cadastrar_professor(Escola *escolas, int qtd_escolas);
void cadastrar_sala(Escola *escolas, int qtd_escolas);
void cadastrar_aluno(Escola *escolas, int qtd_escolas);
void remover_aluno(Escola *escolas, int qtd_escolas);
void mover_aluno(Escola *escolas, int qtd_escolas);
void listar_professores(Escola *escolas, int qtd_escolas);
void listar_salas_alunos(Escola *escolas, int qtd_escolas);
void liberar_memoria(Escola *escolas, int qtd_escolas);

void menu();

#endif
