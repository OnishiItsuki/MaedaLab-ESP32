# motor controller with PWM for ESP32

2022/02/15 \
大西 幾月 \
E-mail : onishi.itsuki@ist.osaka-u.ac.jp


## 機能
このプログラムは，"lever_angle_reader"で検出したレバー角の受信と，それを元に建機ラジコンのモータ制御処理を行います．
建機ラジコンのモータは6つあり，それぞれPWMで制御します．
モータドライバの詳細は"Pulse_design.xlsx"に記載されています．

処理の全体像は下記のとおりです．
  1. ESP32の初期化.
  2. "lever_angle_reader"を動かしているESP32から，PWM制御信号を受け取る.
  3. 受け取った情報制御から各モータのduty比を計算する．
  4. 各モータに制御信号を送信する．
  5. 2から4を繰り返す．

このプログラムは"lever_angle_reader"とセットで使います．
"lever_angle_reader"の詳細は同名のディレクトリ下にあるREADMEを参照してください．

## ファイル構成
このプログラムのファイル構成は下記の通りです．
```  
.  
|-- documents
|   |-- Pulse_design.xlsx       # PWM通信信号と制御信号のデザイン
|
|-- PWM_motor_controller.ino    # Main
|-- PWM_controller.ino          # PWM制御用の関数と変数
|-- UPD_AP_Rx.ino               # UDP受信機用の関数と変数
--- README.md                   # このファイル
```

## Requirements
ESP32をArduino IDEで使うためにボード情報をインストールします． \
詳細は下記のサイトを参照してください．
 * https://github.com/espressif/arduino-esp32
 * https://dandydot.no-ip.biz/~dot/presen/advtech/seminars/iot_workshop/install-esp32-board-manager/README.md.html .

## 通信フォーマット
信号は`uint8_t`型変数8個セットで構成されます．
構成内容は下記のとおりです．

```
START BYTE | boom | arm | bucket | slewing | right_wheel | left_wheel | PARITY BYTE

START BYTE = 0x0f 
PARITY BYTE = boom XOR arm XOR … XOR left_wheel
```
START BYTEと6chの制御信号，PARITY BYTEで構成されます．\
PARITY BYTEは全制御信号のXORとなります．
制御信号は先頭1bitでモータの回転方向，残り7bitで速度を制御します．

"Pulse_design.xlsx"にも情報があるので，合わせてご覧ください．


## 関数リスト
各ファイルにある関数の情報です．

### PWM_motor_controller.ino
| 関数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| setup | setup() | デバイス全体の初期化 | Nan | ESP32，AD converter，OLED，LEDの初期化とチェック処理 |  |
| loop | loop() | ESP32のmain loop | Nan | レバー角の読み取りと送信 |  |

### PWM_controller.ino
| 関数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
|  |  |  |  |  |  |

### UDP_AP_Rx.ino
| 関数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| TD | TD | TD | a | TD | TD |


## 変数リスト
各ファイルにある変数の情報です．

### PWM_motor_controller.ino
| 変数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| TD | TD | TD | a | TD | TD |

### PWM_controller.ino
| 変数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| TD | TD | TD | a | TD | TD |

### UDP_AP_Rx.ino
| 変数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| TD | TD | TD | a | TD | TD |

