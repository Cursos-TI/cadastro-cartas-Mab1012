#include <stdio.h>

// Definindo a struct para representar uma carta
struct Carta {
    char codigo[3];       // Ex.: "A1"
    char estadoLetra;     // Ex.: 'A' até 'H'
    int cidadeNumero;     // Ex.: 1 até 4
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
};

int main() {
    struct Carta carta1, carta2;

    // Cadastro da Carta 1
    printf("Cadastro da Carta 1:\n");

    // Estado (letra de A a H)
    do {
        printf("Digite a letra do estado (A-H): ");
        scanf(" %c", &carta1.estadoLetra);
    } while (carta1.estadoLetra < 'A' || carta1.estadoLetra > 'H');

    // Cidade (número de 1 a 4)
    do {
        printf("Digite o número da cidade (1-4): ");
        scanf("%d", &carta1.cidadeNumero);
    } while (carta1.cidadeNumero < 1 || carta1.cidadeNumero > 4);

    // Gerando o código automaticamente
    sprintf(carta1.codigo, "%c%d", carta1.estadoLetra, carta1.cidadeNumero);

    // Restante dos dados
    printf("Digite a população: ");
    scanf("%d", &carta1.populacao);

    printf("Digite a área em km²: ");
    scanf("%f", &carta1.area);

    printf("Digite o PIB (em bilhões): ");
    scanf("%f", &carta1.pib);

    printf("Digite a quantidade de pontos turísticos: ");
    scanf("%d", &carta1.pontosTuristicos);

    // -------------------- Carta 2 --------------------
    printf("\nCadastro da Carta 2:\n");

    do {
        printf("Digite a letra do estado (A-H): ");
        scanf(" %c", &carta2.estadoLetra);
    } while (carta2.estadoLetra < 'A' || carta2.estadoLetra > 'H');

    do {
        printf("Digite o número da cidade (1-4): ");
        scanf("%d", &carta2.cidadeNumero);
    } while (carta2.cidadeNumero < 1 || carta2.cidadeNumero > 4);

    sprintf(carta2.codigo, "%c%d", carta2.estadoLetra, carta2.cidadeNumero);

    printf("Digite a população: ");
    scanf("%d", &carta2.populacao);

    printf("Digite a área em km²: ");
    scanf("%f", &carta2.area);

    printf("Digite o PIB (em bilhões): ");
    scanf("%f", &carta2.pib);

    printf("Digite a quantidade de pontos turísticos: ");
    scanf("%d", &carta2.pontosTuristicos);

    // -------------------- Exibindo --------------------
    printf("\n--- Carta 1 ---\n");
    printf("Código: %s\n", carta1.codigo);
    printf("Estado: %c\n", carta1.estadoLetra);
    printf("Cidade: %d\n", carta1.cidadeNumero);
    printf("População: %d\n", carta1.populacao);
    printf("Área: %.3f km²\n", carta1.area);
    printf("PIB: %.1f Bilhões\n", carta1.pib);
    printf("Pontos turísticos: %d\n", carta1.pontosTuristicos);

    printf("\n--- Carta 2 ---\n");
    printf("Código: %s\n", carta2.codigo);
    printf("Estado: %c\n", carta2.estadoLetra);
    printf("Cidade: %d\n", carta2.cidadeNumero);
    printf("População: %d\n", carta2.populacao);
    printf("Área: %.3f km²\n", carta2.area);
    printf("PIB: %.1f Bilhões\n", carta2.pib);
    printf("Pontos turísticos: %d\n", carta2.pontosTuristicos);

    return 0;
}
