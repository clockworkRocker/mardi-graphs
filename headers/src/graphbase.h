namespace mdg {
/* ========================= FORWARD DECLARATIONS ======================== */

namespace mdg {
template <typename NodeType>
class NodeSet;

template <typename EdgeType>
class EdgeSet;

template <typename NodeType>
class NodeOp;

template <typename EdgeType>
class EdgeOp;
}  // namespace mdg
/* =========================== PUBLIC INTERFACE ========================== */
template <typename Derived>
class MDGBase {
 public:
  /// @brief Create an empty graph
  MDGBase();

  /// @brief Copy a graph
  /// @tparam OtherDerived Another graph object type
  /// @param rhs Another graph object
  template <typename OtherDerived>
  MDGBase(const OtherDerived& rhs);

  /// @brief Move a graph
  /// @tparam OtherDerived Another graph object type
  /// @param rhs Another graph object
  template <typename OtherDerived>
  MDGBase(const OtherDerived&& rhs);
};
}  // namespace mdg