#include "test_utils.h"

#include "digraph.h"

using Graph = mdg::Digraph<int, int>;

bool test_chain() {
  const int TotalNodes = 10;

  Graph graph(TotalNodes);
  for (int i = 0; i < TotalNodes - 1; ++i) {
    graph.connect(i, i + 1, true);
  }

  MDG_TEST_INFO << "Performing DFS on graph from node 0\n";
  int steps = 0;
  for (auto edge : graph.edfs(0)) {
    std::cout << edge.start().index() << " -> " << edge.end().index() << '\n';
    ++steps;
  }
  std::cout << "\n";

  MDG_EXPECT_EQUALITY(steps, TotalNodes - 1);

  return 0;
}

bool test_circle() {
  enum { TotalNodes = 10, Target = TotalNodes / 2 };

  mdg::Digraph<int, bool> graph(TotalNodes);
  for (int i = 0; i < TotalNodes - 1; ++i) {
    graph.connect(i, i + 1, true);
  }
  graph.connect(TotalNodes - 1, 0, true);

  MDG_TEST_INFO << ": Performing DFS on graph from node 0\n 0";
  int steps = 0;
  for (auto node : graph.dfs(1)){
    std::cout << " -> " << node.index();
    ++steps;
  }
  std::cout << "\n";

  MDG_EXPECT_EQUALITY(steps, TotalNodes);

  return 0;
}

MDG_TEST_MAIN(TestEdgeDFS, test_chain, test_circle);