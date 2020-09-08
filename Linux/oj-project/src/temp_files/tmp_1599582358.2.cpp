#include<iostream>
#include<string>
#include<vector>

class Solution{
public:
    bool isPalindrome(int x){
         return true;
    }
};

//tail.cpp不给用户看的，最终编译的时候
//会把用户提交的代码和tail.cpp合并成一个文件再进行编译
void Test1(){
    Solution s;
    bool ret = s.isPalindrome(121);
    if(ret){
        std::cout<<"Test1 OK"<<std::endl;
    }
    else{
        std::cout<<"Test1 failed"<<std::endl;
    }
}

void Test2(){
    Solution s;
    bool ret = s.isPalindrome(-121);
    if(!ret){
        std::cout<<"Test2 OK"<<std::endl;
    }
    else{
        std::cout<<"Test2 failed"<<std::endl;
    }
}

int main(){
    Test1();
    Test2();
    return 0;
}
