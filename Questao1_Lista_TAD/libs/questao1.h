#ifndef QUESTAO1_H
#define QUESTAO1_H

typedef struct pessoa Pessoa;
typedef struct casa Casa;
typedef struct mapa Mapa;

void exibir_mapa(Mapa **mapa);

Mapa **criar_mapa();
Casa *criar_casa(Mapa **mapa); 
Pessoa *criar_pessoa(Mapa **mapa, int index_I, int index_J);

void buscar_casa_pelo_numero(Mapa **mapa, int numero_casa, int *verifyCasaNum, int *index_I, int *index_J);

void inserir_casa(Mapa **mapa);
void adicionar_morador(Mapa **mapa);
void remover_morador(Mapa **mapa);
void remover_casa(Mapa **mapa);
void colocar_rua_grama(Mapa **mapa);

void liberar_mapa(Mapa **mapa);
void menu();

#endif