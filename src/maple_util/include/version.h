/*
 * Copyright (c) [2019] Huawei Technologies Co.,Ltd.All rights reserved.
 *
 * OpenArkCompiler is licensed under the Mulan PSL v1. 
 * You can use this software according to the terms and conditions of the Mulan PSL v1.
 * You may obtain a copy of Mulan PSL v1 at:
 *
 * 	http://license.coscl.org.cn/MulanPSL 
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
 * FIT FOR A PARTICULAR PURPOSE.  
 * See the Mulan PSL v1 for more details.  
 */
#ifndef MAPLE_UTIL_INCLUDE_VERSION_H
#define MAPLE_UTIL_INCLUDE_VERSION_H

namespace Version {
//变量声明为constexpr 表示由编译器来验证变量的值是否是一个常量表达式
static constexpr int kMajorMplVersion = 1;
static constexpr int kMinorCompilerVersion = 0;
static constexpr int kMinorRuntimeVersion = 0;

}

#endif
