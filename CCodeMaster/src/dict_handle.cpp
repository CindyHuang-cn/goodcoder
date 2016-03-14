/*===============================================================
*   Copyright (C) 2015 Baidu.com, Inc. All rights reserved.
*   
*   文件名称：dict_handle.cpp
*   创 建 者：chenchen36
*   创建日期：2015.12.21
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <string>
#include "dict_handle.h"

namespace dp{
    DictHandle::DictHandle(){
    }
    DictHandle::~DictHandle(){
    }

    void DictHandle::split_line_columns(const std::string line, const std::string pattern){
        boost::split(_columns, line, boost::is_any_of(pattern));
    }
    const std::vector<std::string> DictHandle::get_columns(){
        return _columns;
    }

    /**
     * @brief 模板特化 处理char* 类型
     * @param size_t index 第几列
     * @param char** 
     * @return ErrorCode 错误码
     */
    template <>
    ErrorCode DictHandle::get_value<char*>(const size_t index, char** value){
        std::vector<std::string> columns = get_columns();
        size_t len = columns.size(); 
        if (index >= len) {
            return OVER_MAX_LEN;
        }
        std::string column = columns[index];
        if (column.empty()) {
            return EMPTY_STR; 
        }
        char* str_tmp  = new char[sizeof(char) * (column.length() + 1)];
        column.copy(str_tmp, column.length(), 0);
        *(str_tmp + column.length()) = '\0';
        *value = str_tmp;
        return OK;
    }
}
