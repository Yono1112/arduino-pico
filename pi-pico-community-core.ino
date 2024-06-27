#include <DHT.h>

// DHT22のDATAピンはデジタルピン7に接続
#define DHTPIN 28
// 接続するセンサの型番
#define DHTTYPE DHT22

// センサーの初期化
DHT dht(DHTPIN, DHTTYPE);

// 測定結果の統計データを保存するための構造体
struct {
  uint32_t total;
  uint32_t ok;
  uint32_t crc_error;
  uint32_t time_out;
  uint32_t connect;
  uint32_t ack_l;
  uint32_t ack_h;
  uint32_t unknown;
} stat = { 0, 0, 0, 0, 0, 0, 0, 0};

void setup()
{
    Serial1.begin(115200);
    dht.begin();
    Serial1.println("Start Raspberry Pi Pico DHT22 Test!");
    Serial1.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)\tTime (us)");
}
void readAndPrintSensorData()
{
    Serial1.print("DHT22, \t");

    uint32_t start = micros();
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    uint32_t stop = micros();

    stat.total++;

    if (isnan(h) || isnan(t))
    {
        Serial1.print("Failed to read from DHT sensor!\t");
        stat.unknown++;
    }
    else
    {
        stat.ok++;
        Serial1.print("OK,\t");
        Serial1.print(h, 1);
        Serial1.print(",\t");
        Serial1.print(t, 1);
        Serial1.print(",\t");
        Serial1.print(stop - start);
        Serial1.println();
    }
}

void printStatistics()
{
    Serial1.println("\nTOT\tOK\tCRC\tTO\tCON\tACK_L\tACK_H\tUNK");
    Serial1.print(stat.total);
    Serial1.print("\t");
    Serial1.print(stat.ok);
    Serial1.print("\t");
    Serial1.print(stat.crc_error);
    Serial1.print("\t");
    Serial1.print(stat.time_out);
    Serial1.print("\t");
    Serial1.print(stat.connect);
    Serial1.print("\t");
    Serial1.print(stat.ack_l);
    Serial1.print("\t");
    Serial1.print(stat.ack_h);
    Serial1.print("\t");
    Serial1.print(stat.unknown);
    Serial1.println("\n");
    Serial1.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)\tTime (us)");
}

void loop()
{
    delay(3000);
    readAndPrintSensorData();

    if (stat.total % 10 == 0)
    {
      printStatistics();
    }
}