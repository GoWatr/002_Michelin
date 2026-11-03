#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long Totalizer_F1;
unsigned long Flowrate_F1;
unsigned long Totalizer_F2;
unsigned long Flowrate_F2;
int dummy_fr = 0;

void lcd_startup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(5, 0);
  lcd.print("GOWATR");
  lcd.setCursor(4, 1);
  lcd.print("FLOWMETER");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("INITIALIZING....");
}

void lcd_send_req_1()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WAITING FOR DATA");
  lcd.setCursor(0, 1);
  lcd.print("FROM FLOWMETER 1");
}
void lcd_send_req_2()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WAITING FOR DATA");
  lcd.setCursor(0, 1);
  lcd.print("FROM FLOWMETER 2");
}
void lcd_print_fm1()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T1 = " + String(Totalizer_F1));
  lcd.setCursor(13, 0);
  lcd.print("Ltr");
  if (Flowrate_F1 < 100) {
    lcd.setCursor(0, 1);
    lcd.print("F1 = " + String(Flowrate_F1));
    lcd.setCursor(13, 1);
    lcd.print("L/m");
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print("F1 = " + String(dummy_fr));
    lcd.setCursor(13, 1);
    lcd.print("L/m");
  }
}

void lcd_print_fm2()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T2 = " + String(Totalizer_F2));
  lcd.setCursor(13, 0);
  lcd.print("Ltr");
  if (Flowrate_F2 < 100) {
    lcd.setCursor(0, 1);
    lcd.print("F2 = " + String(Flowrate_F2));
    lcd.setCursor(13, 1);
    lcd.print("L/m");
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print("F1 = " + String(dummy_fr));
    lcd.setCursor(13, 1);
    lcd.print("L/m");
  }
}
