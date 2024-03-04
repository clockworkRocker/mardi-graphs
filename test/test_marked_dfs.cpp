#include "digraph.h"
#include "test_utils.h"

using namespace mdg;
using SimpleGraph = Digraph<int, bool>;
using EdgeClass = DFS<SimpleGraph>::EdgeMark;

bool test_no_cycles() {
  MDG_TEST_INFO << "Checking graph with no cycles\n";
  SimpleGraph g;
  int backEdges = 0;

  for (int i = 0; i < 4; ++i)
    g.add_node(i);

  g.connect(0, 1, true);
  g.connect(0, 2, true);
  g.connect(0, 3, true);
  g.connect(1, 3, true);

  DFS<SimpleGraph>::Classifier marks(g.num_edges());
  g.dfs(0).markEdges(marks);

  for (const auto& mark : marks)
    if (mark == DFS<SimpleGraph>::EdgeMark::back)
      ++backEdges;

  MDG_EXPECT_EQUALITY(backEdges, 0);

  return 0;
}

bool test_with_one_cycle() {
  MDG_TEST_INFO << "Checking graph with 1 cycle\n";
  SimpleGraph g;
  SimpleGraph::EdgeSet backEdges(g);

  for (int i = 0; i < 4; ++i)
    g.add_node(i);

  g.connect(0, 1, true);
  g.connect(0, 2, true);
  g.connect(0, 3, true);
  // g.connect(1, 3, true);

  g.connect(3, 0, true);

  DFS<SimpleGraph>::Classifier c;
  g.dfs(0).markEdges(c);

  for (unsigned i = 0; i < c.size(); ++i) {
    if (c[i] == DFS<SimpleGraph>::EdgeMark::back)
      backEdges.push_back(i);
  }

  MDG_EXPECT_EQUALITY(backEdges.size(), 1);
  auto backEdge = *backEdges.begin();
  MDG_TEST_INFO << "Found the back edge: " << backEdge.start().index() << " -> "
                << backEdge.end().index() << "\n";

  MDG_EXPECT_EQUALITY((*backEdges.begin()).start().index(), 3);
  MDG_EXPECT_EQUALITY((*backEdges.begin()).end().index(), 0);

  return 0;
}

bool test_with_two_cycles() {
  MDG_TEST_INFO << "Checking graph with 2 cycles from the same node\n";
  SimpleGraph g;
  UnboundEdgeSet correct = {{2, 1}, {3, 0}};
  SimpleGraph::EdgeSet backEdges(g);

  for (int i = 0; i < 4; ++i)
    g.add_node(i);

  g.connect(0, 1, true);
  g.connect(1, 2, true);
  g.connect(2, 3, true);

  g.connect(2, 1, true);
  g.connect(3, 0, true);

  DFS<SimpleGraph>::Classifier c;
  g.dfs(0).markEdges(c);

  for (unsigned i = 0; i < c.size(); ++i) {
    if (c[i] == DFS<SimpleGraph>::EdgeMark::back)
      backEdges.push_back(i);
  }

  MDG_EXPECT_EQUALITY(backEdges.size(), 2);

  int i = 0;
  for (auto e : backEdges) {
    MDG_TEST_INFO << "Found the back edge: " << e.start().index() << " -> "
                  << e.end().index() << "\n";

    MDG_EXPECT_EQUALITY(e.start().index(), correct[i].first);
    MDG_EXPECT_EQUALITY(e.end().index(), correct[i].second);
    ++i;
  }

  return 0;
}

bool test_complex() {
  SimpleGraph g;
  for (int i = 0; i < 7; ++i)
    g.add_node(i);

  g.connect(0, 1, true);
  g.connect(1, 2, true);
  g.connect(1, 5, true);
  g.connect(2, 3, true);
  g.connect(3, 1, true);
  g.connect(3, 4, true);
  g.connect(5, 6, true);
  g.connect(6, 4, true);

  DFS<SimpleGraph>::Classifier c;
  g.dfs(0).markEdges(c);

  DFS<SimpleGraph>::Classifier myMarks = {
      EdgeClass::tree, EdgeClass::tree, EdgeClass::tree, EdgeClass::tree,
      EdgeClass::back, EdgeClass::cross, EdgeClass::tree, EdgeClass::tree};

  auto edges = g.edges();
  auto iter = edges.begin();

  for (unsigned i = 0; i < c.size(); ++i) {
    auto e = *iter;
    MDG_TEST_INFO << "The edge " << e.start().index() << " -> "
                  << e.end().index() << " is a "
                  << (c[i] == EdgeClass::tree      ? "tree"
                      : c[i] == EdgeClass::forward ? "forward"
                      : c[i] == EdgeClass::cross   ? "cross"
                      : c[i] == EdgeClass::back    ? "back"
                                                   : "unknown")
                  << " one\n";
    MDG_EXPECT_EQUALITY(c[i], myMarks[i]);
    ++iter;
  }

  return 0;
}

MDG_TEST_MAIN(TestMarkedDFS,
              test_no_cycles,
              test_with_one_cycle,
              test_with_two_cycles,
              test_complex);