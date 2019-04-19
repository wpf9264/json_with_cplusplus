/************************************************************************
    > File Name: mytest.cpp
    > Author: wpf
    > Mail: wpf9264@163.com 
    > Created Time: 2019年04月19日 星期五 20时41分47秒
************************************************************************/

#include<iostream>
#include"leptjson.h"
#include<cstdlib>
using namespace std;



static int main_ret = 0;
static int test_count = 0;
static int pass_count = 0;

/* 用于统计测试次数，及失败的位置 */
#define EXPECT_EQ_BASE(equality,expect,actual) \
	do{							\
		test_count++;			\
		if (equality){			\
			pass_count++;		\
		}else{					\
			fprintf(stderr,"%s:%d expect:%d actual:%d\n",__FILE__,__LINE__,expect,actual);	\
			main_ret = 1;		\
		}						\
	}while(0)

/* 用于判断实际值是否等于期望值 */
#define EXPECT_EQ_INT(expect,actual) EXPECT_EQ_BASE((expect==actual),expect,actual)

void test_parse_null(class JSON& json)
{
	char p[] = "null";
	EXPECT_EQ_INT(PARSE_OK,json.lept_parse(p));
	EXPECT_EQ_INT(LEPT_NULL,json.get_lept_type());
}


void test_parse_false(class JSON& json)
{
	char p[] = "false";
	EXPECT_EQ_INT(PARSE_OK,json.lept_parse(p));
	EXPECT_EQ_INT(LEPT_FALSE,json.get_lept_type());
}


void test_parse_true(class JSON& json)
{
	char p[] = "true";
	EXPECT_EQ_INT(PARSE_OK,json.lept_parse(p));
	EXPECT_EQ_INT(LEPT_TRUE,json.get_lept_type());
}


void test_parse_expect(class JSON& json)
{
	char p[] = "mytest";	
	EXPECT_EQ_INT(PARSE_EXPECT_VALUE,json.lept_parse(p));	//mytest不是期望字符串，因此这里会不通过
	EXPECT_EQ_INT(LEPT_NULL,json.get_lept_type());		

	char p1[] = "";
	EXPECT_EQ_INT(PARSE_EXPECT_VALUE,json.lept_parse(p1));
	EXPECT_EQ_INT(LEPT_NULL,json.get_lept_type());

	char p2[] = " ";
	EXPECT_EQ_INT(PARSE_EXPECT_VALUE,json.lept_parse(p2));
	EXPECT_EQ_INT(LEPT_NULL,json.get_lept_type());
}


void test_parse_invalid(class JSON& json)
{
	char p[] = "nul";
	EXPECT_EQ_INT(PARSE_INVALID_VALUE,json.lept_parse(p));
	EXPECT_EQ_INT(LEPT_NULL,json.get_lept_type());

	char p1[] = "mytest";
	EXPECT_EQ_INT(PARSE_INVALID_VALUE,json.lept_parse(p1));
	EXPECT_EQ_INT(LEPT_NULL,json.get_lept_type());
}

void test_parse_root_not_singular(class JSON& json)
{
	char p[] = "null test";
	EXPECT_EQ_INT(PARSE_ROOT_NOT_SINGULAR,json.lept_parse(p));
	EXPECT_EQ_INT(LEPT_NULL,json.get_lept_type());
}




void test_parse()
{
	JSON json;
	test_parse_null(json);
	test_parse_false(json);
	test_parse_true(json);
	test_parse_expect(json);
	test_parse_invalid(json);
	test_parse_root_not_singular(json);
}


int main(int argc,char** argv)
{
	test_parse();
	cout<<pass_count<<"/"<<test_count<<"("<<pass_count*100.0/test_count*1.0<<"%) passed"<<endl;
	return main_ret;
}
