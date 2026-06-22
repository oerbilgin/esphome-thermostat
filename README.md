# Making an esphome thermostat

## Materials
- [Waveshare touch 4.3B](https://docs.waveshare.com/ESP32-S3-Touch-LCD-4.3B)

The hardware spec sheets and documentation for the device are in `hardware_resources/`

## ESPHome docker commands
- Compile without flashing: `docker run --rm -v "${PWD}":/config -it esphome/esphome compile <ESPHOME_YAML_FILE>`
- Compile and flash OTA: `docker run --rm -v "${PWD}":/config -it esphome/esphome run <ESPHOME_YAML_FILE> --device <DEVICE_IP_ADDRESS>`


## Device setup
I had quite a hard time initially getting the esphome setup to get the display rendering correctly. The stable configuration I ended up with is in `hello_world.yaml`, which features a stable display and no screen tearing when there is WiFi acivity. Unsure if all build flags are necessary, but it works now.

## Thermostat Control
- Using `wtahler`'s repo https://github.com/wtahler/esphome-mideaXYE-rs485 as a starting point for the RS485 controls

### Changes performed:
- 
