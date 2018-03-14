#include <stdio.h>
#include "main.h"
#include <list>
#include <stack>
using namespace std;

/*void visit_Tarjan(int curV, Args_p args) {
	args->g[curV]->discovery = args->g[curV]->low = args->visited;
}*/


void scc_Tarjan(Args_p args) {

	for (int i = 1; i < args->pontos; i++) {
		if (!args->g[i]->discovery) {
			//visit_Tarjan(i, args);
		}
		args->pontos = 20;
	}
}


int main(int argc, char const *argv[]) {
  Grafo grafo; //ISTO E UMN GRAFO :O
  int pontos, ligacoes, vPai, vFilho, i;
  list<int>::iterator it;

  scanf("%d\n%d", &pontos, &ligacoes);

  grafo = new Vertice[pontos+1];
  for (i = 0; i < ligacoes; i++) {
    scanf("%d %d", &vPai, &vFilho);
    grafo[vPai].adjacentes.push_back(vFilho);
  }



  for (i = 1; i <= pontos; i++) {
    for (it = grafo[i].adjacentes.begin(); it != grafo[i].adjacentes.end(); ++it) {
      printf("%d %d\n", i, *it);
    }

	Args_p args = new args_struct;
	args->g = &grafo;
	args->visited = 0;
	args->pontos = pontos;
	args->stacke = new stack<int>;
	scc_Tarjan(args);
	printf("oi%d\n", args->pontos);
}

  return 0;
}
