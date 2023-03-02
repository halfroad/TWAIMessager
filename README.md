# TWAIMessager
This Arduino IDE based project showcase how the ESP32-S3 (Should be working for other ESP32 boards) TWAI (Two-Wire Automobile Interface) sends and received normal messages, loopback messages.

## How to run the project?

* Connect ESP32-S3 to the USB port, select the corresponding board and port.
* Launch the main program TWAIMessager.ino by Arduino IDE.
* Configure the GPIOs of rx pin and tx pin as follows,
  #define RX_GPIO_PIN               GPIO_NUM_4 (or other available GPIOs)
  #define TX_GPIO_PIN               GPIO_NUM_5 (or other available GPIOs)
* Connect CAN BUS module (i.e SN65HVD230) to ESP32-S3
  #CAN RX pin of CAN BUS module to pin 4 of ESP32-S3 (Other ESP32, please check the schematic of the boards)
  #CAN TX pin of CAN BUS module to pin 5 of ESP32-S3.
* Set the Baud Rate of Serial of Arduino IDE to 115200
* Tweak the timing_config accordingly if there is external CAN bus module.
* Run and Upload the program.
* check the Serial Console.
