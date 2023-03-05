namespace mdg {

enum StorageType {
  NoDirectStorage = -1,
  None,
  DenseMatrix,
  SparseMatrix,
  List
};
namespace internal {
template <typename GraphType>
struct baseTraits {
  typedef int node_t;
  typedef int edge_t;
  typedef NodeSetOp<GraphType> nodeset_t;
  typedef EdgeSetOp<GraphType> edgeset_t;

  enum {
    isMardiGraph = false,
    isDirected = false,
    hasDirectAccess = false,
    storageType = None
  };
};
}  // namespace internal
}  // namespace mdg