namespace mdg {
/* ================================ TRAITS =============================== */
namespace internal {
template <typename GraphType>
struct nodeop_traits<UndirectedNodeOp<GraphType>> {
  typedef GraphType graph_t;
  typedef typename traits<GraphType>::node_t node_t;
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

/* ================== BASE CLASS METHODS IMPLEMENTATIONS ================= */
template <typename GraphType>
typename NodeOpBase<UndirectedNodeOp<GraphType>>::node_type&
NodeOpBase<UndirectedNodeOp<GraphType>>::operator*(int index) {
  return node_type();
}

}  // namespace mdg
