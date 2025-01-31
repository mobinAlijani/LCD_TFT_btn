#include <TFT_eSPI.h>  // کتابخانه TFT_eSPI
#include <bb_captouch.h>
#include <Wire.h>
#include "imag.h"

TFT_eSPI tft = TFT_eSPI();  // تعریف شیء نمایشگر
BBCapTouch bbct;
// متغیر برای ذخیره اطلاعات لمس

#define TOUCH_SDA 39
#define TOUCH_SCL 42
#define TOUCH_INT 40
#define TOUCH_RST -1

bool btnStates[] = { false, false, false, false };  // وضعیت دکمه‌ها
// متغیرهای ذخیره وضعیت لمس

TOUCHINFO ti;
int prevX = -1, prevY = -1;  // مختصات قبلی لمس
bool isTouchedPrev = false;  // وضعیت لمس قبلی


void setup() {
  tft.init();                 // مقداردهی اولیه نمایشگر
  tft.setRotation(1);         // تنظیم چرخش صفحه (افقی)
  tft.fillScreen(TFT_BLACK);  // رنگ پس‌زمینه (مشکی)
  Serial.begin(115200);

  bbct.init(TOUCH_SDA, TOUCH_SCL, TOUCH_RST, TOUCH_INT);
  delay(100);

  MenuShow(-1);
  buttonShow();
  TextShow();
}


void loop() {

  TOUCHINFO ti;

  // خواندن داده‌های تاچ
  if (bbct.getSamples(&ti)) {
    bool isTouched = ti.count > 0;     // آیا صفحه لمس شده است؟
    int x = isTouched ? ti.x[0] : -1;  // اگر لمس فعال است، مختصات X را بخوانید
    int y = isTouched ? ti.y[0] : -1;  // اگر لمس فعال است، مختصات Y را بخوانید

    // بررسی تغییر وضعیت لمس
    if (isTouched != isTouchedPrev || x != prevX || y != prevY) {
      handleTouch(x, y);  // پردازش تغییر
    }

    // به‌روزرسانی وضعیت قبلی
    isTouchedPrev = isTouched;
    prevX = x;
    prevY = y;
  }
}

void handleTouch(int x, int y) {
  // بررسی محدوده دکمه‌های منو
  if (x > 150 && x < 190 && y > 5 && y < 170) {
    btnStates[0] = !btnStates[0];  // تغییر وضعیت دکمه
    MenuShow(0);                   // به‌روزرسانی نمایش دکمه‌ها
    return;
  }

  if (x > 80 && x < 130 && y > 5 && y < 170) {
    btnStates[1] = !btnStates[1];  // تغییر وضعیت دکمه
    MenuShow(1);                   // به‌روزرسانی نمایش دکمه‌ها
    return;
  }

  if (x > 10 && x < 60 && y > 5 && y < 170) {
    btnStates[2] = !btnStates[2];  // تغییر وضعیت دکمه
    MenuShow(2);                   // به‌روزرسانی نمایش دکمه‌ها
    return;
  }


  // بررسی محدوده دکمه پاور
  if (x > 10 && x < 140 && y > 190 && y < 300) {
    btnStates[3] = !btnStates[3];  // تغییر وضعیت دکمه پاور
    buttonShow();                  // به‌روزرسانی نمایش دکمه پاور
    return;
  }
}

void TextShow() {
  //   drawRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color)
  tft.drawRect(190, 10, 120, 70, TFT_RED);
  tft.setTextColor(TFT_WHITE);
  tft.setTextDatum(MC_DATUM);  // تنظیم متن به مرکز
  tft.setTextSize(1);
  tft.drawString("ESP_32", 250, 50,4);
}

void buttonShow() {

  uint16_t centerX = 250;  // مختصات X مرکز
  uint16_t centerY = 160;  // مختصات Y مرکز
  uint16_t radius = 60;    // شعاع نماد دایره روشن/خاموش

  uint16_t btnColor = btnStates[3] ? TFT_GREEN : TFT_RED;

  tft.fillCircle(centerX, centerY, radius, TFT_WHITE);  // رسم دایره پر
  int i = 62;
  while (i-- > 56) {
    tft.drawSmoothCircle(centerX, centerY, i, btnColor, btnColor);  // حلقه‌های بیرونی با گرادیان سبز
  }
  tft.pushImage(218, 128, 64, 64, power);
}

void MenuShow(int num) {
  uint16_t w = 170;  // عرض دکمه‌ها
  uint16_t h = 55;   // ارتفاع دکمه‌ها
  uint16_t r = 15;   // شعاع گوشه‌های گرد

  uint16_t startX = 5;    // مختصات x شروع
  uint16_t startY = 45;   // مختصات y شروع
  uint16_t spacing = 65;  // فاصله بین دکمه‌ها

  tft.setTextDatum(MC_DATUM);  // تنظیم متن به مرکز

  if (num != -1) {

    uint16_t y = startY + num * spacing;
    uint16_t btnColor = btnStates[num] ? TFT_BLUE : TFT_RED;
    // رسم مستطیل گرد با گرادیان (اختیاری)
    drawSmoothRoundRect(startX, y, w, h, r, btnColor, TFT_CYAN);

    // اضافه کردن متن به دکمه
    tft.setTextDatum(MC_DATUM);             // تنظیم متن به مرکز
    tft.setTextColor(TFT_WHITE, btnColor);  // رنگ متن و پس‌زمینه
    tft.drawString("Menu " + String(num + 1), startX + w / 2, y + h / 2, 4);

  } else {
    // رسم دکمه‌ها
    for (int i = 0; i < 3; i++) {
      uint16_t y = startY + i * spacing;
      uint16_t btnColor = btnStates[i] ? TFT_BLUE : TFT_RED;

      // رسم مستطیل گرد با گرادیان (اختیاری)
      drawSmoothRoundRect(startX, y, w, h, r, btnColor, TFT_CYAN);

      // اضافه کردن متن به دکمه
      tft.setTextDatum(MC_DATUM);             // تنظیم متن به مرکز
      tft.setTextColor(TFT_WHITE, btnColor);  // رنگ متن و پس‌زمینه
      tft.drawString("Menu " + String(i + 1), startX + w / 2, y + h / 2, 4);
    }
  }
}

// تابع برای رسم مستطیل نرم با گرادیان
void drawSmoothRoundRect(int x, int y, int w, int h, int r, uint16_t color1, uint16_t color2) {
  for (int i = r; i > 0; i--) {
    uint16_t gradientColor = tft.color565(
      map(i, 0, r, (color1 >> 11) * 8, (color2 >> 11) * 8),                      // قرمز
      map(i, 0, r, ((color1 & 0x07E0) >> 5) * 4, ((color2 & 0x07E0) >> 5) * 4),  // سبز
      map(i, 0, r, (color1 & 0x001F) * 8, (color2 & 0x001F) * 8)                 // آبی
    );
    tft.fillRoundRect(x + (r - i), y + (r - i), w - 2 * (r - i), h - 2 * (r - i), i, gradientColor);
  }
}
