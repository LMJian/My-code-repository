//MVC => controller: 核心业务逻辑

#include"httplib.h"
#include<jsoncpp/json/json.h>
#include"util.hpp"
#include"oj_model.hpp"
#include"oj_view.hpp"
#include"compile.hpp"

int main(){
    //加载题库数据资源
    OjModel model;
    model.Load();

    //使用第三方库httplib 来搭建服务器
    using namespace httplib;
    Server server;
    
    //项目首页
    server.Get("/",[&model](const Request& req, Response& resp){
        (void) req;

        //通过model获取所有的题目信息
        std::vector<Question> all_questions;
        model.GetAllQuestions(&all_questions);

        //将all_questions的数据转换为html
        std::string html;
        OjView::RenderAllQuestions(all_questions,&html);

        //将后端处理完的请求返回给客户端
        resp.set_content(html,"text/html");
    });

    //具体题目的页面
    server.Get(R"(/question/(\d+))",[&model](const Request& req, Response& resp){
        //通过model获取指定题目的信息
        Question question;
        model.GetQuestion(req.matches[1].str(),&question);

        //将question的数据转换为html
        std::string html;
        OjView::RenderQuestion(question,&html);

        //将后端处理完的请求返回给客户端
        resp.set_content(html,"text/html");
    });

    //代码运行结果界面
    server.Post(R"(/compile/(\d+))",[&model](const Request& req, Response& resp){
        //1. 通过model获取指定题目的信息
        Question question;
        model.GetQuestion(req.matches[1].str(),&question);

        //2. 解析body， 获取用户提交的代码
        std::unordered_map<std::string,std::string> body_kv;
        UrlUtil::ParseBody(req.body,&body_kv);
        const std::string& user_code = body_kv["code"];
        
        //3. 构造json格式的参数
        Json::Value req_json;
        //   编译的代码 = 用户提交的代码 + 测试用例代码
        req_json["code"] = user_code + question.tail_cpp;
        req_json["stdin"] = user_code;
        
        //4. 调用编译模块进行编译
        Json::Value resp_json;
        Compiler::CompileAndRun(req_json,&resp_json);

        //5. 将运行结果构造成HTML
        std::string html;
        OjView::RenderResult(resp_json["stdout"].asString(),
                             resp_json["reason"].asString(),&html);

        //6. 将后端处理完的请求返回给客户端
        resp.set_content(html,"text/html");
    });

    server.set_base_dir("./wwwroot");
    server.listen("0.0.0.0",9092);

    return 0;
}