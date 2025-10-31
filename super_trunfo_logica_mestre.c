#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* =============================
   Atributos disponíveis
   ============================= */
typedef enum {
    ATTR_INVALIDO = 0,
    ATTR_POPULACAO = 1,
    ATTR_AREA = 2,
    ATTR_PIB = 3,
    ATTR_PONTOS = 4,
    ATTR_DENSIDADE = 5,       // menor vence na comparação individual
    ATTR_PIB_PER_CAPITA = 6
} Atributo;

const char* nomeAtributo(Atributo a) {
    switch (a) {
        case ATTR_POPULACAO:      return "População";
        case ATTR_AREA:           return "Área (km²)";
        case ATTR_PIB:            return "PIB (bi R$)";
        case ATTR_PONTOS:         return "Pontos Turísticos";
        case ATTR_DENSIDADE:      return "Densidade (hab/km²)";
        case ATTR_PIB_PER_CAPITA: return "PIB per capita (R$)";
        default:                  return "Inválido";
    }
}

/* =============================
   Estrutura da Carta
   ============================= */
struct Carta {
    char codigo[4];           // "A1"
    char estadoLetra;         // A-H
    int  cidadeNumero;        // 1-4
    char paisNome[30];        // (usaremos "País" aqui)
    char cidadeNome[50];      // informativo
    unsigned long int populacao; // hab
    float area;               // km²
    float pib;                // bilhões R$
    int   pontosTuristicos;   // int

    // calculados
    float densidade;          // hab/km²
    float pibPerCapita;       // R$/hab
};

/* =============================
   Cadastro e cálculos
   ============================= */
void calcularMetricas(struct Carta *c) {
    c->densidade = (c->area > 0.0f) ? (float)c->populacao / c->area : 0.0f;
    c->pibPerCapita = (c->populacao > 0) ? (c->pib * 1e9f) / (float)c->populacao : 0.0f;
}

void cadastrarCarta(struct Carta *c) {
    printf("Nome do país: ");
    scanf(" %29[^\n]", c->paisNome);

    do {
        printf("Escolha a letra do país (A-H): ");
        scanf(" %c", &c->estadoLetra);
        c->estadoLetra = (char)toupper((unsigned char)c->estadoLetra);
    } while (c->estadoLetra < 'A' || c->estadoLetra > 'H');

    printf("Nome da cidade (informativo): ");
    scanf(" %49[^\n]", c->cidadeNome);

    do {
        printf("Escolha o número (1-4): ");
        scanf(" %d", &c->cidadeNumero);
    } while (c->cidadeNumero < 1 || c->cidadeNumero > 4);

    snprintf(c->codigo, sizeof(c->codigo), "%c%d", c->estadoLetra, c->cidadeNumero);

    printf("População (hab): ");
    scanf(" %lu", &c->populacao);

    printf("Área (km²): ");
    scanf(" %f", &c->area);

    printf("PIB (em bilhões de R$): ");
    scanf(" %f", &c->pib);

    printf("Pontos Turísticos: ");
    scanf(" %d", &c->pontosTuristicos);

    calcularMetricas(c);
}

void exibirResumo(const struct Carta* c, int idx) {
    printf("Carta %d - %s (%s) | Código: %s\n",
           idx, c->paisNome, c->cidadeNome, c->codigo);
    printf("  População: %lu\n", c->populacao);
    printf("  Área: %.3f km²\n", c->area);
    printf("  PIB: %.3f bilhões de R$\n", c->pib);
    printf("  Pontos Turísticos: %d\n", c->pontosTuristicos);
    printf("  Densidade: %.3f hab/km²\n", c->densidade);
    printf("  PIB per capita: R$ %.2f\n", c->pibPerCapita);
}

/* =============================
   Entrada segura
   ============================= */
void limparBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { /* descarta */ }
}

int lerOpcaoInteira(void) {
    int op;
    if (scanf(" %d", &op) != 1) {
        limparBuffer();
        return -1;
    }
    return op;
}

/* =============================
   Leitura de atributos com menu
   (dinâmico: oculta o já escolhido)
   ============================= */
void mostrarMenuAtributos(Atributo bloqueado) {
    printf("\n=== Escolha um atributo ===\n");
    for (int i = ATTR_POPULACAO; i <= ATTR_PIB_PER_CAPITA; ++i) {
        if (i == bloqueado) continue;
        printf("%d) %s\n", i, nomeAtributo((Atributo)i));
    }
    printf("0) Cancelar\n");
    printf("Opção: ");
}

Atributo escolherAtributo(Atributo bloqueado) {
    while (1) {
        mostrarMenuAtributos(bloqueado);
        int op = lerOpcaoInteira();
        if (op == 0) return ATTR_INVALIDO;
        if (op >= ATTR_POPULACAO && op <= ATTR_PIB_PER_CAPITA && op != bloqueado) {
            return (Atributo)op;
        }
        printf("Opção inválida. Tente novamente.\n");
    }
}

/* =============================
   Obter valor numérico por atributo
   ============================= */
double valorDoAtributo(const struct Carta* c, Atributo a) {
    switch (a) {
        case ATTR_POPULACAO:      return (double)c->populacao;
        case ATTR_AREA:           return (double)c->area;
        case ATTR_PIB:            return (double)c->pib; // em bilhões
        case ATTR_PONTOS:         return (double)c->pontosTuristicos;
        case ATTR_DENSIDADE:      return (double)c->densidade;
        case ATTR_PIB_PER_CAPITA: return (double)c->pibPerCapita;
        default:                  return 0.0;
    }
}

/* =============================
   Comparação individual
   - regra geral: maior vence
   - densidade: menor vence
   Retorna: 1 (c1), 2 (c2), 0 (empate)
   ============================= */
int vencedorAtributo(const struct Carta* c1, const struct Carta* c2, Atributo a) {
    double v1 = valorDoAtributo(c1, a);
    double v2 = valorDoAtributo(c2, a);
    if (a == ATTR_DENSIDADE) {
        return (v1 < v2) ? 1 : (v2 < v1) ? 2 : 0; // ternário
    } else {
        return (v1 > v2) ? 1 : (v2 > v1) ? 2 : 0; // ternário
    }
}

/* =============================
   Impressão de comparação
   ============================= */
void imprimirComparacao(const struct Carta* c1, const struct Carta* c2, Atributo a) {
    double v1 = valorDoAtributo(c1, a);
    double v2 = valorDoAtributo(c2, a);

    printf("\nComparação - %s\n", nomeAtributo(a));

    // Linhas com unidades apropriadas
    switch (a) {
        case ATTR_POPULACAO:
            printf("Carta 1 - %s: %lu\n", c1->paisNome, c1->populacao);
            printf("Carta 2 - %s: %lu\n", c2->paisNome, c2->populacao);
            break;
        case ATTR_AREA:
            printf("Carta 1 - %s: %.3f km²\n", c1->paisNome, c1->area);
            printf("Carta 2 - %s: %.3f km²\n", c2->paisNome, c2->area);
            break;
        case ATTR_PIB:
            printf("Carta 1 - %s: %.3f bilhões R$\n", c1->paisNome, c1->pib);
            printf("Carta 2 - %s: %.3f bilhões R$\n", c2->paisNome, c2->pib);
            break;
        case ATTR_PONTOS:
            printf("Carta 1 - %s: %d\n", c1->paisNome, c1->pontosTuristicos);
            printf("Carta 2 - %s: %d\n", c2->paisNome, c2->pontosTuristicos);
            break;
        case ATTR_DENSIDADE:
            printf("Carta 1 - %s: %.3f hab/km²\n", c1->paisNome, c1->densidade);
            printf("Carta 2 - %s: %.3f hab/km²\n", c2->paisNome, c2->densidade);
            break;
        case ATTR_PIB_PER_CAPITA:
            printf("Carta 1 - %s: R$ %.2f\n", c1->paisNome, c1->pibPerCapita);
            printf("Carta 2 - %s: R$ %.2f\n", c2->paisNome, c2->pibPerCapita);
            break;
        default:
            break;
    }

    int v = vencedorAtributo(c1, c2, a);
    const char* quem = (v == 1) ? c1->paisNome : (v == 2) ? c2->paisNome : "Empate";
    printf("Resultado (regra %s): %s%s\n",
           (a == ATTR_DENSIDADE ? "menor vence" : "maior vence"),
           (v == 0 ? "" : "Carta vencedora: "), (v == 0 ? "Empate!" : quem));
}

/* =============================
   Programa principal
   ============================= */
int main(void) {
    struct Carta c1, c2;

    printf("=== Cadastro das Cartas (uma vez) ===\n\n");
    printf("Cadastro da Carta 1:\n");
    cadastrarCarta(&c1);
    printf("\nCadastro da Carta 2:\n");
    cadastrarCarta(&c2);

    printf("\n=== Resumo ===\n");
    exibirResumo(&c1, 1);
    exibirResumo(&c2, 2);

    while (1) {
        printf("\n==============================\n");
        printf("Desafio Final - Escolha 2 atributos para a rodada\n");

        // 1ª escolha
        Atributo a1 = escolherAtributo(ATTR_INVALIDO);
        if (a1 == ATTR_INVALIDO) { printf("Operação cancelada.\n"); break; }

        // 2ª escolha (dinâmico: não mostra a1)
        Atributo a2 = escolherAtributo(a1);
        if (a2 == ATTR_INVALIDO) { printf("Operação cancelada.\n"); break; }

        // Exibe comparações individuais
        imprimirComparacao(&c1, &c2, a1);
        imprimirComparacao(&c1, &c2, a2);

        // Soma dos valores crus escolhidos (conforme enunciado)
        double s1 = valorDoAtributo(&c1, a1) + valorDoAtributo(&c1, a2);
        double s2 = valorDoAtributo(&c2, a1) + valorDoAtributo(&c2, a2);

        printf("\nSoma dos atributos:\n");
        printf("Carta 1 - %s: %.6f\n", c1.paisNome, s1);
        printf("Carta 2 - %s: %.6f\n", c2.paisNome, s2);

        // Vencedor por soma (maior soma vence)
        int vencedorSoma = (s1 > s2) ? 1 : (s2 > s1) ? 2 : 0; // ternário
        if (vencedorSoma == 1) {
            printf("Resultado da rodada: Carta 1 (%s) venceu pela soma!\n", c1.paisNome);
        } else if (vencedorSoma == 2) {
            printf("Resultado da rodada: Carta 2 (%s) venceu pela soma!\n", c2.paisNome);
        } else {
            printf("Empate!\n");
        }

        // Pergunta se deseja jogar novamente
        printf("\nDeseja fazer outra rodada? (1=Sim, 0=Não): ");
        int deNovo = lerOpcaoInteira();
        if (deNovo != 1) {
            printf("Encerrando. Obrigado!\n");
            break;
        }
    }

    return 0;
}
