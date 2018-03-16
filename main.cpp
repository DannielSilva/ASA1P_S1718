#include <stdio.h>
#include <list>
#include <stack>
using namespace std;

#define min(A,B) A<B ? A : B

typedef struct vertice {
  int discovery = 0;
  int low;
  int stack = 0;
  list<int> adjacentes;
} Vertice;

typedef Vertice* Grafo;

typedef struct args_struct {
	Grafo* g;
	int visited, pontos;
	stack<int>* stackV;
}* Args_p;

void visit_Tarjan(int curV, Args_p args) {
	list<int>::iterator itv;
	int poppedV;

	args->g[curV]->discovery = args->g[curV]->low = args->visited++;
	args->stackV->push(curV);
	args->g[curV]->stack = 1;
	for (itv = args->g[curV]->adjacentes.begin(); itv != args->g[curV]->adjacentes.end(); ++itv) {
		if (!args->g[*itv]->discovery || args->g[*itv]->stack) {
			if (!args->g[*itv]->discovery) {
				visit_Tarjan(*itv, args);
			}
			args->g[curV]->low = min(args->g[curV]->low, args->g[*itv]->low);
		}
	}

	if (args->g[curV]->discovery == args->g[curV]->low) {
		poppedV = args->stackV->top();
		args->stackV->pop();
		args->g[curV]->stack = 1;
	}
}


void scc_Tarjan(Args_p args) {
	for (int i = 1; i < args->pontos; i++) {
		if (!args->g[i]->discovery) {
			visit_Tarjan(i, args);
		}
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
    grafo[vPai].adjacentes.push_front(vFilho);
  }

  Args_p args = new args_struct;
  args->g = &grafo;
  args->visited = 0;
  args->pontos = pontos;
  args->stackV = new stack<int>;


  for (i = 1; i <= pontos; i++) {
    for (it = grafo[i].adjacentes.begin(); it != grafo[i].adjacentes.end(); ++it) {
		printf("%d %d\n", i, *it);
	}
  }

	scc_Tarjan(args);

  return 0;
}
