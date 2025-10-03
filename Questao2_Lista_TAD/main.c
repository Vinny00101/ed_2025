#include <stdio.h>
#include <stdlib.h>
#include "./libs/questao2.h"

int main(){
    Escola *escolas = NULL;
    int qtd_escolas = 0;
    int opcao;
    do{
        menu();
        printf("Escolha uma opção: ");
        scanf("%d",&opcao);
        switch(opcao){
            case 1:
                cadastrar_escola(escolas, &qtd_escolas);
                break;
            case 2:
                listar_escolas(escolas, qtd_escolas);
                break;
            case 3:
                cadastrar_professor(escolas, qtd_escolas);
                break;
            case 4:
                cadastrar_sala(escolas, qtd_escolas);
                break;
            case 5:
                cadastrar_aluno(escolas, qtd_escolas);
                break;
            case 6:
                remover_aluno(escolas, qtd_escolas);
                break;
            case 7:
                mover_aluno(escolas, qtd_escolas);
                break;
            case 8:
                listar_professores(escolas, qtd_escolas);
                break;
            case 9:
                listar_salas_alunos(escolas, qtd_escolas);
                break;
            case 10:
                liberar_memoria(escolas, qtd_escolas);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    }while(opcao != 10);
    return 0;
}
