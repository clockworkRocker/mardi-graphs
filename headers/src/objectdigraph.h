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

 public:  // * Base class methods
 public:  // * Information gettets
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

 protected:
  std::vector<node_type> m_nodes;
  std::vector<edge_type> m_edges;
  internal::AdjacencyStorage<ThisDerived, StorageType> m_adj;
};
}  // namespace mdg

namespace mdg {
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