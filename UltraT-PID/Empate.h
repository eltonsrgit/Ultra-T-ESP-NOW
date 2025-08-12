#ifndef empate_H
#define empate_H

#include "Whiplash.h"

void paraTras() { // estratégia número 6 no controle
  motor.move(-1023, -1023);
}

void giroAntiHorario() { // estratégia número 7 no controle
  leituraSensores();
  int soma = -leitura[0] + leitura[3];

  switch (soma) { // o ultra t vai para frente até que enxergue algo com um dos sensores laterais, então ativa o ataque principal
    case Nada:
      if (ataque) {
        iSeeYou();
      } else {
        motor.move(-1023, 1023);
      }
      break;

    case Direita:
      ataque = true;
      iSeeYou();
      break;

    case Esquerda:
      ataque = true;
      iSeeYou();
      break;
  }
}

void giroHorario() { // estratégia número 8 no controle
  leituraSensores();
  int soma = -leitura[0] + leitura[3];

  switch (soma) { // o ultra t vai para frente até que enxergue algo com um dos sensores laterais, então ativa o ataque principal
    case Nada:
      if (ataque) {
        iSeeYou();
      } else {
        motor.move(1023, -1023);
      }
      break;

    case Direita:
      ataque = true;
      iSeeYou();
      break;

    case Esquerda:
      ataque = true;
      iSeeYou();
      break;
  }
}



#endif