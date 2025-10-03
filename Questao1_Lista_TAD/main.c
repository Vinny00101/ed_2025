#include "./libs/questao1.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    int option;
    Mapa **mapa = criar_mapa();
    if (mapa == NULL) {
        exit(1);
    }
    system("cls");
    do{
        menu();
        scanf("%d",&option);
        switch(option){
            case 1:
                inserir_casa(mapa);
                break;
            case 2:
                adicionar_morador(mapa);
                break;
            case 3:
                remover_morador(mapa);
                break;
            case 4:
                remover_casa(mapa);
                break;
            case 5:
                colocar_rua_grama(mapa);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Option invalida\n");
        }
    } while(option != 6);
    liberar_mapa(mapa);
    return 0;
}