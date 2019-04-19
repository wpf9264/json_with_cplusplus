/************************************************************************
    > File Name: leptjson.h
    > Author: wpf
    > Mail: wpf9264@163.com 
    > Created Time: 2019年04月19日 星期五 17时14分32秒
************************************************************************/

#ifndef _LEPTJSON_H
#define _LEPTJSON_H


/* JSON值的7种类型 */
typedef enum{
	LEPT_NULL,
	LEPT_FALSE,
	LEPT_TRUE,
	LEPT_NUMBER,
	LEPT_STRING,
	LEPT_ARRAY,
	LEPT_OBJECT
}lept_type;

/* 解析函数的结果 */
enum{
	PARSE_OK=0,
	PARSE_EXPECT_VALUE,
	PARSE_INVALID_VALUE,
	PARSE_ROOT_NOT_SINGULAR
}; 

/* 在JSON对象中，信息通过lept_context传递 */
typedef struct{
	const char* str;
}lept_text;

typedef struct{
	lept_type type;
}lept_value;

class JSON{

	public:
		/* 构造函数令指针指向nullptr */
		JSON()
		{
			json_text.str = nullptr;
			json_val.type = LEPT_NULL;
		}
		/* 将json文本字符串转换为json数值 */
		int lept_parse(const char* p_json_str);
		/* 获取json数值的类型 */
		int get_lept_type()const;

	private:
		lept_text	json_text;	 //指向json文本字符串
		lept_value	json_val;	 //保存json数据值
		/* 用于跳过字符串前面的空白，指向有效字符 */
		void lept_parse_blank(lept_text& t);

		/* 根据所指首字符选择相应的解析函数进行解析 */
		int lept_parse_value(lept_text& t,lept_value& v);

		/* 对null类型进行解析 */
		int lept_parse_null(lept_text& t,lept_value& v);

		/* 对true类型进行解析 */
		int lept_parse_true(lept_text& t,lept_value& v);

		/* 对false类型进行解析 */
		int lept_parse_false(lept_text& t,lept_value& v);

		/* 判断指着指向的首字符是否与ch相同 */
		void compare_first_char(lept_text& t,char ch); 

};



#endif
