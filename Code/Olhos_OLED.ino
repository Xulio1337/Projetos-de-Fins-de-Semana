//Guns of the brixton
/* Este codigo é sobre a animação dos olhos, ele foi criado do zero usando algumas bases que encontrei
Por isso, verifique o codigo antes de usa-lo. Caso for usar em um sistema mais complexo sugiro usar
"millis" ao invés de delays... */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definindo o pino do display OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDR      0x3C  // Endereço I2C do display OLED SSD1306

void desenharOlhos();
void MoverPupilasParaAngulo(int angulo);
void RestringirPosicaoPupila(int CentroOlhoX, int CentroOlhoY, int &PupilaX, int &PupilaY);
void piscar();
void expressaoCansado();
void expressaoTriste();
void expressaoBase();
void expressaoDesconfiado();
void expressaoFeliz();

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int TamanhoPupila = 10;  // Tamanho das pupilas
int RaioOcular = 25;  // Raio do globo ocular

// Posições dos olhos
int CentroOlhoX1 = SCREEN_WIDTH / 1.3;
int CentroOlhoY1 = SCREEN_HEIGHT / 2;
int CentroOlhoX2 = SCREEN_WIDTH / 4;
int CentroOlhoY2 = SCREEN_HEIGHT / 2;

// Posições das pupilas
int PupilaX1 = CentroOlhoX1;
int PupilaY1 = CentroOlhoY1;
int PupilaX2 = CentroOlhoX2;
int PupilaY2 = CentroOlhoY2;

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("Falha ao inicializar o display OLED"));
    while (1);
  }
  display.display();
  delay(1000);
}


void desenharOlhos() {
  display.fillCircle(CentroOlhoX1, CentroOlhoY1, RaioOcular, WHITE);
  display.fillCircle(CentroOlhoX2, CentroOlhoY2, RaioOcular, WHITE);
  display.fillCircle(PupilaX1, PupilaY1, TamanhoPupila, BLACK);
  display.fillCircle(PupilaX2, PupilaY2, TamanhoPupila, BLACK);
  display.display();
}

void MoverPupilasParaAngulo(int angulo) {
  int distancia = random(0, RaioOcular - TamanhoPupila);
  
  // Calcular a posição da pupila com base no ângulo
  int novaPupilaX1 = CentroOlhoX1 + distancia * cos(radians(angulo));
  int novaPupilaY1 = CentroOlhoY1 + distancia * sin(radians(angulo));
  int novaPupilaX2 = CentroOlhoX2 + distancia * cos(radians(angulo));
  int novaPupilaY2 = CentroOlhoY2 + distancia * sin(radians(angulo));

  // Suavizar o movimento do globo ocular
  int deslocamentoX1 = (novaPupilaX1 - PupilaX1) / 3;  // Movimento mais suave para o olho 1
  int deslocamentoY1 = (novaPupilaY1 - PupilaY1) / 3;  // Movimento mais suave para o olho 1
  int deslocamentoX2 = (novaPupilaX2 - PupilaX2) / 3;  // Movimento mais suave para o olho 2
  int deslocamentoY2 = (novaPupilaY2 - PupilaY2) / 3;  // Movimento mais suave para o olho 2
  
  // Movimentar suavemente o globo ocular
  CentroOlhoX1 += deslocamentoX1;
  CentroOlhoY1 += deslocamentoY1;
  CentroOlhoX2 += deslocamentoX2;
  CentroOlhoY2 += deslocamentoY2;
  
  // Atualizar as posições das pupilas
  PupilaX1 = novaPupilaX1;
  PupilaY1 = novaPupilaY1;
  PupilaX2 = novaPupilaX2;
  PupilaY2 = novaPupilaY2;

  // Restringir as posições para não ultrapassar os limites do globo ocular
  RestringirPosicaoPupila(CentroOlhoX1, CentroOlhoY1, PupilaX1, PupilaY1);
  RestringirPosicaoPupila(CentroOlhoX2, CentroOlhoY2, PupilaX2, PupilaY2);

  display.clearDisplay();
  display.fillCircle(CentroOlhoX1, CentroOlhoY1, RaioOcular, WHITE);
  display.fillCircle(CentroOlhoX2, CentroOlhoY2, RaioOcular, WHITE);
  display.fillCircle(PupilaX1, PupilaY1, TamanhoPupila, BLACK);
  display.fillCircle(PupilaX2, PupilaY2, TamanhoPupila, BLACK);
  display.display();
}

void RestringirPosicaoPupila(int CentroOlhoX, int CentroOlhoY, int &PupilaX, int &PupilaY) {
  if (PupilaX < CentroOlhoX - RaioOcular + TamanhoPupila) PupilaX = CentroOlhoX - RaioOcular + TamanhoPupila;
  if (PupilaX > CentroOlhoX + RaioOcular - TamanhoPupila) PupilaX = CentroOlhoX + RaioOcular - TamanhoPupila;
  if (PupilaY < CentroOlhoY - RaioOcular + TamanhoPupila) PupilaY = CentroOlhoY - RaioOcular + TamanhoPupila;
  if (PupilaY > CentroOlhoY + RaioOcular - TamanhoPupila) PupilaY = CentroOlhoY + RaioOcular - TamanhoPupila;
}




void piscar() {
  // Fase 1: Apagar linhas mantendo de 16 a 48
  for (int i = 1; i <= 32; i++) {
    if (i >= 16 && i <= 48) continue; // Evita apagar as linhas de 16 a 48
    display.drawLine(0, i - 1, SCREEN_WIDTH - 1, i - 1, BLACK);  // Linha de cima para baixo
    display.drawLine(0, SCREEN_HEIGHT - i, SCREEN_WIDTH - 1, SCREEN_HEIGHT - i, BLACK);  // Linha de baixo para cima
  }
  display.display();
  delay(5);  // Aguardar 5ms

  // Fase 2: Apagar linhas mantendo de 25 a 39
  for (int i = 1; i <= 32; i++) {
    if (i >= 25 && i <= 39) continue; // Evita apagar as linhas de 25 a 39
    display.drawLine(0, i - 1, SCREEN_WIDTH - 1, i - 1, BLACK);  // Linha de cima para baixo
    display.drawLine(0, SCREEN_HEIGHT - i, SCREEN_WIDTH - 1, SCREEN_HEIGHT - i, BLACK);  // Linha de baixo para cima
  }
  display.display();
  delay(5);  // Aguardar 5ms

  // Fase 3: Apagar linhas mantendo de 32
  for (int i = 1; i <= 32; i++) {
    if (i >= 32 && i <= 32) continue; // Evita apagar a linha de 32
    display.drawLine(0, i - 1, SCREEN_WIDTH - 1, i - 1, BLACK);  // Linha de cima para baixo
    display.drawLine(0, SCREEN_HEIGHT - i, SCREEN_WIDTH - 1, SCREEN_HEIGHT - i, BLACK);  // Linha de baixo para cima
  }
  display.display();
  delay(5);  // Aguardar 5ms

  // Limpar tela antes de acender novamente
  display.clearDisplay();
  display.display();
  delay(5);  // Aguardar 5ms

}

  void loop() {
  display.clearDisplay();  

   expressaoBase();

delay(1000);
  piscar();
      expressaoBase();
  expressaoFeliz();

delay(1000);
  expressaoBase();
delay(1000);

  piscar();
      expressaoBase();
  expressaoDesconfiado();

delay(1000);
  expressaoBase();
delay(1000);

  piscar();
      expressaoBase();
  expressaoTriste();

delay(1000);
  expressaoBase();
delay(1000);

  piscar();
      expressaoBase();
   expressaoCansado();
delay(1000);
  expressaoBase();
delay(1000);

  piscar();
      expressaoBase();


  int angulos[3];
  for (int i = 0; i < 3; i++) {
    angulos[i] = random(0, 360);
    delay(500);
  }

  for (int i = 0; i < 3; i++) {
    MoverPupilasParaAngulo(angulos[i]);
    delay(500);
  }

  piscar();

  
  }
  

void expressaoDesconfiado() {


  // Apaga todas as linhas da 1 até a 21
  for (int i = 0; i <= 26; i++) {
    display.drawLine(0, i, SCREEN_WIDTH - 1, i, BLACK);  // Apaga a linha de cima para baixo
  }
   int x1 = 0, y1 = SCREEN_HEIGHT - 1;    // Ponto A (inferior esquerdo)
  int x2 = SCREEN_WIDTH - 1, y2 = SCREEN_HEIGHT - 1; // Ponto B (inferior direito)
  int x3 = SCREEN_WIDTH / 2, y3 = SCREEN_HEIGHT / 2;  // Ponto C (vértice superior, agora centralizado mais abaixo)

  // Preenche o triângulo
  display.fillTriangle(x1, y1, x2, y2, x3, y3, BLACK);
  display.display();  // Atualiza o display
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void expressaoTriste() {
  // Coordenadas do primeiro triângulo retângulo
  int x1 = 0, y1 = 0;                             // Ponto A no canto superior esquerdo
  int x2 = SCREEN_WIDTH / 2, y2 = 0;               // Ponto B na metade da primeira linha
  int x3 = 0, y3 = SCREEN_HEIGHT / 2;              // Ponto C na metade da primeira coluna
  
  // Preenche o primeiro triângulo retângulo
  display.fillTriangle(x1, y1, x2, y2, x3, y3, BLACK);

  // Coordenadas do segundo triângulo retângulo
  int x4 = SCREEN_WIDTH - 1, y4 = 0;               // Ponto A no final da primeira linha
  int x5 = SCREEN_WIDTH / 2, y5 = 0;                // Ponto B na metade da primeira linha
  int x6 = SCREEN_WIDTH - 1, y6 = SCREEN_HEIGHT / 2; // Ponto C na borda direita, metade da altura

    int x_centro = SCREEN_WIDTH / 2;  // Centro do arco (meio da tela)
    int y_centro = SCREEN_HEIGHT - 5; // Posição do arco (perto da parte inferior)
    int raio = 8;
    int espessura = 2;                    // Raio do arco (altura da curvatura)

    // Desenha um arco inferior desenhando apenas a metade inferior do círculo
    for (int i = 200; i <= 340; i++) { 
     for (int j = -espessura; j <= espessura; j++) { // Ângulos de um arco inferior
        int x = x_centro + raio * cos(i * PI / 180);
        int y = y_centro + raio * sin(i * PI / 180);
        display.drawPixel(x, y, WHITE);
     }
    }

  // Preenche o segundo triângulo retângulo
  display.fillTriangle(x4, y4, x5, y5, x6, y6, BLACK);

  // Atualiza o display
  display.display();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void expressaoBase() {
  // Centraliza as posições dos globos oculares e das pupilas
  CentroOlhoX1 = SCREEN_WIDTH / 1.3;   // Posiciona o primeiro olho (direita) no centro horizontal
  CentroOlhoY1 = SCREEN_HEIGHT / 2;    // Centraliza verticalmente

  CentroOlhoX2 = SCREEN_WIDTH / 4;     // Posiciona o segundo olho (esquerda) no centro horizontal
  CentroOlhoY2 = SCREEN_HEIGHT / 2;    // Centraliza verticalmente

  PupilaX1 = CentroOlhoX1;  // A pupila segue o centro do globo ocular
  PupilaY1 = CentroOlhoY1;  // A pupila segue o centro do globo ocular
  PupilaX2 = CentroOlhoX2;  // A pupila segue o centro do globo ocular
  PupilaY2 = CentroOlhoY2;  // A pupila segue o centro do globo ocular

  // Atualiza a tela com os olhos e pupilas no centro
  display.clearDisplay();
  display.fillCircle(CentroOlhoX1, CentroOlhoY1, RaioOcular, WHITE);  // Desenha o globo ocular direito
  display.fillCircle(CentroOlhoX2, CentroOlhoY2, RaioOcular, WHITE);  // Desenha o globo ocular esquerdo
  display.fillCircle(PupilaX1, PupilaY1, TamanhoPupila, BLACK);        // Desenha a pupila direita
  display.fillCircle(PupilaX2, PupilaY2, TamanhoPupila, BLACK);        // Desenha a pupila esquerda
  display.display();  // Atualiza a tela
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void expressaoCansado(){


  for (int i = 0; i <= 26; i++) {
    display.drawLine(0, i, SCREEN_WIDTH - 1, i, BLACK);  // Apaga a linha de cima para baixo
  }
display.display();

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void expressaoFeliz() {
  
    // Desenha o primeiro círculo (à esquerda)
    int x1 = SCREEN_WIDTH / 4;  // Posição X do primeiro círculo
    int y1 = SCREEN_HEIGHT - 1; // Última linha do display
    int raio = 45;              // Raio do círculo

    display.fillCircle(x1, y1, raio, BLACK);  // Desenha o círculo preenchido

    // Desenha o segundo círculo (à direita)
    int x2 = SCREEN_WIDTH / 1.3;  // Posição X do segundo círculo
    int y2 = SCREEN_HEIGHT - 1;   // Última linha do display

    display.fillCircle(x2, y2, raio, BLACK);  // Desenha o círculo preenchido

    display.display(); // Atualiza a tela

     // Desenha o arco inferior do primeiro círculo
    int x_centro1 = SCREEN_WIDTH / 2;  // Centro do arco (meio da tela)
    int y_centro1 = SCREEN_HEIGHT - 20; // Posição do arco (perto da parte inferior)
    int raio2 = 10;                    // Raio do arco (altura da curvatura)
    int espessura = 1;

    for (int i = 20; i <= 160; i++) { // Ângulos de um arco inferior
        for (int j = -espessura; j <= espessura; j++) { // Desenha linhas de pixels para aumentar a espessura
            int x = x_centro1 + (raio2 + j) * cos(i * PI / 180);
            int y = y_centro1 + (raio2 + j) * sin(i * PI / 180);
            display.drawPixel(x, y, WHITE);
        }
    }
display.display();

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
