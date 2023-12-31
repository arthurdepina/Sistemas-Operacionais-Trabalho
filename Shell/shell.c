/**********************************************************
 *                                                        *
 *                   Simulador de Shell                   *
 *                                                        *
 *      Arthur de Pina Balduino Leitão    - 32207840      *
 *      Cesar Hideki Imai                 - 32255659      *
 *      David Varão Lima Bentes Pessoa    - 32253133      *
 *      João Victor Dallapé Madeira       - 32209592      *
 *      Luiz Henrique Bonilha Pasquinelli - 32224419      *
 *                                                        *
 * github.com/arthurdepina/Sistemas-Operacionais-Trabalho *
 *     https://replit.com/@arthurdepina/Trabalho-SO-2     *
 *                                                        *
***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include "n-AryTree.c"
#include "auxiliares.c"

int main() {
    // Node *atual = malloc(sizeof(Node));

    char root_name[100];
    printf("Nome da Raiz?\n");
    printf("> ");
    fgets(root_name, sizeof(root_name), stdin);
    root_name[strcspn(root_name, "\n")] = 0; // remove o caractere de nova linha

    // Preparar o caminho completo para o diretório raiz
    // char root_path[150] = "./";
    // strcat(root_path, root_name);
    
    // Criar o nó raiz e mapear a estrutura do diretório
    Node *atual = createNode(root_name, root_name, 'd', NULL);
    mapDirectory(root_name, atual);
    printf("Nome da raiz definido como: %s\n", root_name);

    show_commands();

    while (true) {
        char input[100];
        char comando, tipo;
        char nome[50];
        int tamanho = 0;

        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Removing the newline character that fgets reads

        switch (input[0]) {
                                        // Criar arquivo ou diretório
            case 'm':

                if (input[2] == 'd') {
                    if (!getting_input(input, &comando, &tipo, nome)) { fail(); break; }
                } else {
                    if (!getting_input_with_size(input, &comando, &tipo, nome, &tamanho)) { fail(); break; }
                }
                if (tipo == 'd') {
                    inserirDiretorio(atual, nome);
                } else if (tipo == 'a') {
                    inserirArquivo(atual, nome, tamanho);
                } else {
                    fail();
                    break;
                }
                break;

                                        // Mudar de diretório ou arquivo
            case 'c':

                if (!getting_input(input, &comando, &tipo, nome)) { fail(); break; }
                // Nesse caso nome será o path até o nó a ser excluído
                atual = changeNode(atual, nome);
                break;

                                        // Deletar diretório ou arquivo
            case 'd':

                if (!getting_input(input, &comando, &tipo, nome)) { fail(); break; }
                // Nesse caso nome será o path até o nó a ser excluído
                printf("\n");
                if (tipo == 'd') {
                    alteraPaths(atual, nome);
                    atual = deletaDiretorio(atual, nome);
                } else if (tipo == 'a') {
                    atual = deletaArquivo(atual, nome);
                } else {
                    fail();
                    break;
                }
                break;

                                        // Exibir árvore em profundidade
            case 'p':

                imprimirProfundidade(atual);
                break;

                                        // Exibir árvore em largura
            case 'l':

                imprimirLargura(atual);
                break;

            case '-':

                if (!strcmp(input, "--end")) {
                    printf("\nPrograma finalizado.\n\n");
                    freeTreeFromNode(atual);
                    return 0;
                } else if (!strcmp(input, "--help")) {
                    show_commands();
                } else if (!strcmp(input, "--show")) {
                    mostrar_no(atual);
                }
                break;

            default:
                printf("Input invalido");
                break;
        }
    }
    freeTreeFromNode(atual);
    return 0;
}

/*          
 *                  Problemas conhecidos:
 * Quando removemos um diretorio, o path dos filhos nao é alterado.
 *      Talvez compense usar listas nos paths. Não vou focar nisso
 *      por agora porque o enunciado nao pede para deletar diretórios.
*/
