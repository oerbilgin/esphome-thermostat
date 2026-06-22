# Making an esphome thermostat

## Hardware
- [Waveshare touch 4.3B](https://docs.waveshare.com/ESP32-S3-Touch-LCD-4.3B)

## ESPHome docker commands
- Compile without flashing: `docker run --rm -v "${PWD}":/config -it esphome/esphome compile <ESPHOME_YAML_FILE>`
- Compile and flash OTA: `docker run --rm -v "${PWD}":/config -it esphome/esphome run <ESPHOME_YAML_FILE> --device <DEVICE_IP_ADDRESS>`

## Device setup
I had quite a hard time initially getting the esphome setup to get the display rendering correctly. The stable configuration I ended up with is in `config/hello_world.yaml`, which features a stable display and no screen tearing when there is WiFi acivity. Unsure if all build flags are necessary, but it works now.

The stable hardware setup is now in `config/hardware_config.yaml` and can be reused. The thermostat UI is in `config/thermostat.yaml`

## Thermostat Control
- Using `wtahler`'s repo https://github.com/wtahler/esphome-mideaXYE-rs485 as a starting point for the RS485 controls

### Changes performed:
- 
