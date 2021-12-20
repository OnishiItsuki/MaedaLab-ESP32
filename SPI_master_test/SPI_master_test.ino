#include <SPI.h> // SPIライブラリを導入

//変数の設定
static const uint8_t SCK_master = 14;
static const uint8_t MISO_master = 12;
static const uint8_t MOSI_master = 13;
static const uint8_t CS_master = 15;

uint8_t send_data = 100;
uint8_t rece_data = 0;

int counter = 0;

// SPI通信設定のインスタンスを立てる
SPISettings mySPISettings = SPISettings(6000000, MSBFIRST, SPI_MODE3);

void setup()
{
    // SPI通信とシリアル通信の初期設定
    Serial.begin(115200);
    pinMode(CS_master, OUTPUT); // スレーブ機器を起こす

    SPI.begin(SCK_master, MISO_master, MOSI_master, CS_master); // SPI通信の初期化、有効化
    delay(100);                                                 //シリアルの起動を安定させる（要調整）
    Serial.println("SPI Master Start.");                        //シリアル始動のご挨拶
}

void loop()
{
    Serial.println(counter++); //シリアルモニタ改行

    Serial.print("  [Send] ");
    Serial.print(send_data);
    Serial.println();

    // SPI通信の開始
    SPI.beginTransaction(mySPISettings); //通信開始
    digitalWrite(CS_master, LOW);        //スレーブ機器を起こす

    rece_data = SPI.transfer(send_data); //※送信と同時に受信データが返り値になる
    delayMicroseconds(50);                             //送受信時間調整用のディレイ

    digitalWrite(CS_master, HIGH); //スレーブ機器を終了
    SPI.endTransaction();          // SPIを解放
    Serial.print("Receive: ");
    Serial.println(rece_data);

    Serial.println("");
    
    delay(1500);
}
