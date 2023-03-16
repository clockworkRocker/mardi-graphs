namespace mdg {
/* ================================ TRAITS =============================== */
namespace internal {
template <typename GraphType>
struct nodeop_traits<UndirectedNodeOp<GraphType>> {
  typedef GraphType graph_t;
  typedef typename traits<GraphType>::node_t node_t;
  typedef typename traits<GraphType>::nodeset_t nodeset_t;
  typedef typename traits<GraphType>::edge_t edge_t;
};
}  // namespace internal

/* ========================== PUBLIC INTERFACE ===========================
 */

template <typename GraphType>
class UndirectedNodeOp : public NodeOpBase<UndirectedNodeOp<GraphType>> {
 public:  // * -------- Types -------- *
  typedef NodeOpBase<UndirectedNodeOp<GraphType>> Base;
  typedef typename Base::node_type node_type;

 public:  // * -------- Inherited methods -------- *
  using Base::operator*;
  using Base::operator->;
};
}  // namespace mdg

/* ================== BASE CLASS METHODS IMPLEMENTATIONS ================= */
/*namespace mdg {
namespace details {
template <typename GraphType>
struct NodeOpImpl<UndirectedNodeOp<GraphType>> {
  static typename UndirectedNodeOp<GraphType>::node_type& deref(
      typename UndirectedNodeOp<GraphType>::Base* ptr) {
    return typename UndirectedNodeOp<GraphType>::node_type();
  }

  static const typename UndirectedNodeOp<GraphType>::node_type& deref(
      const typename UndirectedNodeOp<GraphType>::Base* ptr) {
    return typename UndirectedNodeOp<GraphType>::node_type();
  }
};

}  // namespace details
}  // namespace mdg
*/
