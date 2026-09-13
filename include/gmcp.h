// gmcp.h - GMCP (Generic Mud Communication Protocol) 支持
//
// 驱动侧(FluffOS)已经替我们做完的部分:
//   config.fluffos:  enable gmcp : 1
//   连接时驱动发 IAC WILL 201(GMCP); 客户端回 IAC DO 201 之后:
//     * has_gmcp(ob) 变为真
//     * 驱动调用该连线对象的 gmcp_enable() apply
//   客户端发来的 GMCP 子协商内容, 驱动原样交给连线对象的 gmcp(string) apply。
//   mudlib 用 send_gmcp(string) 发送。
//
// 与 MXP 的区别(重要):
//   MXP 是带内文本, write()/tell_object() 即可;
//   GMCP 是 telnet 子协商, 必须走 send_gmcp(), 而且净荷必须是 JSON。
//   另: send_gmcp() 只能由"当前连线对象"自己调用, 详见 feature/gmcp.lpc。

#ifndef __GMCP_H__
#define __GMCP_H__

#define GMCP_TELOPT			201

// ---- 服务端标识与下发的 Core.Supports.Set ----

// Core.Hello 的 name 字段: 与 LDMud 风云 mudlib(feature/gmcp.c) 保持一致 ——
// 该字段是 MUD 名字符串(客户端据此识别本 MUD), 不是版本对象。
#define GMCP_MUD_NAME		"风云"

#define GMCP_SERVER_NAME	"FluffOS"
#define GMCP_SERVER_VERSION	"fy2005"

// 服务端声明支持的包(字符串数组, 元素格式 "Name Version")
#define GMCP_SERVER_SUPPORTS	({ "Core 1", "Char 1", "Char.Items 1", "Room 1", "Comm.Channel 1" })

// ---- 包 / 消息名 ----
#define GMCP_CORE			"Core"
#define GMCP_CORE_HELLO			"Core.Hello"
#define GMCP_CORE_PING			"Core.Ping"
#define GMCP_CORE_GOODBYE		"Core.Goodbye"
#define GMCP_CORE_SUPPORTS_SET		"Core.Supports.Set"
#define GMCP_CORE_SUPPORTS_ADD		"Core.Supports.Add"
#define GMCP_CORE_SUPPORTS_REMOVE	"Core.Supports.Remove"

#define GMCP_CHAR			"Char"
#define GMCP_CHAR_NAME			"Char.Name"
#define GMCP_CHAR_STATUS		"Char.Status"
#define GMCP_CHAR_STATUSVARS		"Char.StatusVars"
#define GMCP_CHAR_VITALS		"Char.Vitals"
#define GMCP_CHAR_STATS			"Char.Stats"

#define GMCP_CHAR_ITEMS			"Char.Items"
#define GMCP_CHAR_ITEMS_LIST		"Char.Items.List"

#define GMCP_ROOM			"Room"
#define GMCP_ROOM_INFO			"Room.Info"

#define GMCP_COMM			"Comm"
#define GMCP_COMM_CHANNEL_TEXT		"Comm.Channel.Text"

// ---- Char.Items.List 的 location 取值 ----
#define GMCP_LIST_INV			"inv"
#define GMCP_LIST_ROOM			"room"

// ---- Core.Supports.* 的更新模式 ----
#define GMCP_SUP_ADD			1
#define GMCP_SUP_SET			2
#define GMCP_SUP_REMOVE			3

// ---- 保护上限 ----
// 客户端单条 GMCP 的最大字节数(超过一律丢弃, 防止恶意客户端打爆)
#define GMCP_MAX_PAYLOAD		8192
// 每个会话最多记录多少条"未识别请求"日志
#define GMCP_MAX_UNHANDLED_LOG		20

#endif
