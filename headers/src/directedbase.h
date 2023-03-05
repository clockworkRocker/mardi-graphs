#ifndef MDG_DIRECTEDBASE_H
#define MDG_DIRECTEDBASE_H

/* ================================ TRAITS =============================== */
namespace mdg {
namespace internal {
template <typename Derived>
struct traits<DirectedBase<Derived>> : public traits<MDGBase<Derived>> {
  enum { isDirected = true };
};
}  // namespace internal
}  // namespace mdg

/* ============================ PUBLIC INTERFACE =========================== */

namespace mdg {
/***/
template <typename Derived>
class DirectedBase : public MDGBase<Derived> {};
}  // namespace mdg
#endif  // MDG_DIRECTEDBASE_H