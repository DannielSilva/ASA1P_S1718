#include <stdio.h>
#include <algorithm>
#include <list>
#include <stack>
using namespace std;

#define min(A, B) A < B ? A : B
#define index(x, y, width) width* x + y
#define PAR_S 2
#define VERT_S 5
#define offset(v) index(v, 0, VERT_S)  // RETORNA INDICE DO GRAFo
#define discovery(v) index(v, 1, VERT_S)
#define low(v) index(v, 2, VERT_S)
#define inStack(v) index(v, 3, VERT_S)
#define sccNum(v) index(v, 4, VERT_S)
#define from(l) index(l, 0, PAR_S)  // RETORNA VALOR DO V
#define to(l) index(l, 1, PAR_S)

/******************************** ESTRUTURAS ********************************/
/*typedef struct vertice {
  int discovery = 0;
  int low;
  int stack = 0;
  list<int> adjacentes;
} Vertice;*/

typedef int* Grafo;

typedef struct args_struct {
  Grafo g;
  int visited, pontosV;
  stack<int>* stackV;
  int *scc, *tabelaV;
} * Args_p;

/********************************** TARJAN **********************************/
void visit_Tarjan(int curV, Args_p args) {
  int poppedV;  // aux

  args->tabelaV[discovery(curV)] = args->tabelaV[low(curV)] = args->visited++;
  args->stackV->push(curV);
  args->tabelaV[inStack(curV)] = 1;

  for (int i = offset(curV) + 1, v = args->g[i]; i < offset(curV + 1);
       i += 2, v = args->g[i]) {  // i = indice no grafo do filho
    if (!args->tabelaV[discovery(v)] || args->tabelaV[inStack(v)]) {
      if (!args->tabelaV[discovery(v)]) {
        visit_Tarjan(v, args);
      }
      // args->tabelaV[low(v)] = min(args->tabelaV[curV]->low,
      // args->tabelaV[*itv]->low);
    }
  }

  /*if (args->tabelaV[curV]->discovery == args->tabelaV[curV]->low) {
    poppedV = args->st ackV->top();
    args->stackV->pop();
    args->tabelaV[curV]->stack = 1;
}*/
}

void scc_Tarjan(Args_p args) {
  for (int i = 1; i < args->pontosV + 1; i++) {
    if (!args->tabelaV[discovery(i)]) {
      visit_Tarjan(i, args);
    }
  }
}

/********************************** MAIN **********************************/
int main(int argc, char const* argv[]) {
  Grafo grafD, grafO, auxgrafo;
  int pontosV, ligacoesE, vPai, vFilho, actV, *tabelaV;
  Args_p args;

  auto ordGraf = [&grafD](int i, int j) -> bool {
    if (grafD[i * 2] == grafD[j * 2]) {
      return grafD[to(i)] < grafD[to(j)];
    }
    return grafD[from(i)] < grafD[from(j)];
  };

  // LER INPUT ------------------------------------------------
  if (!scanf("%d\n%d", &pontosV, &ligacoesE)) {
    printf("Deu erro a ler\n");
  }

  // CRIACAO DO GRAFO -------------------------------
  grafD = new int[(ligacoesE + 1) * PAR_S];
  grafO = new int[(ligacoesE + 1) * PAR_S];
  auxgrafo = new int[ligacoesE + 1];

  // CRIAR TABELA DE VERTICES ------------------------
  // 0 offset, 1 discovery, 2 low, 3 in stack, 4 SCC number
  tabelaV = new int[(pontosV + 1) * VERT_S];

  // reset a tabela com a informacao de cada vertice
  for (int i = 1; i < pontosV + 1; i++) {
    for (int j = 0; j < VERT_S; j++) {
      tabelaV[index(i, j, VERT_S)] = 0;
    }
  }

  // Construir grafo do input e auxiliar de indices
  for (int l = 1; l < ligacoesE + 1; l++) {
    if (!scanf("%d %d", &vPai, &vFilho)) {
      printf("Deu erro a ler\n");
    }

    grafD[from(l)] = vPai;
    grafD[to(l)] = vFilho;
    auxgrafo[l] = l;
  }

  sort(auxgrafo + 1, auxgrafo + ligacoesE + 1, ordGraf);

  actV = 0;
  for (int l = 1; l < ligacoesE + 1; l++) {
    grafO[from(l)] = grafD[from(auxgrafo[l])];
    grafO[to(l)] = grafD[to(auxgrafo[l])];
    // atualiza a tabela com o offset do vertice
    if (grafO[from(l)] != actV) {
      actV = grafO[from(l)];
      tabelaV[actV] = from(l);
    }
    // printf("%d act %d\n", tabelaV[actV], actV);
    // printf("%d %d\n", grafO[from(l)], grafO[to(l)]);
  }

  // Limpar residuos de criacao do grafo
  delete[] grafD;
  delete[] auxgrafo;

  args = new args_struct;
  args->g = grafO;
  args->visited = 0;
  args->pontosV = pontosV;
  args->stackV = new stack<int>;
  args->tabelaV = tabelaV;
  args->scc = new int[pontosV + 1];

  for (int i = 1; i < pontosV + 1; i++) {
    /*for (it = grafo[i].adjacentes.begin(); it != grafo[i].adjacentes.end();
       ++it) { printf("%d %d\n", i, *it);
    }*/
  }

  scc_Tarjan(args);

  delete[] tabelaV;
  delete[] grafO;
  return 0;
}
