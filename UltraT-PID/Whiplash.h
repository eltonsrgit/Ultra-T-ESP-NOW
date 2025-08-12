#ifndef Whiplash_H
#define Whiplash_H

#include "pid.h"

enum sensor { 
  Esquerda = -1,
  Nada,
  Direita
};

bool ataque = false; 

void whiplash() { // estratégia número 5 no controle
  leituraSensores();
  int soma = -leitura[0] + leitura[3];

  switch (soma) { // o ultra t vai para frente até que enxergue algo com um dos sensores laterais, então ativa o ataque principal
    case Nada:
      if (ataque) {
        iSeeYou();
      } else {
        motor.move(850, 850);
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
