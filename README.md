# STM32F103C8T6 流水灯（按键换向）

## 1. 项目说明

- 主控：STM32F103C8T6 最小系统板（Blue Pill）
- 功能：4 个 LED 依次点亮形成流水灯；按一下按键切换流水方向
- 开发环境：Keil MDK 5.35 + ARMCC 5.06 + STM32F1xx_DFP 1.0.5
- 库：STM32F10x 标准外设库 V3.5.0（已随工程附带，换电脑也能直接编译）

工程文件：`D:\liushudeng\liushuideng.uvprojx`

编译输出：`D:\liushudeng\OBJ\RunningLED.hex`（已编译通过，0 Error / 0 Warning）

---

## 2. 硬件清单

| 名称 | 数量 | 说明 |
|---|---|---|
| STM32F103C8T6 最小系统板 | 1 | Blue Pill，8MHz 晶振 |
| LED（建议不同颜色） | 4 | 5mm 直插，工作电流 5~10mA |
| 电阻 220Ω 或 330Ω | 4 | LED 限流电阻，不要省 |
| 轻触按键 | 1 | 4 脚或 2 脚均可 |
| 面包板 | 1 | 400 孔或 830 孔 |
| 杜邦线 | 若干 | 公对公 / 公对母按需 |
| ST-Link V2 | 1 | SWD 下载调试 |

---

## 3. 面包板接线（重点）

### 3.1 供电与共地

两种供电方式**任选一种**，不要同时供电：

- 方式 A：ST-Link 的 `3.3V` 接 Blue Pill 的 `3.3V`，`GND` 接 `GND`
- 方式 B：Blue Pill 用 USB 供电，ST-Link 只接 `SWDIO / SWCLK / GND`

面包板上把 Blue Pill 的 `GND` 引到面包板的蓝色（或黑色）电源轨，
所有 LED 阴极、按键一端都接到这条 GND 轨，**必须共地**。

### 3.2 4 个 LED（高电平点亮）

| LED | 单片机引脚 | 接线顺序 |
|---|---|---|
| LED1 | PA0 | PA0 → 220Ω → LED 长脚（阳极），LED 短脚（阴极）→ GND |
| LED2 | PA1 | PA1 → 220Ω → LED 长脚，LED 短脚 → GND |
| LED3 | PA2 | PA2 → 220Ω → LED 长脚，LED 短脚 → GND |
| LED4 | PA3 | PA3 → 220Ω → LED 长脚，LED 短脚 → GND |

注意：

- LED 长脚是阳极（正），短脚是阴极（负），接反不亮
- 电阻串在 GPIO 和 LED 阳极之间，不能直接短接
- 代码按“高电平点亮”编写；如果你的 LED 是 3.3V→LED→电阻→GPIO 的接法（低电平点亮），
  需要把 `HARDWARE/LED/led.c` 中 `LED_Show()` 里的 `Bit_SET` 与 `Bit_RESET` 对调

### 3.3 按键（PA4）

| 按键一端 | 按键另一端 |
|---|---|
| PA4 | GND |

- 代码已开启 PA4 内部上拉，**不需要外部上拉电阻**
- 松开时 PA4 为高电平，按下时为低电平
- 轻触按键 4 个脚中，同侧两脚内部相连；建议用对角线两个脚接线，
  或者用万用表蜂鸣档确认“按下导通”的两个脚
- 可选：PA4 与 GND 之间并一个 100nF 电容做硬件消抖（软件已有 10ms 消抖）

### 3.4 ST-Link 下载线

| ST-Link V2 | Blue Pill |
|---|---|
| SWDIO / DIO | PA13（板上 DIO） |
| SWCLK / CLK | PA14（板上 CLK） |
| GND | GND |
| 3.3V | 3.3V（仅当不用 USB 供电时接） |

Blue Pill 的 `BOOT0` 跳线帽接 `0`（靠 GND 一侧），`BOOT1` 也接 `0`。
下载完成后按一下板上的复位键，程序开始运行。

### 3.5 接线示意

```
                     +----------------------+
   ST-Link 3.3V ---> | 3.3V          PA0    |---[220Ω]---|>|--- GND   LED1
   ST-Link GND  ---> | GND           PA1    |---[220Ω]---|>|--- GND   LED2
   ST-Link SWDIO --> | PA13(DIO)     PA2    |---[220Ω]---|>|--- GND   LED3
   ST-Link SWCLK --> | PA14(CLK)     PA3    |---[220Ω]---|>|--- GND   LED4
                     |               PA4    |---[按键]---------- GND
                     |               GND    |--- 面包板 GND 轨
                     +----------------------+
```

（`|>|` 表示 LED，左边是阳极长脚，右边是阴极短脚）

---

## 4. Keil 打开、编译、下载

1. 双击 `D:\liushudeng\liushuideng.uvprojx` 打开工程
2. 按 `F7`（或 Build 按钮）编译，底部应显示 `0 Error(s), 0 Warning(s)`
3. 按 `F8`（Download）通过 ST-Link 下载
4. 按板子复位键，观察流水灯

工程中已经配置好的关键选项：

| 选项 | 值 |
|---|---|
| Device | STM32F103C8 |
| C/C++ → Define | `USE_STDPERIPH_DRIVER, STM32F10X_MD` |
| C/C++ → Include Paths | `.\CORE;.\USER;.\STM32F10x_FWLib\inc;.\HARDWARE\LED;.\HARDWARE\KEY;.\HARDWARE\DELAY` |
| Debug | ST-Link Debugger，Port = SW |
| Flash Download | STM32F10x_128 算法，勾选 Reset and Run |
| Output | 已勾选 Create HEX File |

如果换电脑后提示找不到 `core_cm3.h` 或 `stm32f10x_gpio.h`，
检查 `Options for Target → C/C++ → Include Paths` 是否指向工程内的
`CORE`、`STM32F10x_FWLib\inc` 等目录（工程内已附带全部库文件）。

---

## 5. 程序原理

### 5.1 LED 输出

`LED_Init()` 打开 GPIOA 时钟，把 PA0~PA3 配置为 **推挽输出、50MHz**。
`LED_Show(pattern)` 根据 4 位模式字点亮对应 LED：

| pattern | 点亮 |
|---|---|
| 0x01 | LED1（PA0） |
| 0x02 | LED2（PA1） |
| 0x04 | LED3（PA2） |
| 0x08 | LED4（PA3） |

### 5.2 流水与换向

主循环每 200ms 更新一次模式字：

- 正向：`0x01 → 0x02 → 0x04 → 0x08 → 0x01 ...`（左移，到 0x08 回绕）
- 反向：`0x08 → 0x04 → 0x02 → 0x01 → 0x08 ...`（右移，到 0x01 回绕）

等待 200ms 的过程被拆成 20 次 10ms 小延时，每次延时后扫描按键，
所以按键响应时间约 10ms，不会等满 200ms。

### 5.3 按键检测

`KEY_Init()` 把 PA4 配置为 **上拉输入**。
`KEY_Scan()` 采用“松开标志 + 10ms 延时”的软件消抖：

- 只在按下的瞬间返回一次 `KEY_PRES`，按住不会连续触发
- 松开后标志复位，下次按下才能再次触发

### 5.4 延时

`Delay_Init()` 把 SysTick 时钟设为 HCLK（72MHz），
`Delay_us()` 用 SysTick 的 24 位递减计数器做忙等待，
`Delay_ms()` 循环调用 `Delay_us(1000)`。

> 说明：工程使用标准库默认的 `SystemInit()`，板上 8MHz 晶振起振后
> 系统时钟为 72MHz。若你的板子没有焊接 8MHz 晶振，HSE 起振失败会退回
> 内部 8MHz，灯仍会流动，只是速度慢约 9 倍。

---

## 6. 代码结构

```
D:\liushudeng\
├─ liushuideng.uvprojx      Keil 工程
├─ README.md               本说明
├─ USER\
│   ├─ main.c              主程序：流水 + 按键换向
│   ├─ stm32f10x_it.c/.h   中断服务函数（空实现）
│   └─ stm32f10x_conf.h    标准库配置（GPIO/RCC/misc）
├─ HARDWARE\
│   ├─ LED\led.c/.h        LED 驱动
│   ├─ KEY\key.c/.h        按键扫描
│   └─ DELAY\delay.c/.h    SysTick 延时
├─ CORE\
│   ├─ startup_stm32f10x_md.s   中容量启动文件
│   ├─ system_stm32f10x.c/.h    系统时钟
│   ├─ stm32f10x.h              器件头文件
│   └─ core_cm3.h 等            CMSIS 内核头文件（仅保留 ARMCC 编译所需）
├─ STM32F10x_FWLib\
│   ├─ inc\                标准库头文件（仅 gpio/rcc/misc）
│   └─ src\                标准库源码（仅 gpio/rcc/misc）
└─ OBJ\                    仅保留可烧录的 RunningLED.hex
```

---

## 7. 演示步骤（录视频建议）

1. 先给镜头看面包板接线，说明 PA0~PA3 接 4 个 LED、PA4 接按键
2. 上电/复位：4 个 LED 全亮 0.5 秒（自检），然后全灭
3. 正向流水：LED1→LED2→LED3→LED4，循环
4. 按一下按键：变为 LED4→LED3→LED2→LED1
5. 再按一下：恢复正向
6. 结尾给 Keil 编译成功的画面（0 Error / 0 Warning）

---

## 8. 常见问题

**LED 不亮**

- LED 长短脚接反（长脚接电阻/GPIO，短脚接 GND）
- 忘记串电阻或电阻过大（建议 220Ω~1kΩ）
- 没有共地：LED 阴极必须和 Blue Pill 的 GND 连在一起
- 引脚接错：代码用的是 PA0、PA1、PA2、PA3

**按键没反应**

- 按键接成了同一侧的两个脚（同侧内部一直相连，按下也检测不到）
  改用对角线两脚，或用万用表确认
- 按键没有一端接 GND
- PA4 被其他外设占用（本工程未使用）

**Keil 下载报错 “No Cortex-M Device found”**

- SWDIO/SWCLK 接反或没接
- Blue Pill 没供电，或 ST-Link 与板子没有共地
- BOOT0 没有接 0
- ST-Link 驱动未安装（设备管理器中出现 ST-Link 即正常）

**编译报错 “cannot open source input file core_cm3.h”**

- `Options for Target → C/C++ → Include Paths` 中缺少 `.\CORE`
- 工程目录被移动后，路径需要重新指定

**流水方向不切换**

- 按键按下时间太短，保持 50ms 以上再松开
- 确认 PA4 在按下时对地电压为 0V

---

## 9. 作业提交

- 项目代码：打包 `D:\liushudeng` 整个文件夹（已清理中间文件，`OBJ` 中只保留 `RunningLED.hex`）
- 演示视频：按第 7 节步骤录制
- 邮箱：`2025218535@mail.hfut.edu.cn`
- 如果有 GitHub 仓库，在邮件正文附上 public 仓库链接（作业说明中有加分）
