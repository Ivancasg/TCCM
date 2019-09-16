//Funciones generales para botones

/***************************************************************************************************
****************************************************************************************************
***                        ___                                                                   ***
***                       | __| _ _    _ __  _ _  ___  __  ___  ___ ___                          ***
***                       | _| | ' \  | '_ \| '_|/ _ \/ _|/ -_)(_-</ _ \                         ***
***                       |___||_||_| | .__/|_|  \___/\__|\___|/__/\___/                         ***
***                                   |_|                                                        ***
***                                                                                              ***
****************************************************************************************************
***************************************************************************************************/

/*-------------------------------------------BOTÓN ROJO-------------------------------------------*/

int Boton_Cancelar(int tiempo_ms) {
  if (!digitalRead(Cancelar) ) {
    if (!E_Cancelar) lastTime = millis();
    E_Cancelar = true;
    if (millis() - lastTime >= tiempo_ms) {
      E_Cancelar = false;
      return 2;
    }
    BackReset();
  }
  delay(50);

  if ( (E_Cancelar) && (digitalRead(Cancelar)) ) {
    delay(150);
    E_Cancelar = false;
    return 1;
  }else return 0;
}

/*-------------------------------------------BOTÓN VERDE------------------------------------------*/

int Boton_Aceptar(int tiempo_ms) {
  if (!digitalRead(Aceptar) ) {
    if (!E_Aceptar) lastTime = millis();
    E_Aceptar = true;
    if (millis() - lastTime >= tiempo_ms) {
      E_Aceptar = false;
      return 2;
    }
    BackReset();
  }
  delay(50);

  if ( (E_Aceptar) && (digitalRead(Aceptar)) ) {
    delay(150);
    E_Aceptar = false;
    return 1;
  }else return 0;
}

/*-------------------------------------------BOTÓN ARRIBA-----------------------------------------*/
int Boton_Arriba(int tiempo_ms){
  if (!digitalRead(Arriba) ) {
    if (!E_Arriba) lastTime = millis();
    E_Arriba = true;
    if (millis() - lastTime >= tiempo_ms) {
      E_Arriba = false;
      return 2;
    }
    BackReset();
  }
  delay(50);

  if ( (E_Arriba) && (digitalRead(Arriba)) ) {
    E_Arriba = false;
    delay(100);
    return 1;
  }else return 0;
}

/*-------------------------------------------BOTÓN ABAJO------------------------------------------*/
int Boton_Abajo(int tiempo_ms){
  if (!digitalRead(Abajo) ) {
    if (!E_Abajo) lastTime = millis();
    E_Abajo = true;
    if (millis() - lastTime >= tiempo_ms) {
      E_Abajo = false;
      return 2;
    }
    BackReset();
  }
  delay(50);

  if ( (E_Abajo) && (digitalRead(Abajo)) ) {
    E_Abajo = false;
    delay(100);
    return 1;
  }else return 0;
}
/*-------------------------------------------BOTONES int------------------------------------------*/
int Botones(int index, int min, int max){
  if(!digitalRead(Abajo)){
    BackReset();
    index--;
    delay(100);
    if(index<min) index=max;
  }
  if(!digitalRead(Arriba)){
    BackReset();
    index++;
    delay(100);
    if(index>max) index=min;
  }
  return index;
}
/*-------------------------------------------BOTONES float----------------------------------------*/
float BotonesFloat(float index, float min, float max){
  if(!digitalRead(Abajo)){
    BackReset();
    index--;
    delay(100);
    if(index<min) index=max;
  }
  if(!digitalRead(Arriba)){
    BackReset();
    index++;
    delay(100);
    if(index>max) index=min;
  }
  return index;
}

void Backlight(){
    inactivo++;
    if (inactivo>100){
    lcd.noBacklight();
    }
}

void BackReset(){
  lcd.backlight();
  inactivo=0;
}
