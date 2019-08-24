#include <iostream>
#include <vector>
#include <algorithm>

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
  _countingSort(v, out, *std::max_element(v.begin(), v.end()));
  v = out;
}


#define RADIX_DIGIT(n, exp) (((n)/(exp))%10)

void _countingSortRadix(const std::vector<uint32_t>& in, std::vector<uint32_t>& out,
                  uint32_t k, int exp) {
  out.resize(in.size());
  std::vector<uint32_t> count(k + 1, 0);

  for (uint32_t i = 0; i < in.size(); ++i) count[RADIX_DIGIT(in[i], exp)] += 1;

  for (uint32_t i = 1; i <= k; ++i) count[i] = count[i] + count[i - 1];

  for (uint32_t i = in.size(); i >= 1; --i) {
    uint32_t a = RADIX_DIGIT(in[i - 1], exp);

    out[count[a] - 1] = in[i -1];
    --count[a];
  }
}

void _radixSort(const std::vector<uint32_t>& in, std::vector<uint32_t>& out, uint32_t max) {
  std::vector<uint32_t> v = in;

  for (uint32_t exp = 1; 1000/exp > 0; exp *= 10) {
    _countingSortRadix(v, out, 9, exp);
    v = out;
  }
}

void radixSort(std::vector<uint32_t>& v) {
  std::vector<uint32_t> out(v.size());
  uint32_t max = *std::max_element(v.begin(), v.end());

  _radixSort(v, out, max);

  v = out;
}

int main() {
  std::vector<uint32_t> v = {231, 9, 703, 611, 343, 772, 895, 666, 100, 187, 121};
  std::vector<uint32_t> out(v.size());

  out = v;

  radixSort(out);

  for (auto& i : out) std::cout << i << "\n";

  std::exit(EXIT_SUCCESS);
}
