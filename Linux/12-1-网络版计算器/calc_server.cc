#include"tcp_thread_server.hpp"
#include<sstream>
#include<jsoncpp/json/json.h>

void handler(const string&req,string& resp){
  //1.将req进行反序列化
  Json::Reader reader;
  Json::Value req_json;
  reader.parse(req,req_json);
  //2.进行计算
  //int num1=req_json["num1"].asInt();
  //int num2=req_json["num2"].asInt();
  Json::Value& nums=req_json["nums"];
  string op=req_json["op"].asString();
  int result=0;
  for(size_t i=0;i<nums.size();++i){
    if(op=="+")
      result+=nums[(int)i].asInt();
    else if(op=="-")
      result-=nums[(int)i].asInt();

  }
  /*if(op=="+")
  {
    result =num1+num2;
  }
  else if(op=="-"){
    result=num1-num2;
  }*/
  //3.将结果进行序列化
  Json::Value resp_json;
  Json::FastWriter writer;
  resp_json["result"]=result;
  resp=writer.write(resp_json);

  /*stringstream ss(req);
  int num1=0;
  int num2=0;
  string op;
  ss>>num1;
  ss>>num2;
  ss>>op;
  printf("num1=%d,num2=%d,op=%s\n",num1,num2,op.c_str());
  int ret=0;
  if(op=="+")
    ret=num1+num2;
  else if(op=="-")
    ret=num1-num2;
  else if(op=="*")
    ret=num1*num2;
  else if(op=="/")
    ret=num1/num2;
  else 
    ret=num1%num2;
  //resp=to_string(ret);
  stringstream ss_resp;
  ss_resp<<ret;
  resp=ss_resp.str();*/
}
int main(){
  TcpThreadServer server;
  server.Start("0.0.0.0",9090,handler);

  return 0;
}
