void Menu () {

  if (iForm == 0) { //Pantalla de inicio
    digitalWrite(releTemp, HIGH); //Relee Temperatura apagado
    digitalWrite(releHume, HIGH); //Relee Humedad apagado
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Bienvenido(a)");
    lcd.setCursor(1, 3);
    lcd.print("Configurar");
    lcd.setCursor(12, 3);
    lcd.print("Comenzar");
    iMenu=0;
    while(iForm == 0){
      FH = rtc.now();
      minuto = FH.minute();
      hora = FH.hour();
      dia = FH.day();
      mes = FH.month();
      year = FH.year();
      iMenu = Botones(iMenu, 0, 1);
      iAceptar = Boton_Aceptar(5000);
      if ( (iAceptar == 1) && (iMenu == 0) )  iForm = 1;
      if ( (iAceptar == 1) && (iMenu == 1) )  iForm = 2;
      Print_Fecha(2,1);
      Print_Hora(13,1);
      switch (iMenu) {
        case 0:
        lcd.setCursor(0, 3);
        lcd.print(">");
        lcd.setCursor(11, 3);
        lcd.print(" ");
        break;
        case 1:
        lcd.setCursor(0, 3);
        lcd.print(" ");
        lcd.setCursor(11, 3);
        lcd.print(">");
        break;
      }
      Backlight();
    }
  }

  if (iForm == 1) { //Configurar Fecha y Hora
    FH = rtc.now();
    minuto = FH.minute();
    hora = FH.hour();
    dia = FH.day();
    mes = FH.month();
    year = FH.year();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Configurar");
    lcd.setCursor(1, 1);
    lcd.print("Fecha: ");
    Print_Fecha(9,1);
    lcd.setCursor(1, 2);
    lcd.print("Hora: ");
    Print_Hora(9,2);
    lcd.setCursor(6, 3);
    lcd.print("Aceptar");
    iMenu = 0;
    iValor = 0;
    while (iForm == 1) {
      if (iMenu == 0) {
        lcd.setCursor(0, 1);
        lcd.print(">");
        lcd.setCursor(0, 2);
        lcd.print(" ");
        lcd.setCursor(5, 3);
        lcd.print(" ");
        while (iValor == 0) {
          Print_Fecha(9,1);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          dia = Botones(dia,1,31);
          if (iAceptar == 1)  iValor = 1;
          if (iCancelar == 1) {iForm = 0; iValor = 3;}
          if (iCancelar == 2) {iForm = 0; iValor = 3;}
          Backlight();
        }
        while (iValor == 1){
          Print_Fecha(9,1);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          mes = Botones(mes,1,12);
          if (iAceptar == 1) iValor = 2;
          if (iCancelar == 1) iValor = 0;
          if (iCancelar == 2) {iForm = 0; iValor = 3;};
          Backlight();
        }
        while(iValor == 2) {
          Print_Fecha(9,1);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          year = Botones(year,2019,2099);
          if (iAceptar == 1) {iMenu = 1; iValor=3;}
          if (iCancelar == 1) iValor = 1;
          if (iCancelar == 2) {iForm = 0; iValor = 3;};
          Backlight();
        }
      }
      if (iMenu == 1){
        lcd.setCursor(0, 1);
        lcd.print(" ");
        lcd.setCursor(0, 2);
        lcd.print(">");
        lcd.setCursor(5, 3);
        lcd.print(" ");
        iValor = 0;
        while (iValor == 0) {
          Print_Hora(9,2);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          hora = Botones(hora,0,23);
          if (iAceptar == 1) iValor = 1;
          if (iCancelar == 1) {iMenu = 0; iValor = 2;}
          if (iCancelar == 2) {iForm = 0; iValor = 3;}
          Backlight();
        }
        while (iValor == 1) {
          Print_Hora(9,2);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          minuto = Botones(minuto,0,59);
          if (iAceptar == 1) {iMenu = 2; iValor=2;}
          if (iCancelar == 1) iValor = 0;
          if (iCancelar == 2) {iForm = 0; iValor = 3;}
          Backlight();
        }
      }

      if(iMenu == 2){
        lcd.setCursor(0, 1);
        lcd.print(" ");
        lcd.setCursor(0, 2);
        lcd.print(" ");
        lcd.setCursor(5, 3);
        lcd.print(">");
        while (iMenu == 2) {
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          if (iAceptar == 1) {
            rtc.adjust(DateTime(year,mes,dia,hora,minuto,0));
            iForm = 0;
            iMenu = 3;
          }
          if (iCancelar == 1) {iMenu = 1; iValor = 2;}
          if (iCancelar == 2) {iMenu = 1; iForm = 0;}
          Backlight();
        }
      }
    }
  }

  if (iForm == 2) { //Numero de fases
    Fases=1;
    digitalWrite(releTemp, HIGH);
    digitalWrite(releHume, HIGH);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Numero de fases");
    while(iForm == 2){
      Fases = Botones(Fases, 1, 3);
      iAceptar = Boton_Aceptar(5000);
      iCancelar = Boton_Cancelar(5000);
      lcd.setCursor(9, 2);
      lcd.print(Fases);
      if (iAceptar == 1)  iForm = 3;
      if (iCancelar == 1) iForm = 2;
      if (iCancelar == 2) iForm = 2;
      Backlight();
    }
  }

  if (iForm == 3) { //Configurar fase 1
    FH = rtc.now();
    minuto = FH.minute();
    hora = FH.hour();
    dia = FH.day();
    mes = FH.month();
    year = FH.year();
    Temp1 = 10;
    Hume1 = 50;
    iMenu = 0;
    iValor = 0;
    digitalWrite(releTemp, HIGH);
    digitalWrite(releHume, HIGH);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Configurar Fase 1");
    lcd.setCursor(0, 1);
    lcd.print("Temperatura");
    Print_Temp(Temp1,13,1);
    lcd.setCursor(0, 2);
    lcd.print("Humedad");
    Print_Hume(Hume1,14,2);
    lcd.setCursor(0, 3);
    lcd.print("Fecha");
    Print_Fecha(9,3);
    while(iForm == 3){
      if (iMenu == 0) { //Configurar Temperatura
        lcd.setCursor(12, 1);
        lcd.print(">");
        lcd.setCursor(12, 2);
        lcd.print(" ");
        lcd.setCursor(8, 3);
        lcd.print(" ");
        while (iMenu == 0) {
          Print_Temp(Temp1,13,1);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          Temp1 = BotonesFloat(Temp1, -30,70);
          if (iAceptar == 1) iMenu = 1;
          if (iCancelar == 1) {iMenu = 4; iForm = 2;}
          if (iCancelar == 2) {iMenu = 4; iForm = 0;}
          Backlight();
        }
      }
      if (iMenu == 1) { //Configurar Humedad
        lcd.setCursor(12, 1);
        lcd.print(" ");
        lcd.setCursor(12, 2);
        lcd.print(">");
        lcd.setCursor(8, 3);
        lcd.print(" ");
        while (iMenu == 1) {
          lcd.setCursor(14, 2);
          Print_Hume(Hume1,14,2);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          Hume1 = BotonesFloat(Hume1, 0, 99);
          if (iAceptar == 1) iMenu = 2;
          if (iCancelar == 1) iMenu = 0;
          if (iCancelar == 2) {iMenu = 4; iForm = 0;}
          Backlight();
        }
      }
      if (iMenu == 2) { //Configurar Fecha
        lcd.setCursor(12, 1);
        lcd.print(" ");
        lcd.setCursor(12, 2);
        lcd.print(" ");
        lcd.setCursor(8, 3);
        lcd.print(">");
        while(iValor == 0) {
          Print_Fecha(9,3);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          dia = Botones(dia, 1, 31);
          if (iAceptar == 1) iValor = 1;
          if (iCancelar == 1) {iMenu = 1; iValor = 4;}
          if (iCancelar == 2) {iMenu = 4; iForm = 0; iValor = 4;}
          Backlight();
        }
        while(iValor == 1) {
          Print_Fecha(9,3);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          mes = Botones(mes, 0, 12);
          if (iAceptar == 1) iValor = 2;
          if (iCancelar == 1) {iValor = 0;}
          if (iCancelar == 2) {iMenu = 4; iForm = 0; iValor = 4;}
          Backlight();
        }
        while (iValor == 2) {
          Print_Fecha(9,3);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          year = Botones(year,2019,2099);
          if (iAceptar == 1) { iValor = 3; iMenu = 3;}
          if (iCancelar == 1) {iValor = 1;}
          if (iCancelar == 2) {iMenu = 4; iForm = 0; iValor = 4;}
          Backlight();
        }
      }
      if (iMenu == 3) { //Configurar Hora
        iValor = 0;
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Configurar Fase 1");
        lcd.setCursor(0, 1);
        lcd.print("Humedad");
        Print_Hume(Hume1, 14, 1);
        lcd.setCursor(0, 2);
        lcd.print("Fecha");
        Print_Fecha(9,2);
        lcd.setCursor(0, 3);
        lcd.print("Hora");
        Print_Hora(14, 3);
        lcd.setCursor(12, 1);
        lcd.print(" ");
        lcd.setCursor(8, 2);
        lcd.print(" ");
        lcd.setCursor(12, 3);
        lcd.print(">");
        while (iMenu == 3) {
          while (iValor == 0) {
            Print_Hora(14, 3);
            iAceptar = Boton_Aceptar(5000);
            iCancelar = Boton_Cancelar(5000);
            hora = Botones(hora, 0,23);
            if (iAceptar == 1) iValor = 1;
            if (iCancelar == 1) {iMenu = 2; iValor = 2;}
            if (iCancelar == 2) {iMenu = 4; iForm = 0; iValor = 4;}
            Backlight();
          }
          while (iValor == 1){
            Print_Hora(14, 3);
            iAceptar = Boton_Aceptar(5000);
            iCancelar = Boton_Cancelar(5000);
            minuto = Botones(minuto, 0, 59);
            if ( (iAceptar == 1) && (Fases == 1) ){
              iValor = 2;
              iForm = 6;
              iMenu = 4;
              Date1.setDate(year, mes, dia, hora, minuto, 0);
            } else if ( (iAceptar == 1) && (Fases >= 2) ) {
              iValor = 3;
              iForm = 4;
              iMenu = 4;
              Date1.setDate(year, mes, dia, hora, minuto, 0);
            }
            if (iCancelar == 1) {iValor = 0;}
            if (iCancelar == 2) {iMenu = 4; iValor = 0; iForm = 0;}
            Backlight();
          }
        }
      }
    }
  }

  if (iForm == 4) { //Configurar fase 2
    FH = rtc.now();
    minuto = FH.minute();
    hora = FH.hour();
    dia = FH.day();
    mes = FH.month();
    year = FH.year();
    Temp2 = 10;
    Hume2 = 50;
    iMenu = 0;
    iValor = 0;
    digitalWrite(releTemp, HIGH);
    digitalWrite(releHume, HIGH);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Configurar Fase 2");
    lcd.setCursor(0, 1);
    lcd.print("Temperatura");
    Print_Temp(Temp2,13,1);
    lcd.setCursor(0, 2);
    lcd.print("Humedad");
    Print_Hume(Hume2,14,2);
    lcd.setCursor(0, 3);
    lcd.print("Fecha");
    Print_Fecha(9,3);
    while(iForm == 4){
      if (iMenu == 0) { //Configurar Temperatura
        lcd.setCursor(12, 1);
        lcd.print(">");
        lcd.setCursor(12, 2);
        lcd.print(" ");
        lcd.setCursor(8, 3);
        lcd.print(" ");
        while (iMenu == 0) {
          Print_Temp(Temp2,13,1);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          Temp2 = BotonesFloat(Temp2, -30,70);
          if (iAceptar == 1) iMenu = 1;
          if (iCancelar == 1) {iMenu = 3; iValor = 1; iForm = 3;}
          if (iCancelar == 2) {iMenu = 4; iForm = 0;}
          Backlight();
        }
      }
      if (iMenu == 1) { //Configurar Humedad
        lcd.setCursor(12, 1);
        lcd.print(" ");
        lcd.setCursor(12, 2);
        lcd.print(">");
        lcd.setCursor(8, 3);
        lcd.print(" ");
        while (iMenu == 1) {
          lcd.setCursor(14, 2);
          Print_Hume(Hume2,14,2);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          Hume2 = BotonesFloat(Hume2, 0, 99);
          if (iAceptar == 1) iMenu = 2;
          if (iCancelar == 1) iMenu = 0;
          if (iCancelar == 2) {iMenu = 4; iForm = 0;}
          Backlight();
        }
      }
      if (iMenu == 2) { //Configurar Fecha
        lcd.setCursor(12, 1);
        lcd.print(" ");
        lcd.setCursor(12, 2);
        lcd.print(" ");
        lcd.setCursor(8, 3);
        lcd.print(">");
        while(iValor == 0) {
          Print_Fecha(9,3);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          dia = Botones(dia, 1, 31);
          if (iAceptar == 1) iValor = 1;
          if (iCancelar == 1) {iMenu = 1; iValor = 4;}
          if (iCancelar == 2) {iMenu = 4; iValor = 4; iForm = 0;}
          Backlight();
        }
        while(iValor == 1) {
          Print_Fecha(9,3);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          mes = Botones(mes, 0, 12);
          if (iAceptar == 1) iValor = 2;
          if (iCancelar == 1) iValor = 0;
          if (iCancelar == 2) {iMenu = 4; iValor = 4; iForm = 0;}
          Backlight();
        }
        while (iValor == 2) {
          Print_Fecha(9,3);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          year = Botones(year,2019,2099);
          if (iAceptar == 1) { iValor = 3; iMenu = 3; }
          if (iCancelar == 1) iValor = 1;
          if (iCancelar == 2) {iMenu = 4; iValor = 4; iForm = 0;}
          Backlight();
        }
      }
      if (iMenu == 3) { //Configurar Hora
        iValor = 0;
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Configurar Fase 2");
        lcd.setCursor(0, 1);
        lcd.print("Humedad");
        Print_Hume(Hume2, 14, 1);
        lcd.setCursor(0, 2);
        lcd.print("Fecha");
        Print_Fecha(9,2);
        lcd.setCursor(0, 3);
        lcd.print("Hora");
        Print_Hora(14, 3);
        lcd.setCursor(12, 1);
        lcd.print(" ");
        lcd.setCursor(8, 2);
        lcd.print(" ");
        lcd.setCursor(12, 3);
        lcd.print(">");
        while (iMenu == 3) {
          while (iValor == 0) {
            Print_Hora(14, 3);
            iAceptar = Boton_Aceptar(5000);
            iCancelar = Boton_Cancelar(5000);
            hora = Botones(hora, 0,23);
            if (iAceptar == 1) iValor = 1;
            if (iCancelar == 1) {iMenu = 2; iValor = 2;}
            if (iCancelar == 2) {iMenu = 4; iValor = 4; iForm = 0;}
            Backlight();
          }
          while (iValor == 1){
            Print_Hora(14, 3);
            iAceptar = Boton_Aceptar(5000);
            iCancelar = Boton_Cancelar(5000);
            minuto = Botones(minuto, 0, 59);
            if ( (iAceptar == 1) && (Fases == 2) ){
              iValor = 2;
              iForm = 6;
              iMenu = 4;
              Date2.setDate(year, mes, dia, hora, minuto, 0);
            } else if ( (iAceptar == 1) && (Fases == 3) ) {
              iValor = 3;
              iForm = 5;
              iMenu = 4;
              Date2.setDate(year, mes, dia, hora, minuto, 0);
            }
            if (iCancelar == 1) iValor = 0;
            if (iCancelar == 2) {iMenu = 4; iValor = 4; iForm = 0;}
            Backlight();
          }
        }
      }
    }
  }

  if (iForm == 5) { //Configurar fase 3
    FH = rtc.now();
    minuto = FH.minute();
    hora = FH.hour();
    dia = FH.day();
    mes = FH.month();
    year = FH.year();
    Temp3 = 10;
    Hume3 = 50;
    iMenu = 0;
    iValor = 0;
    digitalWrite(releTemp, HIGH);
    digitalWrite(releHume, HIGH);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Configurar Fase 3");
    lcd.setCursor(0, 1);
    lcd.print("Temperatura");
    Print_Temp(Temp3,13,1);
    lcd.setCursor(0, 2);
    lcd.print("Humedad");
    Print_Hume(Hume3,14,2);
    lcd.setCursor(0, 3);
    lcd.print("Fecha");
    Print_Fecha(9,3);
    while(iForm == 5){
      if (iMenu == 0) { //Configurar Temperatura
        lcd.setCursor(12, 1);
        lcd.print(">");
        lcd.setCursor(12, 2);
        lcd.print(" ");
        lcd.setCursor(8, 3);
        lcd.print(" ");
        while (iMenu == 0) {
          Print_Temp(Temp3,13,1);
          iAceptar = Boton_Aceptar(5000);
          Temp3 = BotonesFloat(Temp3, -30,70);
          if (iAceptar == 1) iMenu = 1;
          if (iCancelar == 1) {iMenu = 3; iValor = 1; iForm = 4;}
          if (iCancelar == 2) {iMenu = 4; iForm = 0;}
          Backlight();
        }
      }
      if (iMenu == 1) { //Configurar Humedad
        lcd.setCursor(12, 1);
        lcd.print(" ");
        lcd.setCursor(12, 2);
        lcd.print(">");
        lcd.setCursor(8, 3);
        lcd.print(" ");
        while (iMenu == 1) {
          lcd.setCursor(14, 2);
          Print_Hume(Hume3,14,2);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          Hume3 = BotonesFloat(Hume3, 0, 99);
          if (iAceptar == 1) iMenu = 2;
          if (iCancelar == 1) iMenu = 0;
          if (iCancelar == 2) {iMenu = 4; iForm = 0;}
          Backlight();
        }
      }
      if (iMenu == 2) { //Configurar Fecha
        lcd.setCursor(12, 1);
        lcd.print(" ");
        lcd.setCursor(12, 2);
        lcd.print(" ");
        lcd.setCursor(8, 3);
        lcd.print(">");
        while(iValor == 0) {
          Print_Fecha(9,3);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          dia = Botones(dia, 1, 31);
          if (iAceptar == 1) iValor = 1;
          if (iCancelar == 1) {iMenu = 1; iValor = 4;}
          if (iCancelar == 2) {iMenu = 4; iValor = 4; iForm = 0;}
          Backlight();
        }
        while(iValor == 1) {
          Print_Fecha(9,3);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          mes = Botones(mes, 0, 12);
          if (iAceptar == 1) iValor = 2;
          if (iCancelar == 1) iValor = 0;
          if (iCancelar == 2) {iMenu = 4; iValor = 4; iForm = 0;}
          Backlight();
        }
        while (iValor == 2) {
          Print_Fecha(9,3);
          iAceptar = Boton_Aceptar(5000);
          iCancelar = Boton_Cancelar(5000);
          year = Botones(year,2019,2099);
          if (iAceptar == 1) { iValor = 3; iMenu = 3; }
          if (iCancelar == 1) iValor = 1;
          if (iCancelar == 2) {iMenu = 4; iValor = 4; iForm = 0;}
          Backlight();
        }
      }
      if (iMenu == 3) { //Configurar Hora
        iValor = 0;
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Configurar Fase 3");
        lcd.setCursor(0, 1);
        lcd.print("Humedad");
        Print_Hume(Hume3, 14, 1);
        lcd.setCursor(0, 2);
        lcd.print("Fecha");
        Print_Fecha(9,2);
        lcd.setCursor(0, 3);
        lcd.print("Hora");
        Print_Hora(14, 3);
        lcd.setCursor(12, 1);
        lcd.print(" ");
        lcd.setCursor(8, 2);
        lcd.print(" ");
        lcd.setCursor(12, 3);
        lcd.print(">");
        while (iMenu == 3) {
          while (iValor == 0) {
            Print_Hora(14, 3);
            iAceptar = Boton_Aceptar(5000);
            iCancelar = Boton_Cancelar(5000);
            hora = Botones(hora, 0,23);
            if (iAceptar == 1) iValor = 1;
            if (iCancelar == 1) {iMenu = 2; iValor = 2;}
            if (iCancelar == 2) {iMenu = 4; iValor = 4; iForm = 0;}
            Backlight();
          }
          while (iValor == 1){
            Print_Hora(14, 3);
            iAceptar = Boton_Aceptar(5000);
            iCancelar = Boton_Cancelar(5000);
            minuto = Botones(minuto, 0, 59);
            if (iAceptar == 1) {
              iValor = 2;
              iForm = 6;
              iMenu = 4;
              Date3.setDate(year, mes, dia, hora, minuto, 0);
            }
            if (iCancelar == 1) iValor = 0;
            if (iCancelar == 2) {iMenu = 4; iValor = 4; iForm = 0;}
            Backlight();
          }
        }
      }
    }
  }

  if(iForm == 6) {  //Confirmar fase 1
    minuto = Date1.minute();
    hora = Date1.hour();
    dia = Date1.day();
    mes = Date1.month();
    year = Date1.year();
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Confirmar Fase 1");
    lcd.setCursor(1,1);
    lcd.print("T: ");
    lcd.print(Temp1);
    lcd.setCursor(12,1);
    lcd.print("H: ");
    lcd.print(Hume1);
    Print_Fecha(1,2);
    Print_Hora(12,2);
    while(iForm == 6){
      if (Fases == 1){
        lcd.setCursor(5,3);
        lcd.print("Iniciar 5s");
        iAceptar = Boton_Aceptar(5000);
        iCancelar = Boton_Cancelar(5000);
        if(iAceptar == 2) iForm = 9;
        if ( (iCancelar == 1) && (Fases == 2)) {iMenu = 3; iValor = 1; iForm = 3;}
        if ( (iCancelar == 1) && (Fases == 2)) {iMenu = 3; iValor = 1; iForm = 4;}
        if ( (iCancelar == 1) && (Fases == 3)) {iMenu = 3; iValor = 1; iForm = 5;}
        if (iCancelar == 2) iForm = 0;
      }
      else if (Fases >= 2){
        lcd.setCursor(3,3);
        lcd.print("Siguiente fase");
        iAceptar = Boton_Aceptar(5000);
        iCancelar = Boton_Cancelar(5000);
        if(iAceptar == 1) iForm = 7;
        if ( (iCancelar == 1) && (Fases == 1)) {iMenu = 3; iValor = 1; iForm = 3;}
        if ( (iCancelar == 1) && (Fases == 2)) {iMenu = 3; iValor = 1; iForm = 4;}
        if ( (iCancelar == 1) && (Fases == 3)) {iMenu = 3; iValor = 1; iForm = 5;}
        if (iCancelar == 2) iForm = 0;
      }
      Backlight();
    }
  }

  if(iForm == 7) { //Confirmar fase 2
    minuto = Date2.minute();
    hora = Date2.hour();
    dia = Date2.day();
    mes = Date2.month();
    year = Date2.year();
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Confirmar Fase 2");
    lcd.setCursor(1,1);
    lcd.print("T: ");
    lcd.print(Temp2);
    lcd.setCursor(12,1);
    lcd.print("H: ");
    lcd.print(Hume2);
    Print_Fecha(1,2);
    Print_Hora(12,2);
    while(iForm == 7){
      if (Fases == 2){
        lcd.setCursor(5,3);
        lcd.print("Iniciar 5s");
        iAceptar = Boton_Aceptar(5000);
        iCancelar = Boton_Cancelar(5000);
        if(iAceptar == 2) iForm=9;
        if (iCancelar == 1) iForm = 6;
        if (iCancelar == 2) iForm = 0;
      }
      else if (Fases == 3){
        lcd.setCursor(3,3);
        lcd.print("Siguiente fase");
        iAceptar = Boton_Aceptar(5000);
        iCancelar = Boton_Cancelar(5000);
        if(iAceptar == 1) iForm = 8;
        if (iCancelar == 1) iForm = 6;
        if (iCancelar == 2) iForm = 0;
      }
      Backlight();
    }
  }

  if(iForm == 8) { //Confirmar fase 3
    minuto = Date3.minute();
    hora = Date3.hour();
    dia = Date3.day();
    mes = Date3.month();
    year = Date3.year();
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Confirmar Fase 3");
    lcd.setCursor(1,1);
    lcd.print("T: ");
    lcd.print(Temp3);
    lcd.setCursor(12,1);
    lcd.print("H: ");
    lcd.print(Hume3);
    Print_Fecha(1,2);
    Print_Hora(12,2);
    while(iForm == 8){
      lcd.setCursor(5,3);
      lcd.print("Iniciar 5s");
      iAceptar = Boton_Aceptar(5000);
      iCancelar = Boton_Cancelar(5000);
      if(iAceptar == 2) iForm=9;
      if (iCancelar == 1) iForm = 7;
      if (iCancelar == 2) iForm = 0;
      Backlight();
    }
  }

  if(iForm == 9){
    lcd.clear();
    lcd.setCursor(1, 2);
    lcd.print("Almacenando datos");
    delay(3000);
    lcd.clear();
    while(iForm == 9){
    lcd.setCursor(6, 0);
    lcd.print("Gracias");
    lcd.setCursor(3, 2);
    lcd.print("Elaborado por");
    lcd.setCursor(2, 3);
    lcd.print("alumnos del MIT");
    Backlight();
    }
  }
}
