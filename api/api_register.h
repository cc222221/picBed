#ifndef _API_REGISTER_H_
#define _API_REGISTER_H_
#include <string>
using std::string;
// int ApiRegisterUser(string &url, string &post_data, string &str_json);
// int ApiRegisterUser(string &url, string &post_data);
int ApiRegisterUser(uint32_t conn_uuid, string &url, string &post_data);
#endif