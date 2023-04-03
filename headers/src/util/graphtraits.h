#ifndef MDG_COMMON_TYPEDEFS
#define MDG_COMMON_TYPEDEFS(GraphName)                                  \
  typedef typename internal::traits<GraphName>::node_t node_type;       \
  typedef typename internal::traits<GraphName>::edge_t edge_type;       \
  typedef typename internal::traits<GraphName>::nodeop_t nodeop_type;   \
  typedef typename internal::traits<GraphName>::edgeop_t edgeop_type;   \
  typedef typename internal::traits<GraphName>::nodeset_t nodeset_type; \
  typedef typename internal::traits<GraphName>::edgeset_t edgeset_type;
#endif

#ifndef MDG_COMMON_FRIENDS
#define MDG_COMMON_FRIENDS(GraphName) \
  friend nodeop_type;                 \
  friend edgeop_type;                 \
  friend nodeset_type;                \
  friend edgeset_type;
#endif
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