#include "test_utils.h"
#include "digraph.h"

bool test_chain() {
  enum { TotalNodes = 10, Target = TotalNodes / 2 };

  mdg::Digraph<int, bool> graph(TotalNodes);
  for (int i = 0; i < TotalNodes - 1; ++i) {
    graph.connect(i, i + 1, true);
  }

  MDG_TEST_INFO << ": Performing DFS on graph from node 0\n 0";
  int steps = 0;
  for (auto node : graph.dfs(1)){
    std::cout << " -> " << node.index();
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

bool test_tree() {
  enum {TotalNodes = 8};
  mdg::Digraph<int, bool> graph(TotalNodes);
  auto order = {1, 2, 4, 8, 5, 3, 6, 7};
  
  MDG_TEST_INFO << ": Performing DFS on graph from node 0.\n";
  for (int i = 0; i < TotalNodes/2; ++i) {
    graph.connect(i + 1, (i + 1) * 2, true);
    graph.connect(i + 1, (i + 1) * 2 + 1, true);
  }

  auto place = order.begin();
  for (auto node : graph.dfs(0)){
    MDG_EXPECT_EQUALITY(node.index() + 1, *place);
    ++place;
  }
  return 0;
}

bool test_single() {
  return 0;
}

bool test_empty() {
  mdg::Digraph<int, int> a;
  int counter = 0;
  auto dfs = a.dfs(0);

  for (auto iter = dfs.begin(); iter != dfs.end(); ++iter)
    ++counter;


  MDG_EXPECT_EQUALITY(counter, 0);
  return 0;
}

MDG_TEST_MAIN(TestDFS, test_chain, test_circle, test_tree, test_single, test_empty);