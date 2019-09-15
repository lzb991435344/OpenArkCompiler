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
#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H
#include <list>
#include <set>
#include <stack>
#include <map>
#include <string>
#include "mir_config.h"
#include "mpl_logging.h"

namespace maple {

constexpr bool FALSE = false;
constexpr bool TRUE = true;

// Class declaration
class MemPool;

// Memory Pool controller class
class MemPoolCtrler {
  friend MemPool;

 public:  // Methods
  MemPoolCtrler() {}

  ~MemPoolCtrler();

  MemPool *NewMemPool(const std::string&);
  void DeleteMemPool(MemPool *memPool);
  bool IsEmpty() const {
    return memPools.empty();
  }

  unsigned GetMempoolSize() const {
    return memPools.size();
  }

 private:  // Methods
  struct MemBlock {
    unsigned int available;  // Available memory size
    unsigned int origSize;   // original size
    void *ptr;               // Current pointer to the first available position
  };


  class MemBlockCmp {
   public:
    bool operator()(const MemBlock *l, const MemBlock *r) const {
      if (l->available != r->available) {
        return l->available > r->available;
      } else {
        return (std::uint64_t)(l->ptr) > (std::uint64_t)(r->ptr);
      }
    }
  };

  // Free small/large size memory block list
  std::list<MemBlock*> freeMemBlocks;
  std::map<unsigned int, std::set<MemBlock*, MemBlockCmp>> largeFreeMemBlocks;
  std::set<MemPool*> memPools;  // set of mempools managed by it
};

class MemPool {
  friend MemPoolCtrler;

 public:  // Methods
 //带参的构造函数，进行初始化
  MemPool(MemPoolCtrler *ctl, const std::string &name) : ctrler(ctl), name(name) {
  }

  ~MemPool();
  void *Malloc(size_t size);
  void *Calloc(size_t size);
  void *Realloc(const void *ptr, size_t oldSize, size_t newSize);
  void Push();
  bool Pop();
  const std::string &GetName(void) const {
    return name;
  }

  template <class T>
  T *Clone(const T &t) {
    void *p = Malloc(sizeof(T));
    //调用拷贝构造函数进行对象的深拷贝
    p = new (p) T(t);  // Call clone constructor
    return static_cast<T*>(p);//指针转换
  }

  // New templates
  template <class T, typename... Arguments>
  T *New(Arguments &&... args) {
    void *p = Malloc(sizeof(T));
    p = new (p) T(std::forward<Arguments>(args)...);  // Call constructor
    return static_cast<T*>(p);
  }

  // New Array template
  template <class T>
  T *NewArray(unsigned int num) {

    //Malloc返回一个void*的指针
    void *p = Malloc(sizeof(T) * num);//申请一块连续的空间
    p = new (p) T[num]; //申请特定类型的数组
    //静态转换  static_cast 用于普通数据类型的转换
    return static_cast<T*>(p);
  }

#define BitsAlign(size) (((size) + 7) & (0xFFFFFFF8))
#define MemBlockFirstPtr(x) \
  static_cast<void*>((reinterpret_cast<char*>(x)) + BitsAlign(sizeof(MemPoolCtrler::MemBlock)))

 //基本的常量 
 private:                                         // constants

  //最小的内存块是2k  2^11
  static constexpr size_t kMinBlockSize = 0x800;  // Minimum BlockSize is 2K
  static constexpr size_t kMemBlockOverhead = (BitsAlign(sizeof(MemPoolCtrler::MemBlock)));

  //得到一个指向大块内存的指针
  MemPoolCtrler::MemBlock *GetLargeMemBlock(size_t size);  // Raw allocate large memory block
  MemPoolCtrler::MemBlock *GetMemBlock(size_t size);

  //指向内存管理类的指针对象
  MemPoolCtrler *ctrler;  // Hookup controller object
  std::string name;       // Name of the memory pool


  //使用栈来保存分配到的内存块
  // Save the memory block stack
  std::stack<MemPoolCtrler::MemBlock*> memBlockStack;
  std::stack<MemPoolCtrler::MemBlock*> largeMemBlockStack;


  // Save mem_block and large_mem_block pointers when push()
  //同样的类型，使用pair<>保存指针对象
  std::stack<std::pair<MemPoolCtrler::MemBlock*, MemPoolCtrler::MemBlock*>> markerStack;
};

extern MemPoolCtrler mempoolctrler;
}  // namespace maple
#endif
