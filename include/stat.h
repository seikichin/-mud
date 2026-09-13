#ifndef __STAT_H__
#define __STAT_H__

// stat() 返回 ({ 档案大小, 最后修改时间, 该档物件编译时间, 建立时间 })
#define STAT_FILE_SIZE          0
#define STAT_LAST_MODIFIED      1
#define STAT_TIME_OBJECT_LOADED 2
#define STAT_TIME_FILE_CREATED  3

#endif // __STAT_H__
