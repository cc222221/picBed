#ifndef _API_COMMON_H_
#define _API_COMMON_H_
#include "cache_pool.h"
#include "db_pool.h"
#include "redis_keys.h"
#include "common.h"
#include "picbed_logging.h"
#include "json/json.h"
#include <string>

extern string s_dfs_path_client;
extern string s_web_server_ip;
extern string s_web_server_port;
extern string s_storage_web_server_ip;
extern string s_storage_web_server_port;
using std::string;
;
int ApiInit();
//获取用户文件个数
int CacheSetCount(CacheConn *cache_conn, string key, int64_t count);
int CacheGetCount(CacheConn *cache_conn, string key, int64_t &count);
int CacheIncrCount(CacheConn *cache_conn, string key);
int CacheDecrCount(CacheConn *cache_conn, string key);
int DBGetUserFilesCountByUsername(CDBConn *db_conn, string user_name,
                                  int &count);
int DBGetShareFilesCount(CDBConn *db_conn, int &count);
int DBGetSharePictureCountByUsername(CDBConn *db_conn, string user_name,
                                     int &count);
int RemoveFileFromFastDfs(const char *fileid);
#endif