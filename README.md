# 1 Project Description

```
this project aims to build a web server for a software which provides users to upload, download, store, share pictures and others files of content size being below 512 Bytes

```
# 2 How to build this project

```
this project depends on those libraries: 
/usr/include/fastdfs /usr/include/fastcommon /usr/local/include/hiredis
/usr/include/mysql; you may download these libraries by git clone 
from github and compile them, they will be stored in /usr/include/

first:  mkdir build
second: cmake ..
finall: make -j12 

then you will get the executable file,which is named picbed_http_server.

```
