#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* =========================
   Estruturas e assinaturas
   ========================= */

struct Carta {
    char codigo[4];       // Ex.: "A1"
    char estadoLetra;     // A-H
    int  cidadeNumero;    // 1-4
    char estadoNome[30];
    char cidadeNome[50];
    unsigned long int populacao; // habitantes
    float area;           // km²
    float pib;            // bilhões de R$
    int   pontosTuristicos;

    // Calculados
    float densidadePopulacional; // hab/km²
    float pibPerCapita;          // R$/hab
};

void cadastrarCarta(struct Carta *c);
void calcularMetricas(struct Carta *c);
void exibirResumoCarta(const struct Carta *c, int indice);
int menu();
void compararEAvisar(const struct Carta *c1, const struct Carta *c2, int opcao);

/* =========================
   Funções de cadastro/cálculo
   ========================= */

void cadastrarCarta(struct Carta *c) {
    printf("Nome do estado/país: ");
    scanf(" %29[^\n]", c->estadoNome);

    do {
        printf("Escolha a letra do estado (A-H): ");
        scanf(" %c", &c->estadoLetra);
        c->estadoLetra = (char)toupper((unsigned char)c->estadoLetra);
    } while (c->estadoLetra < 'A' || c->estadoLetra > 'H');

    printf("Nome da cidade/região (apenas informativo): ");
    scanf(" %49[^\n]", c->cidadeNome);

    do {
        printf("Escolha o número da cidade (1-4): ");
        scanf(" %d", &c->cidadeNumero);
    } while (c->cidadeNumero < 1 || c->cidadeNumero > 4);

    snprintf(c->codigo, sizeof(c->codigo), "%c%d", c->estadoLetra, c->cidadeNumero);

    printf("População (habitantes): ");
    scanf(" %lu", &c->populacao);

    printf("Área (em km²): ");
    scanf(" %f", &c->area);

    printf("PIB (em bilhões de R$): ");
    scanf(" %f", &c->pib);

    printf("Quantidade de pontos turísticos: ");
    scanf(" %d", &c->pontosTuristicos);

    calcularMetricas(c);
}

void calcularMetricas(struct Carta *c) {
    if (c->area > 0.0f) {
        c->densidadePopulacional = (float)c->populacao / c->area;
    } else {
        c->densidadePopulacional = 0.0f;
    }

    if (c->populacao > 0) {
        c->pibPerCapita = (c->pib * 1e9f) / (float)c->populacao; // PIB em bilhões -> R$
    } else {
        c->pibPerCapita = 0.0f;
    }
}

void exibirResumoCarta(const struct Carta *c, int indice) {
    printf("Carta %d - %s (%s) | Código: %s\n", indice, c->cidadeNome, c->estadoNome, c->codigo);
    printf("  População: %lu\n", c->populacao);
    printf("  Área: %.3f km²\n", c->area);
    printf("  PIB: %.3f bilhões de R$\n", c->pib);
    printf("  Pontos turísticos: %d\n", c->pontosTuristicos);
    printf("  Densidade demográfica: %.3f hab/km²\n", c->densidadePopulacional);
    printf("  PIB per capita: R$ %.2f\n", c->pibPerCapita);
}

/* =========================
   Menu e comparação
   ========================= */

int menu() {
    int opcao;
    printf("\n=== MENU DE COMPARAÇÃO ===\n");
    printf("1) População (maior vence)\n");
    printf("2) Área (maior vence)\n");
    printf("3) PIB (maior vence)\n");
    printf("4) Pontos turísticos (maior vence)\n");
    printf("5) Densidade demográfica (MENOR vence)\n");
    printf("6) PIB per capita (maior vence)\n");
    printf("7) Mostrar nomes (informativo)\n");
    printf("0) Sair\n");
    printf("Escolha uma opção: ");
    if (scanf(" %d", &opcao) != 1) {
        // Limpeza simples caso usuário digite algo inválido
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) { /* descarta */ }
        return -1; // inválido
    }
    return opcao;
}

void compararEAvisar(const struct Carta *c1, const struct Carta *c2, int opcao) {
    // Mensagem comum com nomes
    if (opcao == 7) {
        printf("\nCartas selecionadas:\n");
        printf("Carta 1: %s (%s) | Código: %s\n", c1->cidadeNome, c1->estadoNome, c1->codigo);
        printf("Carta 2: %s (%s) | Código: %s\n", c2->cidadeNome, c2->estadoNome, c2->codigo);
        return;
    }

    // Lógica de comparação com if-else aninhado (requisito do nível)
    // Estrutura: primeiro seleciona atributo (switch), depois ramifica com if-else
    switch (opcao) {
        case 1: { // População (maior vence)
            unsigned long int v1 = c1->populacao, v2 = c2->populacao;
            printf("\nComparação - População:\n");
            printf("Carta 1 - %s (%s): %lu\n", c1->cidadeNome, c1->estadoNome, v1);
            printf("Carta 2 - %s (%s): %lu\n", c2->cidadeNome, c2->estadoNome, v2);

            if (v1 > v2) {
                printf("Resultado: Carta 1 (%s) venceu!\n", c1->cidadeNome);
            } else if (v2 > v1) {
                printf("Resultado: Carta 2 (%s) venceu!\n", c2->cidadeNome);
            } else {
                printf("Empate!\n");
            }
            break;
        }
        case 2: { // Área (maior vence)
            float v1 = c1->area, v2 = c2->area;
            printf("\nComparação - Área (km²):\n");
            printf("Carta 1 - %s (%s): %.3f km²\n", c1->cidadeNome, c1->estadoNome, v1);
            printf("Carta 2 - %s (%s): %.3f km²\n", c2->cidadeNome, c2->estadoNome, v2);

            if (v1 > v2) {
                printf("Resultado: Carta 1 (%s) venceu!\n", c1->cidadeNome);
            } else if (v2 > v1) {
                printf("Resultado: Carta 2 (%s) venceu!\n", c2->cidadeNome);
            } else {
                printf("Empate!\n");
            }
            break;
        }
        case 3: { // PIB (maior vence) - em bilhões de R$
            float v1 = c1->pib, v2 = c2->pib;
            printf("\nComparação - PIB (bilhões de R$):\n");
            printf("Carta 1 - %s (%s): %.3f bi\n", c1->cidadeNome, c1->estadoNome, v1);
            printf("Carta 2 - %s (%s): %.3f bi\n", c2->cidadeNome, c2->estadoNome, v2);

            if (v1 > v2) {
                printf("Resultado: Carta 1 (%s) venceu!\n", c1->cidadeNome);
            } else if (v2 > v1) {
                printf("Resultado: Carta 2 (%s) venceu!\n", c2->cidadeNome);
            } else {
                printf("Empate!\n");
            }
            break;
        }
        case 4: { // Pontos turísticos (maior vence)
            int v1 = c1->pontosTuristicos, v2 = c2->pontosTuristicos;
            printf("\nComparação - Pontos Turísticos:\n");
            printf("Carta 1 - %s (%s): %d\n", c1->cidadeNome, c1->estadoNome, v1);
            printf("Carta 2 - %s (%s): %d\n", c2->cidadeNome, c2->estadoNome, v2);

            if (v1 > v2) {
                printf("Resultado: Carta 1 (%s) venceu!\n", c1->cidadeNome);
            } else if (v2 > v1) {
                printf("Resultado: Carta 2 (%s) venceu!\n", c2->cidadeNome);
            } else {
                printf("Empate!\n");
            }
            break;
        }
        case 5: { // Densidade demográfica (MENOR vence)
            float v1 = c1->densidadePopulacional, v2 = c2->densidadePopulacional;
            printf("\nComparação - Densidade demográfica (hab/km²):\n");
            printf("Carta 1 - %s (%s): %.3f hab/km²\n", c1->cidadeNome, c1->estadoNome, v1);
            printf("Carta 2 - %s (%s): %.3f hab/km²\n", c2->cidadeNome, c2->estadoNome, v2);

            if (v1 < v2) {                 // if externo
                printf("Resultado: Carta 1 (%s) venceu!\n", c1->cidadeNome);
            } else {                        // else externo
                if (v2 < v1) {              // if interno (aninhado)
                    printf("Resultado: Carta 2 (%s) venceu!\n", c2->cidadeNome);
                } else {
                    printf("Empate!\n");
                }
            }
            break;
        }
        case 6: { // PIB per capita (maior vence)
            float v1 = c1->pibPerCapita, v2 = c2->pibPerCapita;
            printf("\nComparação - PIB per capita (R$):\n");
            printf("Carta 1 - %s (%s): R$ %.2f\n", c1->cidadeNome, c1->estadoNome, v1);
            printf("Carta 2 - %s (%s): R$ %.2f\n", c2->cidadeNome, c2->estadoNome, v2);

            if (v1 > v2) {
                printf("Resultado: Carta 1 (%s) venceu!\n", c1->cidadeNome);
            } else if (v2 > v1) {
                printf("Resultado: Carta 2 (%s) venceu!\n", c2->cidadeNome);
            } else {
                printf("Empate!\n");
            }
            break;
        }
        default:
            printf("\nOpção inválida. Tente novamente.\n");
            break;
    }
}

/* =========================
   Programa principal
   ========================= */

int main(void) {
    struct Carta carta1, carta2;

    printf("=== Cadastro de Cartas (uma vez) ===\n\n");
    printf("Cadastro da primeira carta:\n");
    cadastrarCarta(&carta1);

    printf("\nCadastro da segunda carta:\n");
    cadastrarCarta(&carta2);

    printf("\n=== Resumo das cartas cadastradas ===\n");
    exibirResumoCarta(&carta1, 1);
    exibirResumoCarta(&carta2, 2);

    // Loop do menu
    while (1) {
        int opcao = menu();
        if (opcao == 0) {
            printf("Encerrando. Obrigado por jogar!\n");
            break;
        } else if (opcao < 0) {
            printf("\nEntrada inválida. Digite o número da opção.\n");
            continue;
        }
        compararEAvisar(&carta1, &carta2, opcao);
    }

    return 0;
}