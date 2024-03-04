#ifndef MDG_NODESET_H
#define MDG_NODESET_H
namespace mdg {
/* ============================ PUBLIC INTERFACE ============================ */

/**
 * @brief A proxy class useful for iteration over the graph's nodes
*/
template <typename NodeType, typename EdgeType, typename AdjType>
class Digraph<NodeType, EdgeType, AdjType>::NodeSet {
  class Iterator;

 public:  // * Types
  typedef Digraph<NodeType, EdgeType, AdjType> Graph;
  typedef Graph::NodeOp NodeOp;
  typedef NodeType Node;

 public:  // * Construction and assignment
  NodeSet(Graph& graph, int size = 0);

 public:  // * Comparison
  bool operator==(const NodeSet& other) const;
  bool operator!=(const NodeSet& other) const;

 public: // * Stats
  bool empty() const;
  int size() const;

 public:  // * Manipulation
  void push_back(int index);
  void push_back(const NodeOp& node);
  NodeOp front();
  NodeOp back();

 public:  // * Iteration
  Iterator begin();
  Iterator end();

 protected:
  Graph& m_graph;
  std::vector<int> m_indices;
};
}  // namespace mdg

/* ================================ ITERATOR ================================ */
namespace mdg {
template <typename NodeType, typename EdgeType, typename AdjType>
class Digraph<NodeType, EdgeType, AdjType>::NodeSet::Iterator {
 public:  // * Types
  typedef Digraph<NodeType, EdgeType, AdjType> Graph;
  typedef Graph::NodeSet NodeSet;
  typedef Graph::NodeOp NodeOp;
  typedef Graph::Node Node;

 public:  // * Construction
  Iterator(NodeSet& set, int pos);

 public:  // * Comparison
  bool operator==(const Iterator& other) const;
  bool operator!=(const Iterator& other) const;

 public:  // * Pointer semantics
  NodeOp operator*() const;
  Iterator& operator++();

 private:
  NodeSet& m_set;
  int m_pos;
};
}  // namespace mdg

/* ============================= IMPLEMENTATIONS ============================ */
#include "../src/nodeset.cpp"
#endif  // MDG_NODESET_H