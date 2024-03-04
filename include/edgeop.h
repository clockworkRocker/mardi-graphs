#ifndef MDG_EDGEOP_H
#define MDG_EDGEOP_H

/* ============================ PUBLIC INTERFACE ============================ */
namespace mdg {
template <typename NodeType, typename EdgeType, typename AdjType>
class Digraph<NodeType, EdgeType, AdjType>::EdgeOp {
 public:  // * Types
  typedef Digraph<NodeType, EdgeType, AdjType> Graph;
  typedef Graph::NodeOp NodeOp;
  typedef EdgeType Edge;
 
 public: // * Friends
  friend Graph::EdgeSet;

 public:  // * Construction
  EdgeOp(Graph& graph, int u, int v);

  /**
   * @brief Construct an EdgeOp using the edge object index
   * @warning This performs an edge lookup in the adjacency matrix to determine
   *          the start and end nodes for the edge. Basically it is slow af.
   */
  EdgeOp(Graph& graph, int index);

 public:  // * Comparison
  bool operator==(const EdgeOp& other);
  bool operator!=(const EdgeOp& other);

 public:  // * Getters
  Edge& operator*();
  const Edge& operator*() const;
  Edge* operator->();
  const Edge* operator->() const;

  NodeOp start() const;
  NodeOp end() const;
  int index() const;

  operator bool() const;

 private:
  Graph& m_graph;
  int m_start, m_end;
  int m_index;
};
}  // namespace mdg
/* ============================= IMPLEMENTATIONS ============================ */
#include "../src/edgeop.cpp"

#endif  // MDG_EDGEOP_H