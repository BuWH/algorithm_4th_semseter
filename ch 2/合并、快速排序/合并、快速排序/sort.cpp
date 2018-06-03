#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <time.h>
#include <vector>

typedef struct data {
  std::vector<int> DD;
  std::vector<int> ADD;
  std::vector<int> nums;
  int n;
} DATA;

int get_DD(std::vector<int> sequence, int n) {
  int count = 0;
  for (int i = 0; i <= n - 2; ++i) {
    for (int j = i + 1; j <= n - 1; ++j) {
      if (sequence[j] < sequence[i])
        ++count;
    }
  }
  return count;
}

std::vector<int> create_sequence(int n, int N) {
  std::vector<int> nums;
  for (int i = 0; i <= N - 1; ++i) {
    nums.push_back(i + 1);
  }
  srand(unsigned(time(0)));
  random_shuffle(nums.begin(), nums.end());
  return nums;
}

int recursive_times = 0;

void merge(std::vector<int> &data, int left, int mid, int right) {
  std::vector<int> temp;
  auto i_end = data.begin() + mid + 1;
  auto j_end = data.begin() + right + 1;
  auto i = data.begin() + left;
  auto j = data.begin() + mid + 1;
  while (i != i_end && j != j_end) {
    if (*i < *j) {
      temp.push_back(*i);
      ++i;
    } else {
      temp.push_back(*j);
      ++j;
    }
  }
  for (; i != i_end; ++i, temp.push_back(*i));
  for (; j != j_end; ++j, temp.push_back(*j));
  for (auto buff : temp) {
    data[left] = buff;
    ++left;
  }
  return;
}

int recursive_merge_sort(std::vector<int> &data, int left, int right) {
  if (left == right)
    return 1;
  else {
    int mid = (left + right) / 2;
    int depth_l = recursive_merge_sort(data, left, mid);
    int depth_r = recursive_merge_sort(data, mid + 1, right);
    merge(data, left, mid, right);
    return depth_l > depth_r ? depth_l + 1 : depth_r + 1;
  }
}

void not_recursive_merge_sort(std::vector<int> &data) {
  int s = 1;
  while (s < data.size()) {
      for(int i = 0;i<data.size()-s;i+= 2*s){
          if(data.size()<i+2*s){
              merge(data,i,i+s-1,data.size()-1);
          }
          else
              merge(data,i,i+s-1,i+2*s-1);
      }
      s *= 2;
  }
}

int partition(std::vector<int> &data, int left, int right) {
  int i = left, j = right + 1;
  int x = data[i];
  while (true) {
    while (data[++i] < x && i < right)
      ;
    while (data[--j] > x)
      ;
    if (i >= j)
      break;
    int temp = data[i];
    data[i] = data[j];
    data[j] = temp;
  }
  data[left] = data[j];
  data[j] = x;
  return j;
}

int quick_sort(std::vector<int> &data, int left, int right) {
  if (left >= right)
    return 1;
  else {
    int mid = partition(data, left, right);
    int depth_l = quick_sort(data, left, mid - 1);
    int depth_r = quick_sort(data, mid + 1, right);
    return depth_l > depth_r ? depth_l + 1 : depth_r + 1;
  }
}

int random_partition(std::vector<int> &data, int left, int right) {
  srand(unsigned(time(0)));
  int i = rand() % (right - left);
  int temp = data[left];
  data[left] = data[i];
  data[i] = temp;
  return partition(data, left, right);
}

int random_quick_sort(std::vector<int> &data, int left, int right) {
  if (left >= right)
    return 1;
  else {
    int mid = random_partition(data, left, right);
    int depth_l = quick_sort(data, left, mid - 1);
    int depth_r = quick_sort(data, mid + 1, right);
    return depth_l > depth_r ? depth_l + 1 : depth_r + 1;
  }
}

int main() {
  int seq_num = 1, group_num = 6;
  int n[] = {2000, 5000, 10000, 15000, 20000, 30000}, N = 30000, M = 5;
  clock_t start, end;
  for (int i = 1; i <= group_num; i++) {
    DATA sort_data;
    std::vector<unsigned long> recursive_merge_time;
    std::vector<unsigned long> not_recursive_merge_time;
    std::vector<unsigned long> quick_sort_time;
    std::vector<unsigned long> random_quick_sort_time;
    sort_data.n = n[i - 1];
    for (int j = 1; j <= M; ++j) {
      std::vector<int> unsorted_nums = create_sequence(n[i - 1], N);
      sort_data.nums.clear();
      for (auto t : unsorted_nums) {
        sort_data.nums.push_back(t);
      }
      sort_data.DD.push_back(get_DD(sort_data.nums, n[i - 1]));
      sort_data.ADD.push_back(sort_data.DD.back() / sort_data.n);
      std::cout << seq_num++ << "|" << sort_data.n << "|" << i << "|"
                << sort_data.DD.back() << "|" << sort_data.ADD.back() << "|";
      start = clock();
      int recursive_time =
          recursive_merge_sort(sort_data.nums, 0, sort_data.n - 1);
      end = clock();
      recursive_merge_time.push_back(end - start);
      std::cout << (end - start) << "/" << recursive_time << "|";
      sort_data.nums.clear();
      for (auto t : unsorted_nums) {
        sort_data.nums.push_back(t);
      }
      start = clock();
      not_recursive_merge_sort(sort_data.nums);
      end = clock();
      not_recursive_merge_time.push_back(end - start);
      std::cout << (end - start) << "|";
      sort_data.nums.clear();
      for (auto t : unsorted_nums) {
        sort_data.nums.push_back(t);
      }
      start = clock();
      recursive_time = quick_sort(sort_data.nums, 0, sort_data.n - 1);
      end = clock();
      quick_sort_time.push_back(end - start);
      std::cout << (end - start) << "/" << recursive_time << "|";
      sort_data.nums.clear();
      for (auto t : unsorted_nums) {
        sort_data.nums.push_back(t);
      }
      start = clock();
      recursive_time = random_quick_sort(sort_data.nums, 0, sort_data.n - 1);
      end = clock();
      random_quick_sort_time.push_back(end - start);
      std::cout << (end - start) << "/" << recursive_time << "|" << std::endl;
    }
    int DD_sum = 0, ADD_sum = 0, rmt = 0, nrmt = 0, qs1 = 0, qs2 = 0;
    for (auto g : sort_data.DD) {
      DD_sum += g;
    }
    for (auto g : sort_data.ADD) {
      ADD_sum += g;
    }
    for (auto g : recursive_merge_time) {
      rmt += g;
    }
    for (auto g : not_recursive_merge_time) {
      nrmt += g;
    }
    for (auto g : quick_sort_time) {
      qs1 += g;
    }
    for (auto g : random_quick_sort_time) {
      qs2 += g;
    }
    std::cout << std::endl
              << "ave|" << sort_data.n << "|" << i << "|" << DD_sum / M << "|"
              << ADD_sum / M << "|" << rmt / M << "|" << nrmt / M << "|"
              << qs1 / M << "|" << qs2 / M << "|" << std::endl
              << std::endl;
  }
}
