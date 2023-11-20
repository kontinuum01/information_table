#include <RGBmatrixPanel.h>                                   // Подключаем библиотеку для работы с матрицей


// Используем эти выводы, если матрица подключена к Arduino MEGA
#define CLK 11
#define OE   9
#define LAT 10
#define A   A0                                                // Вывод Arduino, к которому подключён вывод A матрицы
#define B   A1                                                // Вывод Arduino, к которому подключён вывод B матрицы
#define C   A2                                                // Вывод Arduino, к которому подключён вывод C матрицы
#define D   A3                                                // Вывод Arduino, к которому подключён вывод D матрицы

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, true, 64);    // Объявляем объект matrix для работы с матрицей 64х32, всключаем двойную буферизацию
uint8_t r, g, b;                                              // Переменные цвета светодиодов
 
 /*
  Данный код позволяет принять данные, идущие из порта, в строку (String) без "обрывов"
*/
String strData = "";
boolean recievedFlag;

void drawPixel();

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  matrix.begin();                                             // Инициируем работу с матрицей
  matrix.setTextWrap(true);                                   // Включаем перенос текста на следующую строку
  matrix.setTextSize(1);                                      // Устанавливаем размер текста равным 1 (6 пикселей на символ)
}
void loop() {
   while (Serial1.available() > 0) {         // ПОКА есть что то на вход    
     strData += (char)Serial1.read();       // забиваем строку принятыми данными
    recievedFlag = true;                   // поднять флаг что получили данные
    delay(2);                              // ЗАДЕРЖКА. Без неё работает некорректно!
     }
  if (recievedFlag) {                      // если данные получены
 // Serial.println(strData);               // Выводим текст 
  matrix.fillScreen(0);                                       // Очищаем экран
  matrix.setTextColor(matrix.Color333(3,0,0));                // Устанавливаем цвет текста
  matrix.setCursor(9,8);                                      // Указываем начальную координату вывода текста {столбец ; строка}
  matrix.println(strData);                                    // Выводим текст
  matrix.swapBuffers(true);                                  // Выводим текст из буфера на матрицу
    strData = "";                          // очистить
    recievedFlag = false;                  // опустить флаг
    
  }  
  
}

void drawPixel(){
  
  matrix.fillScreen(0);
  r = random(1,8);g = random(1,8);b = random(1,8);                      // задаём случайные значения для цвета светодиодов
  matrix.drawPixel(random(64), random(32), matrix.Color333(r, g, b));   // случайным образом зажигаем светодиоды, включая их случайным цветом
  delay(90);                                                            // задержка 90мс
}
