#ifndef MDG_NODESETOP_H
#define MDG_NODESETOP_H
namespace mdg {
template <typename GraphType>
class NodeSetIterator : public internal::traits<GraphType>::nodeop_t {
 public:
};

template <typename GraphType>
class NodeSetOp {
 public:  // * Types
  typedef typename NodeSetIterator<GraphType> iterator;
  typedef internal::traits<GraphType>::nodeop_t nodeop;

 public:  // * Iterators because those are sexy!
  iterator begin();
  iterator end();

 public:  // * Access methods
  nodeop operator[](int index);

 private:
  std::vector<unsigned> indices;
};
}  // namespace mdg
#endif  // MDG_NODESETOP_H