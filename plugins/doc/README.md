# MySQL 插件实现
## 构建插件
> 构建插件需要将 mysql-server 源代码这个完全克隆下来，在 mysql-server/plugin 文件夹下创建项目
在MySQL项目下实现插件定制化
```shell
# 控制台日志插件
/home/lin/clion/bin/cmake/linux/bin/cmake --build /home/lin/Documents/mysql-server/cmake-build-debug --target console_log_plugin -- -j 2
# 展示 sql
/home/lin/clion/bin/cmake/linux/bin/cmake --build /home/lin/Documents/mysql-server/cmake-build-debug --target show_sql -- -j 2
```
## 安装与卸载插件
``` sql
# 安装插件
install plugin console_log_plugin soname 'console_log_plugin.so';
# 卸载插件
uninstall plugin console_log_plugin;
# 查看插件所在的目录
show variables like 'plugin_dir';
# 拷贝插件到相应的目录下
mkdir -pv 
# 卸载后可以删除data目录，用于重新初始化msyqld
rm -rf /home/lin/mysql-server/cmake-build-debug/data/
# 再进行重新初始化
/home/lin/mysql-server/cmake-build-debug/runtime_output_directory/mysqld -uroot --initialize-insecure

```
## 项目案例
[后台日志项目](../console_log_plugin/console_log.cpp)
## 注意事项
1. 插件初始化完，才开始启动 mysqld;
