#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#define PI 3.14159265
#define R (6.371229*1e6)

struct node {
    double longitude;
    double latitude;
    double dist;
    int num;
};

void read_data(std::vector<struct node> &data, const std::string &filename) {
    std::fstream f;
    f.open("/Users/wenhe/Documents/我的坚果云/课件/大二下课件/算法设计与分析/上机作业-第3章-2018/" + filename, std::ios::in);
    while (!f.eof()) {
        struct node temp;
        f >> temp.longitude >> temp.latitude >> temp.num;
        //std::cout<<"No: "<<temp.num<<" l: "<<temp.longitude<<" a: "<<temp.latitude<<std::endl;
        data.push_back(temp);
    }
    f.close();
}

double get_rad(double d) {
    return (d * PI / 180);
}

double get_dist(const struct node &d1, const struct node &d2) {
    double lat1 = d1.latitude;
    double lat2 = d2.latitude;
    double lon1 = d1.longitude;
    double lon2 = d2.longitude;
    double rad_lat_1 = get_rad(lat1);
    double rad_lat_2 = get_rad(lat2);
    double a = rad_lat_1 - rad_lat_2;
    double b = get_rad(lon1) - get_rad(lon2);
    double dist = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(rad_lat_1) * cos(rad_lat_2) * pow(sin(b / 2), 2)));
    dist = dist * R;
    return dist;
}

double get_c(const struct node &a, const struct node &b, const struct node &c) {
    return get_dist(a, b) + get_dist(b, c) + get_dist(a, c);
}

void print_graph(std::vector<std::vector<int>> &partner, int i, int j) {
    if (j - i >= 1) {
        std::cout << i - 1 << " " << partner[i][j] << " " << j << std::endl;
        print_graph(partner, i, partner[i][j]);
        print_graph(partner, partner[i][j] + 1, j);
    }
}

void triangulate(const std::vector<struct node> data) {
    std::vector<std::vector<double>> t(data.size(), std::vector<double>(data.size(), 0));
    std::vector<std::vector<int>> partner(data.size(), std::vector<int>(data.size(), 0));
    double current;
    for (int i = 1; i < data.size(); ++i) {
        t[i][i] = 0;
    }
    for (int r = 2; r < data.size(); ++r) {
        for (int i = 1; i < data.size() - r + 1; ++i) {
            int j = i + r - 1;
            t[i][j] = t[i + 1][j] + get_c(data[i - 1], data[i], data[j]);
            partner[i][j] = i;
            for (int k = i + 1; k < j; ++k) {
                current = t[i][k] + t[k + 1][j] + get_c(data[i - 1], data[k], data[j]);
                if (current < t[i][j]) {
                    t[i][j] = current;
                    partner[i][j] = k;
                }
            }
        }
    }
    std::cout << "min weight: " << t[1][data.size() - 1] << std::endl;
    print_graph(partner, 1, data.size() - 1);
}

int main() {
    std::vector<struct node> data1, data2;
    read_data(data1, "tri1.txt");
    read_data(data2, "tri2.txt");
    triangulate(data1);
    triangulate(data2);
    return 0;
}