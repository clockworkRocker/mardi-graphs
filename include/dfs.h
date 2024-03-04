#ifndef MDG_DFS_H
#define MDG_DFS_H

namespace mdg {

/**
 * @brief Iterable depth-first search through the nodes
 */
template <typename GraphType>
class DFS {
  class Iterator;

 public:  // * Constants
  enum class EdgeMark : unsigned char { unknown, tree, forward, cross, back };
  enum class Color : unsigned char { white, gray, black };

 public:  // * Types
  typedef GraphType Graph;
  typedef typename GraphType::NodeOp ObjectOp;

  typedef std::vector<EdgeMark> Classifier;

 public:  // * Construction
  /**
   * Create a DFS object for given graph that starts from the node with the
   * given index
   */
  DFS(GraphType& graph, int index);

 public:  // * DFS-specific stats
  /**
   * @return indices of the nodes in topological sort order
   */
  std::vector<int> topologicalSort();

  /**
   * @brief Mark the edges of the graph as tree, forward, cross or back
   * @param[out] marks Vector of output marks
   * @return true if all the edges have been marked
  */
  bool markEdges(Classifier& marks) const;

 public:  // * Iteration
  Iterator begin();
  Iterator end();

 private:
  GraphType& m_graph;
  int m_start;
};
}  // namespace mdg

/* ============================= IMPLEMENTATIONS ============================ */
#include "../src/searches/dfs.cpp"

#endif  // MDG_DFS_H