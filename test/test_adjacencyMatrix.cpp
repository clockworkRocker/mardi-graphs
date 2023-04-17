#include <MardiGraphs/Core>
#include <iostream>
#include <iomanip>

using namespace mdg::internal;

int main() {
  enum { InitSize = 6, ExpandedSize = 5 };

  AdjacencyStorage<mdg::ObjectDigraph<int, int, mdg::DenseMatrix>,
                   mdg::DenseMatrix>
      storag(InitSize);
  storag.connect(0, 1, 0);
  storag.connect(0, 2, 0);
  storag.connect(1, 0, 0);
  storag.connect(1, 2, 0);
  storag.connect(2, 0, 0);
  storag.connect(2, 1, 0);

  std::cout << "Printing initial storage:\n";
  for (int i = 0; i < InitSize; ++i) {
    for (int j = 0; j < InitSize; ++j)
      std::cout << ' ' << std::setw(3) << storag(i, j);
    std::cout << '\n';
  }

  storag.expand(ExpandedSize);

  AdjacencyStorage<mdg::ObjectDigraph<int, int, mdg::DenseMatrix>,
                   mdg::DenseMatrix>
      storag2 = storag;

  std::cout << "Printing expanded storage:\n";
  for (int i = 0; i < ExpandedSize; ++i) {
    for (int j = 0; j < ExpandedSize; ++j)
      std::cout << ' ' << std::setw(3) << storag2(i, j);
    std::cout << '\n';
  }

  return 0;
}