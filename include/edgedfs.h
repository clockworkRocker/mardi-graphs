#ifndef MDG_EDGEDFS_H
#define MDG_EDGEDFS_H

namespace mdg {
/**
 * @brief Iterable depth-first search through the edges
 */
template <typename GraphType>
class EdgeDFS {
  class Iterator;

 public:
  typedef GraphType Graph;
  typedef typename Graph::EdgeOp ObjectOp;

 public:  // * Construction
  EdgeDFS(Graph& graph, int index);

 public:  // * Iteration
  Iterator begin();
  Iterator end();

 private:
  GraphType& m_graph;
  int m_start;
};
}  // namespace mdg

#include "../src/searches/edgedfs.cpp"

#endif  // MDG_EDGEDFS_H