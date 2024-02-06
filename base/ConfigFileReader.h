
#ifndef CONFIGFILEREADER_H_
#define CONFIGFILEREADER_H_

#include "util.h"

//一次性解析文件，将其放入内存，再去读取
class CConfigFileReader
{
public:
    CConfigFileReader(const char *filename);
    ~CConfigFileReader();

    char *GetConfigName(const char *name); //提供key,返回value
    int SetConfigValue(const char *name, const char *value);//提高key,value,写入

private:
    void _LoadFile(const char *filename);
    int _WriteFIle(const char *filename = NULL);
    void _ParseLine(char *line);
    char *_TrimSpace(char *name);

    bool m_load_ok;
    map<string, string> m_config_map;
    string m_config_file;
};

#endif /* CONFIGFILEREADER_H_ */
