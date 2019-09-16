float Print_Temp(float temp, byte a, byte b){
  if (temp>9) {
    lcd.setCursor(a+1,b);
    lcd.print(temp);
  } else if(temp>-1) {
    lcd.setCursor(a,b);
    lcd.print(" ");
    lcd.setCursor(a+1,b);
    lcd.print("0");
    lcd.print(temp);
  }else if (temp <= -1 && temp >= -9){
    lcd.setCursor(a,b);
    lcd.print("-");
    lcd.setCursor(a+1,b);
    lcd.print("0");
    lcd.print(temp*(-1));
  }else{
    lcd.setCursor(a,b);
    lcd.print(temp);
  }
}

float Print_Hume(float hume, byte a, byte b){
  if (Hume1>9) {
    lcd.setCursor(a,b);
    lcd.print(Hume1);
  } else {
    lcd.setCursor(a,b);
    lcd.print("0");
    lcd.print(Hume1);
  }
}

int Print_Fecha(byte a, byte b){
  if (dia>9){
    lcd.setCursor(a, b);
    lcd.print(dia);
    lcd.print("/");
  } else{
    lcd.setCursor(a, b);
    lcd.print("0");
    lcd.print(dia);
    lcd.print("/");
  }
  if (mes>9){
    lcd.setCursor(a+3, b);
    lcd.print(mes);
    lcd.print("/");
  } else{
    lcd.setCursor(a+3, b);
    lcd.print("0");
    lcd.print(mes);
    lcd.print("/");
  }
  lcd.print(year);
}

int Print_Hora(byte a, byte b){
  if(hora>9){
    lcd.setCursor(a, b);
    lcd.print(hora);
    lcd.print(":");
  } else {
    lcd.setCursor(a, b);
    lcd.print("0");
    lcd.print(hora);
    lcd.print(":");
  }
  if (minuto>9) {
    lcd.setCursor(a + 3, b);
    lcd.print(minuto);
  } else {
    lcd.setCursor(a + 3, b);
    lcd.print("0");
    lcd.print(minuto);
  }
}



void showDate(const DateTime& dt) {
    Serial.print(dt.year(), DEC);
    Serial.print('/');
    Serial.print(dt.month(), DEC);
    Serial.print('/');
    Serial.print(dt.day(), DEC);
    Serial.print(' ');
    Serial.print(dt.hour(), DEC);
    Serial.print(':');
    Serial.print(dt.minute(), DEC);
    Serial.print(':');
    Serial.print(dt.second(), DEC);
    Serial.println();
}
