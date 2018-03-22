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
  int visited, pontosV, ligacoesE;
  stack<int>* stackV;
  int *scc, *tabelaV;
} * Args_p;

/********************************** TARJAN **********************************/
void visit_Tarjan(int curV, Args_p args) {
  int poppedV, v;  // aux
  printf("--------------sou o curV %d\n", curV);
  args->tabelaV[discovery(curV)] = args->tabelaV[low(curV)] = ++args->visited;
  printf("tenho discovery %d e low %d\n", args->tabelaV[discovery(curV)],
         args->tabelaV[low(curV)]);
  args->stackV->push(curV);
  args->tabelaV[inStack(curV)] = 1;
  // printf("sou o %d com offset d e o offset do seguint e %d\n",curV,
  // args->tabelaV[offset((curV+1))]);
  printf("Pos ligaçao ini %d limite pos %d i pos prox %d\n", args->tabelaV[offset(curV)], (args->ligacoesE + 1) * PAR_S, args->tabelaV[offset((curV + 1))]);
  for (int i = args->tabelaV[offset(curV)];
         i != 0 && i < (args->ligacoesE + 1) * PAR_S &&
                  (i < args->tabelaV[offset((curV + 1))] || curV < args->pontosV + 1);
       i += 2) {  // i = indice no grafo da ligacao
    v = args->g[i + 1];
    printf("sou o curV %d a analisar o filho %d, i=%d\n", curV, v, i);
    if (!args->tabelaV[discovery(v)] || args->tabelaV[inStack(v)]) {
      printf("entrei no if com ou\n");
      if (!args->tabelaV[discovery(v)]) {
        printf("sou o %d e vou visitar o %d\n", curV, v);
        visit_Tarjan(v, args);
      }
      printf("sou o %d e vou comprar com o %d\n", curV, v);
      args->tabelaV[low(curV)] =
          min(args->tabelaV[low(curV)], args->tabelaV[low(v)]);
    }
  }

  if (args->tabelaV[discovery(curV)] == args->tabelaV[low(curV)]) {
    printf("D=%d Off=%d\n", args->tabelaV[discovery(curV)],
           args->tabelaV[low(curV)]);
    args->scc[++args->scc[0]] = curV;
    printf("ESTOU CURV %d n scc %d\n", curV, args->scc[0]);
    do {
      poppedV = args->stackV->top();
      printf("vertice poppado %d %d\n", poppedV, args->scc[0]);
      args->stackV->pop();
      args->tabelaV[inStack(poppedV)] = 0;
      args->scc[args->scc[0]] = min(poppedV, args->scc[args->scc[0]]);
      args->tabelaV[sccNum(poppedV)] = args->scc[0];

    } while (curV != poppedV);
  }
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
  Grafo grafD, grafO, grafS, auxgrafo;
  int pontosV, ligacoesE, vPai, vFilho, actV, *tabelaV, *scc;
  Args_p args;

  auto ordGraf = [&grafS](int i, int j) -> bool {
    if (grafS[i * 2] == grafS[j * 2]) {
      return grafS[to(i)] < grafS[to(j)];
    }
    return grafS[from(i)] < grafS[from(j)];
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
  grafS = grafD;
  sort(auxgrafo + 1, auxgrafo + ligacoesE + 1, ordGraf);

  actV = 0;
  for (int l = 1; l < ligacoesE + 1; l++) {
    grafO[from(l)] = grafS[from(auxgrafo[l])];
    grafO[to(l)] = grafS[to(auxgrafo[l])];
    // atualiza a tabela com o offset do vertice
    if (grafO[from(l)] != actV) {
      actV = grafO[from(l)];
      tabelaV[offset(actV)] = from(l);
    }
    // printf("%d act %d\n", tabelaV[actV], actV);
    // printf("%d %d\n", grafO[from(l)], grafO[to(l)]);
  }

  // Limpar residuos de criacao do grafo
  delete[] grafD;

  scc = new int[pontosV + 1];
  scc[0] = 0;
  args = new args_struct;
  args->g = grafO;
  args->visited = 0;
  args->pontosV = pontosV;
  args->ligacoesE = ligacoesE;
  args->stackV = new stack<int>;
  args->tabelaV = tabelaV;
  args->scc = scc;

  printf("---------\nantes de tarjan\n");
  for (int i = 1; i < ligacoesE + 1; i++) {
    printf("%d %d\n", grafO[from(i)], grafO[to(i)]);
  }

  scc_Tarjan(args);

  for (int i = 1; i < scc[0] + 1; i++) printf("SCC %d %d\n", i, scc[i]);

  for (int i = 1; i < ligacoesE + 1; i++) {
    printf("B %d E MINIMO %d\n", grafO[to(i)], grafO[from(i)]);
    grafO[from(i)] = scc[tabelaV[sccNum(grafO[from(i)])]];
    grafO[to(i)] = scc[tabelaV[sccNum(grafO[to(i)])]];
    printf("A %d E MINIMO %d\n", grafO[to(i)], grafO[from(i)]);
  }

  printf("---------\ndepois de tarjan\n");
  for (int i = 1; i < ligacoesE + 1; i++) {
    printf("%d %d\n", grafO[from(i)], grafO[to(i)]);
  }

  grafS = grafO;

  for (int l = 1; l < ligacoesE + 1; l++) {
    auxgrafo[l] = l;
  }

  sort(auxgrafo + 1, auxgrafo + ligacoesE + 1, ordGraf);
  printf("---------\ndepois do sort\n");

  int pai = 0, filho = 0, s = 0;
  int filtgrafo_size = min((ligacoesE + 1), (scc[0] * scc[0]));
  int* filtgrafo = new int[filtgrafo_size];
  for (int l = 1; l < ligacoesE + 1; l++) {
    // grafO[from(l)] = grafS[from(auxgrafo[l])];
    // grafO[to(l)] = grafS[to(auxgrafo[l])];
    printf("i devia %d estava %d\n", l, auxgrafo[l]);
    if ((pai != grafS[from(auxgrafo[l])] || filho != grafS[to(auxgrafo[l])]) &&
        grafS[from(auxgrafo[l])] != grafS[to(auxgrafo[l])]) {
      pai = grafS[from(auxgrafo[l])];
      filho = grafS[to(auxgrafo[l])];
      filtgrafo[s++] = auxgrafo[l];
      printf("ii %d %d\n", l, auxgrafo[l]);
    }
    printf("pai %d filho %d\n", pai, filho);
  }

  for (int l = 1; l < ligacoesE + 1; l++) {
    // grafO[from(l)] = grafS[from(auxgrafo[l])];
    /// grafO[to(l)] = grafS[to(auxgrafo[l])];
    // printf("mal %d %d\n", grafO[from(l)], grafO[to(l)]);
    /*if ((pai!=grafO[from(l)] ||filho!=grafO[to(l)])&&
    grafO[from(l)]!=grafO[to(l)]){ pai=grafO[from(l)]; filho=grafO[to(l)];
            filtgrafo[s++] = l;
    }*/
  }
  printf("%d\n%d\n", scc[0], s);
  for (int i = 0; i < s; i++) {
    printf("%d %d\n", grafO[from(filtgrafo[i])], grafO[to(filtgrafo[i])]);
  }

  delete[] tabelaV;
  delete[] grafO;
  delete[] auxgrafo;
  return 0;
}
