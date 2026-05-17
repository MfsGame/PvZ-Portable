# PvZ-Portable
<div align="center">
  <img src="icon-readme.png" alt="PvZ-Portable" width="450">
</div>

[![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/wszqkzqk/PvZ-Portable)
一款由社区驱动、**跨平台**的《植物大战僵尸：年度版》重实现项目，旨在为全平台带来**100%原汁原味**的游戏体验。

| 🌿 原汁原味 | 🎮 便携运行 | 🛠️ 开源开放 |
| :---: | :---: | :---: |
| 近乎100%还原游戏玩法 | 支持32/64位系统<br>可运行于 Linux、Windows、macOS、Android、iOS、WebAssembly、Switch 等平台 | 基于 OpenGL ES 2.0 & SDL |

🌐 **不想安装？** [直接在浏览器游玩！](https://wszqkzqk.github.io/pvz-portable-wasm/pvz-portable.html)（仍需自备正版游戏资源文件）

**⚠️ 重要提示：**
- 本仓库**不包含**任何由 PopCap Games 或 Electronic Arts 持有版权的游戏资源（如图像、音乐、字体等）。用户必须从**合法购买**的《植物大战僵尸：年度版》中自行获取 `main.pak` 和 `properties/` 文件夹。
- 本项目代码基于社区研究成果（如[植物大战僵尸吧](https://tieba.baidu.com/f?ie=utf-8&kw=%E6%A4%8D%E7%89%A9%E5%A4%A7%E6%88%98%E5%83%B5%E5%B0%B8)、[PVZ Wiki](https://wiki.pvz1.com/doku.php?id=home)、[PvZ Tools](https://pvz.tools/memory/)）**手动重写实现**。作者（wszqkzqk）**从未对原版程序进行逆向工程**，仅基于公开资料与游戏测试编写；**直接通过逆向工程生成的代码不会被接受**。
- 本项目仅用于**教育目的**，专注于**跨平台移植技术**、引擎现代化，以及学习如何将经典游戏逻辑适配到各类硬件架构（如 Nintendo Switch、3DS）。
- **非商用**：本项目与 PopCap Games、Electronic Arts 无任何关联，未获授权、认证或支持。
- 项目图标与平台标识由作者（wszqkzqk）借助 AI 绘图工具制作，**并非 PopCap/EA 官方资源**。
- 使用本项目进行游戏，**必须**通过 [EA 官网](https://www.ea.com/games/plants-vs-zombies/plants-vs-zombies) 或 [Steam](https://store.steampowered.com/app/3590/Plants_vs_Zombies_GOTY_Edition/) 购买正版以获取原始游戏文件。

## 功能特性
- [x] 基于 SDL + OpenGL ES 2.0 渲染（桌面端兼容 OpenGL 2.1）
  - 支持**窗口自由缩放**，原版游戏无法实现
  - **为何使用 OpenGL ES 2.0？** GLES 2.0 是几乎所有现代 GPU API 的通用子集，所有支持 OpenGL 2.1+ 的桌面驱动、手机 GPU、游戏主机均原生支持，可实现**开箱即用、跨平台无额外依赖**。必要时可通过 [ANGLE](https://chromium.googlesource.com/angle/angle) 翻译为 DirectX/Metal/Vulkan。
- [x] 基于 [SDL Mixer X](https://github.com/WohlSoft/SDL-Mixer-X) 实现跨平台音频系统
  - 项目使用 SDL Mixer X 分支版本，通过 libopenmpt 支持 MO3 格式，分支位于 SexyAppFramework/sound/SDL-Mixer-X
- [x] 为内存受限的主机平台关闭缓存以节省内存
- [x] **兼容**原版 PvZ 年度版的**全局用户存档**（存档信息、冒险进度、金币、禅境花园等，存储于 `user*.dat`）
  - [x] 修复 2038 年问题，同时保持兼容
- [x] 支持便携的关卡中途存档格式 `.v4`（可在 Windows、Linux、macOS、Android、Switch 等平台**互通关卡进度**）
  - [x] 支持 `.v4` 存档与人类可读的 YAML 格式互转，方便编辑
- [x] 使用 `std::thread` 实现跨平台线程
- [x] 使用 `std::filesystem` 实现跨平台文件系统
- [x] 程序内部统一使用 UTF-8 编码
- [x] **多语言支持**：支持官方年度版各语言资源，包括**中文、德语、西班牙语、法语、意大利语**
- [x] 支持 32/64 位编译
- [x] 支持多种 CPU 架构（i686、x86_64、aarch64、riscv64、loongarch64 等）
- [x] 全平台支持 Unicode 路径
- [x] 支持大小端字节序
  - [x] 跨字节序存档兼容
  - 理论支持大端平台，因缺乏硬件未实测

本项目支持以下平台（不限于）：

| 平台 | 资源路径 | 运行状态 |
| :--- | :--- | :--- |
| Linux | 程序目录（资源）；用户应用数据目录（可写文件） | 正常运行 |
| Windows | 程序目录（资源）；用户应用数据目录（可写文件） | 正常运行 |
| macOS | 程序目录（资源）；用户应用数据目录（可写文件） | 正常运行 |
| BSD 系列 | 程序目录（资源）；用户应用数据目录（可写文件） | 正常运行（至少 FreeBSD 已验证） |
| Haiku | 程序目录（资源）；用户应用数据目录（可写文件） | 部分可用：无音乐 |
| Android | `Android/data/io.github.wszqkzqk.pvzportable/files/` | 正常运行 |
| iOS / iPadOS | 应用文档目录（文件 App 中可见） | 正常运行（仅侧载；未签名 IPA） |
| 网页版（WASM） | 浏览器 IndexedDB（存档）；运行时上传资源 | 正常运行（需 HTTP 服务器） |
| Nintendo Switch | sdmc:/switch/PvZPortable | 实机正常运行；Kenji‑NX 启动崩溃 |
| Nintendo 3DS | sdmc:/3ds/PvZPortable | 老 3DS 内存不足，新 3DS 勉强运行（已停更） |

## 游玩准备
你需要 PvZ 年度版的游戏数据：将 `main.pak` 和 `properties/` 文件夹放在 `pvz-portable` 可执行文件**同级目录**（游戏会按程序所在路径搜索资源）。也可使用解压后的资源文件替代 `main.pak`。

### 可写数据与缓存说明
- 游戏默认从程序目录读取资源（`main.pak`、`properties/`），可在任意工作目录启动程序，仍能正常加载资源。
- 用户可写文件（设置、存档、编译缓存、截图）存储在**系统推荐的应用数据路径**，当前版本路径为 `io.github.wszqkzqk/PvZPortable`，包含子目录：
  - `userdata/` — 玩家存档
  - `cache64/`（64 位）/`cache32/`（32 位） — 编译后的二进制缓存（动画/定义）；属于**本地启动缓存**，非便携文件；校验失败时游戏会自动重新编译。
  - `registry.regemu` — 模拟注册表/设置存储

### 常见系统路径示例
- Linux：`~/.local/share/io.github.wszqkzqk/PvZPortable/`
- Windows：`%APPDATA%\io.github.wszqkzqk\PvZPortable\`
- macOS：`~/Library/Application Support/io.github.wszqkzqk/PvZPortable/`

### 自定义路径（命令行参数）
- `-resdir="<路径>"`：设置**资源目录**（存放 `main.pak` 和 `properties/`），仅影响资源读取，不影响存档位置。
- `-savedir="<路径>"`：设置**存档目录**（存放设置、存档、缓存、截图），覆盖系统默认路径。

**注意**：必须用 `-参数="路径"` 格式，**不支持**空格分隔（如 `-resdir 路径`）。

## 安卓版专用说明
从 [Releases](https://github.com/wszqkzqk/PvZ-Portable/releases) 下载 APK，或自行编译。本项目**不含任何游戏资源**，需从**正版《植物大战僵尸：年度版》**导入资源。

### 首次启动
1. **安装 APK**（可能需要开启“未知来源安装”）。
2. **启动应用** — 未检测到资源时，会自动进入**资源导入界面**。
3. **导入游戏资源**，二选一：
   - 包含 `main.pak` 和 `properties/` 的**ZIP 包**（可在根目录或一级子目录，如 `PvZ/main.pak`）。
   - 直接包含 `main.pak` 和 `properties/` 的**文件夹**，或一级子目录包含。
4. 导入成功后点击 **Start Game** 开始游戏。

### 后续管理数据
在桌面长按应用图标，打开 **Manage Data** 快捷入口，可重新导入资源、导出/导入存档。

### 注意事项
- 要求 Android 9.0+；预编译 APK 仅支持 arm64‑v8a，可自行编译其他架构。
- 所有数据存于 `Android/data/io.github.wszqkzqk.pvzportable/files/`，无需额外存储权限，采用系统**存储访问框架（SAF）**。
- 存档可与桌面版互通。
- 安卓移植属于跨平台研究项目，保留原版 4:3 比例与鼠标操作逻辑；**未做触屏专属 UI 优化**，SDL2 自动将触屏映射为鼠标操作，可玩但非移动端友好设计。

## iOS / iPadOS 专用说明
从 [Releases](https://github.com/wszqkzqk/PvZ-Portable/releases) 下载未签名 IPA，或用 `ios/build-ios.sh` 自行编译。IPA 必须**侧载安装**，常用工具：[AltStore](https://altstore.io/)、[TrollStore](https://github.com/opa334/TrollStore)，或用免费 Apple ID 从 Xcode 直接部署。

### 导入游戏资源
应用的文档目录通过 iTunes/Finder 文件共享和 iOS 文件 App 开放（`UIFileSharingEnabled`）。将 `main.pak` 和 `properties/` 直接放入应用文档目录（文件 App 中显示为“PvZ Portable”）。

### 注意事项
- 要求 iOS 15.0+（arm64）。
- 免费 Apple ID 签名 7 天过期；TrollStore 安装永久有效。
- 触屏映射鼠标、画面比例逻辑与安卓版一致。

## 浏览器版（WebAssembly）
**[在线试玩](https://wszqkzqk.github.io/pvz-portable-wasm/pvz-portable.html)** — 打开链接，加载你正版拥有的游戏资源（ZIP 包或 `main.pak` + `properties/` 文件夹），点击 **Start Game** 即可。所有文件仅在本地浏览器处理，**不会上传到任何服务器**（托管页面为纯静态）。存档保存在浏览器 IndexedDB，可通过界面按钮导入/导出为 ZIP。

你也可以 [下载 WASM 构建包](https://github.com/wszqkzqk/PvZ-Portable/releases) 自行搭建服务。注意：HTML 文件必须通过 HTTP 访问（如 `python3 -m http.server`），直接本地打开会因浏览器安全限制无法运行。

## 游戏版本兼容性
本项目针对《植物大战僵尸》**年度版 1.2.0.1073 英文版**（独立 PopCap 发行版）设计与测试。**非英文年度版**（1.2.0.1093 德/西/法/意 或 1.1.0.1056 中文基于 1.2.0.1073）与 **Steam 年度版 1.2.0.1096** 均可完整游玩，所有游戏机制正常运行。唯一差异是不同版本字符串键名改动导致的轻微界面文本显示问题，用户可通过自定义 `properties/default.xml` 轻松修复。

**推荐**：使用 **1.2.0.1073 英文版** 资源包，体验最佳、开箱即用。

<details>
<summary>非 1.2.0.1073 英文版资源的已知显示差异（点击展开）</summary>

| 问题（仅非 1.2.0.1073 英文版） | 原因 |
| :---: | :---: |
| **图鉴蓝色描述文字缺失** | 1.2.0.1096 中将纯文本介绍段落从 `[XXX_DESCRIPTION]` 拆分到新键 `[XXX_DESCRIPTION_HEADER]`，引擎只读取 `[XXX_DESCRIPTION]`，因此标题不显示。 |
| **“Restart”按钮文字缺失** | 1.2.0.1096 中将键 `[RESTART_LEVEL]` 重命名为 `[RESTART_LEVEL_BUTTON]`。 |
| **未遇到的僵尸显示 `???`** 而非 `(not encountered yet)` | 1.2.0.1096 中将 `[NOT_ENCOUNTERED_YET]` 值改为 `???`，原文本移至新键 `[NOT_ENCOUNTERED_YET_DESCRIPTION]`。 |
| **疯狂戴夫植物售价显示为正确价格的 1/10** | 1.2.0.1073 中 `[CRAZY_DAVE_1700]` 模板在 `{SELL_PRICE}` 后带一个 `0`（即 `${SELL_PRICE}0`），因为引擎传入价格已除以 10。1.2.0.1096 移除了末尾的 0，导致显示为 1/10。 |
</details>

所有问题均可通过在游戏资源旁添加缺失或修正的字符串到 `properties/default.xml` 解决。

## 多语言支持
PvZ‑Portable 支持《植物大战僵尸》**年度版非英文**官方游戏资源。引擎可处理带 BOM 的文本文件，并将旧版 Windows‑1252 编码转为 UTF‑8，因此本地化文件可正确加载。若游戏资源中存在 `properties/default.xml` 和/或 `properties/Layout.xml`，会在 `LawnStrings.txt` 之后加载，并可覆盖任意字符串。这两个文件均为可选，不存在时使用内置英文默认值。

由于 `default.xml` 优先级高于 `LawnStrings.txt`，用户也可**创建或编辑 `properties/default.xml`** 来添加或覆盖任意字符串键，无需修改引擎即可轻松修复版本相关显示问题。

## 依赖项
PC 端编译前，请确保安装所需依赖：
- **构建工具**：`CMake`、`Ninja`、支持 C++20 的 C/C++ 编译器（如 `gcc`、`clang`、`MSVC`）（同时需要支持 C++20 的标准库，如 `libstdc++`、`libc++` 或 MSVC STL）
- **图形**：`OpenGL ES 2.0` 或 `OpenGL 2.1+`（运行时通过 SDL2 自动检测）
- **音频**：`libopenmpt`、`libogg`、`libvorbis`、`mpg123`
- **图像**：`libpng`、`libjpeg‑turbo`
- **窗口/输入**：`SDL2`

### Arch Linux
```bash
sudo pacman -S --needed base-devel cmake libjpeg-turbo libogg libopenmpt libpng libvorbis mpg123 ninja sdl2-compat
 
 
Debian/Ubuntu
 
bash
  
sudo apt install cmake ninja-build libogg-dev libjpeg-dev libopenmpt-dev libpng-dev libvorbis-dev libmpg123-dev libsdl2-dev
 
 
Windows (MSYS2 UCRT64)
 
bash
  
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-libjpeg-turbo mingw-w64-ucrt-x86_64-libopenmpt mingw-w64-ucrt-x86_64-libogg mingw-w64-ucrt-x86_64-libpng mingw-w64-ucrt-x86_64-libvorbis mingw-w64-ucrt-x86_64-mpg123 mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-SDL2
 
 
macOS (Homebrew)
 
bash
  
brew install cmake dylibbundler jpeg-turbo libogg libopenmpt libpng libvorbis mpg123 ninja sdl2
 
 
编译说明
 
在  CMakeLists.txt  所在目录运行以下命令（已安装 CMake 等依赖）：
 
bash
  
cmake -G Ninja -B build
 
 
bash
  
cmake --build build
 
 
性能优化
 
推荐使用 Release 构建类型以获得最佳性能，会自动开启编译器优化：
 
bash
  
cmake -G Ninja -B build -DCMAKE_BUILD_TYPE=Release
 
 
高级用户可指定  CFLAGS / CXXFLAGS  开启架构专属优化（如  -march=native  充分利用 CPU 指令集）：
 
bash
  
cmake -G Ninja -B build -DCMAKE_C_FLAGS="-march=native" -DCMAKE_CXX_FLAGS="-march=native" -DCMAKE_BUILD_TYPE=Release
 
 
配置选项
 
可在第一条  cmake  命令中添加选项自定义功能：
 
选项 默认值 说明 
 PVZ_DEBUG   OFF （ Debug  模式下为  ON ） 开启作弊键、调试显示等调试功能 
 LIMBO_PAGE   ON  开启隐藏关卡页面（Limbo Page） 
 DO_FIX_BUGS   OFF  应用社区修复官方 1.2.0.1073 年度版的“bug”；但很多玩家把这些“bug”当“特性” 
 CONSOLE   OFF （ Debug  模式下为  ON ） 显示控制台窗口（仅 Windows） 
 BUILD_STATIC   OFF  静态链接生成单文件可执行程序（仅 Windows MinGW 工具链；MSVC 请用 vcpkg‑static 套件） 
 
当前  DO_FIX_BUGS  包含修复：
 
- 修复 I, Zombie 模式下蹦极僵尸重复掉落阳光/物品
- 修复被魅惑的巨人僵尸攻击植物改为攻击僵尸
- 修复被魅惑的巨人投掷被魅惑的小鬼（尺寸、血量、方向修正）
- 修复被魅惑的巨人在花瓶破碎者模式可打碎花瓶
- 修复被魅惑的豌豆/机枪僵尸向前射击而非向后
- 修复被魅惑的火爆辣椒/窝瓜僵尸伤害僵尸而非植物
- 修复被魅惑的窝瓜僵尸追踪与砸击坐标
- 修复被魅惑的辣椒僵尸正确清除僵王技能（冰球/火球）与梯子逻辑
- 同步舞者僵尸动画（修复“女仆”位移 bug）
- 修复扶梯僵尸手臂恢复显示异常
- 修复僵王攻击（小车、火球/冰球）与 6 行（泳池）关卡生成范围
 
示例：在 Release 构建中手动开启  PVZ_DEBUG ，可在高性能下使用作弊键：
 
bash
  
cmake -G Ninja -B build -DCMAKE_BUILD_TYPE=Release -DPVZ_DEBUG=ON
 
 
若命令无法成功构建，请提交 Issue 并详细说明问题。
 
存档兼容性（全局存档与关卡中途存档）
 
PvZ‑Portable 使用两类完全不同的存档：
 
1. 全局用户存档（ users.dat 、 user1.dat  等）- 存储档案信息、冒险进度、金币、禅境花园等
- 与原版 PC 游戏格式完全兼容
- 设计上本身就是可移植的（显式序列化）
2. 关卡中途存档（ game1_0.v4  等；旧版  game1_0.dat  等）- 存储“保存并退出”时的关卡完整状态（僵尸、子弹、植物等）
- 游戏默认只写入  *.v4  文件：-  *.v4 ：可移植格式，支持在不同平台间共享进度
-  *.dat ：旧版内存裸数据，不可跨平台共享，会因架构差异崩溃
- 加载时优先使用  .v4 ； *.dat  仅用于迁移兼容
- 若从旧版  *.dat  加载，游戏会自动重新保存为  .v4 ，迁移成功后删除旧  *.dat 
 
为何需要新的中途存档格式？
 
原版游戏中途存档（ .dat ）是直接将内存结构写入磁盘，速度快但脆弱，依赖特定内存布局，在以下情况会失效：
 
- 不同 CPU 架构：x86、ARM、RISC‑V、龙芯（对齐）
- 32 位 vs 64 位：指针大小与结构体布局不同
- 不同编译器：MSVC vs GCC/Clang（填充、枚举大小、打包）
 
因此旧存档通常无法跨平台/架构/编译器加载。v4 格式使用 TLV（类型‑长度‑值）标签逐字段序列化，确保在 x86_64 Linux 保存的关卡可在龙芯、ARM（Switch）等平台正常加载不崩溃。
 
v4 格式开发者规范
 
- 新字段用新 TLV ID，不重复使用
- 加载旧存档时为缺失字段保留默认值
- 对可能改变布局的数据避免裸结构转储，优先使用显式逐字段同步与固定宽度基本类型
 
存档编辑与转换工具
 
提供 Python 脚本  scripts/pvzp‑v4‑converter.py  用于查看与修改  .v4  存档文件。
 
功能：
 
- info：查看存档基本信息（波数、阳光、僵尸数量等）
- export：将二进制  .v4  转为可读 YAML 方便编辑
- import：将修改后的 YAML 转回  .v4  并生成正确校验值
 
使用示例：
 
bash
  
# 查看基本信息
python scripts/pvzp-v4-converter.py info ~/.local/io.github.wszqkzqk/PvZPortable/userdata/game1_13.v4

# 导出为 YAML 编辑
python scripts/pvzp-v4-converter.py export ~/.local/io.github.wszqkzqk/PvZPortable/userdata/game1_13.v4 level.yaml

# 从 YAML 导回存档（先备份原文件！）
mv ~/.local/io.github.wszqkzqk/PvZPortable/userdata/game1_13.v4 ~/.local/io.github.wszqkzqk/PvZPortable/userdata/game1_13.v4.bak
python scripts/pvzp-v4-converter.py import level.yaml ~/.local/io.github.wszqkzqk/PvZPortable/userdata/game1_13.v4
 
 
贡献指南
 
贡献代码请遵循以下规范：SexyAppFramework 编码哲学 本框架与许多其他 API 的区别在于：部分类属性不使用访问器封装，而是直接以公有成员暴露使用。例如应用窗口标题可在创建窗口前直接给应用对象的 `std::string mTitle` 赋值。我们认为这在很多场景下能减少实现类所需代码。变量前缀规范：
 
-  m ：类成员变量
-  the ：方法/函数参数
-  a ：局部变量开源协议
 
Copyright (C) 2026 Zhou Qiankang wszqkzqk@qq.com
 
本项目基于 GNU Lesser General Public License v3.0 或更高版本（LGPL-3.0-or-later）开源。
 
- 仓库根目录包含完整协议文本：-  LICENSE  — LGPL-3.0 正文
-  COPYING  — GPL-3.0 正文（LGPL 引用）
- 代码以“原样”提供，无任何明示或暗示担保。
- 《植物大战僵尸》原版知识产权归 PopCap/EA 所有，本协议仅适用于本仓库中的实现代码。
- 本项目不包含任何原版游戏受版权保护的资源。
 
PopCap Games Framework 致谢
 
 SexyAppFramework  目录中可能包含基于 PopCap Games Framework 的原始代码，该代码受宽松的 PopCap Games Framework 协议 约束（src/SexyAppFramework/LICENSE）。若原版代码仍存在，以下声明适用：
 
"This product includes portions of the PopCap Games Framework, © 2005-2009 PopCap Games, Inc. All rights reserved. (http://popcapframework.sourceforge.net/)."
 
注：该部分代码已由社区大量重构、优化与现代化，并以 LGPL-3.0-or-later 协议发布。
 
致谢
 
- PopCap Games：创作这款优秀游戏，并以宽松协议公开其框架。
- SDL 开发团队：提供强大的跨平台开发库，支撑本移植项目。
- OpenMPT 团队：提供 libopenmpt，实现高质量 MO3 音乐播放。
- 所有为本项目做出贡献的开发者，特别感谢 @Headshotnoby 与 @Patoke 打下基础。