#include "sort.h"

void selectionSort(std::vector<int64_t>& v) {
  for (uint32_t i = 0; i < v.size() - 1; ++i) {
    uint32_t min_id = i;

    for (uint32_t j = min_id + 1; j < v.size(); ++j)
      if (v[min_id] > v[j]) min_id = j;

    if (min_id != i) std::swap(v[min_id], v[i]);
  }
}

void insertionSort(std::vector<int64_t>& v) {
  for (uint32_t i = 1; i < v.size(); ++i) {
    uint32_t j = i;

    while (j && v[j - 1] > v[j]) {
      std::swap(v[j], v[j - 1]);
      --j;
    }
  }
}