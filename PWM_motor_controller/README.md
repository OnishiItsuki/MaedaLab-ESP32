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

## 依存環境
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

詳しくは"Pulse_design.xlsx"をご覧ください．


## 関数リスト
各ファイルにある関数の情報です．
各ファイル内でのみアクセスする関数は"_"を先頭に付けています．

### PWM_motor_controller.ino
| 関数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| setup | setup() | デバイスの初期化 | Nan | ESP32のWiFiを用いたUDP通信とPWM制御のためのモジュールの初期化 |  |
| loop | loop() | ESP32のmain loop | Nan | 制御信号の受信とmotorの制御．信号を受信できなかった場合の処理もここで行う． |  |
| _set_basic_signal | _set_basic_signal() | ベースとなる信号をセットする | Nan | 制御信号を受信できなかったときにmotorに送る信号をセットする | 停止信号をセットしています． |

### PWM_controller.ino
| 関数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| _set_duty_ratio_for_each_pins | _set_duty_ratio_for_each_pins() | ピンからモータドライバーに送る制御信号をセットする | Nan | `control_input_signal`に入っているduty比を元に，モータドライバーに送る制御信号を決定する． |  |
| _pin_init | _pin_init() | pinの初期化 | Nan | ESP32とモータドライバ間の通信で使うpinを初期化します．pinと受信した制御信号の対応もここで決まります．pinの初期状態はfree spinとなっています．  |  |
| PWM_init | PWM_init() | PWM制御を利用時に`setup()`で呼ぶ関数 | Nan | ピンの初期化とピン出力を決める関数のtickerを生成します． |  |
| compute_motor_control_signals | computer_motor_control_signals(uint8_t input_signal[]) | pin制御信号の生成 | Nan | 入力された制御信号列からpin制御信号を生成して`control_input_signal`を生成します．入力信号が1から127の時は正転，129から255の時は反転します．また，入力信号が0のとき，モータはfree回転し，128の時は停止します． |  |

### UDP_AP_Rx.ino
| 関数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| WiFi_init | WiFi_init() | WiFiを利用時に`setup()`で呼ぶ関数 | Nan | WiFiのモジュールの初期化を行います．この関数を利用したESP32がホストになります．IP，SSIDの設定はこの巻子で行います． |  |
| UDP_init | UDP_init() | UDP通信を利用時に`setup()`で呼ぶ関数 | Nan | UDPのモジュールの初期化を行います．PORT設定はこの関数で行われます． |  |
| _compute_parity | _compute_parity(uint8_t input_signal[]) | parity byteの計算 | uint8_t computed parity byte | 入力信号列（signal_size）からparity byteを計算します． |  |
| _check_signal_rules | _check_signal_rules(uint8_t input_signal[]) | 受信信号の確認 | bool check_result | 入力信号列（signal_size）が通信フォーマットに沿っているかを確認します．具体的にはスタートバイトの確認とパリティバイトの確認を行います． |  |
| receive_signal | receive_signal(uint8_t signal_buffer[]) | PWM制御信号を受信する | bool 受信信号の確認結果 | UDPによるPWM制御信号の受信を行います．受信信号は受信の正誤を確認した後に，信号部分のみを取り出して入力された配列（signal_buffer）に格納します． |  |


## 変数リスト
各ファイルにある変数の情報です．
local変数については説明を省略します．
マクロは大文字スネーク記法，変数は小文字スネーク記法（省略した単語は大文字）で書いています．
設定値は基本的にマクロで書いています．

### PWM_motor_controller.ino
| 変数名 | 用途 | 備考 |
| :---: | :---: | :---: |
| NUM_CH | ADCで読み取る信号のチャネル数．6で固定でOK（マジックナンバー回避が目的のため） |  |

### PWM_controller.ino
pinとモータドライバとの対応は
[このディレクトリ](https://drive.google.com/drive/folders/13rdrTIzANPNWbBI62d2jNv5huxH2cr-4?usp=sharing)
を参照してください．

| 変数名 | 用途 | 備考 |
| :---: | :---: | :---: |
| DUTY_RATIO_BIT_SIZE | duty比を指定するbit数．7を設定すれば，0から127までの値を入力として受け入れられる． |  |
| PWM_FREQ | PWM信号のベースとなる周波数． |  |
| SET_SIGNAL_SPAN_MS | pinの値を変更する関数を呼び出す周期．tickerの割り込み処理の周期を設定している． |  |
| BYTE_A | for文でモータドライバーAにアクセスする配列にを指すマクロ． |  |
| BYTE_B | for文でモータドライバーBにアクセスする配列にを指すマクロ． |  |
| XXX_OUT_Y | XXX（各駆動部のモータ）への信号を出すピンを設定する．YにはモータドライバのA，Bに対応する値が入る． | 詳しくはgoogle driveを見てください． |
| control_signal_buffer_size | モータ制御信号のサイズ．各チャネル2系統あるため，NUM_CH * 2となっている． |  |
| control_input_signal | モータ制御信号のbuffer．配列のindexと対応するモータの関係は`_pin_init()`で設定されている． |  |

### UDP_AP_Rx.ino
| 変数名 | 用途 | 備考 |
| :---: | :---: | :---: |
| SSID | WiFiホストのSSID．なんでもいいが，クライアントと一致させる必要がある． |  |
| PASSWORD | WiFiホストのPASSWORD．なんでもいいが，クライアントと一致指せる必要がある． |  |
| HOST_PORT | ホストのソケットのポート設定．なんでもいいが，クライアントと一致指せる必要がある． |  |
| host_IP | WiFiホストのIP．なんでもいいが，クライアントと一致指せる必要がある． |  |
| subnet | subnet |  |
| start_BYTE | スタートバイトの値． |  |
| signal_size | UDPで送信する信号のサイズ．スタートビット，各チャネルの信号，パリティビットで構成されるため，NUM_CH + 2となっている． |  |
