#include "library.h"

#include <iostream>

static int console_log_plugin_initializer(MYSQL_PLUGIN p) {
    std::cout << "lin pingchuan ~\\(≧▽≦)/~啦啦啦" << std::endl;
    return 0;
}

static int CONSOLE_LOG_INTERFACE_VERSION = 1;
static struct st_mysql_daemon console_log_descriptor = {
        CONSOLE_LOG_INTERFACE_VERSION// interface version
};

mysql_declare_plugin(console_log){
                                         MYSQL_DAEMON_PLUGIN,
                                         &console_log_descriptor, /* type specific descriptor      */
                                         "console_log",           /* plugin name                   */
                                         "lin pingchuan",                    /* author                        */
                                         "just put into console log",   /* description                   */
                                         PLUGIN_LICENSE_GPL, /* license                       */
                                         console_log_plugin_initializer,        /* plugin initializer            */
                                         NULL,               /* plugin check uninstall        */
                                         NULL,               /* plugin deinitializer          */
                                         0x0010,             /* version                       */
                                         NULL,               /* status variables              */
                                         NULL,               /* system variables              */
                                         NULL,               /* reserverd                     */
                                         0                   /* flags                         */

                                 }mysql_declare_plugin_end;