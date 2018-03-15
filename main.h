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
