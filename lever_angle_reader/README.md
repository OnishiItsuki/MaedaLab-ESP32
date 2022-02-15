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

## ファイル構成
このプログラムのファイル構成は下記の通りです．
```  
.  
|-- documents
|   |-- LTC2309.pdf             # ADC (LTC2309)のデータシート
|
|-- lever_angle_reader.ino      # Main
|-- ADC_controller.ino          # ADC用の関数と変数
|-- OLED_controller.ino         # OLED用の関数と変数
|-- SIGNAL_LED_controller.ino   # Signal LED用の関数
|-- UDP_Tx.ino                  # UDP送信機用の関数
--- README.md                   # このファイル
```


## 依存関係
ESP32をArduino IDEで使うためにボード情報をインストールします． \
詳細は下記のサイトを参照してください．
 * https://github.com/espressif/arduino-esp32
 * https://dandydot.no-ip.biz/~dot/presen/advtech/seminars/iot_workshop/install-esp32-board-manager/README.md.html .

依存するライブラリを列挙します．
それぞれのライブラリの詳細はライブラリ名の下に記載したサイトを参照してください．

  * ESP8266 and ESP32 driver for SSD1366 displays
    * https://wak-tech.com/archives/825
    * https://github.com/ThingPulse/esp8266-oled-ssd1306

## 通信フォーマット
"PWM_motor_controller"下のREADME内の同項目を参照してください．

## 関数リスト
各ファイルにある関数の情報です．

### lever_angle_reader.ino
| 関数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| setup | setup() | デバイス全体の初期化 | Nan | ESP32，AD converter，OLED，LEDの初期化とチェック処理 |  |
| loop | loop() | ESP32のmain loop | Nan | レバー角の読み取りと送信 |  |

### ADC_controller.ino
| 関数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
|  |  |  |  |  |  |

### OLED_controller.ino
| 関数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| TD | TD | TD | a | TD | TD |

### SIGNAL_LED_controller.ino
| 関数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| TD | TD | TD | a | TD | TD |

### UDP_Tx.ino
| 関数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| TD | TD | TD | a | TD | TD |


## 変数リスト
各ファイルにある変数の情報です．

### lever_angle_reader.ino
| 変数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| TD | TD | TD | a | TD | TD |

### ADC_controller.ino
| 変数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| TD | TD | TD | a | TD | TD |

### OLED_controller.ino
| 変数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| TD | TD | TD | a | TD | TD |

### SIGNAL_LED_controller.ino
| 変数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| TD | TD | TD | a | TD | TD |

### UDP_Tx.ino
| 変数名 | 構文 | 機能 | 返り値 | 処理説明 | 備考 |
| :---: | :---: | :---: | :---: | :---: | :---: |
| TD | TD | TD | a | TD | TD |

