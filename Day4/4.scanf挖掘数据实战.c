#include<stdio.h>
#include<stdlib.h>
void test1(){
	char data[500] = "131610	陈小姐	女	20	165	高中	未婚	朝阳	双子座	在校学生	普通话	北京	面议元/天	有过几次	学生伴游	清纯漂亮 自信可爱的我独在北京上学.在这浪漫的季节偶尔来到这里寻找我的有缘人.愿我们的相聚能留下人生中最美好的回忆!	10:00—23:00		2264938779@qq.com		226493870779";

	char name[20] = {0};
	int age = 0;
	int tall = 0;
	sscanf(data,"%*s%s%*s%d%d%*s",name,&age,&tall);
	printf("name=%s\nage=%d\ntall=%d\n",name,age,tall);

}
void test2(){
	//由于是逗号分隔,所以scanf会把不会把非空白字符当做分隔符,所以整句话都被scanf当作了一个字符串
	char data[500] = "420111197203024016,13600477059,nixiaodong@vip.sina.com";
	char id[100] = {0};
	char telphone[100] = {0};
	char email[200] = {0};
	int i = 0;
	for(;i < 500;i++){
		if(data[i] == ','){
			data[i] = ' ';
		}
	}
	sscanf(data,"%s%s%s",id,telphone,email);
	printf("id=%s\ntelphone=%s\nemail=%s\n",id,telphone,email);
}
/*
	sprintf():将变量拼接成字符串
	sscanf():将字符串分割成变量

	处理字符串时,',','#'这些都是分隔符,我们需要将其转成空格来处理
*/
int main(){
	//test1();
	test2();
	return 0;
}
