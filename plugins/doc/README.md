# MySQL 插件实现
## 构建插件
在MySQL项目下实现插件定制化
```shell
/home/lin/clion/bin/cmake/linux/bin/cmake --build /home/lin/Documents/mysql-server/cmake-build-debug --target console_log_plugin -- -j 2
```
## 安装与卸载插件
``` sql
# 安装插件
install plugin console_log_plugin soname 'console_log_plugin.so';
# 卸载插件
uninstall plugin console_log_plugin;
# 查看插件所在的目录
show variables like 'plugin_dir';
```
## 注意事项
1. 插件初始化完，才开始启动 mysqld;
