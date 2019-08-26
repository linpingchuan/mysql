# MySQL 插件实现注意点
在MySQL项目下实现插件定制化
```shell
/home/lin/clion/bin/cmake/linux/bin/cmake --build /home/lin/Documents/mysql-server/cmake-build-debug --target console_log_plugin -- -j 2
```

``` sql
install plugin console_log_plugin soname 'console_log_plugin.so';
```