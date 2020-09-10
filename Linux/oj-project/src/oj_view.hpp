//MVC => view: 负责显示页面

#pragma once
#include<ctemplate/template.h>
#include"oj_model.hpp"

class OjView{
public:
    //根据所有的题目列表信息，生成HTML， 供网站首页显示
    static void RenderAllQuestions(const std::vector<Question>& all_questions,
                                   std::string* html){
        //使用ctemplate开源库来构造HTML
        
        //1. 先创建一个ctemplate对象
        ctemplate::TemplateDictionary dict("all_questions");

        //2. 循环添加对象
        for(const auto& question : all_questions ){
            ctemplate::TemplateDictionary* table_dict = dict.AddSectionDictionary("question");

            //3. 每个对象设置键值对的时候是和模板中留下的{{}}对应的
            table_dict->SetValue("id",question.id);
            table_dict->SetValue("name",question.name);
            table_dict->SetValue("star",question.star);
        }

        //4. 进行数据的替换，生成最终的HTML
        ctemplate::Template* tpl = ctemplate::Template::GetTemplate("./template/all_questions.html",
                                                                    ctemplate::DO_NOT_STRIP);
        tpl->Expand(html,&dict);
    }

    //根据指定的question, 生成HTML
    static void RenderQuestion(const Question& question,std::string* html){
        //1. 先创建一个ctemplate对象
        ctemplate::TemplateDictionary dict("question");
        
        //2. 设置键值对，是和模板中留下的{{}}对应的
        dict.SetValue("id",question.id);
        dict.SetValue("name",question.name);
        dict.SetValue("star",question.star);
        dict.SetValue("desc",question.desc);
        dict.SetValue("header",question.header_cpp);
        
        //3. 进行数据的替换，生成最终的HTML
        ctemplate::Template* tpl = ctemplate::Template::GetTemplate("./template/question.html",
                                                                    ctemplate::DO_NOT_STRIP);
        tpl->Expand(html,&dict);
    }

    //根据运行结果或编译出错的结果，构造生成HTML
    static void RenderResult(const std::string& str_stdout,
                             const std::string& reason,std::string* html){
        //1. 先创建一个ctemplate对象
        ctemplate::TemplateDictionary dict("result");

        //2. 设置键值对，是和模板中留下的{{}}对应的
        dict.SetValue("stdout",str_stdout);
        dict.SetValue("reason",reason);

        //3. 进行数据的替换，生成最终的HTML
        ctemplate::Template* tpl = ctemplate::Template::GetTemplate("./template/result.html",
                                                                    ctemplate::DO_NOT_STRIP);
        tpl->Expand(html,&dict);
    }
};