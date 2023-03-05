#include "src/forward_declarations.h"
#include "src/util/graphtraits.h"
#include "src/util/nodeoptraits.h"
#include "src/mdgbase.h"
#include "src/directedbase.h"
#include "src/operations/nodeopbase.h"
#include "src/operations/undirectednodeop.h"
#include "src/operations/directednodeop.h"

#include <iostream>
#include <string>
#include <typeinfo>

using namespace mdg;

class MyGraphType;

namespace mdg {
namespace internal {
template <>
struct traits<MyGraphType> : public traits<DirectedBase<MyGraphType>> {
  typedef std::string node_t;
  typedef UndirectedNodeOp<MyGraphType> nodeop_t;
  typedef int edge_t;
  typedef EdgeOp<MyGraphType> edgeop_t;
};
}  // namespace internal
}  // namespace mdg

class MyGraphType : public DirectedBase<MyGraphType> {
 public:
  typedef MDGBase<MyGraphType> Base;
  using Base::edge_type;
  using Base::edgeop_type;
  using Base::edgeset_type;
  using Base::node_type;
  using Base::nodeop_type;
  using Base::nodeset_type;

  using Base::derived;

  MyGraphType() : MDGBase() {}
};

int main() {
  MyGraphType a;
  // std::string data = a.nodeData(5);

  std::cout << internal::traits<MyGraphType>::isDirected << "\n";

  return 0;
}