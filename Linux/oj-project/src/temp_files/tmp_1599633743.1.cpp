#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Solution{
public:
    bool isPalindrome(int x){
         return true;
    }
};
void Test1(const Solution& s){
    bool ret = s.isPalindrome(121);
    if(ret){
        std::cout<<"Test1 OK"<<std::endl;
    }
    else{
        std::cout<<"Test1 failed"<<std::endl;
    }
}

void Test2(const Solution& s){
    bool ret = s.isPalindrome(-121);
    if(!ret){
        std::cout<<"Test2 OK"<<std::endl;
    }
    else{
        std::cout<<"Test2 failed"<<std::endl;
    }
}

void Test3(const Solution& s){
    bool ret = s.isPalindrome(10);
    if(!ret){
        std::cout<<"Test3 OK"<<std::endl;
    }
    else{
        std::cout<<"Test3 failed"<<std::endl;
    }
}

int main(){
    Solution s;
    Test1(s);
    Test2(s);
    Test3(s);
    return 0;
}
