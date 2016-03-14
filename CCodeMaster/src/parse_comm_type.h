/*===============================================================
*   Copyright (C) 2015 Baidu.com, Inc. All rights reserved.
*   
*   文件名称：parse_comm_type.h
*   创 建 者：chenchen36
*   创建日期：2015.12.23
*   描    述：解析内置类型
*
*   更新日志：
*
================================================================*/
#ifndef GOOGCODER_PARSE_COMM_TYPE_H
#define GOOGCODER_PARSE_COMM_TYPE_H
#include <string>
#include <sstream>
#include <vector>
#include "util.h"
namespace dp{
    template <typename T> class ParseCommType{
        public :
        void parse_str_defined_type(const std::string str, T* result);
        void parse_str_defined_type(const std::string str, T** result, size_t* count);
    };

    /**
     * @brief 解析内置类型
     * @param string
     * @param T*
     * @return void
     */
    template <typename T>
    void ParseCommType<T>::parse_str_defined_type(const std::string str, T* result){
        std::stringstream stream;
        stream << str;
        stream >> *result;
    }

    /**
     * @brief 解析内置类型bulid-in T[num]
     * @param string
     * @param T**
     * @param size_t*
     * @return void
     */
    template <typename T>
    void ParseCommType<T>::parse_str_defined_type(const std::string str, T** result, size_t* count){
        std::vector<T> vec;
        Util::split_string<T>(str, ",", &vec);
        *count = vec.size();
        T* result_tmp = new T[*count];
        std::copy(vec.begin(), vec.end(), result_tmp);
        *result = result_tmp;
    }
}
#endif
