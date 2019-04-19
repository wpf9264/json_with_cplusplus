/************************************************************************
    > File Name: leptjson.cpp
    > Author: wpf
    > Mail: wpf9264@163.com 
    > Created Time: 2019年04月19日 星期五 19时17分29秒
************************************************************************/

#include<iostream>
#include<assert.h>
#include<cstdlib>
#include<string>
#include"leptjson.h"

using namespace std;

void JSON::compare_first_char(lept_text& t,char ch)
{
	assert(*t.str==ch);
	t.str++;
}; 

int JSON::lept_parse_null(lept_text& t,lept_value& v)
{
	compare_first_char(t,'n');
	if (t.str[0]!='u' || t.str[1]!='l' || t.str[2]!='l'){
		return PARSE_INVALID_VALUE;
	}
	t.str += 3;
	v.type = LEPT_NULL;
	return PARSE_OK;
}


int JSON::lept_parse_false(lept_text& t,lept_value& v)
{
	compare_first_char(t,'f');
	if (t.str[0]!='a' || t.str[1]!='l' || t.str[2]!='s' || t.str[3]!='e'){
		return PARSE_INVALID_VALUE;
	}
	t.str += 4;
	v.type = LEPT_FALSE;
	return PARSE_OK;
}

int JSON::lept_parse_true(lept_text& t,lept_value& v)
{
	compare_first_char(t,'t');
	if (t.str[0]!='r' || t.str[1]!='u' || t.str[2]!='e'){
		return PARSE_INVALID_VALUE;
	}
	t.str += 3;
	v.type = LEPT_TRUE;
	return PARSE_OK;
}

void JSON::lept_parse_blank(lept_text& t)
{
	const char* p = json_text.str;
	while(*p==' ' || *p=='\t' || *p=='\n' || *p=='\r'){
		p++;
	}
	json_text.str = p;
}


int JSON::lept_parse_value(lept_text& t,lept_value& v)
{
	switch(*t.str){
		case 'n' :	return lept_parse_null(t,v);
		case 't' :	return lept_parse_true(t,v);
		case 'f' :	return lept_parse_false(t,v);
		case '\0':	return PARSE_EXPECT_VALUE;
		default  :	return PARSE_INVALID_VALUE;
	}
}

int JSON::lept_parse(const char* p_str)
{
	//这里同样不知道怎么断言非空
	json_text.str = p_str;
	json_val.type = LEPT_NULL;
	lept_parse_blank(json_text);				//跳过字符串的空白
	int res = lept_parse_value(json_text,json_val);	//对真实内容进行解析
	if (res==PARSE_OK){
		lept_parse_blank(json_text);			//判断是否含有多个单词
		if (*json_text.str!='\0'){
			res = PARSE_ROOT_NOT_SINGULAR;      //有，返回解析结果为：not_singular
		}
	}
	return res;
}

int JSON::get_lept_type()const
{
	//这里该怎么断言lept_value不为空呢？？？
	return json_val.type;
}
