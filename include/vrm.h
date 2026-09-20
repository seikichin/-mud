// vrm.h - 虚拟随机迷宫（Virtual Random Maze）公共宏定义
#ifndef __VRM_H__
#define __VRM_H__

// ---- 6 个基础方向（随机迷宫生成器只用这 6 个） ----
#define UP   32
#define D    16
#define N    8
#define S    4
#define W    2
#define E    1
#define ALL  63      // 6 向掩码（生成器候选位；勿改，改则随机迷宫地形变化）

// ---- 斜向 12 向（地图文件可表达；移动层/小地图本来就支持） ----
// 平面斜向
#define NE   64      // 东北 (+x,+y)
#define NW   128     // 西北 (-x,+y)
#define SE   256     // 东南 (+x,-y)
#define SW   512     // 西南 (-x,-y)
// 立体斜向（高处）
#define NU   1024    // 北边高处 (0,+y,+z)
#define SU   2048    // 南边高处 (0,-y,+z)
#define EU   4096    // 东边高处 (+x,0,+z)
#define WU   8192    // 西边高处 (-x,0,+z)
// 立体斜向（低处）
#define ND   16384   // 北边低处 (0,+y,-z)
#define SD   32768   // 南边低处 (0,-y,-z)
#define ED   65536   // 东边低处 (+x,0,-z)
#define WD   131072  // 西边低处 (-x,0,-z)

// 全部 18 个网格方向位（地图格值的合法性上限）
#define ALL_DIRS  262143

#define MAX_LONG     100
#define VALID_LEAVES 3

#endif
