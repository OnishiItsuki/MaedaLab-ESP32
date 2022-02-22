# Lever angle reader for ESP32

2022/02/15 \
大西 幾月 \
E-mail : onishi.itsuki@ist.osaka-u.ac.jp

## 機能
このプログラムは，AD converter（以降ADCと記載）によるレバー角の測定と結果の送信を行います． \
操作対象となるデバイスは下記の通りです．
括弧内に使用したデバイスの型番を記載します．
  * ADC (LTC2309)
  * OLED display (SSD1306)
  * Signal LED

プログラムの流れは下記のとおりです．
  1. ESP32，ADC，OLED display，LEDの初期化．
  2. ADCに読み取りのための信号をI2Cを用いて送信．
  3. ADCから測定された電圧を受信．
  4. 電圧からPWM制御信号を生成．
  5. 測定結果をPWM_motor_controllerを稼働させているESP32に送信．
  6. 2から5の処理を繰り返す．

このプログラムは"PWM_motor_controller"とセットで使います．
"PWM_motor_controller"の詳細は同名のディレクトリ下にあるREADMEを参照してください．

## 依存環境
ESP32をArduino IDEで使うためにボード情報をインストールします． \
詳細は下記のサイトを参照してください．
 * https://github.com/espressif/arduino-esp32
 * https://dandydot.no-ip.biz/~dot/presen/advtech/seminars/iot_workshop/install-esp32-board-manager/README.md.html .

依存するライブラリを列挙します．
それぞれのライブラリの詳細はライブラリ名の下に記載したサイトを参照してください．

  * ESP8266 and ESP32 driver for SSD1366 displays
    * https://wak-tech.com/archives/825
    * https://github.com/ThingPulse/esp8266-oled-ssd1306


## ファイル構成
このプログラムのファイル構成は下記の通りです．
```  
.  
|-- documents
|   |-- ESP32-ADC.brd           # このデバイスの基盤設計図（ボード情報）
|   |-- ESP32-ADC.sch           # このデバイスの基盤設計図（配線情報）
|   --- LTC2309.pdf             # ADC (LTC2309)のデータシート
|
|-- lever_angle_reader.ino      # Main
|-- ADC_controller.ino          # ADC用の関数と変数
|-- OLED_controller.ino         # OLED用の関数と変数
|-- SIGNAL_LED_controller.ino   # Signal LED用の関数
|-- UDP_Tx.ino                  # WiFi+UDPによる信号送信用の関数
--- README.md                   # このファイル
```

## 通信フォーマット
"PWM_motor_controller"下のREADME内の同項目を参照してください．

## 関数リスト
各ファイルにある関数の情報です．
各ファイル内でのみアクセスする関数は"_"を先頭に付けています．

### lever_angle_reader.ino
| 関数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| setup | setup() | デバイス全体の初期化 | Nan | ESP32，AD converter，OLED，LEDの初期化とチェック処理 |  |
| loop | loop() | ESP32のmain loop | Nan | レバー角の読み取りと送信 |  |

### ADC_controller.ino
| 関数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| ADC_init | ADC_init() | ADCの利用時に`setup()`で呼ぶ関数 | Nan | ADCのデバイスの初期化（？）とESP32側でのADC利用のための処理 | 未実装 |
| _send_read_signal | _send_read_signal() | ADCに読み取り信号を送る． | Nan | ADC用にI2C回線を専有し，読み取り信号を送信する．step2の処理に相当する． | 未実装 |
| _receive_voltage_values | _receive_voltage_values(int buffer[]) | ADCから観測値を取得する． | Nan | ADCから観測値を取得し，受け取った配列に格納する．step3の処理に相当する．| 未実装 |
| read_voltage_from_ADC | read_voltage_from_ADC(int buffer[]) | ADCから観測値を取得する． | Nan | `lever_angle_reader.ino`からADCにアクセスするための関数．内部では_send_read_signalと_receive_voltage_valuesを呼び出している． |  |

### OLED_controller.ino
| 関数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| OLED_init | OLED_init() | OLEDディスプレイの利用時に`setup()`で呼ぶ関数 | Nan | ディスプレイの初期化と異常検知用の全要素表示を行う． |  |
| disp_init | disp_init() | ディスプレイの初期化 | Nan | 初期化とフォント（フォントサイズを含む）設定を行う． |  |
| OLED_clear | OLED_clear() | ディスプレイの表示を消す | Nan | ディスプレイの表示を消す． | 今はdisp_init()を呼び出すことで実装している．もう少しいい方法があるかも． |
| disp_all_pixel | disp_all_pixel() | 全画素をONにする | Nan | 全画素をONにする |  |
| disp_add_string | disp_add_string(int16_t x, int16_t y, String message) | ディスプレイに文字を表示する． | Nan | messageに入力された文字列を(x, y)の位置に出力する．過去のディスプレイの表示は消されずに追加される． |  |
| disp_show_string | disp_show_string(String message) | 入力された文字列を成型して表示 | Nan | messageで入力された文字列を画面端もしくは"\n"で折り返す．縦方向には特に処理を行わないのであまり多くの文字を各と画面下で文字が切れる．（簡単な判定で警告を出す機能はある．） | 2行まではうまく表示できるはず．．．あまり期待した動作をしなさそうです．．． |

### SIGNAL_LED_controller.ino
| 関数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| LED_init | LED_init() | LEDを使うときに最初に呼び出す関数 | Nan | ピンアサインを行う．PIN番号はSIGNAL_LED_PINにより設定する． |  |
| led_on | led_on() | LEDを点灯する． | Nan | LEDを点灯する． |  |
| led_off | led_off() | LEDを消灯する． | Nan | LEDを消灯する． |  |

### UDP_Tx.ino
| 関数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| _WiFi_setup | _WiFi_setup(String message) | ESP32間の通信を担うWiFiの初期化 | Nan | WiFiインスタンスの初期化と設定を行う．Serial通信とディスプレイでの状態表示をも行う．messageには何のために呼び出されたかの説明を入れる． | WiFiが接続されるまでloopし続けるので注意．（特に単体でdebugするとき） |
| _signal_buffer_init | _signal_buffer_init() | signal_bufferの初期化 | Nan | signal_bufferを初期化する． |  |
| UDP_init | UDP_init() | ESP32間の通信を行う際に`setup()`で呼ぶ関数 | Nan | UDPを用いたWiFiの初期化処理と接続を行う．接続に成功したらその旨をSerial通信とディスプレイで表示する． |  |
| _compute_signal_from_voltage | _compute_signal_from_voltage(int voltage_value) | WiFiで送信される値を計算する |WiFiで送信される値 | ADCで観測した電圧からWiFiで送信する値を計算する．入力，出力ともに配列ではなく，値であることに注意． | 現状intからuint8_tにコンバートするだけの関数になっている． |
| _compute_parity | _compute_parity(uint8_t signal_buffer[]) | parity bitの値を計算する | parity bitの値 | index 1からindex NUM_CH-2までにWiFiで送信される値を格納した配列を受け取り，parity bitの値を計算して返す． |  |
| _generate_udp_signal_from_voltage | _generate_udp_signal_from_voltage(int voltage[]) | WiFiで送信する値の生成 | Nan | ADCで観測した値の配列からWiFiで送信する信号を生成する．結果はsignal_bufferに格納される． |  |
| _send_signal | _send_signal() | WiFiでsignal_bufferの値を送信する | Nan | WiFiの接続を確認し，signal_bufferの値を送信する．WiFiの接続が切れていた場合は再接続処理を行う．急激な動きを防ぐために，関数の実行後に送信の可否に寄らずsignal_bufferの値は初期化される． | WiFiが接続されない間はloopし続けるので注意 |
| send_udp_signal | send_udp_signal(int voltage[]) | ADCの観測結果をWiFiで送信する | Nan | ADCでの観測結果を受け取り，前処理の後にWiFiで相手のESP32に送信する． |  |


## 変数リスト
各ファイルにある変数の情報です．
local変数については説明を省略します．
マクロは大文字スネーク記法，変数は小文字スネーク記法（省略した単語は大文字）で書いています．
設定値は基本的にマクロで書いています．

### lever_angle_reader.ino
| 変数名 | 用途 | 備考 |
| :---: | :---: | :---: |
| SDA_PIN | I2C通信のSDAのPINを決める．使えるPINに制約があるので，ググって調べてください． | デフォルトは21（`ADC_controller.ino`と`OLED_controller.ino`で定義） |
| SCL_PIN | I2C通信のSCLのPINを決める．使えるPINに制約があるので，ググって調べてください． | デフォルトは22（`ADC_controller.ino`と`OLED_controller.ino`で定義） |
| SIGNAL_LED_PIN | LEDの制御PINを決める． | デフォルトは27（`SIGNAL_LED_controller.ino`で定義） |
| NUM_CH | ADCで読み取る信号のチャネル数．6で固定でOK（マジックナンバー回避が目的のため） |  |
| voltage_buffer | ADCで読み取った数値を格納する配列． | 現在はint型にしていますが，ADCの仕様に合わせて変えてください． |

### ADC_controller.ino
| 変数名 | 用途 | 備考 |
| :---: | :---: | :---: |
| SDA_PIN | I2C通信のSDAのPINを決める．使えるPINに制約があるので，ググって調べてください． | この値は基本的に変更しない．一時的に変更する場合は，`lever_angle_reader.ino`に書く． |
| SCL_PIN | I2C通信のSCLのPINを決める．使えるPINに制約があるので，ググって調べてください． | この値は基本的に変更しない．一時的に変更する場合は，`lever_angle_reader.ino`に書く． |
| MAX_SLAVE_RESPONSE_LENGTH | ADCに要求するバイト数． | ADC実装後に確認 |
| ADC_ADDR | ADCのI2C通信におけるアドレス． |  |

### OLED_controller.ino
| 変数名 | 用途 | 備考 |
| :---: | :---: | :---: |
| SDA_PIN | I2C通信のSDAのPINを決める．使えるPINに制約があるので，ググって調べてください． | この値は基本的に変更しない．一時的に変更する場合は，`lever_angle_reader.ino`に書く． |
| SCL_PIN | I2C通信のSCLのPINを決める．使えるPINに制約があるので，ググって調べてください． | この値は基本的に変更しない．一時的に変更する場合は，`lever_angle_reader.ino`に書く． |
| OLED_ADDR | OLEDディスプレイのI2C通信でのアドレス． |  |
| FONT | ディスプレイのフォントとフォントサイズを決める．入力値の詳細はググってください． |  |
| font_size_width | フォントの横幅に相当する定数．これでフォントサイズが変わるわけでは無く，`disp_show_string`の成型に影響する．表示を見ながら適当に設定指定ください． |  |
| font_size_height | フォントの縦幅に相当する定数．これでフォントサイズが変わるわけでは無く，`disp_show_string`の成型に影響する．表示を見ながら適当に設定指定ください． |  |
| disp_width | ディスプレイの横幅．`disp_all_pixel`などで使用している． | 調整済みなので，128から変更しない．
| disp_height | ディスプレイの縦幅．`disp_all_pixel`などで使用している． | 調整済みなので，64から変更しない． |
| max_num_char_width | 横幅に入る最大文字数．上記の変数から計算するので設定不要． |  |
| max_num_line | ディスプレイに表示できる最大行数．上記の変数から計算するので設定不要． |  |

### SIGNAL_LED_controller.ino
| 変数名 | 用途 | 備考 |
| :---: | :---: | :---: |
| SIGNAL_LED_PIN | LEDの制御PINを決める． | この値は基本的に変更しない．一時的に変更する場合は，`lever_angle_reader.ino`に書く． |

### UDP_Tx.ino
| 変数名 | 用途 | 備考 |
| :---: | :---: | :---: |
| SSID | WiFiホストのSSID．なんでもいいが，ホストと一致させる必要がある． |  |
| PASSWORD | WiFiホストのPASSWORD．なんでもいいが，ホストと一致指せる必要がある． |  |
| HOST_IP | WiFiホストのIP．なんでもいいが，ホストと一致指せる必要がある． |  |
| HOST_PORT | ホストのソケットのポート設定．なんでもいいが，ホストと一致指せる必要がある． |  |
| CLIENT_PORT | クライアントのソケットのポート設定．なんでもいい． |  |
| RECONNECTION_SPAN_MS | WiFiの接続が切れている時に接続を再確認する時間間隔． |  |
| signal_size | UDPで送信する信号のサイズ．スタートビット，各チャネルの信号，パリティビットで構成されるため，NUM_CH + 2となっている． |  |
| start_BYTE | スタートバイトの値． |  |
| signal_buffer | 送信する信号のbuffer． |  |
