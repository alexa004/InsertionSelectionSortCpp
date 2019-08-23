#include <iostream>
#include <vector>

void countingSort(const std::vector<uint32_t>& in, std::vector<uint32_t>& out,
                  uint32_t k) {
  out.resize(in.size());
  std::vector<uint32_t> count(k + 1, 0);

  for (uint32_t i = 0; i < in.size(); ++i) count[in[i]] += 1;

  for (uint32_t i = 1; i <= k; ++i) count[i] = count[i] + count[i - 1];

  for (uint32_t i = in.size(); i >= 1; --i) {
    out[count[in[i - 1]] - 1] = in[i - 1];
    count[in[i - 1]] = count[in[i - 1]] - 1;
  }
}

int main() {
  std::vector<uint32_t> in = {2, 5, 3, 0, 2, 3, 0, 3};
  std::vector<uint32_t> out;

  countingSort(in, out, 5);

  for (auto& i : out) std::cout << i;
    std::cout << "\n";

  std::exit(EXIT_SUCCESS);
}
