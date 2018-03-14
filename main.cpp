#include <stdio.h>
#include <list>
using namespace std;

typedef struct vertice {
  int discovery = 0;
  int low = 0;
  int stack = 0;
  list<int> adjacentes;
} Vertice;

typedef Vertice* Grafo;

int main(int argc, char const *argv[]) {
  Grafo grafo; //ISTO E UMN GRAFO :O
  int pontos;
  int ligacoes;
  int vPai, vFilho, i;

  scanf("%d\n%d", &pontos, &ligacoes);
  grafo = new Vertice[pontos+1];

  for(i=0; i<ligacoes; i++) {
    scanf("%d %d", &vPai, &vFilho);
    grafo[vPai].adjacentes.push_back(vFilho);
  }

  list<int>::iterator it;
  for(i=1; i<=pontos; i++) {
    for (it = grafo[i].adjacentes.begin(); it != grafo[i].adjacentes.end(); ++it) {
      printf("%d %d\n", i, *it);
    }
  }

  return 0;
}
