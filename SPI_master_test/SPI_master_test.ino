#include <ESP32DMASPIMaster.h>
ESP32DMASPI::Master master;

static const uint8_t SCK_master = 14;
static const uint8_t MISO_master = 12;
static const uint8_t MOSI_master = 13;
static const uint8_t CS_master = 15;

static const uint32_t BUFFER_SIZE = 5;
uint8_t* spi_master_tx_buf;
uint8_t* spi_master_rx_buf;

void setup() {
    Serial.begin(115200);

    // to use DMA buffer, use these methods to allocate buffer
    spi_master_tx_buf = master.allocDMABuffer(BUFFER_SIZE);
    spi_master_rx_buf = master.allocDMABuffer(BUFFER_SIZE);

    master.setDataMode(SPI_MODE3);
    master.setFrequency(SPI_MASTER_FREQ_8M);
    master.setMaxTransferSize(BUFFER_SIZE);
    master.setDMAChannel(1); // 1 or 2 only
    master.setQueueSize(1); // transaction queue size

    // begin() after setting
    // HSPI = CS: 15, CLK: 14, MOSI: 13, MISO: 12
    // VSPI = CS: 5, CLK: 18, MOSI: 23, MISO: 19
    master.begin(SCK_master, MISO_master, MOSI_master, CS_master);
}

void loop() {
   	// set buffer data here

    // start and wait to complete transaction
    master.transfer(spi_master_tx_buf, spi_master_rx_buf, BUFFER_SIZE);

    // do something here with received data (if needed)
    for (size_t i = 0; i < BUFFER_SIZE; ++i)
        printf("%d ", spi_master_rx_buf[i]);
    printf("\n");

    delay(2000);
}
