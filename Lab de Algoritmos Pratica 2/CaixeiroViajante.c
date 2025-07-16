#include <stdio.h>
#include <math.h>


// Coordenadas das 10 cidades separadas em X e Y em dois conjuntos
double coordenadasX[10] = {0, 2, 5, 1, 6, 3, 7, 4, 8, 6}; // decidi colocar elas assim pra facilitar em alguns pontos do codigo viu George 
double coordenadasY[10] = {0, 3, 4, 1, 2, 5, 1, 4, 3, 6};


// Matriz de distâncias
double dist[10][10];

// Vetores para controle
int perm[10 - 1];          //cidades a serem permutadas (1 a 9)
int melhorRota[10 - 1];    // aqui vai ficar a melhor rota
double menorDistancia = 1000000.0;  // Um valor inicial bem alto
long int totalRotas = 0; // long long porque é um valor grande sendo 362.880 ou seja 9!

// Funçao que criei pra calcular a distância euclidiana
double euclidiana(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

// Função pra preecher as distancias
void calcularDistancias() {
    int i, j;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            dist[i][j] = euclidiana(coordenadasX[i], coordenadasY[i], coordenadasX[j], coordenadasY[j]);
        }
    }
}

// Função para trocar valores durante a geração da permutação
void trocar(int a[], int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

// Gera permutações 
void Permutacao(int inicio, int fim) {
    if (inicio == fim) {
        double soma = 0;
        int i;

        // Rota começa e termina na cidade 0 como é pedido na pratica
        int rota[10 + 1];
        rota[0] = 0;
        for (i = 0; i < 10 - 1; i++) {
            rota[i + 1] = perm[i];
        }
        rota[10] = 0;

        for (i = 0; i < 10; i++) {
            soma += dist[rota[i]][rota[i + 1]];
        }

        totalRotas++;

        //Mostra a rota atual
        printf("Rota Num. %ld: 0 -----> ", totalRotas);
        for (i = 0; i < 10 - 1; i++) {
            printf("%d -----> ", perm[i]);
        }
        printf("0 | Dist.: %.2lf\n", soma);
        

        // Atualiza melhor rota
        if (soma < menorDistancia) {
            menorDistancia = soma;
            for (i = 0; i < 10 - 1; i++) {
                melhorRota[i] = perm[i];
            }
        }

        return;
    }

    int i;
    for (i = inicio; i <= fim; i++) {
        trocar(perm, inicio, i);
        Permutacao(inicio + 1, fim);
        trocar(perm, inicio, i); // desfaz a troca
    }
}

int main() {
    int i;

    // Inicializa permutação de cidades (de 1 a 9)
    for (i = 0; i < 10 - 1; i++) {
        perm[i] = i + 1;
    }

    calcularDistancias();
    Permutacao(0, 10 - 2);

    // Mostra melhor rota encontrada
    printf("\nMelhor rota encontrada:\n0 -----> ");
    for (i = 0; i < 10 - 1; i++) {
        printf("%d -----> ", melhorRota[i]);
    }
    printf("0 | Dist. total: %.2lf\n", menorDistancia);
    printf("Total de rotas avaliadas: %ld\n", totalRotas);

    return 0;
}
