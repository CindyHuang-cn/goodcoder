/*===============================================================
*   Copyright (C) 2015 Baidu.com, Inc. All rights reserved.
*   
*   文件名称：parse_user_type.h
*   创 建 者：chenchen36
*   创建日期：2015.12.25
*   描    述：解析用户自定义类型
*
*   更新日志：
*
================================================================*/
#ifndef GOODCODER_PARSE_USER_TYPE_H
#define GOODCODER_PARSE_USER_TYPE_H
#include <string>
#include <map>
#include <boost/any.hpp>
#include <boost/function.hpp>
#include "util.h"
#include <iostream>
namespace dp{
    template <typename T>class ParseUserType{
        public:
            typedef boost::function<void(const std::string, T*)> Func;
            ErrorCode parse_str_defined_type(const std::string str, T* result);
            void set_func_map(ParseUserType<T>::Func func);
            ErrorCode get_func_map(ParseUserType<T>::Func *func);

        private:
            static std::map<const std::string, boost::any> _s_func_map;
    };

    /**
     * @brief 解析用户定义的类型
     * @param string
     * @param T*
     * @return ErrorCode
     */
    template <typename T>
    ErrorCode ParseUserType<T>::parse_str_defined_type(const std::string str, T* result){
        Func func;
        ErrorCode error_code = get_func_map(&func);
        if (error_code != OK) {
            return error_code;	
        }
        func(str, result);
        return OK;
    }

    /**
     * @brief 注册用户自定义函数
     * @param ParseUserType<T>::Func
     * @return void
     */
    template <typename T>
    void ParseUserType<T>::set_func_map(ParseUserType<T>::Func func){
        const std::string key = typeid(T).name();
        _s_func_map[key] = func;	
    }

    /**
     * @brief 获取用户自定义函数 
     * @param ParseUserType<T>::Func
     * @return ErrorCode
     */
    template <typename T>
    ErrorCode ParseUserType<T>::get_func_map(ParseUserType<T>::Func *func){
        const std::string key = typeid(T).name();
        std::map<const std::string, boost::any>::iterator it = _s_func_map.find(key);
        if (it == _s_func_map.end()) {
            return TYPEMAP_NOT_FOUND;
        }
        typedef typename ParseUserType<T>::Func Key2Func;
        *func =  boost::any_cast<Key2Func>(it->second);
        return OK;
    } 

    /**
     * @brief 类静态函数初始化 
     */
    template <typename T>
    std::map<const std::string, boost::any> ParseUserType<T>::_s_func_map;
}
#endif
