#include <iostream>
#include <ctime>
#include "digraph.h"

int main() {
  mdg::Digraph<int, int> graph;
  srand(time(NULL));

  for (int i = 0; i < 10000; ++i) {
    graph.add_node(rand() % 8);
  }
  for (int i = 0; i < 10000; ++i) {
    graph.connect(rand() % 10000, rand() % 10000, rand() % 64);
  }

  for (auto edge : graph.node(rand() % 10000).incoming()) {
    std::cout << edge.index() << ": " << edge.start().index() << '-' << edge.end().index() <<  '\n';
  }

  return 0;
}