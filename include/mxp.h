// mxp.h - MXP (MUD eXtension Protocol) 支持
//
// 协商流程 (由驱动完成):
//   config.fluffos 里 enable mxp : 1  → 连接时驱动发 IAC DO 91 (MXP)
//   客户端回 IAC WILL 91 → 驱动置 USING_MXP 并调用玩家对象的 mxp_enable() apply
//   mudlib 用 has_mxp(ob) 判断客户端是否支持
//
// 注意: MXP 标记是带内文本, 直接 write()/tell_object() 输出即可, 不需要 telnet 子协商。
//       但必须只在 has_mxp() 为真时输出, 否则普通客户端会看到控制字符。
//
// 行模式参考 MXP v1.0 规范:
//   0=open 1=secure(到行尾) 2=locked(到行尾) 3=reset
//   4=temp secure(仅下一个标签) 5/6/7=锁定为 open/secure/locked 模式

#ifndef __MXP_H__
#define __MXP_H__

// ---- 行模式 (ESC [ n z) ----
#define MXP_OPEN_LINE    "[0z"
#define MXP_SECURE_LINE  "[1z"
#define MXP_LOCKED_LINE  "[2z"
#define MXP_RESET        "[3z"
#define MXP_TEMP_SECURE  "[4z"
#define MXP_LOCK_OPEN    "[5z"
#define MXP_LOCK_SECURE  "[6z"
#define MXP_LOCK_LOCKED  "[7z"

// ---- 自动地图行标签 ----
#define MXP_ROOMNAME_LINE "[10z"
#define MXP_ROOMDESC_LINE "[11z"
#define MXP_ROOMEXIT_LINE "[12z"

#endif
