#include <SPI.h>

#define SCK 14
#define MISO 12
#define MOSI 13
#define CS 15
#define StartBIT0 0b1000
#define StartBIT1 0b1001

static const int spiClk = 1000000; // クロック 1 MHz

SPIClass *vspi = NULL; //	VSPIを使用する
uint counter = 0;

void setup()
{
  pinMode(CS, OUTPUT);    //デジタル10番ピンをOUTPUTに設定
  digitalWrite(CS, HIGH); //デジタルの10番ピンからHighを出力

  SPISettings mySPISettings = SPISettings(8000000, MSBFIRST, SPI_MODE0);
  // SPI.setBitOrder(LSBFIRST);           // 下位ビットから送信
  // SPI.setClockDivider(SPI_CLOCK_DIV8); //分周器1/8を指定 同期クロック16/8=2MHz
  // SPI.setDataMode(SPI_MODE0);          //アイドル時Low、立上がりエッジでデータ取得

  SPI.begin(SCK, MISO, MOSI, CS); //SPI通信の初期化、有効化
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
  SPI.beginTransaction(mySPISettings);

  digitalWrite(CS, LOW); //対象の電子部品を接続したSS
  SPI.transfer(0x04);
  uint32_t value1 =SPI.transfer(0x40);
  uint32_t value2 = SPI.transfer(0); //valueに電子部品から受信したデータを格納
  digitalWrite(CS, HIGH);           //通信終了

  SPI.endTransaction();

  Serial.print("read 1: ");
  Serial.print(value1, HEX);
  Serial.print("   ,read 2: ");
  Serial.println(value2, HEX);
}
