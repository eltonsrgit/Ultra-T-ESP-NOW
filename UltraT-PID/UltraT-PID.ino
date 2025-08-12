#include <SumoIR.h>
#include "DRV8833.h"
#include "ledFX.h"
#include "pid.h"
#include "Whiplash.h"
#include "Empate.h"

int strategy = 0;
SumoIR IR;

void setup() {
  Serial.begin(115200);

  IR.begin(15); // sensor conectado no pino 15 (não mudar)

  motor.begin();
  motor.bip(5, 250, 2500); // motor bipa (x vezes, intervalo (ms), frequencia em Hz)

  setupSensores();

  ////////////////////////////////// para o LED ////////////////////////////////////
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  
  pixels.begin();
  pixels.setBrightness(60);
  pixels.clear();
  ledLight(0, 0, 0);
  //////////////////////////////////////////////////////////////////////////////////
}

void loop() {
  IR.update();

  if (IR.prepare()) { // número 1 no controle
    ledBlink(150, 150, 0, 100);
    motor.stop();
    Serial.println("-> sumo prepare");
  }
  
  else if (IR.start()) {
    Serial.println("-> sumo start");
  } 
  
  else if (IR.on()) { // número 2 no controle
    pixels.clear();
    ledLight(0, 150, 0);

    switch (strategy) {
      default: //fallthrough
      case 4:
        iSeeYou();
      break;

      case 5:
        whiplash();
      break;

      case 6:
        paraTras();
      break;

      case 7:
        giroAntiHorario();
      break;
      
      case 8:
        giroHorario();
      break;
    }
    Serial.println("-> sumo on");
  }
  
  else if (IR.stop()) { // número 3 no controle
    pixels.clear();
    ledLight(0, 0, 150);
    motor.stop();
    ledDetection();
    Serial.println("-> sumo stop");
  }
  
  else { // robô inicia caindo aqui
    strategySelection(); // seletor de estratégias

    motor.stop();
    Serial.println("-> sumo off");
  }
}

void strategySelection() {
  int cmd = IR.read();
  
  // Só muda se receber comando válido
  if (cmd >= 4 && cmd <= 9) {
    strategy = cmd;
  }

  // Acende LEDs para a estratégia atual
  if (strategy >= 4 && strategy <= 8) {
    const int num_leds = strategy % 8;
    for(uint8_t i = 0; i < num_leds; i++) {
      switch ((strategy - 3) % 5) {
        case 0: pixels.setPixelColor(i, pixels.Color(150, 0,   0  )); break;
        case 1: pixels.setPixelColor(i, pixels.Color(150, 150, 150)); break;
        case 2: pixels.setPixelColor(i, pixels.Color(0,   0,   150)); break;
        case 3: pixels.setPixelColor(i, pixels.Color(255, 150, 0  )); break;
        case 4: pixels.setPixelColor(i, pixels.Color(0,   150, 255)); break;
      }
      pixels.show();
    }
    delay(80);
    for(uint8_t i = 0; i < num_leds; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
    }
    delay(80);
  }
}
