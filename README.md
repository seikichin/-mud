# 风云 2005 · FluffOS Mudlib

**风云 2005**（FY2005）是国内经典的中文 MUD 泥巴（mudlib），最初运行于 MudOS / LDMud 系驱动。
本仓库是它在 **[FluffOS](https://github.com/fluffos/fluffos)** 驱动上的移植与持续维护版本，
并在此基础上实现了 **MXP / GMCP** 客户端协议，使支持这些协议的现代客户端（如 Mudlet）
可以渲染富文本元素与状态栏。

> 游戏标题屏（`adm/etc/welcome`）：
> 「－　＝　风　云　２　０　０　５　＝　－　　＊国 内 经 典 版＊」

---

## 一、项目概况

| 项目 | 说明 |
|---|---|
| 名称 | 风云 2005（FY2005） |
| 类型 | 中文 LPC MUD mudlib（武侠题材） |
| 驱动 | FluffOS（LPC / MudOS 系驱动，按 LDMud 语法习惯移植） |
| 客户端 | 传统 ANSI 颜色 + telnet 协商 + **MXP** + **GMCP** |
| 编码 | 源码以 **UTF-8** 为主，部分历史档为 GBK；登录内码可选 `0) gbk` / `1) utf-8` |
| 规模 | 约 1.2 万个文件（其中 `d/` 世界区域 7100+） |

## 二、目录结构

```
adm/        管理区
  daemons/  常驻守护进程（logind / channeld / combatd / taskd / spawnd ...）
  etc/      preload 列表、spawn_table、welcome、festival 等数据表
  obj/      simul_efun、master 等特殊对象
cmds/       指令
  std/      通用指令（look / go / get / put ...）
  usr/      玩家指令（score / skills / task / hp ...）
  wiz/      巫师指令（goto / update / snoop ...）
  arch/     高级巫师指令
  adm/      管理员指令
  skill/    技能指令
daemon/     技能与门派逻辑（class/ 下按门派分层）
d/          世界区域（每个子目录一个区域）
obj/        通用物件、NPC、奖励物品
std/        标准对象基类（room / char / weapon / armor / item ...）
feature/    能力混入（damage / equip / save / gmcp / mxp ...）
include/    头文件（globals.h / ansi.h / gmcp.h / mxp.h ...）
p/          住宅区（玩家自建房间模板）
quest/      任务数据
questnpc/   悬赏 NPC
questobj/   任务物品
doc/        帮助文档（help / wiz / questdoc）
data/       运行期玩家数据（多数不入库，见 .gitignore）
log/        运行日志（不入库）
```

## 三、构建与运行

1. 获取并编译 FluffOS（本仓库**不含**驱动二进制）

   ```sh
   git clone https://github.com/fluffos/fluffos.git
   cd fluffos
   cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo
   ninja -C build
   ```

2. 准备运行配置（复制驱动自带的 `config`），至少修改两处

   ```
   mudlib directory : /path/to/this/mudlib     # 绝对路径
   port number : 6666
   ```

3. 启动

   ```sh
   cd <fluffos bin dir>
   ./driver /path/to/config.fluffos
   ```

> 本仓库的日常运维采用 `/home/fluffos/mudlib/{play,work}` 双树布局：
> `play/` 为生产运行目录，`work/` 为 git 工作副本。

## 四、相对原版的改动

- **驱动移植**：MudOS / LDMud → FluffOS（对象创建、`#include` 路径、类型测试、
  `sprintf` 宽度语义、`promise` / `FFI` 等差异）
- **客户端协议**：实现 MXP 元素定义与 GMCP（`Core.Hello` 等），
  并修复「重连线后 MXP 定义不再下发导致标签退化为普通文本」的问题
- **兼容性修复**：数据表中裸 `.c` 引用、房间存档路径、死链清理、全库编译零错误等
- **显示对齐修复**：全库框线字符由「东亚模糊宽度」字符（`─ ═ │ ║` 等，在 UTF-8 客户端
  只占 1 列）替换为全角等价字符（`一 ＝ ｜ 「 」`），使 UTF-8 与 GBK 客户端下表格一致对齐

## 五、编码约定（贡献须知）

- 新增 / 修改的 `.lpc` 请使用 **UTF-8（无 BOM）**
- 玩家可见文本中的框线与分隔符请使用**全角字符**（`＝ 一 ｜ 「 」`），
  不要使用 `─ ═ │ ║`、`◆ ◎` 等 EAW = Ambiguous 的字符（会破坏行宽对齐）
- `sprintf("%-*s")` 的宽度按**屏幕显示列**计算，且**自动忽略 ANSI 颜色码**，
  因此**不要**再手工补偿颜色码长度（旧的 MudOS 写法会导致行宽浮动）
- 运行期玩家数据（`data/`、`p/residence/userroom/`、`log/`）不入库，见 `.gitignore`

## 六、致谢与版权

- 原始 mudlib：风云 2005 —— FengYun Workshop（Copyright (C) 1995–2005）
- FluffOS 移植与后续维护：见本仓库 git 提交历史

> 本仓库为**非官方整理 / 移植副本**，原作者保留其权利。
> 如涉及版权问题，请联系仓库维护者。