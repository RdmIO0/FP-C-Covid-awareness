//
//  main.c
//  Projeto
//
//  Created by Artem Alekseev on 05/01/2021.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 50
#define MAX_ESCOLAS 120
#define MAX_QUESTIONARIOS 1000

typedef struct escola {
    int identificador;
    char nome[50];
    char localidade[50];
} ESCOLA_T;

typedef struct hora {
    int hora;
    int minutos;
    int segundos;
} HORA_T;

typedef struct data {
    int dia;
    int mes;
    int ano;
    HORA_T hora;
} DATA_T;


typedef struct questionario {
    int identificador_q;
    ESCOLA_T escola;
    DATA_T data;
    char risco_c [20];
    int idade;
    char genero [20];
    char localidade[50];
    char participante [30];
    char contacto_covid [10];
    char sintomas [100];
    char doencas [100];
    int temperatura;
    
} QUESTIONARIO_T;




int ler_inteiro(char texto[], int min, int max);
int menu_opcoesprincipal(void);
int menu_opcoesestatisticas(void);
ESCOLA_T ler_escola(void);
int registar_escolas(ESCOLA_T escolas[], int num_escolas);
void mostrar_escola(ESCOLA_T escola);
void mostrar_escolas(ESCOLA_T escolas[], int num_escolas);
void ler_string(char texto[], char str[], int max);
int registar_questionario(QUESTIONARIO_T questionarios[], int num_questionarios);
QUESTIONARIO_T ler_questionario(void);


int main() {
    ESCOLA_T escolas[MAX_ESCOLAS];
    int num_escolas = 0;
    int op,op1;
    
    
    
    do {
        op = menu_opcoesprincipal();
        switch (op) {
        case 1:
                num_escolas += registar_escolas(escolas, num_escolas);
            break;

        case 2:
                mostrar_escolas(escolas, num_escolas);
            break;

        case 3:
                
            break;

        case 4:
                
            break;

        case 5:
                
                do{
                    op1 = menu_opcoesestatisticas();
                    switch (op1) {
                    case 1:
                        
                        break;

                    case 2:
                            
                        break;

                    case 3:
                            
                        break;

                    case 4:
                             
                        break;
                    }
                }while (op1 != 0);

            break;
        
           

        case 6:
                
            break;
                
        case 7:
                
            break;
                
        }
    } while (op != 0);
    return 0;
}
    


int menu_opcoesprincipal(void) {
    int op;

    printf("* MENU PRINCIPAL *\n");
    printf("1 - Registar uma Escola\n");
    printf("2 - Consultar todas as Escolas\n");
    printf("3 - Registar um novo questionario\n");
    printf("4 - Consultar questionarios\n");
    printf("5 - Estatisticas\n");
    printf("6 - Guardar ficheiro\n");
    printf("7 - Ler ficheiros guardados\n");
    printf("0 - Sair\n");
    op = ler_inteiro("Opcao: ", 0, 7);
    return op;
}

int menu_opcoesestatisticas(void){
    int op1;
    
    printf("* Estatisticas *\n");
    printf("1 - Numero de questionarios respondidos\n");
    printf("2 - Numero de questionarios respondidos (por Escola)\n");
    printf("3 - Total de inquéritos por género e idade\n");
    printf("4 - Percentagem de inquéritos por nível de risco de contágio\n");
    printf("0 - Voltar Atras\n");
    op1 = ler_inteiro("Opcao: ", 0, 4);
    return op1;
}
int ler_inteiro(char texto[], int min, int max) {
    int num;

    do {
        printf("%s", texto);
        fflush(stdin);
        scanf("%d", &num);
        if (num < min || num > max) {
            printf("Numero invalido.\n");
        }
    } while (num < min || num > max);
    return num;
}
int registar_escolas(ESCOLA_T escolas[], int num_escolas) {
    ESCOLA_T escola;
    if (num_escolas >= MAX_ESCOLAS) {
        printf("Numero maximo de escolas atingido.\n");
        return 0;
    }
    escola = ler_escola();
    escolas[num_escolas] = escola;
    return 1;
}
ESCOLA_T ler_escola(void) {
    ESCOLA_T escola;
    escola.identificador = ler_inteiro("Identificador da escola: ", 1, 50);
    ler_string("Nome da escola: ", escola.nome, MAX_NOME);
    ler_string("Nome da localidade: ",escola.localidade, MAX_NOME);
    return escola;
}
void ler_string(char texto[], char str[], int max) {
    printf("%s", texto);
    fflush(stdin);
    fgets(str, max, stdin);
    size_t len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}
void mostrar_escola(ESCOLA_T escola) {
    printf("Numero do identificador da escola: %d\n", escola.identificador);
    printf("Nome da Escola: %s\n", escola.nome);
    printf("Localidade: %s\n", escola.localidade);
}
void mostrar_escolas(ESCOLA_T escolas[], int num_escolas) {
    int i;

    for (i = 0; i < num_escolas; i++) {
        mostrar_escola(escolas[i]);
        printf("\n");
    }
}
int registar_questionario(QUESTIONARIO_T questionarios[], int num_questionarios) {
    QUESTIONARIO_T questionario;
    if (num_questionarios >= MAX_QUESTIONARIOS) {
        printf("Numero maximo de questionarios atingido.\n");
        return 0;
    }
    questionario = ler_questionario();
    questionarios[num_questionarios] = questionario;
    return 1;
}
QUESTIONARIO_T ler_questionario(void) {
    
    QUESTIONARIO_T questionario;
    questionario.escola.identificador = ler_inteiro("Identificador da escola: ", 1, 50);
    return questionario;
}
