// adicionar à biblioteca
#include <Unistep2.h>

#define ldrX A4 // declração de constantes para sensores de luz
#define ldrY A5

// Definir os motores
Unistep2 stepperX(2, 3, 4, 5, 4096, 1000);  // pinos utilizados no driver IN1, IN2, IN3, IN4, e colocados por ordem nos pinos ligados ao Arduino ex. D2, D3, D4, D5
Unistep2 stepperY(8, 9, 10, 11, 4096, 1000);

void setup() {
  pinMode(7, INPUT_PULLUP);  // designação de pino de botão de ON/OFF
  Serial.begin(9600);        // inicia o Serial (muito parecio com uma consola de comandos)
}

void loop() {
  if (digitalRead(7) == LOW) {  // condição if para detectar se o botão está ligado (Ligado = LOW, Desligado = HIGH)

    if (analogRead(ldrX) < 50) {
      stepperX.run();  // executar motorX
    }

    if (analogRead(ldrY) < 50) {
      stepperY.run();
    }

    int aa0 = analogRead(A0) - 511;  // declaração e atribuição de variáveis de potenciómetros
    int aa1 = analogRead(A1) - 511;

    stepperX.steptime = int(map(abs(aa0), 0, 512, 4000, 1000));  // atribuição de velocidade de passos de motor consoante o valor do potenciómetro
    stepperY.steptime = int(map(abs(aa1), 0, 512, 4000, 1000));

    int dir0 = aa0 > 0 ? 1 : -1;  // condição if para detectar a direção do motor
    int dir1 = aa1 > 0 ? 1 : -1;

    stepperX.move(dir0 * 1);  // execução de passos para motorX
    stepperY.move(dir1 * 1);

  } else {
    delay(100);  // delay caso o botão esteja desligado para não sobrecarregar tanto o sistema
  }
}
