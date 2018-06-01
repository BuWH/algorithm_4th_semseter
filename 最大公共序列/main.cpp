#include <iostream>
#include <string>
#include <vector>
#include <fstream>

void read_data(std::vector<char> &A,std::vector<char> &B,std::vector<char> &C,std::vector<char> &D){
    std::fstream data;
    std::string temp;
    data.open("/Users/wenhe/Documents/我的坚果云/课件/大二下课件/算法设计与分析/上机作业-第3章-2018/附件1.最长公共子序列输入文件2017-4-26.txt",std::ios::in);
    data.seekg(std::ios::beg);
    data>>temp;data>>temp;A.assign(temp.begin(), temp.end());
    data>>temp;data>>temp;B.assign(temp.begin(), temp.end());
    data>>temp;data>>temp;C.assign(temp.begin(), temp.end());
    data>>temp;data>>temp;D.assign(temp.begin(), temp.end());
    data.close();
}

void print_data(std::vector<char> Chars){
    for(auto i:Chars){
        std::cout<<i;
    }
    std::cout<<std::endl;
    return;
}

int main(){
    std::vector<char> A,B,C,D;
    read_data(A, B, C, D);
    print_data(A);
    print_data(B);
}