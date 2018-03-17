#include <stdio.h>
#include <list>
#include <stack>
using namespace std;

#define min(A, B) A < B ? A : B
#define index(x, y, width) width* x + y
#define PAR_S 2
#define VERT_S 5

/******************************** ESTRUTURAS ********************************/
/*typedef struct vertice {
  int discovery = 0;
  int low;
  int stack = 0;
  list<int> adjacentes;
} Vertice;*/

typedef int* Grafo;

typedef struct args_struct {
  // Grafo* g;
  int visited, pontos;
  stack<int>* stackV;
} * Args_p;

/********************************** TARJAN **********************************/
void visit_Tarjan(int curV, Args_p args) {
  /*list<int>::iterator itv;
  int poppedV;

  args->g[curV]->discovery = args->g[curV]->low = args->visited++;
  args->stackV->push(curV);
  args->g[curV]->stack = 1;
  for (itv = args->g[curV]->adjacentes.begin();
       itv != args->g[curV]->adjacentes.end(); ++itv) {
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
  }*/
}

void scc_Tarjan(Args_p args) {
  /*for (int i = 1; i < args->pontos; i++) {
    if (!args->g[i]->discovery) {
      visit_Tarjan(i, args);
    }
  }*/
}

/********************************** MAIN **********************************/
int main(int argc, char const* argv[]) {
  Grafo grafo;
  int pontosV, ligacoesE, vPai, vFilho, i;
  int* tabelaV;
  // list<int>::iterator it;

  scanf("%d\n%d", &pontosV, &ligacoesE);

  grafo = new int[(ligacoesE + 1) * PAR_S];
  // offset, discovery, low, in stack, SCC number
  tabelaV = new int[pontosV * VERT_S];

  for (i = 1; i <= ligacoesE; i++) {
    scanf("%d %d", &vPai, &vFilho);
    grafo[index(i, 0, PAR_S)] = vPai;
    grafo[index(i, 1, PAR_S)] = vFilho;
  }

  /*Args_p args = new args_struct;
  args->g = &grafo;
  args->visited = 0;
  args->pontos = pontos;
  args->stackV = new stack<int>;*/

  for (i = 1; i <= pontosV; i++) {
    /*for (it = grafo[i].adjacentes.begin(); it != grafo[i].adjacentes.end();
       ++it) { printf("%d %d\n", i, *it);
                        }*/
  }

  // scc_Tarjan(args);

  return 0;
}
