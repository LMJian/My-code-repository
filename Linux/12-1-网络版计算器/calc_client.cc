#include"tcp_client.hpp"
#include<sstream>
#include<jsoncpp/json/json.h>

int main(){
  TcpClient client("127.0.0.1",9090);
  while(1){
    cout<<"请输入两个操作数"<<endl;
    fflush(stdout);
    int num1=0;
    int num2=0;
    string op;
    cin>>num1>>num2;
    cout<<"请输入操作符"<<endl;
    cin>>op;
    
    //根据输入构建json对象
    Json::Value req_json;
    req_json["num1"]=num1;
    req_json["num2"]=num2;
    req_json["op"]=op;
    //把json对象序列化
    Json::StyledWriter writer;
    string req =writer.write(req_json);
    cout<<"req:"<<req<<endl;
    //发送到服务器
    client.Send(req);
    //读取结果
    string resp;
    client.Recv(resp);
    //将结果进行json解析
    Json::Value resp_json;
    Json::Reader reader;
    reader.parse(resp,resp_json);
    cout<<"result:"<<resp_json["result"].asInt()<<endl;

    /*stringstream ss;
    ss<<num1<<" "<<num2<<" "<<op;
    client.Send(ss.str());
    string resp;
    client.Recv(resp);
    cout<<"recv->"<<resp<<endl;*/
  }
  return 0;
}
