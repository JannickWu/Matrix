
#include "avr/pgmspace.h"
#include "Arduino.h"

#define Min_Score 0
#define Max_Score 5.0 // The max value is 9.9, because the 8*8 matrix can only display 2 numbers 

//How many times a loop will run. such as for(int i=0; i<Time__Delay; i++)
//In order to avoid the matrix flash too fast, we need to use a time-delay.
#define Time_Delay 1000

#define Number_of_Rows 8
#define Number_of_Cols 8
#define Number_of_LEDs 64   //We use a 8*8 matrix, so the constant is 64

#define Boundary_of_Very_Good 0.8  // If the score if bigger than 0.8*Max_Score, the assess is "Very Good";
#define Boundary_of_Good 0.6          //  0.6*Max_Score<=Score<0.8*Max_Score, "Good"
#define Boundary_of_Normal 0.4      //   0.4*Max_Score<=Score<0.6*Max_Score, "Normal"
#define Boundary_of_Bad 0.2           //   0.2*Max_Score<=Score<0.4*Max_Score, "Bad"
#define Boundary_of_Really_Bad 0.0 //   0.0*Max_Score<=Score<0.2*Max_Score, "Really Bad"

#define Speed_of_Move 25  // How fast the alphabets move.  0<Speed_of_Move<=80, the bigger, the faster.


class MATRIX {
public:
	MATRIX(int ser_row, int clk_row, int ser_col, int clk_col, int latch) :SER_ROW(ser_row), CLK_ROW(clk_row),
		SER_COL(ser_col), CLK_COL(clk_col), LATCH(latch) {
		pinMode(SER_ROW, OUTPUT);
		pinMode(CLK_ROW, OUTPUT);
		pinMode(SER_COL, OUTPUT);
		pinMode(CLK_COL, OUTPUT);
		pinMode(LATCH, OUTPUT);
	};
	void setStack(int number);
	void setDouble(double number);
	void setInteger(int number);
	void Light_First_Number(const char Number[5][3]);
	void Light_Second_Number(const char Number[5][3]);
	void setLevel(double level, int speed);
	void setText(String text, int speed);
	int get_index(char alphabet);
	void Test_method1();
	void Test_method2();
	void Test_method3();

	
private:
	int SER_ROW, CLK_ROW, SER_COL, CLK_COL, LATCH;
};