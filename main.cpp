#include <stdio.h>
#include <algorithm>
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
  Grafo grafD, grafO, auxgrafo;
  int pontosV, ligacoesE, vPai, vFilho, *tabelaV;

  auto ordGraf = [&grafD](int i, int j) -> bool {
    if (grafD[i * 2] == grafD[j * 2]) {
      return grafD[index(i, 1, PAR_S)] < grafD[index(j, 1, PAR_S)];
    }
    return grafD[index(i, 0, PAR_S)] < grafD[index(j, 0, PAR_S)];
  };

  //LER INPUT ------------------------------------------------
 if (!scanf("%d\n%d", &pontosV, &ligacoesE)) {
    printf("Deu erro a ler\n");
 }

  //CRIACAO DO GRAFO -------------------------------
  grafD = new int[(ligacoesE + 1) * PAR_S];
  grafO = new int[(ligacoesE + 1) * PAR_S];
  auxgrafo = new int[ligacoesE + 1];

  // Construir grafo do input e auxiliar de indices
  for (int l = 1; l <= ligacoesE; l++) {
    if (!scanf("%d %d", &vPai, &vFilho)){
      printf("Deu erro a ler\n");
    }
    
    grafD[index(l, 0, PAR_S)] = vPai;
    grafD[index(l, 1, PAR_S)] = vFilho;
    auxgrafo[l] = l;
  }

  sort(auxgrafo + 1, auxgrafo + ligacoesE + 1, ordGraf);

  /*Args_p args = new args_struct;
  args->g = &grafo;
  args->visited = 0;
  args->pontos = pontos;
  args->stackV = new stack<int>;*/

  for (int l = 1; l <= ligacoesE; l++) {
    grafO[index(l, 0, PAR_S)] = grafD[index(auxgrafo[l], 0, PAR_S)];
    grafO[index(l, 1, PAR_S)] = grafD[index(auxgrafo[l], 1, PAR_S)];
    //printf("%d", auxgrafo[l]);
    //printf("%d %d\n", grafO[index(l, 0, PAR_S)], grafO[index(l, 1, PAR_S)]);
  }

  //Limpar residuos de criacao do grafo
  delete[] grafD;
  delete[] auxgrafo;

  //CRIAR TABELA DE VERTICES ------------------------
  // offset, discovery, low, in stack, SCC number
  tabelaV = new int[(pontosV + 1) * VERT_S];

  // reset a tabela com a informacao de cada vertice
  for (int i = 1; i < pontosV + 1; i++) {
    for (int j = 0; j < VERT_S; j++) {
      tabelaV[index(i, j, VERT_S)] = 0;
    }
  }
  for (int i = 1; i <= pontosV; i++) {
    /*for (it = grafo[i].adjacentes.begin(); it != grafo[i].adjacentes.end();
       ++it) { printf("%d %d\n", i, *it);
    }*/
  }

  // scc_Tarjan(args);

  delete[] tabelaV;
  delete[] grafO;
  return 0;
}
