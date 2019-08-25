# MySQL 学习文档

## clone MySQL 代码，进行编译
```
git clone git@github.com:mysql/mysql-server.git
sudo apt-get install make cmake gcc g++ bison libncurses5-dev build-essential -y
sudo apt-get install libssl-dev -y 
mkdir -pv ~/mysql-build
cd mysql-build 
cmake ~/mysql-server -DDEBUG=1  -DWITH_BOOST=~/boost
make -j 4
```

## 构建 MySQL ，编写第一个 MySQL 插件

```shell
sudo apt update
# install 官方 lib 库
sudo apt-get install libmysqld-dev -y
sudo apt-get install libmysql++-dev
```

## CLion 中，进行编译
```shell
# cmake option
-DCMAKE_BUILD_TYPE=Debug --DWITH_BOOST=~/boost/boost_1_69_0
```

## 编译后 启动 MySQLd
```shell
mysqld -uroot --initialize-insecure
mysqld -uroot 
# 启动后，默认端口为 33060
# 可通过以下命令进行查看
lsof -i | grep 33060
```

### 参考文档
1. [MySQL 插件详解](https://jin-yang.github.io/post/mysql-plugin.html)
2. [编写 MySQL 储存引擎](https://dev.mysql.com/doc/internals/en/custom-engine.html)
3. [编写自己的 MySQL 插件](https://dev.mysql.com/doc/refman/8.0/en/writing-plugins.html)
4. [编写 MySQL 插件](https://dev.mysql.com/doc/refman/8.0/en/writing-plugins-overview.html)
5. [MariaDB 教程](https://mariadb.com/kb/en/library/development-writing-plugins-for-mariadb/)
6. [插件编写中文文档](https://www.docs4dev.com/docs/zh/mysql/5.7/reference/writing-plugins.html#%E7%BC%96%E5%86%99%E6%8F%92%E4%BB%B6)
7. [MySQL 图片插件](https://github.com/netkiller/mysql-image-plugin/blob/master/CMakeLists.txt)
8. [增加MySQL链接库](https://stackoverflow.com/questions/35068444/add-and-link-mysql-libraries-in-a-cmakelist-txt)
9. [扩展MySQL](https://www.deituicms.com/mysql8cn/cn/extending-mysql.html)
### 项目地址


### 心得体会
[编写 MySQL 插件](./plugins/doc/README.md)