#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* =========================
   Seletor de atributo (mude aqui)
   =========================
   Opções:
   1 = População
   2 = Área
   3 = PIB
   4 = Densidade Populacional  (MENOR vence)
   5 = PIB per capita
*/
#define ATTR_POPULACAO        1
#define ATTR_AREA             2
#define ATTR_PIB              3
#define ATTR_DENSIDADE        4
#define ATTR_PIB_PER_CAPITA   5

//Para comparar outro atributo, altere SELECTED_ATTR.

// >>> Escolha o atributo a comparar:
#define SELECTED_ATTR ATTR_PIB_PER_CAPITA

struct Carta {
    char codigo[4];           // Ex.: "A1" + '\0'
    char estadoLetra;         // A-H
    int  cidadeNumero;        // 1-4
    char estadoNome[30];
    char cidadeNome[50];
    unsigned long int populacao; // habitantes
    float area;               // km²
    float pib;                // bilhões de R$
    int   pontosTuristicos;

    // Calculados
    float densidadePopulacional; // hab/km²
    float pibPerCapita;          // R$ por habitante
};

/* =========================
   Cadastro de carta
   ========================= */
void cadastrarCarta(struct Carta *c) {
    printf("Nome do estado: ");
    scanf(" %29[^\n]", c->estadoNome);

    do {
        printf("Escolha a letra do estado (A-H): ");
        scanf(" %c", &c->estadoLetra);
        c->estadoLetra = (char)toupper((unsigned char)c->estadoLetra);
    } while (c->estadoLetra < 'A' || c->estadoLetra > 'H');

    printf("Nome da cidade: ");
    scanf(" %49[^\n]", c->cidadeNome);

    do {
        printf("Escolha o número da cidade (1-4): ");
        scanf(" %d", &c->cidadeNumero);
    } while (c->cidadeNumero < 1 || c->cidadeNumero > 4);

    // Gerar código (ex.: "A1")
    snprintf(c->codigo, sizeof(c->codigo), "%c%d", c->estadoLetra, c->cidadeNumero);

    printf("População: ");
    scanf(" %lu", &c->populacao);

    printf("Área (em km²): ");
    scanf(" %f", &c->area);

    printf("PIB (em bilhões): ");
    scanf(" %f", &c->pib);

    printf("Quantidade de pontos turísticos: ");
    scanf(" %d", &c->pontosTuristicos);

    // Cálculos com proteção contra zero
    if (c->area > 0.0f) {
        c->densidadePopulacional = (float)c->populacao / c->area;
    } else {
        c->densidadePopulacional = 0.0f;
    }

    if (c->populacao > 0) {
        // PIB vem em bilhões -> converter para reais (x 1e9) antes de dividir
        c->pibPerCapita = (c->pib * 1e9f) / (float)c->populacao;
    } else {
        c->pibPerCapita = 0.0f;
    }
}

/* =========================
   Utilidades de exibição
   ========================= */
const char* nomeAtributo(int attr) {
    switch (attr) {
        case ATTR_POPULACAO:       return "População";
        case ATTR_AREA:            return "Área";
        case ATTR_PIB:             return "PIB";
        case ATTR_DENSIDADE:       return "Densidade Populacional";
        case ATTR_PIB_PER_CAPITA:  return "PIB per capita";
        default:                   return "Atributo";
    }
}

// Obtém valor do atributo como double (para comparar) e
// imprime uma linha com a unidade correta
double obterValorEImprimir(const struct Carta* c, int indice, int attr) {
    double v = 0.0;

    if (attr == ATTR_POPULACAO) {
        v = (double)c->populacao;
        printf("Carta %d - %s (%s %c%d): %lu\n",
               indice, c->cidadeNome, c->estadoNome, c->estadoLetra, c->cidadeNumero, c->populacao);
    } else if (attr == ATTR_AREA) {
        v = (double)c->area;
        printf("Carta %d - %s (%s %c%d): %.3f km²\n",
               indice, c->cidadeNome, c->estadoNome, c->estadoLetra, c->cidadeNumero, c->area);
    } else if (attr == ATTR_PIB) {
        v = (double)c->pib;
        printf("Carta %d - %s (%s %c%d): %.3f bilhões de R$\n",
               indice, c->cidadeNome, c->estadoNome, c->estadoLetra, c->cidadeNumero, c->pib);
    } else if (attr == ATTR_DENSIDADE) {
        v = (double)c->densidadePopulacional;
        printf("Carta %d - %s (%s %c%d): %.3f hab/km²\n",
               indice, c->cidadeNome, c->estadoNome, c->estadoLetra, c->cidadeNumero, c->densidadePopulacional);
    } else if (attr == ATTR_PIB_PER_CAPITA) {
        v = (double)c->pibPerCapita;
        printf("Carta %d - %s (%s %c%d): R$ %.2f\n",
               indice, c->cidadeNome, c->estadoNome, c->estadoLetra, c->cidadeNumero, c->pibPerCapita);
    }

    return v;
}

/* =========================
   Programa principal
   ========================= */
int main(void) {
    struct Carta carta1, carta2;

    printf("=== Cadastro de Cartas Super Trunfo ===\n\n");

    printf("Cadastro da primeira carta:\n");
    cadastrarCarta(&carta1);

    printf("\nCadastro da segunda carta:\n");
    cadastrarCarta(&carta2);

    // Relatório básico das cartas
    printf("\n=== Resumo das cartas cadastradas ===\n");
    printf("Carta 1: %s (%s) | Código: %s | População: %lu | Área: %.3f km² | PIB: %.3f bi | Pontos: %d\n",
           carta1.cidadeNome, carta1.estadoNome, carta1.codigo, carta1.populacao, carta1.area, carta1.pib, carta1.pontosTuristicos);
    printf("         Densidade: %.3f hab/km² | PIB per capita: R$ %.2f\n",
           carta1.densidadePopulacional, carta1.pibPerCapita);

    printf("Carta 2: %s (%s) | Código: %s | População: %lu | Área: %.3f km² | PIB: %.3f bi | Pontos: %d\n",
           carta2.cidadeNome, carta2.estadoNome, carta2.codigo, carta2.populacao, carta2.area, carta2.pib, carta2.pontosTuristicos);
    printf("         Densidade: %.3f hab/km² | PIB per capita: R$ %.2f\n\n",
           carta2.densidadePopulacional, carta2.pibPerCapita);

    // Comparação de UM atributo escolhido no código
    const int atributo = SELECTED_ATTR;
    const char* nomeAttr = nomeAtributo(atributo);

    printf("=== Comparação de cartas (Atributo: %s) ===\n\n", nomeAttr);
    double v1 = obterValorEImprimir(&carta1, 1, atributo);
    double v2 = obterValorEImprimir(&carta2, 2, atributo);

    int vencedora = 0; // 0 = empate, 1 = carta1, 2 = carta2
    if (atributo == ATTR_DENSIDADE) {
        // Menor vence
        if (v1 < v2) vencedora = 1;
        else if (v2 < v1) vencedora = 2;
        else vencedora = 0;
    } else {
        // Maior vence
        if (v1 > v2) vencedora = 1;
        else if (v2 > v1) vencedora = 2;
        else vencedora = 0;
    }

    printf("\nResultado: ");
    if (vencedora == 1) {
        printf("Carta 1 (%s, %s) venceu!\n", carta1.cidadeNome, carta1.estadoNome);
    } else if (vencedora == 2) {
        printf("Carta 2 (%s, %s) venceu!\n", carta2.cidadeNome, carta2.estadoNome);
    } else {
        printf("Empate!\n");
    }

    return 0;
}
