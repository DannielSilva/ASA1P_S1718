#include <stdio.h>
#include <list>
using namespace std;

class Grafo {
    int _size;

  public:
    Grafo(int size) {

    }
    void printname() {
    }
};

int main(int argc, char const *argv[]) {
  int pontos;
  int ligacoes;
  int v1, v2, i;
  //Grafo grafo;

  scanf("%d\n%d", &pontos, &ligacoes);
  //printf("%d %d\n", pontos, ligacoes);
  for(i=0; i<ligacoes; i++) {
    scanf("%d %d", &v1, &v2);

  }

  return 0;
}
