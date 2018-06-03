#include <iostream>
#include <fstream>
#include <vector>

void read_data(std::vector<int> &data){
    std::fstream file;
    int temp;
    file.open("/Users/wenhe/Documents/我的坚果云/课件/大二下课件/算法设计与分析/上机作业-第3章-2018/附件2.最大子段和输入数据2017-序列1.txt",std::ios::in);
    while(!file.eof()){
        file>>temp;
        data.push_back(temp);
    }
}

void get_sum(std::vector<int> data){
    int start = 0,end = 0;
    int sum = 0,sum_before = 0;
    for(int i = 0;i<data.size();++i){
        if(sum_before > 0){
            sum_before += data[i];
        }else{
            sum_before = data[i];
            start = i;
            end = i;
        }
        if(sum_before > sum){
            sum = sum_before;
            end = i;
        }
    }
    std::cout<<"start: "<<start<<" end: "<<end<<" sum:"<<sum<<std::endl;
}

int main()
{
    std::vector<int> data;
    read_data(data);
    get_sum(data);
    return 0;
}