#include <list>
#include <stack>
using namespace std;

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
	stack<int>* stacke;
}* Args_p;
