#include <ESP32DMASPISlave.h>

ESP32DMASPI::Slave slave;

static const uint8_t SCK_slave = 14;
static const uint8_t MISO_slave = 12;
static const uint8_t MOSI_slave = 13;
static const uint8_t CS_slave = 15;

static const uint32_t BUFFER_SIZE = 8192;
uint8_t *spi_slave_tx_buf;
uint8_t *spi_slave_rx_buf;

void setup()
{
    Serial.begin(115200);

    // to use DMA buffer, use these methods to allocate buffer
    spi_slave_tx_buf = slave.allocDMABuffer(BUFFER_SIZE);
    spi_slave_rx_buf = slave.allocDMABuffer(BUFFER_SIZE);

    slave.setDataMode(SPI_MODE3);
    slave.setMaxTransferSize(BUFFER_SIZE);
    slave.setDMAChannel(2); // 1 or 2 only
    slave.setQueueSize(1);  // transaction queue size

    // begin() after setting
    // HSPI = CS: 15, CLK: 14, MOSI: 13, MISO: 12
    // VSPI = CS: 5, CLK: 18, MOSI: 23, MISO: 19
    slave.begin(SCK_slave, MISO_slave, MOSI_slave, CS_slave);
}

void loop()
{
    // set buffer (reply to master) data here

    // if there is no transaction in queue, add transaction
    if (slave.remained() == 0)
        slave.queue(spi_slave_rx_buf, spi_slave_tx_buf, BUFFER_SIZE);

    // if transaction has completed from master,
    // available() returns size of results of transaction,
    // and buffer is automatically updated

    while (slave.available())
    {
        // do something here with received data
        for (size_t i = 0; i < BUFFER_SIZE; ++i)
            printf("%d ", spi_slave_rx_buf[i]);
        printf("\n");

        slave.pop();
    }
}
