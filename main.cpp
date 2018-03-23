/*******************************************************************************/
/*********************** ANALISE E SINTESE DE ALGORITMOS ***********************/
/********************************* 1o Projecto *********************************/
/*******************************************************************************/
/*******************************************************************************/
/*************************** JOAO DANIEL SILVA 86445 ***************************/
/**************************** FRANCISCO SOUSA 86416 ****************************/
/*******************************************************************************/
#include <stdio.h>
#include <algorithm>
#include <list>
#include <stack>
using namespace std;

#define min(A, B) A < B ? A : B
#define index(x, y, width) width * x + y
#define PAR_S 2
#define VERT_S 5
#define offset(v) index(v, 0, VERT_S) // retorna indice no array de vertices
#define discovery(v) index(v, 1, VERT_S)
#define low(v) index(v, 2, VERT_S)
#define inStack(v) index(v, 3, VERT_S)
#define sccNum(v) index(v, 4, VERT_S)
#define from(l) index(l, 0, PAR_S) // retorna vertice da ligacao
#define to(l) index(l, 1, PAR_S)

/********************************* ESTRUTURAS *********************************/
typedef int* Grafo;

typedef struct args_struct {
	Grafo g;
	int visited, pontosV, ligacoesE;
	stack<int>* stackV;
	int *scc, *tabelaV;
} * Args_p;

/*********************************** TARJAN ***********************************/
void visit_Tarjan(int curV, Args_p args) {
	int poppedV;
	args->tabelaV[discovery(curV)] = args->tabelaV[low(curV)] = ++args->visited;
	args->stackV->push(curV);
	args->tabelaV[inStack(curV)] = 1;
	for (int v, i = args->tabelaV[offset(curV)];
				 i != 0 && (
						(i < args->ligacoesE * PAR_S && curV == args->g[i])
						||
						(i == args->ligacoesE * PAR_S)
						/*(i < args->ligacoesE * PAR_S && i != args->tabelaV[offset((curV + 1))])
						||
						(i == args->ligacoesE * PAR_S)*/
						); i += 2) { // i = indice no grafo da ligacao
		v = args->g[i + 1];
		if (!args->tabelaV[discovery(v)] || args->tabelaV[inStack(v)]) {
			if (!args->tabelaV[discovery(v)]) {
				visit_Tarjan(v, args);
			}
			args->tabelaV[low(curV)] =
					min(args->tabelaV[low(curV)], args->tabelaV[low(v)]);
		}
	}

	if (args->tabelaV[discovery(curV)] == args->tabelaV[low(curV)]) {
		args->scc[++args->scc[0]] = curV;
		do {
			poppedV = args->stackV->top();
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

/************************************ MAIN ************************************/
int main(int argc, char const* argv[]) {
	Grafo grafD, grafO, grafS, auxgrafo, filtgrafo;
	int pontosV, ligacoesE, vPai, vFilho, actV, numE, numSCC, filtgrafo_size, *tabelaV, *scc;
	Args_p args;

	auto ordGraf = [&grafS](int i, int j) -> bool {
		if (grafS[i * 2] == grafS[j * 2]) {
			return grafS[to(i)] < grafS[to(j)];
		}
		return grafS[from(i)] < grafS[from(j)];
	};

	// LER INPUT ---------------------------------------------------------------
	if (!scanf("%d\n%d", &pontosV, &ligacoesE)) {
		printf("Deu erro a ler\n");
	}

	// CRIACAO DO GRAFO --------------------------------------------------------
	grafD = new int[(ligacoesE + 1) * PAR_S];
	grafO = new int[(ligacoesE + 1) * PAR_S];
	auxgrafo = new int[ligacoesE + 1];

	// CRIAR TABELA DE VERTICES ------------------------------------------------
	// 0 offset, 1 discovery, 2 low, 3 in stack, 4 SCC number
	tabelaV = new int[(pontosV + 1) * VERT_S];

	// inicializar tabela de vertices
	for (int i = 1; i < pontosV + 1; i++) {
		for (int j = 0; j < VERT_S; j++) {
			tabelaV[index(i, j, VERT_S)] = 0;
		}
	}

	// Construir grafo do input e inicializar auxiliar de indices
	for (int l = 1; l < ligacoesE + 1; l++) {
		if (!scanf("%d %d", &vPai, &vFilho)) {
			printf("Deu erro a ler\n");
		}
		grafD[from(l)] = vPai;
		grafD[to(l)] = vFilho;
		auxgrafo[l] = l;
	}
	// ORDENAR LIGACOES NO GRAFO -----------------------------------------------
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
	}

	// Limpar residuos de criacao do grafo
	delete[] grafD;

	// APLICAR TARJAN ----------------------------------------------------------
	// Inicializar estruturas args
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

	scc_Tarjan(args);

	delete args->stackV;
	delete args;

	// SELECIONAR LIGACOES ENTRE SCCS ------------------------------------------
	// Substituir vertices pelo minimo da sua scc
	for (int i = 1; i < ligacoesE + 1; i++) {
		grafO[from(i)] = scc[tabelaV[sccNum(grafO[from(i)])]];
		grafO[to(i)] = scc[tabelaV[sccNum(grafO[to(i)])]];
		auxgrafo[i] = i;
	}

	numSCC = scc[0];
	delete[] tabelaV;
	delete[] scc;

	// Ordenar ligacoes com os minimos
	grafS = grafO;
	sort(auxgrafo + 1, auxgrafo + ligacoesE + 1, ordGraf);

	vPai = 0; vFilho = 0; numE = 0; filtgrafo_size = min( (ligacoesE + 1), ((numSCC * (numSCC - 1)) / 2) );
	filtgrafo = new int[filtgrafo_size];

	// Guardar indices de ligacoes entre sccs num array auxiliar
	for (int l = 1; l < ligacoesE + 1; l++) {
		if ((vPai != grafS[from(auxgrafo[l])] || vFilho != grafS[to(auxgrafo[l])]) &&
				grafS[from(auxgrafo[l])] != grafS[to(auxgrafo[l])]) {
			vPai = grafS[from(auxgrafo[l])];
			vFilho = grafS[to(auxgrafo[l])];
			filtgrafo[numE++] = auxgrafo[l];
		}
	}

	// IMPRIMIR OUTPUT ---------------------------------------------------------
	printf("%d\n%d\n", numSCC, numE);
	for (int i = 0; i < numE; i++) {
		printf("%d %d\n", grafO[from(filtgrafo[i])], grafO[to(filtgrafo[i])]);
	}

	delete[] filtgrafo;
	delete[] grafO;
	delete[] auxgrafo;
	return 0;
}
