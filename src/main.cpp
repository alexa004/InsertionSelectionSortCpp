#include <iostream>
#include <vector>

void _countingSort(const std::vector<uint32_t>& in, std::vector<uint32_t>& out,
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

void countingSort(std::vector<uint32_t>& v) {
  std::vector<uint32_t> out(v.size());
  _countingSort(v, out, 9);
  v = out;
}

int main() {
  std::vector<uint32_t> v = {2, 9, 7, 6, 3, 7, 8, 6, 0, 1, 1};

  countingSort(v);

  for (auto& i : v) std::cout << i;
    std::cout << "\n";

  std::exit(EXIT_SUCCESS);
}
