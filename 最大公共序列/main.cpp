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
    for(int i = Chars.size()-1;i >= 0;--i){
        std::cout << Chars[i];
    }
    std::cout<<std::endl;
}

std::vector<char> result(std::vector<char> &a,std::vector<char> &b){
    int length[a.size()][b.size()];
    int from[a.size()][b.size()];
    std::vector<char> answer;
    for(int i = 1;i < a.size();++i)
        length[i][0] = 0;
    for(int i = 1;i < b.size();++i)
        length[0][i] = 0;
    for(int i = 1;i < a.size();++i){
        for(int j = 1;j<b.size();++j){
            if(a[i] == b[j]){
                length[i][j] = length[i-1][j-1] + 1;
                from[i][j] = 1;
            }else if(length[i-1][j] >= length[i][j-1] ){
                length[i][j] = length[i-1][j];
                from[i][j] = 2;
            }else{
                length[i][j] = length[i][j-1];
                from[i][j] = 3;
            }
        }
    }
    int j = b.size() - 1;
    int i = a.size() - 1 ;
    while(i!=0 && j!=0){
        if(from[i][j] == 1){
            answer.push_back(a[i]);
            i--,j--;
        }else if(from[i][j] == 2){
            i--;
        }else{
            j--;
        }
    }
    return answer;
}

int main(){
    std::vector<std::vector<char>> data;
    std::vector<char> temp;
    data.assign(4,temp);
    read_data(data[0], data[1], data[2], data[3]);
    temp = result(data[0],data[1]);
    print_data(temp);
}