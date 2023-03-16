#ifndef MDG_OPERATIONS_DIRECTEDNODEOP_H
#define MDG_OPERATIONS_DIRECTEDNODEOP_H

/* ================================ TRAITS =============================== */

namespace mdg {
namespace internal {
template <typename GraphType>
struct nodeop_traits<DirectedNodeOp<GraphType>> {
  typedef GraphType graph_t;
  typedef typename GraphType::node_type node_t;
  typedef typename GraphType::edge_type edge_t;
};
}  // namespace internal
}  // namespace mdg

/* ============================ PUBLIC INTERFACE =========================== */

namespace mdg {
/**
 * @brief A lightweight object for node operations in directed graphs
 * @tparam GraphType Any class deriving from DirectedBase
 */
template <typename GraphType>
class DirectedNodeOp : public NodeOpBase<DirectedNodeOp<GraphType>> {
 public:  // * -------- Types --------
  typedef NodeOpBase<DirectedNodeOp<GraphType>> Base;
  typedef typename Base::node_type node_type;
  typedef typename Base::edge_type edge_type;

 public:  // * -------- Inherited methods -------- *
  using Base::operator*;
  using Base::operator->;
  using Base::operator=;

 public:
  DirectedNodeOp(GraphType& graph, int index);

 public:  // * -------- New methods -------- *
  /// @brief Get the nodes that the incoming edges lead from to this node
  NodeSetOp<GraphType> parents() const;

  /// @brief Get the nodes that the outgoing edges lead to from this node
  NodeSetOp<GraphType> children() const;

  /// @brief Get the edges that lead into this node
  EdgeSetOp<GraphType> incoming() const;

  /// @brief Get the edges that go out of this node
  EdgeSetOp<GraphType> outgoing() const;
};
template <typename GraphType>
inline DirectedNodeOp<GraphType>::DirectedNodeOp(GraphType& graph, int index)
    : Base(graph, index) {}
}  // namespace mdg

#endif  // MDG_OPERATIONS_DIRECTEDNODEOP_H