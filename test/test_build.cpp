#include "src/forward_declarations.h"
#include "src/util/graphtraits.h"
#include "src/util/nodeoptraits.h"
#include "src/mdgbase.h"
#include "src/operations/nodeopbase.h"
#include "src/operations/undirectednodeop.h"
#include "src/operations/directednodeop.h"

#include <iostream>
#include <typeinfo>

using namespace mdg;

class MyGraphType;

namespace mdg {
namespace internal {
template <>
struct traits<MyGraphType> {
  typedef int node_t;
  typedef DirectedNodeOp<MyGraphType> nodeop_t;
  typedef NodeSetOp<MyGraphType> nodeset_t;
  typedef int edge_t;
  typedef EdgeOp<MyGraphType> edgeop_t;
  typedef EdgeSetOp<MyGraphType> edgeset_t;

  static constexpr bool isMDGBaseDerived = false;
  static constexpr bool isDirectedBaseDerived = false;
  static constexpr bool isUndirectedBaseDerived = false;
};
}  // namespace internal
}  // namespace mdg

class MyGraphType : public MDGBase<MyGraphType> {
 public:
  typedef MDGBase<MyGraphType> Base;
  using Base::edge_type;
  using Base::edgeop_type;
  using Base::edgeset_type;
  using Base::node_type;
  using Base::nodeop_type;
  using Base::nodeset_type;

  using Base::derived;
};

int main() {
  DirectedNodeOp<MyGraphType> a(MyGraphType());

  std::cout << typeid(typename MyGraphType::nodeop_type).name() << "\n";

  return 0;
}