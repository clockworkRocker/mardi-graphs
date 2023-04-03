#ifndef MDG_DIRECTEDBASE_H
#define MDG_DIRECTEDBASE_H

/* ================================ TRAITS =============================== */
namespace mdg {
namespace internal {
template <typename Derived>
struct traits<DirectedBase<Derived>> : public traits<MDGBase<Derived>> {
  typedef DirectedNodeOp<Derived> nodeop_t;
  typedef EdgeOp<Derived> edgeop_t;

  enum { isDirected = true };
};
}  // namespace internal
}  // namespace mdg

/* ============================ PUBLIC INTERFACE =========================== */

namespace mdg {
/***/
template <typename Derived>
class DirectedBase : public MDGBase<Derived> {
 public:  // * Types
  typedef MDGBase<Derived> Base;
  MDG_COMMON_TYPEDEFS(DirectedBase<Derived>)

  using Base::derived;
};
}  // namespace mdg
#endif  // MDG_DIRECTEDBASE_H