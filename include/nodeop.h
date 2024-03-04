#ifndef MDG_NODEOP_H
#define MDG_NODEOP_H

/* ========================== FORWARD DECLARATIONS ========================== */
namespace mdg {
template <typename NodeType, typename EdgeType, typename AdjType>
class Digraph<NodeType, EdgeType, AdjType>::NodeOp {
 public: // * Types
  typedef Digraph<NodeType, EdgeType, AdjType> Graph;
  typedef NodeType Node;

 public: // * Friends
  friend Graph::NodeSet;

 public: // * Construction
  NodeOp(Graph& graph, int index);

 public:  // * Stats
  int index() const;
  int degree() const;

 public:  // * Pointer semantics
  Node& operator*();
  const Node& operator*() const;
  Node* operator->();
  const Node* operator->() const;

  template <typename OtherNodeOp>
  bool operator==(const OtherNodeOp& other) const;
  template <typename OtherNodeOp>
  bool operator!=(const OtherNodeOp& other) const;

 public: // * Conversion
  operator bool() const;

 public:
  /// Get the nodes that are connected with this with incoming edges
  Graph::NodeSet parents() const;

  /// Get the nodes that are connected with this with outgoing edges
  Graph::NodeSet children() const;

  /// Get the incoming edges for this node
  Graph::EdgeSet incoming() const;

  /// Get the outgoing edges for this node
  Graph::EdgeSet outgoing() const;

 protected:
  Graph& m_graph;
  int m_index;
};
}  // namespace mdg

/* ============================= IMPLEMENTATIONS ============================ */
#include "../src/nodeop.cpp"

#endif  // MDG_NODEOP_H