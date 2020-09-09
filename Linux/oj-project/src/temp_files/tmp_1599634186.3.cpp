#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Solution{
public:
    bool isPalindrome(int x){
         string a = to_string(x);
         string b(a.rbegin(),a.rend());
         return a==b;
    }
};
void Test1(Solution& s){
    bool ret = s.isPalindrome(121);
    if(ret){
        std::cout<<"Test1 OK"<<std::endl;
    }
    else{
        std::cout<<"Test1 failed"<<std::endl;
    }
}

void Test2(Solution& s){
    bool ret = s.isPalindrome(-121);
    if(!ret){
        std::cout<<"Test2 OK"<<std::endl;
    }
    else{
        std::cout<<"Test2 failed"<<std::endl;
    }
}

void Test3(Solution& s){
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
