void Control (){
 FH = rtc.now();
if(Fases >= 1){


}

 float t = dht.readTemperature();
 float h = dht.readHumidity();
 if ( isnan(t) || isnan(h) ) { //Error en la lectura dht
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.println("ERROR");
   return;
 }
}
