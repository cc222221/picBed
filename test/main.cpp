/**
 * 头文件包含规范
 * 1.本类的声明（第一个包含本类h文件，有效减少以来）
 * 2.C系统文件
 * 3.C++系统文件
 * 4.其他库头文件
 * 5.本项目内头文件
 */

// using std::string; // 可以在整个cc文件和h文件内使用using， 禁止使用using
// namespace xx污染命名空间

#include "cache_pool.h"
#include "config_file_reader.h"
#include "db_pool.h"
#include "netlib.h"
#include "util.h"

#include "Async_logging.h"
#include "api_dealfile.h"
#include "api_upload.h"
#include "tc_logging.h"

extern void SingeThreadTestLogin();
extern void SingeThreadRegister();
off_t kRollSize = 1 * 1000 * 1000; // 只设置1M
static AsyncLogging *g_asyncLog = NULL;

static void asyncOutput(const char *msg, int len) {
    g_asyncLog->append(msg, len);
}

int initLog() {
    printf("pid = %d\n", getpid());
    g_logLevel = Logger::INFO;   // 设置级别
    char name[256] = "tuchuang"; //日志名字  tuchuang.log
    // 回滚大小kRollSize（1M）, 最大1秒刷一次盘（flush）
    AsyncLogging *log =
        new AsyncLogging(::basename(name), kRollSize,
                         1); // 注意，每个文件的大小
                             // 还取决于时间的问题，不是到了大小就一定换文件。
    // Logger::setOutput(asyncOutput);   // 不是说只有一个实例

    g_asyncLog = log;
    log->start(); // 启动日志写入线程

    return 0;
}

void deInitLog() {
    if (g_asyncLog) {
        delete g_asyncLog;
        g_asyncLog = NULL;
    }
}

int main(int argc, char *argv[]) {
    signal(SIGPIPE, SIG_IGN);

    // 初始化日志，暂且只是打印到屏幕上，课程不断迭代
    initLog();

    // 初始化mysql、redis连接池，内部也会读取读取配置文件tc_http_server.conf
    CacheManager *cache_manager = CacheManager::getInstance();
    if (!cache_manager) {
        LOG_ERROR << "CacheManager init failed";
        std::cout << "CacheManager init failed";
        return -1;
    }

    CDBManager *db_manager = CDBManager::getInstance();
    if (!db_manager) {
        LOG_ERROR << "DBManager init failed";
        std::cout << "DBManager init failed";
        return -1;
    }

    // 读取配置文件
    CConfigFileReader config_file("tc_http_server.conf");

    char *dfs_path_client = config_file.GetConfigName("dfs_path_client");
    char *web_server_ip = config_file.GetConfigName("web_server_ip");
    char *web_server_port = config_file.GetConfigName("web_server_port");
    char *storage_web_server_ip =
        config_file.GetConfigName("storage_web_server_ip");
    char *storage_web_server_port =
        config_file.GetConfigName("storage_web_server_port");

    // 将配置文件的参数传递给对应模块
    ApiUploadInit(dfs_path_client, web_server_ip, web_server_port,
                  storage_web_server_ip, storage_web_server_port);
    ApiDealfileInit(dfs_path_client);

    // SingeThreadTestLogin();
    SingeThreadRegister();
    SingeThreadRegister();
    SingeThreadRegister();
    deInitLog();
    return 0;
}
