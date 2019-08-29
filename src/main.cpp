#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

void _countingSort(const std::vector<int32_t>& in, std::vector<int32_t>& out, int32_t k) {
  out.resize(in.size());
  std::vector<int32_t> count(k + 1, 0);

  for (int32_t i = 0; i < in.size(); ++i) count[in[i]] += 1;

  for (int32_t i = 1; i <= k; ++i) count[i] = count[i] + count[i - 1];

  for (int32_t i = in.size(); i >= 1; --i) {
    out[count[in[i - 1]] - 1] = in[i - 1];
    count[in[i - 1]] = count[in[i - 1]] - 1;
  }
}

void countingSort(std::vector<int32_t>& v) {
  int32_t min = *std::min_element(v.begin(), v.end());
  bool neg = min < 0;

  if (neg)
    for (auto& i : v) i -= min;

  std::vector<int32_t> out(v.size());
  _countingSort(v, out, *std::max_element(v.begin(), v.end()));
  v = out;

  if (neg)
    for (auto& i : v) i += min;
}

#define RADIX_DIGIT(n, exp) (((n)/(exp))%10)

void _countingSortRadix(const std::vector<int32_t>& in, std::vector<int32_t>& out, int exp) {
  out.resize(in.size());
  constexpr int32_t k = 9;
  std::vector<int32_t> count(k + 1, 0);

  for (int32_t i = 0; i < in.size(); ++i) count[RADIX_DIGIT(in[i], exp)] += 1;

  for (int32_t i = 1; i <= k; ++i) count[i] = count[i] + count[i - 1];

  for (int32_t i = in.size(); i >= 1; --i) {
    int32_t a = RADIX_DIGIT(in[i - 1], exp);

    out[count[a] - 1] = in[i -1];
    --count[a];
  }
}

void _radixSort(const std::vector<int32_t>& in, std::vector<int32_t>& out, int32_t max) {
  std::vector<int32_t> v = in;

  for (int32_t exp = 1; max/exp > 0; exp *= 10) {
    _countingSortRadix(v, out, exp);
    v = out;
  }
}

void radixSort(std::vector<int32_t>& v) {
  int32_t min = *std::min_element(v.begin(), v.end());
  bool neg = min < 0;

  if (neg)
    for (auto& i : v) i -= min;

  std::vector<int32_t> out(v.size());
  int32_t max = *std::max_element(v.begin(), v.end());

  _radixSort(v, out, max);

  v = out;

  if (neg)
    for (auto& i : v) i += min;
}

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cout << "usage: bin/sort <option> <test_file_path>\n";
    std::cout << "\t options: c (counting sort), r (radix sort)\n";
    std::exit(EXIT_SUCCESS);
  }

  std::string file_path(argv[2]);
  std::ifstream fs(file_path, std::ios::binary);

  if (!fs.is_open()) {
    std::cout << "ERROR: Failed to open file: " + file_path << std::endl;
    std::exit(EXIT_FAILURE);
  }

  int32_t num = 0;
  fs >> num;

  std::vector<int32_t> in(num, 0);
  for (auto& i : in) fs >> i;
  fs.close();

  char select = argv[1][0];
  if (select == 'c') {
    countingSort(in);
  } else if (select == 'r') {
    radixSort(in);
  } else {
    std::cout << "\"" << select << "\" - is not a valid option\n";
    std::exit(EXIT_FAILURE);
  }


  std::ofstream ofs("output.txt", std::ios::binary);
  for (auto& i : in) ofs << (int32_t)i << "\n";

  ofs.close();

  std::exit(EXIT_SUCCESS);
}
