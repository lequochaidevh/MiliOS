#include "dummy.h"
#include <stdint.h>
#include "xprintf.h"

void entry_critical() { xprintf("[entry_critical]"); }

void exit_critical() { xprintf("[exit_critical]"); }

// 1. Khai báo mảng heap
static uint8_t fake_heap[64 * 1024];

// 2. Định nghĩa __heap_end__ là một con trỏ thay vì uint32_t
// (Hoặc dùng uintptr_t để an toàn về kích thước)
uintptr_t __heap_end__;

// 3. Tạo một hàm khởi tạo để gán giá trị khi chạy
void dummy_init(void) {
    __heap_end__ = (uintptr_t)(&fake_heap[0] + sizeof(fake_heap));
}