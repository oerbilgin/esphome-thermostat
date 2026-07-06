#include "esphome.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>


#define RX_PIN 43 // This is the correct pin for the waveshare device
#define TX_PIN 44 // This is the correct pin for the waveshare device

#define CMD_VAL 1
#define SEND_MODE 6
#define SEND_FAN 7
#define SEND_TEMP 8
#define SEND_CRC 14
#define SEND_LEN 16

#define REC_MODE 8
#define REC_FAN 9
#define REC_TEMP 10
#define T1_INDEX 11
#define T2A_INDEX 12
#define T2B_INDEX 13
#define T3_INDEX 14
#define REC_E1 22
#define REC_E2 23
#define AMPS 15 // maybe... when off i see 0xFF which is 256 and the docs say this is freqency

#define foo 0x13

using namespace esphome;

class xyeVars {
  public:
    uint8_t setTemp = 70;
    uint8_t sendTimeCount = 0;
    bool newInput = false;
    std::string op = "off";
    std::string fanMode = "auto";
    uint8_t fanBytes = 0x00;
    uint8_t opBytes = 0x00;
    bool doneReading = false;
    uint8_t waitCount = 0;
    uint8_t prevResp = 0;
    bool waitingToSend = false;
    bool waitingForResponse = false;
    bool commandSent = false;
    uint8_t recData[30] = { 
      0x00, // 0 preamble; usually 0xAA
			0x00, // x 1 response code: 0xc0 - Query, 0xc3 - Set, 0xC4 - Extended Query?, OxC6 - Follow Me, 0xcc - Lock, 0xcd - Unlock 
			0x00, // x 2 to master, 0x00 or 0x80
			0x00, // x 3 destination, always 0x00
			0x00, // x 4 source/own id, always 0x00
			0x00, // x 5 destination, always 0x00
			0x00, // x 6 unclear, maybe capabilities, always 0x30
			0x00, // x 7 unclear, maybe capabilities, always 0x14
			0x00, // > 8 opeation mode; 0x00/0x04 - off, 0x80 - auto, 0x88 - Cool, 0x82 - Dry, 0x84 - Heat, 0x81 - Fan
			0x00, // > 9 fan mode; 0x8* = Auto Fan flag. 0x0* = manual set flag. Current fan speed = 0x*0 = Stopped, 0x*1 = High, 0x*2 = Medium, 0x*4 = Low.
			0x00, // > 10 set temp
			0x00, // > 11 T1 temp
			0x00, // > 12 T2A temp
			0x00, // x 13 T2B temp -- i usually see this as 0x00
			0x00, // > 14 T3 temp
			0x00, // x 15 current in amps? I see 0xFF when off. might mean missing sensor
			0x00, // x 16 unclear, might be frequency... I see 0x00 when off. could it be swapped with current?
			0x00, // x 17 timer start? Sum of: 0x01 - 15min, 0x02 - 30min, 0x04 - 1h, 0x08 - 2h, 0x10 - 4h, 0x20 - 8h, 0x40 - 16h 0x80 - invalid
			0x00, // x 18 timer stop? Sum of: 0x01 - 15min, 0x02 - 30min, 0x04 - 1h, 0x08 - 2h, 0x10 - 4h, 0x20 - 8h, 0x40 - 16h 0x80 - invalid
			0x00, // x 19 may be state of outdoor unit, but i have only seen 0x00. 0x00 is off, 0x01 means run?, 0x02 fan only, 0x03 fan and compressor.
			0x00, // > 20 mode flags: 0x02 - Aux Heat (Turbo), 0x00 - norm, 0x01 - ECO Mode (sleep), 0x04 - SWING, 0x88 VENT. I only saw sleep 0x01, not turbo
			0x00, // x 21 oper flags: 0x04 - water pump running, 0x80 - locked
			0x00, // > 22 error: E + bit pos, (0…7)
			0x00, // > 23 error: E + bit pos, (7…f)
			0x00, // ? 24 protect: P + bit pos, (0…7)
			0x00, // ? 25 protect: P + bit pos, (7…f)
			0x00, // ? 26 CCM Comm error
			0x00, // x 27 unclear
			0x00, // ? 28 startup status flag 1? Counts up and then 0xE0 is Normal Operation 
			0x00, // ? 29 Startup Status Flag 2? - 0x01 is Normal Operation
    };
    uint8_t sendData[16] = {0xaa, 0xc3, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x55};
    uint8_t waitSendData[16] = {0xaa, 0xc3, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x55};
    uint8_t queryData[16] = {0xaa, 0xc0, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x81, 0x55};
    uint8_t checkData[6] = {0xaa, 0xc0, 0x80, 0x00, 0x00, 0x00};
} xyeVars;


