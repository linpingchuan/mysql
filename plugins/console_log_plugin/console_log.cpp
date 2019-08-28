//
// Created by lin on 8/22/19.
//
#include <iostream>
#include <mysql/plugin.h>
#include <fcntl.h>

struct mysql_console_log_context {
    my_thread_handle console_log_thread;
    File console_log_file;
};

#define CONSOLE_STRING_BUFFER 100

/**
 * 每隔五秒记录一下日志
 * @param conn
 */
static void *log(void *p) {
    time_t result;
    struct mysql_console_log_context *conn = (struct mysql_console_log_context *) p;
    char buffer[CONSOLE_STRING_BUFFER];
    struct tm tm_tmp;
    while (true) {
        sleep(5);

        result = time(nullptr);
        localtime_r(&result, &tm_tmp);
        snprintf(buffer, sizeof(buffer),
                 "I love tina at %02d-%02d-%02d %2d:%02d:%02d\n",
                 tm_tmp.tm_year % 100, tm_tmp.tm_mon + 1, tm_tmp.tm_mday,
                 tm_tmp.tm_hour, tm_tmp.tm_min, tm_tmp.tm_sec);


        my_write(conn->console_log_file, (uchar *) buffer, strlen(buffer), MYF(0));
    }
}

PSI_memory_key key_memory_mysql_console_log_context;

static int plugin_deinit(void *p) {
    DBUG_ENTER("console_log_plugin_deinit");
    struct st_plugin_int *plugin = (struct st_plugin_int *) p;
    struct mysql_console_log_context *conn = (struct mysql_console_log_context *) plugin->data;
    // 开始停止守护线程的写入
    my_thread_cancel(&conn->console_log_thread);

    time_t result = time(nullptr);
    struct tm tm_tmp;
    localtime_r(&result, &tm_tmp);
    char buffer[CONSOLE_STRING_BUFFER];

    snprintf(buffer, sizeof(buffer), "Farewell at %02d%2d%02d %2d:%02d:%02d\n",
             tm_tmp.tm_year % 100, tm_tmp.tm_mon + 1, tm_tmp.tm_mday,
             tm_tmp.tm_hour, tm_tmp.tm_min, tm_tmp.tm_sec);

    my_write(conn->console_log_file, (uchar *) buffer, strlen(buffer), MYF(0));

    void *dummy_retval;
    // 等待写日志线程文件写入完毕
    my_thread_join(&conn->console_log_thread, &dummy_retval);
    // 关闭文件描述符
    my_close(conn->console_log_file, MYF(0));
    // 释放内存
    my_free(conn);
    std::cout<<"deinit"<<std::endl;
    DBUG_RETURN(0);
    return 0;
}

static int plugin_check_uninstall(void *p) {
    DBUG_ENTER("console_log_plugin_init");
    std::cout << "开始检查是否已经卸载" << std::endl;
    struct st_plugin_int *plugin = (struct st_plugin_int *) p;
    std::cout << "ref_count: " << plugin->ref_count << std::endl;
    DBUG_RETURN(0);
    return 0;
}

/**
 * 插件初始化
 * @return
 */
static int plugin_init(void *p) {
    DBUG_ENTER("console_log_plugin_init");

    struct mysql_console_log_context *conn;
    // 线程变量
    my_thread_attr_t attr;
    char console_log_filename[FN_REFLEN];
    char buffer[CONSOLE_STRING_BUFFER];
    time_t result = time(nullptr);
    struct tm tm_tmp;

    struct st_plugin_int *plugin = (struct st_plugin_int *) p;

    conn = (struct mysql_console_log_context *) my_malloc(
            key_memory_mysql_console_log_context,
            sizeof(struct mysql_console_log_context),
            MYF(0)
    );
    fn_format(console_log_filename, "console", "", ".log", MY_REPLACE_EXT | MY_UNPACK_FILENAME);
    unlink(console_log_filename);
    conn->console_log_file = my_open(console_log_filename, O_CREAT | O_RDWR, MYF(0));

    localtime_r(&result, &tm_tmp);
    snprintf(buffer, sizeof(buffer),
             "I love tina at %02d-%02d-%02d %2d:%02d:%02d\n",
             tm_tmp.tm_year % 100, tm_tmp.tm_mon + 1, tm_tmp.tm_mday,
             tm_tmp.tm_hour, tm_tmp.tm_min, tm_tmp.tm_sec);
    my_write(conn->console_log_file, (uchar *) buffer, strlen(buffer), MYF(0));

    my_thread_attr_init(&attr);
    my_thread_attr_setdetachstate(&attr, MY_THREAD_CREATE_JOINABLE);

    // 现在创建线程
    if (my_thread_create(&conn->console_log_thread, &attr, log, (void *) conn) != 0) {
        fprintf(stderr, "无法创建日志线程!\n");
        exit(0);
    }
    plugin->data = conn;
    DBUG_RETURN(0);
}

static struct st_mysql_daemon console_log_descriptor = {
        MYSQL_DAEMON_INTERFACE_VERSION // interface version
};

mysql_declare_plugin(console_log){
                                         MYSQL_DAEMON_PLUGIN,
                                         &console_log_descriptor, /*  specific descriptor      */
                                         "console_log_plugin",           /* plugin name                   */
                                         "lin pingchuan",                    /* author                        */
                                         "just put into console log",   /* description                   */
                                         PLUGIN_LICENSE_GPL, /* license                       */
                                         plugin_init,        /* plugin initializer            */
                                         plugin_check_uninstall,               /* plugin check uninstall        */
                                         plugin_deinit,               /* plugin deinitializer          */
                                         0x0100,             /* version                       */
                                         NULL,               /* status variables              */
                                         NULL,               /* system variables              */
                                         NULL,               /* reserverd                     */
                                         0                   /* flags                         */

                                 }mysql_declare_plugin_end;