#include <stdio.h>

struct Carta {
    char codigo[4];       // Ex.: "A1" + '\0'
    char estadoLetra;     // A-H
    int cidadeNumero;     // 1-4
    char estadoNome[30];  // Nome do estado
    char cidadeNome[50];  // Nome da cidade
    int populacao;        // habitantes
    float area;           // km²
    float pib;            // bilhões de reais
    int pontosTuristicos; // quantidade
    float densidadePopulacional; // hab/km²
    float pibPerCapita;          // reais por habitante
};

int main() {
    struct Carta carta1, carta2;

    printf("=== Cadastro de Cartas Super Trunfo ===\n\n");

    // -------------------- Carta 1 --------------------
    printf("Cadastro da primeira carta:\n");

    printf("Nome do estado: ");
    scanf(" %[^\n]", carta1.estadoNome);

    printf("Escolha a letra do estado (A-H): ");
    scanf(" %c", &carta1.estadoLetra);

    printf("Nome da cidade: ");
    scanf(" %[^\n]", carta1.cidadeNome);

    printf("Escolha o número da cidade (1-4): ");
    scanf(" %d", &carta1.cidadeNumero);

    sprintf(carta1.codigo, "%c%d", carta1.estadoLetra, carta1.cidadeNumero);

    printf("População: ");
    scanf(" %d", &carta1.populacao);

    printf("Área (em km²): ");
    scanf(" %f", &carta1.area);

    printf("PIB (em bilhões): ");
    scanf(" %f", &carta1.pib);

    printf("Quantidade de pontos turísticos: ");
    scanf(" %d", &carta1.pontosTuristicos);

    // Cálculos da Carta 1
    carta1.densidadePopulacional = carta1.populacao / carta1.area;
    carta1.pibPerCapita = (carta1.pib * 1e9f) / carta1.populacao;

    // -------------------- Carta 2 --------------------
    printf("\nCadastro da segunda carta:\n");

    printf("Nome do estado: ");
    scanf(" %[^\n]", carta2.estadoNome);

    printf("Escolha a letra do estado (A-H): ");
    scanf(" %c", &carta2.estadoLetra);

    printf("Nome da cidade: ");
    scanf(" %[^\n]", carta2.cidadeNome);

    printf("Escolha o número da cidade (1-4): ");
    scanf(" %d", &carta2.cidadeNumero);

    sprintf(carta2.codigo, "%c%d", carta2.estadoLetra, carta2.cidadeNumero);

    printf("População: ");
    scanf(" %d", &carta2.populacao);

    printf("Área (em km²): ");
    scanf(" %f", &carta2.area);

    printf("PIB (em bilhões): ");
    scanf(" %f", &carta2.pib);

    printf("Quantidade de pontos turísticos: ");
    scanf(" %d", &carta2.pontosTuristicos);

    // Cálculos da Carta 2
    carta2.densidadePopulacional = carta2.populacao / carta2.area;
    carta2.pibPerCapita = (carta2.pib * 1e9f) / carta2.populacao;

    // -------------------- Exibindo --------------------
    printf("\n=== Cartas Cadastradas ===\n");

    printf("\n--- Carta 1 ---\n");
    printf("Estado: %c\n", carta1.estadoLetra);
    printf("Código: %s\n", carta1.codigo);
    printf("Nome da Cidade: %s\n", carta1.cidadeNome);
    printf("População: %d\n", carta1.populacao);
    printf("Área: %.2f km²\n", carta1.area);
    printf("PIB: %.2f bilhões de reais\n", carta1.pib);
    printf("Número de Pontos Turísticos: %d\n", carta1.pontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta1.densidadePopulacional);
    printf("PIB per Capita: %.2f reais\n", carta1.pibPerCapita);

    printf("\n--- Carta 2 ---\n");
    printf("Estado: %c\n", carta2.estadoLetra);
    printf("Código: %s\n", carta2.codigo);
    printf("Nome da Cidade: %s\n", carta2.cidadeNome);
    printf("População: %d\n", carta2.populacao);
    printf("Área: %.2f km²\n", carta2.area);
    printf("PIB: %.2f bilhões de reais\n", carta2.pib);
    printf("Número de Pontos Turísticos: %d\n", carta2.pontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta2.densidadePopulacional);
    printf("PIB per Capita: %.2f reais\n", carta2.pibPerCapita);

    return 0;
}
