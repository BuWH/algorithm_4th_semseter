#include <iostream>
#include <algorithm>
#include <fstream>
#include <random>
#include <chrono>
#include <vector>
using namespace std;

int DD(vector<int>sequence,int n){
    int count = 0;
    for(int i = 0;i <= n-2;++i){
        for(int j = i+1;j<= n-1;++j){
            if(sequence[j] <sequence[i])
                ++count;
        }
    }
    return count;
}

void create_sequence(int n,int N,int M){
    fstream file;
    file.open("/Users/wenhe/desktop/data_nums.txt",ios::trunc | ios::out);
    vector<int> nums;
    
    for(int i = 0;i <= N-1;++i){
        nums.push_back(i+1);
    }
    for(int j = 0;j <= M-1;++j){
        srand(unsigned(time(0)));
        random_shuffle(nums.begin(), nums.end());
        cout<<DD(nums,n)<<endl;
        file<<DD(nums,n)<<endl;
        cout<<DD(nums,n)/n<<endl;
        file<<DD(nums,n)/n<<endl;
        for(int i = 0;i <= n-1;++i){
            file<<nums[i]<<" ";
        }
        file<<endl;
    }
}
