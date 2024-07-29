# SignalSeeker

SignalSeeker is a wardriving device based on the ESP8266 microcontroller, designed to scan and log nearby Wi-Fi networks along with their GPS coordinates. The device uses an OLED display to show information and status icons, and an SD card to store the scanned network details.

## Features

- Scans for Wi-Fi networks and logs SSID, RSSI, channel, BSSID, and encryption type.
- Logs GPS coordinates of each detected network.
- Displays status icons for Wi-Fi, SD card, and GPS.
- Stores data in a CSV file on the SD card.

## Hardware Requirements

- ESP8266 microcontroller
- GPS module (e.g., Neo-6M)
- OLED display (e.g., SSD1306 128x32)
- SD card module
- Necessary wiring and power supply

## Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software) or [PlatformIO](https://platformio.org/)
- [ESP8266 Board Package](https://github.com/esp8266/Arduino)
- [TinyGPS++ library](https://github.com/mikalhart/TinyGPSPlus)
- [SdFat library](https://github.com/greiman/SdFat)
- [U8g2 library](https://github.com/olikraus/u8g2)

## Wiring

Connect the components as follows:

- **GPS Module**:
  - GPS RX to ESP8266 TX (GPIO1)
  - GPS TX to ESP8266 RX (GPIO3)
- **OLED Display**:
  - SDA to ESP8266 SDA (GPIO4)
  - SCL to ESP8266 SCL (GPIO5)
- **SD Card Module**:
  - MISO to ESP8266 MISO (GPIO12)
  - MOSI to ESP8266 MOSI (GPIO13)
  - SCK to ESP8266 SCK (GPIO14)
  - CS to ESP8266 CS (GPIO15)

<img src="/schematic.png" alt="hackernowful" width="900px" height="500px" /><br><br>
## Installation

1. **Clone the repository**:
    ```sh
    git clone https://github.com/your-username/signal-seeker.git
    cd signal-seeker
    ```

2. **Install dependencies**:
    Open the Arduino IDE or PlatformIO and install the required libraries mentioned above.

3. **Upload the code**:
    Connect your ESP8266 to the computer and upload the code from the `signal-seeker.ino` file.

## Usage

1. **Power up the device**: Connect the ESP8266 to a power source.
2. **Initialize components**: The device will initialize the SD card and GPS module.
3. **Start scanning**: The device will continuously scan for Wi-Fi networks and log their details along with GPS coordinates.
4. **Check the display**: The OLED display will show the number of detected networks and status icons for Wi-Fi, SD card, and GPS.
5. **Access logged data**: The scanned network details are stored in `networks.csv` on the SD card.

## CSV File Format

The `networks.csv` file stores data in the following format:<br>
SSID, Latitude, Longitude, RSSI, Channel, BSSID, Encryption
## Example Output
MyWiFi,37.7749,-122.4194,-45,6,00:14:22:01:23:45,WPA2<br>
PublicWiFi,37.7749,-122.4194,-67,11,00:14:22:01:23:46,Open


## Troubleshooting

- **SD card initialization failed**: Ensure the SD card is properly connected and formatted.
- **GPS not working**: Check the connections and ensure the GPS module has a clear view of the sky.
- **Wi-Fi scan not working**: Ensure the ESP8266 is correctly powered and within range of Wi-Fi networks.

## Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Author

Hacker Nowful

Hacker Nowful is a cybersecurity enthusiast and developer with a passion for creating innovative tools for the security community. With expertise in various programming languages and a deep understanding of security principles, Nowful contributes to open-source projects aimed at enhancing security testing and education. For more information, visit his [GitHub profile](https://github.com/HackerNowful).

## Acknowledgments

Special thanks to the open-source community and contributors who have helped in the development and improvement of SignalSeeker. Your support and contributions are greatly appreciated.

- Special thanks to the Cifer Tech For the BITMAP

Visit [SignalSeeker](https://github.com/HackerNowful/SignalSeeker) to get started.

<br>
#esp8266 #wardriving #arduino #wardrive #pandapod #hackernowful #samykamkar
