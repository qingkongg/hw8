#include "../inc/TLB.h"

#include <stdlib.h>

unsigned global_TLB_init(void) {
  global_tlb = calloc(1, sizeof(TLB));
  return 0;
}

void global_TLB_free(void) {
  if (global_tlb == NULL) {
    return;
  }
  free(global_tlb);
  global_tlb = NULL;
}

unsigned read_TLB(proc_id_t pid, unsigned vpn) {
  // 遍历TLB条目
  for (int i = 0; i < TLB_SIZE; i++) {
    TLB_entry entry = global_tlb->entries[i];
    // 检查条目是否有效且匹配给定的pid和vpn
    if (entry.valid && entry.vpn == vpn && global_tlb->pid == pid) {
      // 更新最后使用时间
      entry.lut = ++global_tlb->clock;
      // 返回物理页号
      return entry.ppn;
    }
  }
  // 如果没有找到匹配的条目，返回TLB_MISS
  return TLB_MISS;
}


void write_TLB(proc_id_t pid, unsigned vpn, unsigned ppn) {
  if(pid){
    
  }
  int lru_index = -1;
  uint32_t min_lut = UINT32_MAX;

  // 遍历TLB条目以找到空闲条目或最久未使用的条目
  for (int i = 0; i < TLB_SIZE; i++) {
    if (!global_tlb->entries[i].valid) {
      // 找到空闲条目，直接使用
      lru_index = i;
      break;
    } 
    else if (global_tlb->entries[i].lut < min_lut) {
      // 更新最久未使用的条目信息
      min_lut = global_tlb->entries[i].lut;
      lru_index = i;
    }
  }

  // 如果所有条目都被占用，则使用最久未使用的条目
  if (lru_index == -1) {
    // 这种情况不应该发生，因为我们总是应该能找到一个条目
    // 但如果发生了，我们可以选择记录错误或其他处理方式
    return;
  }

  // 写入新的TLB条目
  global_tlb->entries[lru_index].vpn = vpn;
  global_tlb->entries[lru_index].ppn = ppn;
  global_tlb->entries[lru_index].valid = 1;
  global_tlb->entries[lru_index].lut = ++global_tlb->clock; // 更新最后使用时间
}

void remove_TLB(proc_id_t pid, unsigned vpn) {
// 遍历TLB查找匹配的条目
  for (int i = 0; i < TLB_SIZE; i++) {
    if (global_tlb->entries[i].valid && global_tlb->entries[i].vpn == vpn && global_tlb->pid == pid) {
    // 如果找到匹配的条目，将其标记为无效
    global_tlb->entries[i].valid = 0;
    // 可以选择重置其他字段，但在这个上下文中不是必需的
    break;  // 找到后即退出循环
    }
  }
}
