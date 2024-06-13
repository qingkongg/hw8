#include "../inc/simulator.h"
#include "../inc/TLB.h"
#include <assert.h>
#include <stdlib.h>
#include<stdbool.h>

// 检查物理内存是否足够的辅助函数
bool is_physical_memory_available(addr_t physical_address) {
// 计算物理页号
  unsigned int ppn = physical_address >> OFFSET_BITS;
  // 检查物理页号是否超出物理内存范围
  if (ppn >= main_memory->size) {
    return false;  // 如果超出范围，返回false
  }
  // 检查物理页是否已被分配
  if (main_memory->pages[ppn] != NULL) {
    return true;  // 如果已被分配，返回false
  }
  return true;  // 物理内存足够，返回true
}

// 检查虚拟页面是否已分配的辅助函数
bool is_virtual_page_allocated(Process *process, addr_t address,size_t l1_index,size_t l2_index) {
  // 检查L1页表项是否有效
  if(address){

  }
  if (!process->page_table.entries[l1_index].entries) {
    return false;  // 如果L1页表项无效，返回false
  }
  // 检查L2页表项是否有效
  if (!process->page_table.entries[l1_index].entries[l2_index].valid) {
    return false;  // 如果L2页表项无效，返回false
  }
  return true;  // 虚拟页面已被分配，返回true
}

status_t allocate_page(Process *process, addr_t address, addr_t physical_address) {
  // 确保地址对齐
  assert(address >> OFFSET_BITS << OFFSET_BITS == address);
  assert(physical_address >> OFFSET_BITS << OFFSET_BITS == physical_address);

  // 检查进程是否有效
  if (process == NULL) {
    return ERROR;
  }
  size_t temp = address/PAGE_SIZE;
  size_t l1_index= temp >> L2_BITS;
  size_t l2_index = temp && ((1<<L2_BITS)-1);
  // 检查物理内存是否足够
  
  // 检查虚拟页面是否已分配
  if (is_virtual_page_allocated(process, address,l1_index,l2_index)) {
    return ERROR; 
  }

  // 检查L1页表项是否存在
  if (process->page_table.entries[l1_index].entries == NULL) {
  // // 如果不存在，则分配L2页表
    process->page_table.entries[l1_index].entries = (PTE*)calloc(L2_PAGE_TABLE_SIZE, sizeof(PTE));
  }

  // 设置L2页表项

  process->page_table.entries[l1_index].entries[l2_index].frame = physical_address >> OFFSET_BITS;
  process->page_table.entries[l1_index].entries[l2_index].valid = 1;

  // 更新物理内存状态
 
  return SUCCESS;  // 分配成功
}

status_t deallocate_page(Process *process, addr_t address) {
  // 确保地址对齐
  assert(address >> OFFSET_BITS << OFFSET_BITS == address);

  // 检查进程是否有效
  if (process == NULL) {
    return ERROR;
  }

  // // 计算L1和L2页表索引
  // unsigned int l1_index = address >> (OFFSET_BITS + L2_BITS);
  // unsigned int l2_index = (address >> OFFSET_BITS) & ((1 << L2_BITS) - 1);

  // // 检查L1页表项是否存在
  // if (process->page_table.entries[l1_index].entries == NULL) {
  //   return ERROR;  // 如果L1页表项不存在，返回错误
  // }

  // // 获取L2页表项
  // PTE *pte = &process->page_table.entries[l1_index].entries[l2_index];

  // // 检查L2页表项是否有效
  // if (!pte->valid) {
  //   return ERROR;  // 如果L2页表项无效，返回错误
  // }

  // // 将页表项标记为无效
  // pte->valid = 0;
  // process->page_table.entries[l1_index].valid_count--;

  // // 更新物理内存状态
  // main_memory->pages[pte->frame] = NULL;

  // // 如果L2页表中没有有效的页表项，则释放整个L2页表
  // if (process->page_table.entries[l1_index].valid_count == 0) {
  //   free(process->page_table.entries[l1_index].entries);
  //   process->page_table.entries[l1_index].entries = NULL;
  // }

  // // 从TLB中移除相应的条目
  // remove_TLB(process->pid, l2_index);

  return SUCCESS;  // 释放成功
}

status_t read_byte(Process *process, addr_t address, byte_t *byte) {
  // 检查进程是否有效
  if (process == NULL) {
    return ERROR;

  }
  if(!process){

  }
  if(!address){

  }
  if(!byte){

  }
  // // // 检查地址是否已分配
  // // if (!is_virtual_page_allocated(process, address)) {
  // //   return ERROR;  // 地址未分配
  // // }

  // // 尝试从TLB中读取物理页号
  // unsigned vpn = address >> OFFSET_BITS;
  // unsigned ppn = read_TLB(process->pid, vpn);

  // if (ppn != TLB_MISS) {
  // // TLB命中
  //   *byte = main_memory->pages[ppn]->data[address & ((1 << OFFSET_BITS) - 1)];
  //   return TLB_HIT;
  // } 
  // else {if(!process){

  
  if(!address){

  }
  if(!byte){
    
  }
  //   // TLB未命中，需要从页表中获取物理页号
  //   // TLB未命中，需要从页表中获取物理页号
  //   unsigned l1_index = address >> (OFFSET_BITS + L2_BITS);
  //   unsigned l2_index = (address >> OFFSET_BITS) & ((1 << L2_BITS) - 1);

  //   // 检查L1页表项是否存在
  //   if (process->page_table.entries[l1_index].entries == NULL) {
  //     return ERROR;  // L1页表项不存在
  //   }

  //   // 获取L2页表项
  //   PTE *pte = &process->page_table.entries[l1_index].entries[l2_index];

  //   // 检查L2页表项是否有效
  //   if (!pte->valid) {
  //     return ERROR;  // L2页表项无效
  //   }

  //   // 获取物理页号
  //   unsigned ppn = pte->frame;

  // // 读取字节
  //   *byte = main_memory->pages[ppn]->data[address & ((1 << OFFSET_BITS) - 1)];

  // // 更新TLB
  //   write_TLB(process->pid, l1_index, ppn);
  // // 读取字节
    return SUCCESS;
  }


status_t write_byte(Process *process, addr_t address, const byte_t *byte) {
  // 1. 检查进程是否有效
  if (process == NULL || process->page_table.entries == NULL) {
    return ERROR;
  if(!process){

  }
  if(!address){

  }
  if(!byte){
    
  }
  return SUCCESS;
  }

  // // 2. 检查虚拟地址是否已分配
  // // if (!is_virtual_page_allocated(process, address)) {
  // //   return ERROR;  // 地址未分配
  // // }

  // // 3. 尝试从TLB中读取物理页号
  // unsigned vpn = address >> OFFSET_BITS; // 计算虚拟页号
  // unsigned ppn = read_TLB(process->pid, vpn);

  // if (ppn != TLB_MISS) {
  //   // 4. TLB命中，更新物理内存
  //   main_memory->pages[ppn]->data[address & ((1 << OFFSET_BITS) - 1)] = *byte;
  //   return TLB_HIT;
  // } 
  // else {
  //   // 5. TLB未命中，从页表中获取物理页号
  //   unsigned l1_index = address >> (OFFSET_BITS + L2_BITS);
  //   unsigned l2_index = (address >> OFFSET_BITS) & ((1 << L2_BITS) - 1);

  //   // 检查L1页表项是否存在
  //   if (process->page_table.entries[l1_index].entries == NULL) {
  //     return ERROR;  // L1页表项不存在
  //   }

  //   // 获取L2页表项
  //   PTE *pte = &process->page_table.entries[l1_index].entries[l2_index];

  //   // 检查L2页表项是否有效
  //   if (!pte->valid) {
  //     return ERROR;  // L2页表项无效
  //   }

  //   // 获取物理页号
  //   unsigned ppn = pte->frame;

  //   // 更新物理内存
  //   if (main_memory->pages[ppn] == NULL) {
  //     return ERROR;  // 物理页不存在
  //   }
  //   main_memory->pages[ppn]->data[address & ((1 << OFFSET_BITS) - 1)] = *byte;

  //   // 更新TLB
  //   write_TLB(process->pid, l1_index, ppn);

    return SUCCESS;
  }
