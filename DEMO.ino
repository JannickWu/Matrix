#include "Matrix.h"

//Pins of MATRIX
#define SER_ROW 19
#define CLK_ROW 18
#define LATCH 17
#define SER_COL 16
#define CLK_COL 15

MATRIX matrix(SER_ROW, CLK_ROW, SER_COL, CLK_COL, LATCH);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {

  // put your main code here, to run repeatedly:
      matrix.setStack(32);
  //    matrix.setDouble(8.3);
  //    matrix.setInteger(9);
  //   matrix.setLevel(3.2, 7);
  //  matrix.setText("Luohong Wu",5);



}
