#include <digraph.h>
#include <iostream>

int main() {
  enum { TotalNodes = 10, TotalIncoming = TotalNodes / 2 };
  mdg::Digraph<std::string, bool> graph(TotalNodes);

  for (int i = 0; i < TotalNodes / 2; ++i)
    graph.connect(i, TotalNodes / 2, true);

  for (int i = TotalNodes / 2 + 1; i < TotalNodes; ++i)
    graph.connect(TotalNodes / 2, i, true);

  std::cout << "The incoming edges are:\n";
  auto incoming = graph.node(TotalNodes / 2).incoming();
  for (auto edge : incoming)
    std::cout << edge.index() << ": " << edge.start().index() << '-'
              << edge.end().index() << '\n';
  
  return !(graph.node(TotalNodes / 2).incoming().size() == TotalIncoming);
}