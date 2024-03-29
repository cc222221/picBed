#ifndef _APIUPLOAD_H_
#define _APIUPLOAD_H_
#include <string>
using std::string;

int ApiUpload(string &url, string &post_data, string &str_json);

int ApiUploadInit(char *dfs_path_client, char *web_server_ip,
                  char *web_server_port, char *storage_web_server_ip,
                  char *storage_web_server_port);

#endif // !__UPLOAD_H_