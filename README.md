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
- Used `wtahler`'s repo https://github.com/wtahler/esphome-mideaXYE-rs485 as a starting point for the RS485 controls

## Development tips
### Setup
```sh
uv venv .venv --python 3.12
source .venv/bin/activate
uv pip install esphome pillow
```

### Commands
Assuming we are in the `venv`, and in the `config/` directory
- `esphome compile thermostat.yaml`
- `esphome run thermostat.yaml --device 192.168.1.56`
- `esphome logs thermostat.yaml --device 192.168.1.56 --no-states`

### VSCode extensions
- ESPHome extension
    - set the dashboard URI to `http://localhost:6052`
    - set the validator to `dashboard`
    - run esphome server via `docker-compose up -d`

### ESPHome emulator
```sh
brew install sdl2
source .venv/bin/activate
cd config
esphome run simulator_config.yaml
```