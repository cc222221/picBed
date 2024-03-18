# 1 编译说明



```
cd tc-src
mkdir build
cd build
cmake ..
make
```

得到执行文件

```
tc_http_server
```

**需要将修改的tc_http_server.conf的拷贝到执行目录。**



# 2 导入数据库

```
root@iZbp1h2l856zgoegc8rvnhZ:~/0voice/tc/tuchuang$ mysql -uroot -p          #登录mysql

mysql>
mysql> source /root/tuchuang/tuchuang/0voice_tuchuang.sql;   #导入数据库，具体看自己存放的路径
```



# 3 代码版本说明

-n对应图床课程的第n节课。



v0.2 tuchuang-2
目前该版本为单线程版本，日志也直接打印到控制台，随着课程会不断迭代。


v0.3 tuchuang-3

1. 日志异步处理
2. 文件数量 计数采用redis
3. 使用c++11线程池处理，目前只是小部分函数使用了多线程处理
4. 数据回发
5. 修复一些bug



v0.6 tuchuang-6

1. tc-src 代码风格以谷歌C++风格为主，支持部分函数使用c++11线程池，其他的函数大家可以根据api_register.cc范例做修改。

2. 修正部分头文件重复的问题
3. 大家可以在此版本的基础上进一步优化。
4. 谷歌C++代码风格地址：https://www.bookstack.cn/read/google-cpp-style/1.md



# 4 数据库是否创建索引对比范例

比如user的name字段为例子。



## 字符串（16字符）查询

```
不创建索引：
20221109 12:32:34.065727Z WARN  Reg 10000 times need the time: 7848ms, average time: 0.7848ms, qps: 1274 - TestRegister.cpp:104
20221109 12:32:39.351793Z WARN  SEL 1000 times need the time: 5286ms, average time: 5.286ms, qps: 189

 - TestRegister.cpp:129
   20221109 12:32:46.937852Z WARN  Reg 10000 times need the time: 7586ms, average time: 0.7586ms, qps: 1318 - TestRegister.cpp:104
   20221109 12:32:53.398511Z WARN  SEL 1000 times need the time: 6461ms, average time: 6.461ms, qps: 154

 - TestRegister.cpp:129
   20221109 12:33:00.958943Z WARN  Reg 10000 times need the time: 7560ms, average time: 0.756ms, qps: 1322 - TestRegister.cpp:104
   20221109 12:33:10.246383Z WARN  SEL 1000 times need the time: 9288ms, average time: 9.288ms, qps: 107

创建索引： 对于字符串（16字符）查询，至少能有50倍的差别
20221109 12:35:01.232602Z WARN  Reg 10000 times need the time: 7667ms, average time: 0.7667ms, qps: 1304 - TestRegister.cpp:104
20221109 12:35:01.375095Z WARN  SEL 1000 times need the time: 143ms, average time: 0.143ms, qps: 6993

20221109 12:35:09.628334Z WARN  Reg 10000 times need the time: 8252ms, average time: 0.8252ms, qps: 1211 - TestRegister.cpp:104
20221109 12:35:09.752298Z WARN  SEL 1000 times need the time: 124ms, average time: 0.124ms, qps: 8064

20221109 12:35:17.659541Z WARN  Reg 10000 times need the time: 7907ms, average time: 0.7907ms, qps: 1264 - TestRegister.cpp:104
20221109 12:35:17.780371Z WARN  SEL 1000 times need the time: 121ms, average time: 0.121ms, qps: 8264
```

## 字符串（32字符）查询



```
20221109 12:39:02.116297Z INFO  db_host:127.0.0.1, db_port:3306, db_dbname:0voice_tuchuang_index, db_username:root, db_password:123456 - DBPool.cpp:635
20221109 12:39:02.137699Z INFO  db_host:127.0.0.1, db_port:3306, db_dbname:0voice_tuchuang_index, db_username:root, db_password:123456 - DBPool.cpp:635
20221109 12:39:09.937993Z WARN  Reg 10000 times need the time: 7785ms, average time: 0.7785ms, qps: 1284 - TestRegister.cpp:104
20221109 12:39:27.018825Z WARN  SEL 1000 times need the time: 17080ms, average time: 17.08ms, qps: 58

 - TestRegister.cpp:129
   20221109 12:39:34.339589Z WARN  Reg 10000 times need the time: 7321ms, average time: 0.7321ms, qps: 1365 - TestRegister.cpp:104
   20221109 12:39:54.142958Z WARN  SEL 1000 times need the time: 19803ms, average time: 19.803ms, qps: 50

 - TestRegister.cpp:129
   20221109 12:40:01.536958Z WARN  Reg 10000 times need the time: 7393ms, average time: 0.7393ms, qps: 1352 - TestRegister.cpp:104
   20221109 12:40:23.985673Z WARN  SEL 1000 times need the time: 22449ms, average time: 22.449ms, qps: 44

创建索引： 对于字符串（32字符）查询，至少能有100倍的差别; 但也看到插入索引对写入性能是有一定的影响10%左右
20221109 12:42:34.041657Z WARN  Reg 10000 times need the time: 7989ms, average time: 0.7989ms, qps: 1251 - TestRegister.cpp:104
20221109 12:42:34.259736Z WARN  SEL 1000 times need the time: 218ms, average time: 0.218ms, qps: 4587

 - TestRegister.cpp:129
   20221109 12:42:42.211293Z WARN  Reg 10000 times need the time: 7951ms, average time: 0.7951ms, qps: 1257 - TestRegister.cpp:104
   20221109 12:42:42.346641Z WARN  SEL 1000 times need the time: 135ms, average time: 0.135ms, qps: 7407

 - TestRegister.cpp:129
   20221109 12:42:50.328924Z WARN  Reg 10000 times need the time: 7981ms, average time: 0.7981ms, qps: 1252 - TestRegister.cpp:104
   20221109 12:42:50.481601Z WARN  SEL 1000 times need the time: 153ms, average time: 0.153ms, qps: 6535



1百万条数据 有索引的插入和查询, 16字符 
20221109 12:35:01.232602Z WARN  Reg 10000 times need the time: 7667ms, average time: 0.7667ms, qps: 1304 - TestRegister.cpp:104
20221109 12:35:01.375095Z WARN  SEL 1000 times need the time: 143ms, average time: 0.143ms, qps: 6993

1百万条数据 没索引的插入和查询，16字符，查询速度令人发指
20221109 12:32:46.937852Z WARN  Reg 10000 times need the time: 7586ms, average time: 0.7586ms, qps: 1318 - TestRegister.cpp:104
20221109 12:32:53.398511Z WARN  SEL 1000 times need the time: 6461ms, average time: 6.461ms, qps: 154


1百万条数据 有索引的插入和查询, 32字符
20221109 12:58:49.877556Z WARN  Reg 1000000 times need the time: 822402ms, average time: 0.822402ms, qps: 1215 - TestRegister.cpp:104
20221109 12:58:50.092348Z WARN  SEL 1000 times need the time: 214ms, average time: 0.214ms, qps: 4672

1百万条数据 没索引的插入和查询，32字符，查询速度令人发指
20221109 13:12:38.593070Z WARN  Reg 1000000 times need the time: 762373ms, average time: 0.762373ms, qps: 1311 - TestRegister.cpp:104
20221109 13:19:22.471249Z WARN  SEL 1000 times need the time: 403877ms, average time: 403.877ms, qps: 2
```

