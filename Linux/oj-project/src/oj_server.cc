#include"httplib.h"
#include<jsoncpp/json/json.h>
#include"util.hpp"
#include"oj_model.hpp"
#include"oj_view.hpp"
#include"compile.hpp"

//controller作为服务器核心逻辑，需要创建好对应的服务器框架代码
//在这个框架中来组织逻辑

int main(){
    //服务器启动只加载一次数据即可
    OjModel model;
    model.Load();

    using namespace httplib;
    Server server;
    server.Get("/all_questions",[&model](const Request& req, Response& resp){
        (void) req;
        //数据来自于model对象
        std::vector<Question> all_questions;
        model.GetAllQuestions(&all_questions);
        //如何借助all_questions数据得到的最终的html？
        std::string html;
        OjView::RenderAllQuestions(all_questions,&html);
        resp.set_content(html,"text/html");
    });
    //C++11引入的原始字符串
    server.Get(R"(/question/(\d+))",[&model](const Request& req, Response& resp){
        Question question;
        model.GetQuestion(req.matches[1].str(),&question);
        std::string html;
        OjView::RenderQuestion(question,&html);
        resp.set_content(html,"text/html");
    });
    server.Post(R"(/compile/(\d+))",[&model](const Request& req, Response& resp){
        //1. 先根据id获取到题目的信息
        Question question;
        model.GetQuestion(req.matches[1].str(),&question);

        //2. 解析body， 获取到用户提交的代码
        std::unordered_map<std::string,std::string> body_kv;
        UrlUtil::ParseBody(req.body,&body_kv);
        const std::string& user_code = body_kv["code"];
        
        //3. 构造json格式的参数
        Json::Value req_json;
        //真实需要编译的代码，是用户提交的代码 + 该题目的测试用例的代码
        req_json["code"] = user_code + question.tail_cpp;
        Json::Value resp_json;   //resp_json放到响应中        
        //4. 调用编译模块进行编译了
        Compiler::CompileAndRun(req_json,&resp_json);

        //5. 根据编译结果构造成最终的网页
        std::string html;
        OjView::RenderResult(resp_json["stdout"].asString(),
            resp_json["reason"].asString(),&html);
        resp.set_content(html,"text/html");
    });
    server.set_base_dir("./wwwroot");
    server.listen("0.0.0.0",9092);
    return 0;
}
