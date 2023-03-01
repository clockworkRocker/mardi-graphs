namespace mdg {
namespace internal {
template <typename GraphType>
struct traits {
  typedef int node_t;
  typedef int edge_t;
  typedef NodeSetOp<GraphType> nodeset_t;
  typedef EdgeSetOp<GraphType> edgeset_t;

  static constexpr bool isMDGBaseDerived = false;
  static constexpr bool isDirectedBaseDerived = false;
  static constexpr bool isUndirectedBaseDerived = false;
};
}  // namespace internal
}  // namespace mdg