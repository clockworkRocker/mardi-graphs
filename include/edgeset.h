#ifndef MDG_EDGESET_H
#define MDG_EDGESET_H

namespace mdg {
/* ============================ PUBLIC INTERFACE ============================ */

/**
 * @brief A proxy class useful for iteration over the graph's edges
 */
template <typename NodeType, typename EdgeType, typename AdjType>
class Digraph<NodeType, EdgeType, AdjType>::EdgeSet {
  class Iterator;

 public:  // * Types
  typedef Digraph<NodeType, EdgeType, AdjType> Graph;
  typedef Graph::EdgeOp EdgeOp;

 public:  // * Construction and assignment
  EdgeSet(Graph& graph);

 public:  // * Comparison
  int size() const;
  bool operator==(const EdgeSet& other) const;
  bool operator!=(const EdgeSet& other) const;

 public:  // * Editing
  void push_back(int u, int v);
  void push_back(int index);
  void push_back(const EdgeOp& edge);
  EdgeOp front() const;
  EdgeOp back() const;

 public:  // * Iteration
  Iterator begin();
  Iterator end();

 protected:
  Graph& m_graph;
  std::vector<int> m_starts;
  std::vector<int> m_ends;
};
}  // namespace mdg

/* ================================ ITERATOR ================================ */
namespace mdg {
template <typename NodeType, typename EdgeType, typename AdjType>
class Digraph<NodeType, EdgeType, AdjType>::EdgeSet::Iterator {
 public:  // * Types
  typedef Digraph<NodeType, EdgeType, AdjType> Graph;
  typedef Graph::EdgeSet EdgeSet;
  typedef Graph::EdgeOp EdgeOp;

 public:  // * Construction
  Iterator(EdgeSet& set, int pos);

 public:  // * Comparison
  bool operator==(const Iterator& other) const;
  bool operator!=(const Iterator& other) const;

 public:  // * Pointer semantics
  EdgeOp operator*() const;
  Iterator& operator++();

 private:
  EdgeSet& m_set;
  int m_pos;
};
}  // namespace mdg

/* ============================= IMPLEMENTATIONS ============================ */
#include "../src/edgeset.cpp"
#endif  // MDG_EDGESET_H