#pragma once
#include "esphome.h"

namespace my_colors {
    lv_color_t text_dark_gray = lv_color_hex(0x6B7280);
    lv_color_t text_light_gray = lv_color_hex(0xC3C4C6);

    lv_color_t bg_blue_green = lv_color_hex(0xCFF0F8);
    lv_color_t bg_dark_blue = lv_color_hex(0xCEDDF8);
    lv_color_t bg_light_blue = lv_color_hex(0xCFF0F8);
    lv_color_t bg_green = lv_color_hex(0xDCFCE7);
    lv_color_t bg_yellow = lv_color_hex(0xFEF3C7);
    lv_color_t bg_orange = lv_color_hex(0xFEDCC8);
    lv_color_t bg_red = lv_color_hex(0xFEE2E2);
    lv_color_t bg_purple = lv_color_hex(0xFCE1FE);
    lv_color_t bg_maroon = lv_color_hex(0xCF7D88);

    lv_color_t text_blue_green = lv_color_hex(0x11A6A6);
    lv_color_t text_dark_blue = lv_color_hex(0x3838E5);
    lv_color_t text_light_blue = lv_color_hex(0x0369A1);
    lv_color_t text_green = lv_color_hex(0x16A34A);
    lv_color_t text_yellow = lv_color_hex(0xCA8A04);
    lv_color_t text_orange = lv_color_hex(0xC86604);
    lv_color_t text_red = lv_color_hex(0xDC2626);
    lv_color_t text_purple = lv_color_hex(0xA928DC);
    lv_color_t text_maroon = lv_color_hex(0xAC2A44);
}

lv_color_t get_color_mix(float temp, size_t num_thresholds, const float thresholds[], const lv_color_t colors[]) {
    if (num_thresholds == 0) {
        return colors[0];
    }

    if (temp < thresholds[0]) {
        return colors[0];
    }

    if (temp >= thresholds[num_thresholds - 1]) {
        return colors[num_thresholds];
    }

    size_t segment = 0;
    for (; segment + 1 < num_thresholds; ++segment) {
        if (temp < thresholds[segment + 1]) {
            break;
        }
    }

    float low_t = thresholds[segment];
    float high_t = thresholds[segment + 1];
    lv_color_t c_low = colors[segment];
    lv_color_t c_high = colors[segment + 1];

    float val = temp;
    if (val < low_t)  val = low_t;
    if (val > high_t) val = high_t;

    uint8_t ratio = (uint8_t)(((val - low_t) / (high_t - low_t)) * 255.0f);
    lv_color_t color = lv_color_mix(c_high, c_low, ratio);

    ESP_LOGD("get_temp_color", "temp=%.2f low=%.2f high=%.2f ratio=%hhu", temp, low_t, high_t, ratio);
    return color;
}

// Returns an LVGL color interpolated between your cool and hot bounds
lv_color_t get_temp_bg_color(float temp) {
    ESP_LOGD("get_temp_bg_color", "Input is %f", temp);

    const int NUM_STEPS = 6;
    float thresholds[NUM_STEPS] = {45.0f, 62.0f, 67.0f, 74.0f, 78.0f, 85.0f};
    lv_color_t colors[NUM_STEPS + 1] = { 
        my_colors::bg_dark_blue,
        my_colors::bg_light_blue,
        my_colors::bg_blue_green,
        my_colors::bg_green,
        my_colors::bg_yellow,
        my_colors::bg_orange,
        my_colors::bg_red
    };

    return get_color_mix(temp, NUM_STEPS, thresholds, colors);
}

lv_color_t get_temp_text_color(float temp) {
    ESP_LOGD("get_temp_text_color", "Input is %f", temp);

    const int NUM_STEPS = 6;
    float thresholds[NUM_STEPS] = {45.0f, 62.0f, 67.0f, 74.0f, 78.0f, 85.0f};
    lv_color_t colors[NUM_STEPS + 1] = {
        my_colors::text_dark_blue,
        my_colors::text_light_blue,
        my_colors::text_blue_green,
        my_colors::text_green,
        my_colors::text_yellow,
        my_colors::text_orange,
        my_colors::text_red
    };

    return get_color_mix(temp, NUM_STEPS, thresholds, colors);
}

lv_color_t get_aqi_text_color(float val) {
    ESP_LOGD("get_aqi_text_color", "Input is %f", val);

    if (val < 50) {
        return my_colors::text_green;
    } else if (val < 100) {
        return my_colors::text_yellow;
    } else if (val < 150) {
        return my_colors::text_orange;
    } else if (val < 200) {
        return my_colors::text_red;
    } else if (val < 300) {
        return my_colors::text_purple;
    } else {
        return my_colors::text_maroon;
    }
}

lv_color_t get_aqi_bg_color(float val) {
    ESP_LOGD("get_aqi_bg_color", "Input is %f", val);

    if (val < 50) {
        return my_colors::bg_green;
    } else if (val < 100) {
        return my_colors::bg_yellow;
    } else if (val < 150) {
        return my_colors::bg_orange;
    } else if (val < 200) {
        return my_colors::bg_red;
    } else if (val < 300) {
        return my_colors::bg_purple;
    } else {
        return my_colors::bg_maroon;
    }
}

lv_color_t get_wind_text_color(float val) {
    ESP_LOGD("get_wind_text_color", "Input is %f", val);

    if (val < 3) {
        return my_colors::text_light_blue;
    } else if (val < 12) {
        return my_colors::text_green;
    } else if (val < 24) {
        return my_colors::text_yellow;
    } else if (val < 38) {
        return my_colors::text_red;
    } else if (val < 54) {
        return my_colors::text_purple;
    } else {
        return my_colors::text_maroon;
    }
}

lv_color_t get_wind_bg_color(float val) {
    ESP_LOGD("get_wind_bg_color", "Input is %f", val);

    if (val < 3) {
        return my_colors::bg_light_blue;
    } else if (val < 12) {
        return my_colors::bg_green;
    } else if (val < 24) {
        return my_colors::bg_yellow;
    } else if (val < 38) {
        return my_colors::bg_red;
    } else if (val < 54) {
        return my_colors::bg_purple;
    } else {
        return my_colors::bg_maroon;
    }
}