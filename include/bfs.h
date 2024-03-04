#ifndef MDG_BFS_H
#define MDG_BFS_H


/* =========================== PUBLIC INTERFACE ============================ */

namespace mdg {
/**
 * @brief Iterable breadth-first search that goes over a graph's nodes
*/
template <typename GraphType>
class BFS {
  class Iterator;

 public:
  typedef GraphType Graph;
  typedef typename GraphType::NodeOp ObjectOp;

 public: // * Constructors
  BFS(Graph& graph, int index);

 public: // * Search-specific stats
  /// @return The maximum size of the BFS queue
  int maxBreadth();

 public:
  Iterator begin() const;
  Iterator end() const;

 private:
  Graph& m_graph;
  int m_start;
};
}  // namespace mdg

/* ============================= IMPLEMENTATIONS ============================ */
#include "../src/searches/bfs.cpp"

#endif  // MDG_BFS_H