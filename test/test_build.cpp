
#include <iostream>
#include <string>
#include <MardiGraphs/Core>

using namespace mdg;

class MyGraphType;

namespace mdg {
namespace internal {
template <>
struct traits<MyGraphType> : public traits<DirectedBase<MyGraphType>> {
  typedef std::string node_t;
  typedef DirectedNodeOp<MyGraphType> nodeop_t;
  typedef int edge_t;
  typedef EdgeOp<MyGraphType> edgeop_t;
};
}  // namespace internal
}  // namespace mdg

class MyGraphType : public DirectedBase<MyGraphType> {
 public:
  typedef DirectedBase<MyGraphType> Base;
  MDG_COMMON_TYPEDEFS(MyGraphType)

  using Base::derived;

  MyGraphType() : Base() {}

  nodeop_type node(int index) {
    return {*this, index > 0 && index < m_nodes.size() ? index : -1};
  }
  node_type& nodeData(int index) { return m_nodes[index]; }

 protected:
  std::vector<node_type> m_nodes = {"a", "b", "c"};
  std::vector<edge_type> m_edges;
};

int main() {
  ObjectDigraph<std::string, std::string> a(6);
  std::vector<int> indices(3);

  indices[0] = a.addEdge(0, 1, "hallo");
  indices[1] = a.addEdge(0, 2, "hallo");
  indices[2] = a.addEdge(0, 3, "hallo again");

  for (auto& i : indices)
    std::cout << ' ' << i;

  std::cout << std::endl;

  return 0;
}