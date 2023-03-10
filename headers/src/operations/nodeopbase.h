#ifndef MDG_OPERATIONS_NODEOPBASE_H
#define MDG_OPERATIONS_NODEOPBASE_H

#define THE_GRAPH_CLASS_SHOULD_BE_DERIVED_FROM_MDGBASE 1

namespace mdg {

/* ============================ PUBLIC INTERFACE =========================== */

/// @brief A lightweight object for node access with pointer semantics and some
///        additional methods for graph topology access
/// @tparam GraphType Graph exspression type. Must be derived from MDGBase
template <typename Derived>
class NodeOpBase {
 public:  // * -------- Types --------
  typedef typename internal::nodeop_traits<Derived>::graph_t graph_type;
  typedef typename internal::nodeop_traits<Derived>::node_t node_type;
  typedef typename internal::nodeop_traits<Derived>::edge_t edge_type;

 public:  // * -------- Constructors -------- *
  NodeOpBase(graph_type& graph, int index = -1);
  NodeOpBase(const NodeOpBase<Derived>& rhs);
  NodeOpBase(const NodeOpBase<Derived>&& rhs);

 public:  // * -------- Accessors -------- *
  /// @brief Get a reference to the associated graph node
  node_type& operator*();

  /// @brief Get a const reference to the associated graph node
  /// @throws
  const node_type& operator*() const;

  /// @brief Get a pointer to the associated graph node
  node_type* operator->();

  /// @brief Get a const pointer to the associated graph node
  /// @throws
  const node_type* operator->() const;

 public:  // * -------- Information methods -------- *
  /// @brief Get the degree of the node (the number of nodes it is connected to)
  int degree() const;

 protected:
  int m_index;
  graph_type& m_graph;
};
}  // namespace mdg

/* ============================ IMPLEMENTATIONS ============================ */
namespace mdg {

template <typename Derived>
typename NodeOpBase<Derived>::node_type& NodeOpBase<Derived>::operator*() {
  static_assert(THE_GRAPH_CLASS_SHOULD_BE_DERIVED_FROM_MDGBASE &&
                internal::traits<graph_type>::isMardiGraph);
  return m_graph.nodeData(m_index);
}

template <typename Derived>
const typename NodeOpBase<Derived>::node_type& NodeOpBase<Derived>::operator*()
    const {
  static_assert(THE_GRAPH_CLASS_SHOULD_BE_DERIVED_FROM_MDGBASE &&
                internal::traits<graph_type>::isMardiGraph);

  return m_graph.nodeData(m_index);
}

template <typename Derived>
inline typename NodeOpBase<Derived>::node_type*
NodeOpBase<Derived>::operator->() {
  static_assert(THE_GRAPH_CLASS_SHOULD_BE_DERIVED_FROM_MDGBASE &&
                internal::traits<graph_type>::isMardiGraph);

  return nullptr;
}

}  // namespace mdg
#endif  // MDG_OPERATIONS_NODEOPBASE_H