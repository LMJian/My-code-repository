#pragma once
//直接包含，直接使用，痛点：在编写代码当中由于找不到头文件，所以会报错，编译的时候，使用-I选项指定头文件的路径就可以了
//设置环境变量CPLUS_INCLUDE_PATH
#include<ctemplate/template.h>
#include<string>
#include<vector>
#include"oj_model.hpp"


class OjView{
  public:
    //渲染html页面，并且将将页面返还给调用
    static void ExpandAllQuestionshtml(std::string* html,std::vector<Question>& ques){
      //1.获取数据字典--->将拿到的试题数据按照一定顺序保存到内存当中
      ctemplate::TemplateDictionary dict("all_questions");

      for(const auto& que:ques){
        ctemplate::TemplateDictionary* section_dict=dict.AddSectionDictionary("question");
        section_dict->SetValue("id",que.id_);
        section_dict->SetValue("id",que.id_);
        section_dict->SetValue("name",que.name_);
        section_dict->SetValue("star",que.star_);
      }
      //2.获取模板类指针，加载预定义的html页面到内存当中
      ctemplate::Template* tl=ctemplate::Template::GetTemplate("./template/all_questions.html",ctemplate::DO_NOT_STRIP);
      //3.渲染，拿着模板类的指针，将数据字典当中的数据更新到html页面的内存中
     tl->Expand(html,&dict);  
    }

    //id name star desc header ==> string html
    static void ExpandOneQuestion(const Question& ques,std::string& desc,std::string& header,std::string* html){
      ctemplate::TemplateDictionary dict("question");
      dict.SetValue("id",ques.id_);
      dict.SetValue("name",ques.name_);
      dict.SetValue("star",ques.star_);
      dict.SetValue("desc",desc);
      dict.SetValue("header",header);

      ctemplate::Template* tpl=ctemplate::Template::GetTemplate("./template/question.html",ctemplate::DO_NOT_STRIP);
      tpl->Expand(html,&dict);
    }
};
