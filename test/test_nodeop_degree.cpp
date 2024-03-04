#include <iostream>
#include "digraph.h"

int main() {
  enum { TotalNodes = 10, TotalDegree = 9 };
  mdg::Digraph<std::string, bool> graph(TotalNodes);
  
  for (int i = 0; i < TotalNodes/2; ++i)
    graph.connect(i, TotalNodes/2, true);
  
  for (int i = TotalNodes/2 + 1; i < TotalNodes; ++i)
    graph.connect(TotalNodes/2, i, true);

  return !(graph.node(TotalNodes/2).degree() == TotalDegree);
}