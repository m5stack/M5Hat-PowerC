/*
*******************************************************************************
* Copyright (c) 2022 by M5Stack
*                  Equipped with M5StickCPlus sample source code
*                          配套  M5StickCPlus 示例源代码
* Visit for more information: https://docs.m5stack.com/en/hat/hat-powerc
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/hat/hat-powerc
*
* Product: PowerC HAT
* Date: 2022/07/19
*******************************************************************************
  Read battery current and voltage information such as whether it is charging or
  not
  读取电池电流电压是否充电等信息
*/
#include <M5StickCPlus.h>

#include "Hat_PowerC.h"
TFT_eSprite canvas = TFT_eSprite(&M5.Lcd);

PowerC powerc;

void setup() {
    M5.begin();
    M5.Lcd.setRotation(1);
    canvas.createSprite(160, 80);
    canvas.setTextColor(ORANGE);
    while (!powerc.begin()) {
        canvas.fillSprite(BLACK);
        canvas.setCursor(0, 10);
        canvas.println("POWERC INIT ERROR");
        canvas.println("Pls click the power btn and check the I2C connect.");
        canvas.pushSprite(10, 0);
        delay(1000);
    }
}

char info[50];

void loop() {
    if (powerc.update()) {
        float v     = powerc.voltage;
        float i     = powerc.current;
        float p     = powerc.power;
        bool charge = powerc.charged;
        canvas.fillSprite(BLACK);
        canvas.setCursor(0, 10);
        sprintf(info, "BAT: %1.2fV\r\n%1.2fmA\r\npower:%1.2fw\r\nischarge: %d",
                v, i, p, charge);
        canvas.println(info);
        canvas.pushSprite(10, 0);
        delay(100);
    } else {
        canvas.fillSprite(BLACK);
        canvas.setCursor(0, 10);
        canvas.println("powerc update error..");
        canvas.pushSprite(10, 0);
    }
}
