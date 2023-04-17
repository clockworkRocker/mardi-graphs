#ifndef MDG_OBJECTDIGRAPH_H
#define MDG_OBJECTDIGRAPH_H

/* ================================ TRAITS =============================== */
namespace mdg {
namespace internal {
template <typename NodeType, typename EdgeType, int StorageType>
struct traits<ObjectDigraph<NodeType, EdgeType, StorageType>>
    : public traits<
          DirectedBase<ObjectDigraph<NodeType, EdgeType, StorageType>>> {
  typedef NodeType node_t;
  typedef EdgeType edge_t;

  enum {
    storageType = StorageType,
    hasDirectAccess = true,
    hasNodeObjects = true,
    hasEdgeObjects = true
  };
};
}  // namespace internal
}  // namespace mdg

/* ============================ PUBLIC INTERFACE =========================== */
namespace mdg {
/**
 * @brief A directed graph that has objects associated with its nodes and edges
 */
template <typename NodeType, typename EdgeType, int StorageType = DenseMatrix>
class ObjectDigraph
    : public DirectedBase<ObjectDigraph<NodeType, EdgeType, StorageType>> {
  /// This is to bypass the stypid macro parsing error with nested templates
  typedef ObjectDigraph<NodeType, EdgeType, StorageType> ThisDerived;

 public:  // * Types
  typedef DirectedBase<ObjectDigraph<NodeType, EdgeType, StorageType>> Base;

  MDG_COMMON_TYPEDEFS(ThisDerived)
  MDG_COMMON_FRIENDS(ThisDerived)

 public:  // * -------- Constructors -------- * //
  ObjectDigraph(unsigned numNodes = 0);
  ObjectDigraph(const std::vector<node_type>& nodeset);
  ObjectDigraph(std::vector<node_type>&& nodeset);

 public:  // * -------- Base class methods -------- * //
  using Base::bfs;
  using Base::dfs;

 public:  // * -------- Information gettets -------- * //
          /// @brief Get the size of the set of nodes
  int numNodes() const;

  /// @brief Get the size of the set of edges
  int numEdges() const;

 public:  // * Access methods
  /// @brief Get a reference to the object associated with the node with the
  ///        given index
  node_type& nodeData(int index);

  /// @brief Get a const reference to the object associated with the node with
  ///        the given index
  const node_type& nodeData(int index) const;

 public:  // * Manipulation methods
  /**
   * @brief Add an edge object to the graph and use it to connect two nodes
   *
   * @param from Node index
   * @param to Node index
   * @param edge And edge object
   * @return The index of the created edge or -1 if creation fails
   */
  int addEdge(unsigned from, unsigned to, const edge_type& edge);

 protected:
  std::vector<node_type> m_nodes;
  std::vector<edge_type> m_edges;
  internal::AdjacencyStorage<ThisDerived, StorageType> m_adj;
};
}  // namespace mdg

namespace mdg {
template <typename NodeType, typename EdgeType, int StorageType>
inline ObjectDigraph<NodeType, EdgeType, StorageType>::ObjectDigraph(
    unsigned numNodes)
    : m_nodes(numNodes), m_adj(numNodes) {}

template <typename NodeType, typename EdgeType, int StorageType>
inline int ObjectDigraph<NodeType, EdgeType, StorageType>::numNodes() const {
  return m_nodes.size();
}

template <typename NodeType, typename EdgeType, int StorageType>
inline int ObjectDigraph<NodeType, EdgeType, StorageType>::numEdges() const {
  return m_edges.size();
}

template <typename NodeType, typename EdgeType, int StorageType>
inline typename ObjectDigraph<NodeType, EdgeType, StorageType>::node_type&
ObjectDigraph<NodeType, EdgeType, StorageType>::nodeData(int index) {
  // TODO: Add boundary checking

  return m_nodes[index];
}
template <typename NodeType, typename EdgeType, int StorageType>
inline const typename ObjectDigraph<NodeType, EdgeType, StorageType>::node_type&
ObjectDigraph<NodeType, EdgeType, StorageType>::nodeData(int index) const {
  // TODO: Add boundary checking

  return m_nodes[index];
}
}  // namespace mdg

#endif  // MDG_OBJECTDIGRAPH_H