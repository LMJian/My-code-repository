#pragma once
//google的开源库
#include<ctemplate/template.h>
#include"oj_model.hpp"

class OjView{
public:
    //根据数据，生成HTML这个动作，通常叫做网页渲染（Render）
    static void RenderAllQuestions(const std::vector<Question>& all_questions,
                            std::string* html){
        //这个函数帮我们把所有的题目数据， 转换成题目列表页HTML
        //在C++代码中直接通过字符串拼接的方式构造HTML太麻烦
        //通过网页模板的方式解决问题
        //模板类似于填空题，事先准备好一个HTML把其中一些需要动态计算的数据挖个空
        //留出来，处理请求过程中，根据计算结果来填这样的空
        
        //1. 先创建一个ctemplate的对象，这是一个总的组织数据的对象
        //2. 循环的往这个对象中添加一些子对象
        //3. 每一个子对象在设置一些键值对（和模板中留下的{{}}是要对应的）
        //4. 进行数据的替换，生成最终的HTML
        ctemplate::TemplateDictionary dict("all_questions");
        for(const auto& question : all_questions ){
            ctemplate::TemplateDictionary* table_dict
                = dict.AddSectionDictionary("question");
            table_dict->SetValue("id",question.id);
            table_dict->SetValue("name",question.name);
            table_dict->SetValue("star",question.star);
        }
        ctemplate::Template* tpl;
        tpl = ctemplate::Template::GetTemplate(
            "./template/all_questions.html",
            ctemplate::DO_NOT_STRIP);
        tpl->Expand(html,&dict);
    }

    static void RenderQuestion(const Question& question,std::string* html){
        ctemplate::TemplateDictionary dict("question");
        dict.SetValue("id",question.id);
        dict.SetValue("name",question.name);
        dict.SetValue("star",question.star);
        dict.SetValue("desc",question.desc);
        dict.SetValue("header",question.header_cpp);
        
        ctemplate::Template* tpl;
        tpl = ctemplate::Template::GetTemplate(
            "./template/question.html",
            ctemplate::DO_NOT_STRIP);
        tpl->Expand(html,&dict);
    }

    static void RenderResult(const std::string& str_stdout,
            const std::string& reason,std::string* html){
        ctemplate::TemplateDictionary dict("result");
        dict.SetValue("stdout",str_stdout);
        dict.SetValue("reason",reason);
        
        ctemplate::Template* tpl;
        tpl = ctemplate::Template::GetTemplate(
            "./template/result.html",
            ctemplate::DO_NOT_STRIP);
        tpl->Expand(html,&dict);
    }
};
