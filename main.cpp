#include <stdio.h>
#include <list>
using namespace std;

typedef struct grafoj {
  int numV;

} *Grafo;

int main(int argc, char const *argv[]) {
  int pontos;
  int ligacoes;
  int v1, v2, i;
  list<int>* grafo; //ISTO E UMN GRAFO :O

  scanf("%d\n%d", &pontos, &ligacoes);
  grafo = new list<int>[pontos+1];

  for(i=0; i<ligacoes; i++) {
    scanf("%d %d", &v1, &v2);
    grafo[v1].push_back(v2);
  }

  list<int>::iterator it;
  for(i=1; i<=pontos; i++) {
    for (it = grafo[i].begin(); it != grafo[i].end(); ++it) {
      printf("%d %d\n", i, *it);
    }
  }

  return 0;
}
