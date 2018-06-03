//
//  main.cpp
//  线性时间、最近点对
//
//  Created by 温和 on 2018/4/24.
//  Copyright © 2018年 温和. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

#define STANDARD 100
#define EARTH_RADIUS 6.371229 * 1e6
#define PI 3.1415926

typedef struct node {
  int ID;
  std::string name;
  double longitude;
  double latitude;
  double k_dist;
  bool operator<(const node &exp) const {
    if (this->longitude != exp.longitude) {
      return this->longitude < exp.longitude;
    } else {
      return this->latitude < exp.latitude;
    }
  }
} NODES;

double get_distance(struct pair p);

typedef struct pair {
  NODES a, b;
  double distance;
  bool operator<(const struct pair &exp) const {
    return get_distance(*this) < get_distance(exp);
  }
  void print() {
    std::cout << "最近点对为：" << a.ID << " 与 " << b.ID << std::endl
              << "最小距离为：" << distance << std::endl;
  }
} PAIR;

double rad(double d) { return d * PI / 180; }

double get_distance(NODES a, NODES b) {
  double radLat1 = rad(a.latitude);
  double radLat2 = rad(b.latitude);
  double m = radLat1 - radLat2;
  double n = rad(a.longitude) - rad(b.longitude);
  double s = 2 * asin(sqrt(pow(sin(m / 2), 2) +
                           cos(radLat1) * cos(radLat2) * pow(sin(n / 2), 2)));
  s = s * EARTH_RADIUS;
  return s;
}

double get_distance(PAIR p) { return get_distance(p.a, p.b); }

void read_data(std::vector<NODES> &data) {
  std::fstream file;
  file.open("/Users/wenhe/Desktop/data_nodes.txt");
  NODES new_node;
  if (file.is_open()) {
    file >> new_node.ID >> new_node.name >> new_node.longitude >>
        new_node.latitude >> new_node.k_dist;
    data.push_back(new_node);
    for (int i = 0; i < 2921 - 1; ++i) {
      file >> new_node.ID >> new_node.name >> new_node.longitude >>
          new_node.latitude >> new_node.k_dist;
      if (new_node.ID != (*(data.end() - 1)).ID)
        data.push_back(new_node);
    }
    file.close();
  }
}

void print_data(std::vector<NODES> data) {
  for (std::vector<NODES>::iterator iter = data.begin(); iter != data.end();
       ++iter) {
    std::cout << (*iter).ID << " " << (*iter).longitude << " "
              << (*iter).latitude << " " << (*iter).k_dist << std::endl;
  }
}

NODES copy_node(NODES old) {
  NODES new_node;
  new_node.ID = old.ID;
  new_node.name = old.name;
  new_node.longitude = old.longitude;
  new_node.latitude = old.latitude;
  new_node.k_dist = old.k_dist;
  return new_node;
}

void swap_node(NODES &a, NODES &b) {
  NODES temp = copy_node(a);
  a = copy_node(b);
  b = copy_node(temp);
}

int partition_by_dist(std::vector<NODES> &data, int left, int right) {
  int i = left, j = right + 1;
  NODES head = copy_node(data[left]);
  double x = head.k_dist;
  while (true) {
    while (data[++i].k_dist < x && i < right)
      ;
    while (data[--j].k_dist > x)
      ;
    if (i >= j)
      break;
    swap_node(data[i], data[j]);
  }
  data[left] = copy_node(data[j]);
  data[j] = copy_node(head);
  return j;
}

void quick_sort_by_dist(std::vector<NODES> &data, int left, int right) {
  if (left < right) {
    int mid = partition_by_dist(data, left, right);
    quick_sort_by_dist(data, left, mid - 1);
    quick_sort_by_dist(data, mid + 1, right);
  }
}

int partition_by_longitude(std::vector<NODES> &data, int left, int right) {
  int i = left, j = right + 1;
  NODES head = copy_node(data[left]);
  double x = head.longitude;
  while (true) {
    while (data[++i].longitude < x && i < right)
      ;
    while (data[--j].longitude > x)
      ;
    if (i >= j)
      break;
    swap_node(data[i], data[j]);
  }
  data[left] = copy_node(data[j]);
  data[j] = copy_node(head);
  return j;
}

void quick_sort_by_longitude(std::vector<NODES> &data, int left, int right) {
  if (left < right) {
    int mid = partition_by_longitude(data, left, right);
    quick_sort_by_longitude(data, left, mid - 1);
    quick_sort_by_longitude(data, mid + 1, right);
  }
}

int partition_by_latitude(std::vector<NODES> &data, int left, int right) {
  int i = left, j = right + 1;
  NODES head = copy_node(data[left]);
  double x = head.latitude;
  while (true) {
    while (data[++i].latitude < x && i < right)
      ;
    while (data[--j].latitude > x)
      ;
    if (i >= j)
      break;
    swap_node(data[i], data[j]);
  }
  data[left] = copy_node(data[j]);
  data[j] = copy_node(head);
  return j;
}

void quick_sort_by_latitude(std::vector<NODES> &data, int left, int right) {
  if (left < right) {
    int mid = partition_by_latitude(data, left, right);
    quick_sort_by_latitude(data, left, mid - 1);
    quick_sort_by_latitude(data, mid + 1, right);
  }
}

int select_partition(std::vector<NODES> &data, int left, int right,
                     double num) {
  int i = left, j = right + 1;
  int k;
  for (k = 0; data[k].k_dist != num; ++k)
    ;
  swap_node(data[k], data[left]);
  NODES head = copy_node(data[left]);
  double x = head.k_dist;
  while (true) {
    while (data[++i].k_dist < x && i < right)
      ;
    while (data[--j].k_dist > x)
      ;
    if (i >= j)
      break;
    swap_node(data[i], data[j]);
  }
  data[left] = copy_node(data[j]);
  data[j] = copy_node(head);
  return j;
}

/*double select(std::vector<NODES> &data,int left,int right,int k,NODES &out){
    if(right - left < STANDARD){
        quick_sort_by_dist(data,left,right);
        out = copy_node(data[left+k-1]);
        return data[left+k-1].k_dist;
    }
    for(int i = 0;i <= (right - left - STANDARD + 1)/STANDARD;++i){
        int s = left + STANDARD * i, t = s + STANDARD - 1;
        quick_sort_by_dist(data, s+STANDARD/2+1, t);
        swap_node(data[left+i], data[s+STANDARD/2]);
    }
    double x = select(data, left, left + (right - left - STANDARD + 1)/STANDARD,
(right - left + STANDARD + 1)/(STANDARD * 2),out); int i =
select_partition(data, left, right,x); int j = i - left + 1; if(k<=j) return
select(data, left, i, k,out); else return select(data, i+1, right, k-j,out);
}
*/
int select(std::vector<NODES> &data, int left, int right, int k, NODES &out) {
  if (right - left < STANDARD) {
    quick_sort_by_dist(data, left, right);
    out = copy_node(data[left + k - 1]);
    return 1;
  }
  for (int i = 0; i <= (right - left - STANDARD + 1) / STANDARD; ++i) {
    int s = left + STANDARD * i, t = s + STANDARD - 1;
    quick_sort_by_dist(data, s + STANDARD / 2 + 1, t);
    swap_node(data[left + i], data[s + STANDARD / 2]);
  }
  select(data, left, left + (right - left - STANDARD + 1) / STANDARD,
         (right - left + STANDARD + 1) / (STANDARD * 2), out);
  double x = out.k_dist;
  int i = select_partition(data, left, right, x);
  int j = i - left + 1;
  if (k <= j) {
    return select(data, left, i, k, out) + 1;
  }
  return select(data, i + 1, right, k - j, out) + 1;
}

PAIR set_pair(NODES m, NODES n) {
  PAIR new_pair;
  new_pair.a = m;
  new_pair.b = n;
  new_pair.distance = get_distance(m, n);
  return new_pair;
}

bool is_in_block(NODES a, NODES b, double dist) {
  NODES temp = copy_node(b);
  temp.longitude = a.longitude;
  if (get_distance(temp, a) <= dist)
    return true;
  else
    return false;
}

std::vector<PAIR> close_pairs(std::vector<NODES> &data, int l, int r) {
  if (r - l <= 2) {
    auto end = data.begin() + r + 1;
    std::vector<PAIR> result;
    for (auto i = data.begin() + l; i != end; ++i) {
      for (auto j = i + 1; j != end; ++j) {
        PAIR temp;
        temp.a = *i;
        temp.b = *j;
        temp.distance = get_distance(temp.a, temp.b);
        result.push_back(temp);
        return result;
      }
    }
  }
  int m = (l + r) / 2;
  auto result_l = close_pairs(data, l, m);
  auto result_r = close_pairs(data, m + 1, r);
  for (auto i : result_r) {
    result_l.push_back(i);
  }
  std::sort(result_l.begin(), result_l.end());
  auto best = result_l[0];
  int left = m, right = m;
  while (left > l && is_in_block(data[left], data[m], best.distance)) {
    --left;
  }
  while (right < r && is_in_block(data[right], data[m], best.distance)) {
    ++right;
  }
  auto end = data.begin() + right + 1;
  for (auto i = data.begin() + left; i != end; ++i) {
    for (auto j = i + 1; j != end; ++j) {
      PAIR temp;
      temp.a = *i;
      temp.b = *j;
      result_l.push_back(temp);
    }
  }
  std::sort(result_l.begin(), result_l.end());
  auto result = {result_l[0], result_l[1]};
  return result;
}

int main() {
  std::vector<NODES> data;
  NODES final_node;
  read_data(data);
  auto result = close_pairs(data, 0, data.size() - 1);
  result[0].print();
  result[1].print();
  /*int k[] = {1,5,50,1030};
  for(int i = 0;i<=3;++i){
      int recursive_time = select(data, 0, data.size()-1, k[i], final_node);
      std::cout<<"第 "<<k[i]<<" 个基站为："<<final_node.ID<<"
  递归层数："<<recursive_time<<std::endl;
  }*/
}
