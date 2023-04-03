#ifndef MDG_MDGBASE_H
#define MDG_MDGBASE_H

/* ================================ TRAITS =============================== */
namespace mdg {
namespace internal {
template <typename Derived>
struct traits<MDGBase<Derived>> : public baseTraits<Derived> {
 public:  // * -------- Compile-time traits -------- *
  enum { isMardiGraph = true };
};

}  // namespace internal
}  // namespace mdg

/* =========================== PUBLIC INTERFACE ========================== */
namespace mdg {
/**
 * @brief A base class for all the graph expressions. Represents a pair of
 *        sets V and E where V is a set of nodes and E is a set of edges.
 * @tparam Derived A derived graph expression class
 */
template <typename Derived>
class MDGBase {
 public:  // * --------- Types -------- *
  typedef typename internal::traits<Derived>::node_t node_type;
  typedef typename internal::traits<Derived>::nodeop_t nodeop_type;
  typedef typename internal::traits<Derived>::nodeset_t nodeset_type;
  typedef typename internal::traits<Derived>::edge_t edge_type;
  typedef typename internal::traits<Derived>::edgeop_t edgeop_type;
  typedef typename internal::traits<Derived>::edgeset_t edgeset_type;

  /// @brief Get a reference to the derived object
  inline Derived& derived();

  /// @brief Get a const reference to the derived object
  inline const Derived& derived() const;

 public:  // * -------- Operators -------- *
  template <typename OtherDerived>
  Derived& operator=(const MDGBase<OtherDerived>& other);

  template <typename OtherDerived>
  Derived& operator=(const MDGBase<OtherDerived>&& other);

 public:  // * -------- Accessors -------- *
  /// @brief Get a node from the set V with a given index
  nodeop_type node(int index);

  /// @brief Get a const node from the set V with a given index
  const nodeop_type node(int index) const;

  /// @brief Get the full set V
  /// @return A set of lightweight wrapper objects for node manipulation
  nodeset_type nodes();

  /// @brief Get a reference to the object associated with the node with the
  ///        given index
  node_type& nodeData(int index);

  /// @brief Get a const reference to the object associated with the node with
  ///        the given index
  const node_type& nodeData(int index) const;

  /// @brief Get an edge between the two given nodes
  /// @return The object to interact with the existing edge or a special
  ///         NullEdge constant object if the edge doesn't exist
  edgeop_type edge(int from, int to);

  /// @brief Get an edge from the set E with a given index
  edgeop_type edge(int index);

  /// @brief Get an edge from the set E with a given index
  const edgeop_type edge(int index) const;

 public:  // * -------- Useful data getters --------- *
  /// @brief Get the size of E and V combined
  int size() const;

  /// @brief Get the size of the set of nodes
  int numNodes() const;

  /// @brief Get the size of the set of edges
  int numEdges() const;

  /// @return The node object that is used to check for node existance
  nodeop_type nullNode() const;

  /// @brief The edge object that is used to check for edge existance
  edgeop_type nullEdge() const;

 public:  // * -------- Editing methods -------- *
  /**
   * @brief Add a node to the graph
   * @return The ID of the node created or -1 if creation fails
   */
  int addNode(const node_type& data);

  /**
   * @brief Construct a node in place and add it to the graph
   * @tparam Args Arguments for the node data constructor
   * @return The ID of the node created or -1 if creation fails
   */
  template <typename... Args>
  int emplaceNode(Args... args);

  /**
   * @brief Add an edge connecting the two given nodes defined by their IDs
   * @return The ID of the edge created or -1 of creation fails
   */
  int addEdge(int from, int to);

 public:  // * ----------- Searches -------- *
  /**
   * @return An iterable object that walks the nodes of the graph from the given
   *         starting node in DFS order
   */
  DFS<Derived> dfs(unsigned from = 0);

  BFS<Derived> bfs(unsigned from = 0);

 protected:  // * -------- Constructors -------- *
  /// @brief Create an empty graph
  MDGBase(){};

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

/* ============================ IMPLEMENTATIONS ============================ */
namespace mdg {
template <typename Derived>
inline Derived& MDGBase<Derived>::derived() {
  return *(static_cast<Derived*>(this));
}

template <typename Derived>
inline const Derived& MDGBase<Derived>::derived() const {
  return *(static_cast<Derived*>(this));
}

template <typename Derived>
inline typename MDGBase<Derived>::nodeop_type MDGBase<Derived>::node(
    int index) {
  return derived().node(index);
}

template <typename Derived>
inline const typename MDGBase<Derived>::nodeop_type MDGBase<Derived>::node(
    int index) const {
  return derived().node(index);
}

template <typename Derived>
inline typename MDGBase<Derived>::node_type& MDGBase<Derived>::nodeData(
    int index) {
  return derived().nodeData(index);
}

template <typename Derived>
inline const typename MDGBase<Derived>::node_type& MDGBase<Derived>::nodeData(
    int index) const {
  return derived().nodeData(index);
}

template <typename Derived>
inline typename MDGBase<Derived>::edgeop_type MDGBase<Derived>::edge(int from,
                                                                     int to) {
  return derived().edge(from, to);
}

template <typename Derived>
inline typename MDGBase<Derived>::edgeop_type MDGBase<Derived>::edge(
    int index) {
  return derived().edge(index);
}

template <typename Derived>
inline const typename MDGBase<Derived>::edgeop_type MDGBase<Derived>::edge(
    int index) const {
  return derived().edge(index);
}

template <typename Derived>
inline int MDGBase<Derived>::size() const {
  return derived().size();
}

template <typename Derived>
inline int MDGBase<Derived>::numNodes() const {
  return derived().numNodes();
}

template <typename Derived>
inline int MDGBase<Derived>::numEdges() const {
  return derived().numEdges();
}

template <typename Derived>
inline typename MDGBase<Derived>::nodeop_type MDGBase<Derived>::nullNode()
    const {
  return nodeop_type(*this, -1);
}

template <typename Derived>
inline typename MDGBase<Derived>::edgeop_type MDGBase<Derived>::nullEdge()
    const {
  return edgeop_type(*this, -1);
}

}  // namespace mdg

#endif  // MDG_MDGBASE_H