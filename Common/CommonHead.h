#pragma once

// 最大的数据包大小，注意保护全部内容，比如自己定义的协议头
#define MAX_PACK_SIZE 2048

// 最大可接受的失败次数，超过这个整个连接视为断开
#define MAX_ERROR_COUNT 10
