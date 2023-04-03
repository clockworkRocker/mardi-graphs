#ifndef MDG_ADJACENCYSTORAGE_H
#define MDG_ADJACENCYSTORAGE_H

namespace mdg {
namespace internal {
template <>
class AdjacencyStorage<DenseMatrix> {};
}  // namespace internal
}  // namespace mdg

#endif  // MDG_ADJACENCYSTORAGE_H