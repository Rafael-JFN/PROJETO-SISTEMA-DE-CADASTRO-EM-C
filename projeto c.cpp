#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

typedef struct {
    char nome[50];
    char email[50];
    int idade;
    char *senha;
} Usuario;

void adicionarUsuario(Usuario usuarios[], int *totalUsuarios);
void visualizarUsuarios(Usuario usuarios[], int totalUsuarios);
void editarUsuario(Usuario usuarios[], int totalUsuarios);
void excluirUsuario(Usuario usuarios[], int *totalUsuarios);
char* gerarSenha(bool maiusculas, bool minusculas, bool especiais);
void liberarUsuarios(Usuario usuarios[], int totalUsuarios);

int main() {
    Usuario usuarios[100];
    int totalUsuarios = 0;
    char opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar usuario\n");
        printf("2. Visualizar usuarios\n");
        printf("3. Editar usuario\n");
        printf("4. Excluir usuario\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf(" %c", &opcao);

        switch (opcao) {
            case '1':
                adicionarUsuario(usuarios, &totalUsuarios);
                break;
            case '2':
                visualizarUsuarios(usuarios, totalUsuarios);
                break;
            case '3':
                editarUsuario(usuarios, totalUsuarios);
                break;
            case '4':
                excluirUsuario(usuarios, &totalUsuarios);
                break;
            case '5':
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != '5');

    liberarUsuarios(usuarios, totalUsuarios);
    return 0;
}

void adicionarUsuario(Usuario usuarios[], int *totalUsuarios) {
    printf("Digite o nome: ");
    scanf("%s", usuarios[*totalUsuarios].nome);
    printf("Digite o email: ");
    scanf("%s", usuarios[*totalUsuarios].email);
    printf("Digite a idade: ");
    scanf("%d", &usuarios[*totalUsuarios].idade);

    printf("Defina os requisitos para a senha:\n");
    bool maiusculas, minusculas, especiais;
    char opcao;

    printf("Incluir letras maiusculas? (s/n): ");
    scanf(" %c", &opcao);
    maiusculas = tolower(opcao) == 's';

    printf("Incluir letras minusculas? (s/n): ");
    scanf(" %c", &opcao);
    minusculas = tolower(opcao) == 's';

    printf("Incluir caracteres especiais? (s/n): ");
    scanf(" %c", &opcao);
    especiais = tolower(opcao) == 's';

    usuarios[*totalUsuarios].senha = gerarSenha(maiusculas, minusculas, especiais);
    (*totalUsuarios)++;
    printf("Usuario adicionado com sucesso!\n");
}

void visualizarUsuarios(Usuario usuarios[], int totalUsuarios) {
    printf("Lista de Usuarios:\n");
    for (int i = 0; i < totalUsuarios; i++) {
        printf("Nome: %s, Email: %s, Idade: %d, Senha: %s\n", usuarios[i].nome, usuarios[i].email, usuarios[i].idade, usuarios[i].senha);
    }
}

void editarUsuario(Usuario usuarios[], int totalUsuarios) {
    printf("Digite o email do usuario que deseja editar: ");
    char email[50];
    scanf("%s", email);

    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(usuarios[i].email, email) == 0) {
            printf("Digite o novo nome: ");
            scanf("%s", usuarios[i].nome);
            printf("Digite a nova idade: ");
            scanf("%d", &usuarios[i].idade);
            printf("Digite a nova senha: ");
            free(usuarios[i].senha);
            char *senha = gerarSenha(true, true, true);
            usuarios[i].senha = senha;
            printf("Usuario editado com sucesso!\n");
            return;
        }
    }

    printf("Usuario nao encontrado.\n");
}

void excluirUsuario(Usuario usuarios[], int *totalUsuarios) {
    printf("Digite o email do usuario que deseja excluir: ");
    char email[50];
    scanf("%s", email);

    for (int i = 0; i < *totalUsuarios; i++) {
        if (strcmp(usuarios[i].email, email) == 0) {
            free(usuarios[i].senha);
            for (int j = i; j < *totalUsuarios - 1; j++) {
                usuarios[j] = usuarios[j + 1];
            }
            (*totalUsuarios)--;
            printf("Usuario excluido com sucesso!\n");
            return;
        }
    }

    printf("Usuario nao encontrado.\n");
}

char* gerarSenha(bool maiusculas, bool minusculas, bool especiais) {
    const char *caracteres_maiusculos = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *caracteres_minusculas = "abcdefghijklmnopqrstuvwxyz";
    const char *caracteres_especiais = "!@#$%^&*()_+[]{}|;:,.<>?";

    const int tamanho_max = 50;
    char pool[tamanho_max] = "";
    char *senha = (char *)malloc(tamanho_max * sizeof(char));

    if (maiusculas) strcat(pool, caracteres_maiusculos);
    if (minusculas) strcat(pool, caracteres_minusculas);
    if (especiais) strcat(pool, caracteres_especiais);

    srand(time(NULL));
    int len = strlen(pool);

    for (int i = 0; i < tamanho_max - 1; i++) {
        senha[i] = pool[rand() % len];
    }

    senha[tamanho_max - 1] = '\0';
    return senha;
}

void liberarUsuarios(Usuario usuarios[], int totalUsuarios) {
    for (int i = 0; i < totalUsuarios; i++) {
        free(usuarios[i].senha);
    }
}

