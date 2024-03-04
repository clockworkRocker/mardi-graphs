#ifndef MDG_GRAPH_H
#define MDG_GRAPH_H

#include <vector>

/* ================================= TYPES ================================== */
namespace mdg {
/// @brief Represent a set of graph's node indices
typedef std::vector<int> UnboundNodeSet;

/// @brief Represent a set of graph's edges
typedef std::vector<std::pair<int, int>> UnboundEdgeSet;
}

/* ========================== FORWARD DECLARATIONS ========================== */
namespace mdg {
template <typename GraphType>
class DFS;

template <typename GraphType>
class BFS;

template <typename GraphType>
class EdgeDFS;

template <typename GraphType>
class EdgeBFS;

template <typename NodeType, typename EdgeType, typename AdjType>
class Digraph;

namespace internal {
template <typename GraphType>
struct traits;
}
}  // namespace mdg

/* ================================= TRAITS ================================= */
namespace mdg {
namespace internal {
template <typename NodeType, typename EdgeType, typename AdjType>
struct traits<Digraph<NodeType, EdgeType, AdjType>> {
  enum { isDirected = true };
  typedef NodeType Node;
  typedef EdgeType Edge;
  typedef AdjType Index;
};
}  // namespace internal
}  // namespace mdg

/* ============================ PUBLIC INTERFACE ============================ */
namespace mdg {
/// @brief Directed graph class
/// @tparam NodeType Data type stored in nodes
/// @tparam EdgeType Data type stored in edges
/// @tparam AdjType Node adjacency data type
template <typename NodeType, typename EdgeType = bool, typename AdjType = int>
class Digraph {
  typedef Digraph<NodeType, EdgeType, AdjType> This;

 public:  // * Types
  typedef NodeType Node;
  typedef EdgeType Edge;
  typedef AdjType Index;

  class NodeOp;
  class EdgeOp;
  class NodeSet;
  class EdgeSet;

 public:  // * Construction and assignment
  Digraph(int size = 0);

 public:  // * Editing
  /// Add a new node to the graph
  /// @return Its index
  int add_node(const Node& data);

  /// Construct another node in-place
  template <typename ... Args>
  int emplace_node(const Args& ... args);

  /// @brief Connect nodes with indices u and v with an edge
  /// @return New edge index or -1 if connection failed
  /// @warning This method will expand the adjacency matrix when necessary which
  ///          is why it is recommended to add all the nodes to the graph first
  ///          and then connect them to minimize copying and memory allocation
  ///          operations
  int connect(int u, int v, const Edge& data);

 public:  // * Stats
  /// @return Number of nodes
  int size() const;

  /// @return Number of edges
  int num_edges() const;

 public:  // * Sets access
  /// @return A proxy object that lets you iterate over the graph's nodes
  NodeSet nodes();

  /// @return A proxy object that lets you interact with the graph's topography
  NodeOp node(int index);

  /// @return A proxy object that lets you iterate over the graphs's edges
  EdgeSet edges();

  /// @return A proxy object that lets you interact with the graph's topography
  /// @param u Start node index
  /// @param v End node index
  EdgeOp edge(int u, int v);

  /// @return A proxy object that lets you interact with the graph's topography
  /// @param u Start node
  /// @param v End node
  EdgeOp edge(const NodeOp& u, const NodeOp& v);

 public:  // * Searches
  /// Depth-first search by nodes from the given starting node
  DFS<This> dfs(int start);

  /// Depth-first search by edges from the given starting node
  EdgeDFS<This> edfs(int start);

  /// Breadth-first search by nodes from the given starting node
  BFS<This> bfs(int start);

 private:
  void resize_adj();

 protected:
  int m_adjSize;

  std::vector<Node> m_nodes;
  std::vector<Edge> m_edges;
  std::vector<Index> m_adj;
};

}  // namespace mdg

/* ============================= IMPLEMENTATIONS ============================ */
#include "../src/digraph.cpp"
#include "edgeop.h"
#include "nodeop.h"
#include "nodeset.h"
#include "edgeset.h"
#include "dfs.h"
#include "bfs.h"
#include "edgedfs.h"

#endif  // MDG_GRAPH_H