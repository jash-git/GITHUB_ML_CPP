题目4 : 好师父推算
---
时间限制:5000ms  
单点时限:1000ms  
内存限制:256MB  
来源:http://hihocoder.com/contest/ntest2015septdm/problem/4

---
####**描述**
师徒系统普遍存在于各类网络游戏中，对于游戏促进新手留存具有重要意义，现在采集到如下信息:  

|好友个数|聊天次数|是否是好师父|
|:-----:|:-----:|:-----:|
|1|3|1|
|2|1|2|

希望你用naïve bayes算法基于“好友个数”和“聊天次数”推算某玩家是好师父的概率，以方便产品优化匹配规则。

----
####**输入**

输入数据由多行构成，每行中的数据用“\t”分隔。  
第1行是1~3个用“\t”分隔的数字，表示输出第几个问题的答案，  
第2行是属性名称，包括fchatnum，cchatnum和remark三个属性，分别代表好友个数、聊天次数和是否是好师父。  
从第3行开始为训练数据，含义与第2行的属性名称相对应。好友个数和聊天次数取值都是1~10的整数，是否是好师父取值是1~2的整数，其中2表示好师父。

----
####**输出**

根据第1行输入数据指定的编号输出以下3个小题的答案，多个小题答案使用换行“\n”分割。  
第1题：输出好师父的先验概率。  
第2题：输出好师父群体中好友个数取值的概率分布，依次对应1~10的概率取值，零值也要输出，中间用逗号分隔。  
第3题：输出给定fchatnum=9，cchatnum=9的玩家是好师父的概率。  
输出结果统一四舍五入保留小数点后3位。

---
完整样例输入下载

总计1000条数据，请在这里[下载](http://media.hihocoder.com/contests/ntes2015septdm/public.txt)。

---
####**样例输入**

1		2		3  
fchatnum 	cchatnum	remark  
1       2       1  
3       3       1  
1       1       1  
6       9       2  
3       7       2  
4       6       2  
4       2       2  
3       8       2  
1       1       1  
8       4       2  
……  

---
####**样例输出**

0.320  
0.034,0.091,0.075,0.144,0.100,0.106,0.119,0.134,0.100,0.097  
0.691  

---
@chenbingjin 2016-08-29