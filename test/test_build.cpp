#include "src/forward_declarations.h"
#include "src/util/graphtraits.h"
#include "src/util/nodeoptraits.h"
#include "src/graphbase.h"
#include "src/operations/nodeopbase.h"
#include "src/operations/undirectednodeop.h"

using namespace mdg;

class MyGraphType;

namespace mdg {
namespace internal {
template <>
struct traits<MyGraphType> {
  typedef int node_t;
  typedef int edge_t;
};
}  // namespace internal
}  // namespace mdg

class MyGraphType : public MDGBase<MyGraphType> {};

int main() {
  UndirectedNodeOp<MyGraphType> a(MyGraphType());
  return 0;
}