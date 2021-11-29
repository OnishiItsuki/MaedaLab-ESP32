#include <SPI.h>

#define SCK 14
#define MISO 12
#define MOSI 13
#define CS 15
#define StartBIT0 0x18
#define StartBIT1 0x19

static const int spiClk = 1000000; // クロック 1 MHz

SPIClass *vspi = NULL; //	VSPIを使用する
uint counter = 0;

void setup()
{
  pinMode(CS, OUTPUT);    //デジタル10番ピンをOUTPUTに設定
  digitalWrite(CS, HIGH); //デジタルの10番ピンからHighを出力

  SPI.setBitOrder(LSBFIRST);           // 下位ビットから送信
  SPI.setClockDivider(SPI_CLOCK_DIV8); //分周器1/8を指定 同期クロック16/8=2MHz
  SPI.setDataMode(SPI_MODE0);          //アイドル時Low、立上がりエッジでデータ取得

  SPI.begin(); //SPI通信の初期化、有効化
  Serial.begin(115200);
}

void loop()
{
  vspiCommand();
  Serial.print("test: ");
  Serial.println(String(counter++));
  delay(500);
}

void vspiCommand()
{
  digitalWrite(CS, LOW);           //対象の電子部品を接続したSS
  SPI.transfer(StartBIT0); //valueに電子部品から受信したデータを格納
  uint32_t value = SPI.transfer(0);
  digitalWrite(CS, HIGH);          //通信終了

  Serial.print("read 0: ");
  Serial.println(value, HEX);
}
