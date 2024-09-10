#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRING 1000
#define MAX_FILMES 10
#define MAX_HORARIOS 3
#define NUM_ASSENTOS 50
#define VALOR_INGRESSO_INTEIRO 3.00
#define VALOR_MEIA_ENTRADA 1.50

// Estrutura para a classe Genero
typedef struct {
    char descricao[MAX_STRING];
} Genero;

// Estrutura para a classe Ator
typedef struct {
    char nome[MAX_STRING];
} Ator;

// Estrutura para a classe Filme
typedef struct {
    char titulo[MAX_STRING];
    int duracao; 
    Genero genero; // Associação com Genero
    Ator ator; // Associação com Ator
    char descricao[MAX_STRING];
    char horarios[MAX_HORARIOS][6]; 
    int sala; 
} Filme;

// Função para selecionar múltiplos assentos
void selecionarAssentos(bool assentos[], int numIngressos, int assentosEscolhidos[]) {
    int assentoEscolhido;
    int count = 0;

    while (count < numIngressos) {
        printf("Escolha um número de assento (1 a %d): ", NUM_ASSENTOS);
        scanf("%d", &assentoEscolhido);

        if (assentoEscolhido >= 1 && assentoEscolhido <= NUM_ASSENTOS) {
            if (assentos[assentoEscolhido - 1]) {
                assentos[assentoEscolhido - 1] = false; // Marcar como ocupado
                assentosEscolhidos[count] = assentoEscolhido;
                count++;
            } else {
                printf("Assento já ocupado. Escolha outro assento.\n");
            }
        } else {
            printf("Número de assento inválido. Escolha um número entre 1 e %d.\n", NUM_ASSENTOS);
        }
    }
}

// Funções para manipulação de filmes
void exibirFilmes(Filme filmes[], int numFilmes, bool assentos[]) {
    int escolha, horario, tipoIngresso, numIngressos;
    int assentosEscolhidos[NUM_ASSENTOS];

    while (1) {
        printf("\nFilmes disponíveis:\n");
        for (int i = 0; i < numFilmes; i++) {
            printf("%d. %s - %d minutos\n", i + 1, filmes[i].titulo, filmes[i].duracao);
        }

        printf("\nEscolha um número de filme para ver detalhes ou 0 para voltar ao menu principal: ");
        scanf("%d", &escolha);

        if (escolha == 0) {
            return; // Voltar ao menu principal
        } else if (escolha > 0 && escolha <= numFilmes) {
            // Exibir detalhes do filme selecionado
            Filme *filme = &filmes[escolha - 1];
            printf("\nTítulo: %s\n", filme->titulo);
            printf("Duração: %d minutos\n", filme->duracao);
            printf("Gênero: %s\n", filme->genero.descricao);
            printf("Ator: %s\n", filme->ator.nome);
            printf("Descrição: %s\n", filme->descricao);

            // Mostrar horários das sessões
            printf("\nHorários das sessões:\n");
            for (int i = 0; i < MAX_HORARIOS; i++) {
                printf("%d. %s\n", i + 1, filme->horarios[i]);
            }

            // Selecionar horário
            while (1) {
                printf("\nEscolha um número de horário para a sessão ou 0 para voltar: ");
                scanf("%d", &horario);
                if (horario == 0) {
                    return; // Voltar ao menu de filmes
                } else if (horario > 0 && horario <= MAX_HORARIOS) {
                    break;
                } else {
                    printf("Número de horário inválido.\n");
                }
            }

            // Mostrar valores dos ingressos
            printf("\nValores dos ingressos:\n");
            printf("1. Inteira: R$ %.2f\n", VALOR_INGRESSO_INTEIRO);
            printf("2. Meia-entrada: R$ %.2f\n", VALOR_MEIA_ENTRADA);

            // Selecionar tipo de ingresso
            while (1) {
                printf("\nEscolha o tipo de ingresso (1 para Inteira, 2 para Meia-entrada): ");
                scanf("%d", &tipoIngresso);
                if (tipoIngresso == 1 || tipoIngresso == 2) {
                    break;
                } else {
                    printf("Tipo de ingresso inválido.\n");
                }
            }

            // Escolher quantidade de ingressos
            while (1) {
                printf("\nQuantos ingressos você deseja comprar? (1 a %d): ", NUM_ASSENTOS);
                scanf("%d", &numIngressos);
                if (numIngressos >= 1 && numIngressos <= NUM_ASSENTOS) {
                    int assentosDisponiveis = 0;
                    for (int i = 0; i < NUM_ASSENTOS; i++) {
                        if (assentos[i]) assentosDisponiveis++;
                    }
                    if (numIngressos <= assentosDisponiveis) {
                        break;
                    } else {
                        printf("Não há assentos suficientes disponíveis. Tente novamente.\n");
                    }
                } else {
                    printf("Número de ingressos inválido.\n");
                }
            }

            // Selecionar assentos
            selecionarAssentos(assentos, numIngressos, assentosEscolhidos);

            // Exibir recibo
            printf("\n=====Compra finalizada!=====\n");
            printf("Recibo:\n");
            printf("Filme: %s\n", filme->titulo);
            printf("Horário: %s\n", filme->horarios[horario - 1]);
            for (int i = 0; i < numIngressos; i++) {
                printf("Assento %d: %d\n", i + 1, assentosEscolhidos[i]);
            }
            printf("Tipo de ingresso: %s\n", tipoIngresso == 1 ? "Inteira" : "Meia-entrada");
            printf("Sala: %d\n", filme->sala);
        } else {
            printf("Número de filme inválido.\n");
        }
    }
}

int main() {
    Filme filmes[MAX_FILMES];
    int numFilmes = 3;
    bool assentos[NUM_ASSENTOS];

    // Inicializar assentos como disponíveis
    for (int i = 0; i < NUM_ASSENTOS; i++) {
        assentos[i] = true;
    }

    strcpy(filmes[0].titulo, "Harry Potter e a Pedra Filosofal");
    filmes[0].duracao = 152;
    strcpy(filmes[0].genero.descricao, "Fantasia");
    strcpy(filmes[0].ator.nome, "Daniel Radcliffe");
    strcpy(filmes[0].descricao, "Harry Potter é um jovem bruxo que descobre sua identidade mágica e entra na escola de magia Hogwarts.");
    strcpy(filmes[0].horarios[0], "13:00");
    strcpy(filmes[0].horarios[1], "16:00");
    strcpy(filmes[0].horarios[2], "20:00");
    filmes[0].sala = 1;

    strcpy(filmes[1].titulo, "Barbie");
    filmes[1].duracao = 114;
    strcpy(filmes[1].genero.descricao, "Aventura");
    strcpy(filmes[1].ator.nome, "Margot Robbie");
    strcpy(filmes[1].descricao, "Barbie vive uma vida perfeita em Barbielândia até que ela se pergunta se existe algo mais no mundo.");
    strcpy(filmes[1].horarios[0], "13:00");
    strcpy(filmes[1].horarios[1], "16:00");
    strcpy(filmes[1].horarios[2], "20:00");
    filmes[1].sala = 2;

    strcpy(filmes[2].titulo, "Divertidamente");
    filmes[2].duracao = 95;
    strcpy(filmes[2].genero.descricao, "Animação");
    strcpy(filmes[2].ator.nome, "Alegria");
    strcpy(filmes[2].descricao, "A vida de Riley é controlada pelas suas emoções internas que vivem em sua mente, e eles devem lidar com as mudanças que vêm com uma mudança de cidade.");
    strcpy(filmes[2].horarios[0], "13:00");
    strcpy(filmes[2].horarios[1], "16:00");
    strcpy(filmes[2].horarios[2], "20:00");
    filmes[2].sala = 3;

    int escolha;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Exibir filmes disponiveis\n");
        printf("2. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                exibirFilmes(filmes, numFilmes, assentos);
                break;

            case 2:
                printf("Saindo...\n");
                return 0;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }

    return 0;
}
