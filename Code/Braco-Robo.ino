//Rock The Casbah

// Este é um codigo simples de um braço robotico movido por servos motores, nele coloquei para atualizar um angulo pelo monitor serial

#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int angle1 = 0; // Ângulo atual do servo 1
int angle2 = 0; // Ângulo atual do servo 2
int angle3 = 0; // Ângulo atual do servo 3
int angle4 = 0; // Ângulo atual do servo 4

void setup() {
  Serial.begin(9600);
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);

  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);
  servo4.write(angle4);

  Serial.println("CONTROLE DOS SERVOS:");
  Serial.println("Digite 'help' para obter instruções detalhadas."); 
  //Chique né, sempre coloque um desses quando for fazer muitos comandos no monitor
}
//Nomeei os void em inglês para ficar mais chique e formal (sim, nommei pe com dois "e"... Eu pesquisei)
void moveServoToAngle(Servo& servo, int& angleVar, int targetAngle, String servoName) {
  if (targetAngle >= 0 && targetAngle <= 180) {
    if (targetAngle == angleVar) {
      Serial.print(servoName);
      Serial.print(" já está no ângulo ");
      Serial.print(targetAngle);
      Serial.println("º.");
    } else {
      servo.write(targetAngle);
      angleVar = targetAngle; // Atualiza a variável do ângulo
      Serial.print(servoName);
      Serial.print(" movido para o ângulo: ");
      Serial.println(targetAngle);
    }
  } else {
    Serial.println("Ângulo inválido. Deve estar entre 0 e 180.");
  }
}

void moveAllServosTo0() {
  Serial.println("Todos os servos movidos para 0 graus.");
  moveServoToAngle(servo1, angle1, 0, "Servo 1");
  moveServoToAngle(servo2, angle2, 0, "Servo 2");
  moveServoToAngle(servo3, angle3, 0, "Servo 3");
  moveServoToAngle(servo4, angle4, 0, "Servo 4");
}

void moveServoForX(Servo& servo, int& angleVar, int targetAngle, String servoName) {
  // Função específica para mover servos com delay para a case 5
  if (targetAngle >= 0 && targetAngle <= 180) {
    if (targetAngle == angleVar) {
      Serial.print(servoName);
      Serial.print(" já está no ângulo ");
      Serial.print(targetAngle);
      Serial.println("º.");
    } else {
      servo.write(targetAngle);
      angleVar = targetAngle; // Atualiza a variável do ângulo
      Serial.print(servoName);
      Serial.print(" movido para o ângulo: ");
      Serial.println(targetAngle);
    }
  } else {
    Serial.println("Ângulo inválido. Deve estar entre 0 e 180.");
  }
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    Serial.println("Comando recebido: " + input);

    if (input == "?") {
      // Exibe os ângulos atuais dos servos
      Serial.print("Servo 1 = ");
      Serial.print(angle1);
      Serial.println("º");
      Serial.print("Servo 2 = ");
      Serial.print(angle2);
      Serial.println("º");
      Serial.print("Servo 3 = ");
      Serial.print(angle3);
      Serial.println("º");
      Serial.print("Servo 4 = ");
      Serial.print(angle4);
      Serial.println("º");
    } else if (input == "00") {
      moveAllServosTo0(); // Move todos os servos para 0 graus
    } else if (input == "help") {
      // Exibe o manual de comandos
      Serial.println("Manual de Comandos:");
      Serial.println("'1' -> Insira o ângulo para mover o Servo 1.");
      Serial.println("'2' -> Insira o ângulo para mover o Servo 2.");
      Serial.println("'3' -> Insira o ângulo para mover o Servo 3.");
      Serial.println("'4' -> Insira o ângulo para mover o Servo 4.");
      Serial.println("'5' -> Move Servo 1 para 180°, Servo 2 para 45°, Servo 3 para 90° e Servo 4 para 70°, com delay de 500ms entre eles.");
      Serial.println("'00' -> Move todos os servos para 0 graus.");
      Serial.println("'?' -> Exibe os ângulos atuais de todos os servos.");
      Serial.println("'help' -> Exibe este manual de comandos.");
    } else {
      int command = input.toInt(); // Converte o comando para inteiro

      switch (command) {
        //Evite muitos "if" e "else" no codigo, a case simplifica e enriquece o codigo
        case 1:
          Serial.println("Digite o ângulo entre 0 e 180 graus:");
          while (!Serial.available()) {}
          moveServoToAngle(servo1, angle1, Serial.readStringUntil('\n').toInt(), "Servo 1");
          break;
//IMPORTANTE, OS ANGULOS NÃO SÃO ACUMALITVOS.
        case 2:
          Serial.println("Digite o ângulo entre 0 e 180 graus:");
          while (!Serial.available()) {}
          moveServoToAngle(servo2, angle2, Serial.readStringUntil('\n').toInt(), "Servo 2");
          break;

        case 3:
          Serial.println("Digite o ângulo entre 0 e 180 graus:");
          while (!Serial.available()) {}
          moveServoToAngle(servo3, angle3, Serial.readStringUntil('\n').toInt(), "Servo 3");
          break;

        case 4:
          Serial.println("Digite o ângulo entre 0 e 180 graus:");
          while (!Serial.available()) {}
          moveServoToAngle(servo4, angle4, Serial.readStringUntil('\n').toInt(), "Servo 4");
          break;

        case 5:
          /* Essa case eu criei apenas como exemplo para vocês poderem criar uma sequência 
          de movimento dos motores sem terem que enviar angulo por angulo. Assim você controla o braço
          para fazer um movimento mais complexo, lembre de arrumar o delay para não emparelhar o movimento do braço
          */
          moveServoForX(servo1, angle1, 180, "Servo 1");
          delay(500);
          moveServoForX(servo2, angle2, 45, "Servo 2");
          delay(500);
          moveServoForX(servo3, angle3, 90, "Servo 3");
          delay(500);
          moveServoForX(servo4, angle4, 70, "Servo 4");
          delay(500);
          break;

        default:
          Serial.println("Comando inválido. Use 'help' ver as opções de comandos.");
          break;
      }
    }
  }
}
