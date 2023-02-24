namespace mdg {
/* ========================= FORWARD DECLARATIONS ======================== */

namespace mdg {
template <typename GraphType>
class NodeSet;

template <typename GraphType>
class EdgeSet;

template <typename GraphType>
class NodeOp;

template <typename GraphType>
class EdgeOp;
}  // namespace mdg
/* =========================== PUBLIC INTERFACE ========================== */

/**
 * @brief A base class for all the graph expressions. Represents a pair of
 *        sets V and E where V is a set of nodes and E is a set of edges.
 * @tparam Derived A derived graph expression class
 */
template <typename Derived>
class MDGBase {
 public:  // * -------- Constructors -------- *
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

 public:  // * -------- Accessors -------- *
  /// @brief Get a node from the set V with a given index
  NodeOpBase<MDGBase<Derived>> node(int index);

  /// @brief Get a const node from the set V with a given index
  const NodeOpBase<MDGBase<Derived>> node(int index) const;

  /// @brief Get an edge from the set E with a given index
  EdgeOp<MDGBase<Derived>> edge(int index);

  /// @brief Get an edge from the set E with a given index
  const EdgeOp<MDGBase<Derived>> edge(int index) const;

 public:  // * -------- Useful data getters --------- *
  /// @brief Get the size of E and V combined
  int size() const;

  /// @brief Get the size of the set of nodes
  int numNodes() const;

  /// @brief Get the size of the set of edges
  int numEdges() const;
};
}  // namespace mdg