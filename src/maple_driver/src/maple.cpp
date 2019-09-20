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
#include "compiler_factory.h"
#include "error_code.h"
#include "mpl_options.h"
#include "mpl_logging.h"
using namespace maple;
void PrintErrorMessage(int ret) {
  switch (ret) {
    case kErrorNoError:
    case kErrorExitHelp:
      break;
    case kErrorExit:
      ERR(kLncErr, "Error Exit!");
      break;
    case kErrorInvalidParameter:
      ERR(kLncErr, "Invalid Parameter!");
      break;
    case kErrorInitFail:
      ERR(kLncErr, "Init Fail!");
      break;
    case kErrorFileNotFound:
      ERR(kLncErr, "File Not Found!");
      break;
    case kErrorToolNotFound:
      ERR(kLncErr, "Tool Not Found!");
      break;
    case kErrorCompileFail:
      ERR(kLncErr, "Compile Fail!");
      break;
    case kErrorNotImplement:
      ERR(kLncErr, "Not Implement!");
      break;
    default:
      break;
  }
}

//main函数

/**
1、java2jar是类似于javac和jar的联合体，要将XXX.java文件编成XXX.class文件，然后打包成XXX.jar文件。
java2jar的内容也很简单：

#!/bin/bash
OUTPUT=$1
CORE_ALL_JAR=$2
shift 2
javac -g -d . -bootclasspath ${CORE_ALL_JAR} $@
jar -cvf ${OUTPUT} *.clas


2、jbc2mpl是将.class文件或者是.jar文件转化为mpl或mplt格式的一个工具。按照LLVM的分层习惯的话，
这就类似于LLVM的前端，将程序转化为中间层表示。

3、maple则是针对方舟编译器的中间表示语言的一个工具。方舟编译器的中间语言本身就叫maple。从maple的可选参数我们可以看
到，它主要是针对maple的一些操作，在maple之中还提供支持run jbc2mpl\me\mpl2mpl2\mplcg。

4.4、mplcg应该是支持对.mpl格式的输入文件，生成后端汇编代码的工具
*/

//函数入口地址
int main(int argc, char **argv) {
  MplOptions mplOptions;
  int ret = mplOptions.Parse(argc, argv);
  if (ret == ErrorCode::kErrorNoError) {
    ret = CompilerFactory::GetInstance().Compile(mplOptions);
  }
  PrintErrorMessage(ret);
  return ret;
}
