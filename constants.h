#define Row1 2
#define Row2 3
#define Row3 4
#define Row4 5
#define Row5 6
#define Row6 7
#define Row7 8
#define Row8 9
#define Col1 10
#define Col2 11
#define Col3 12
#define Col4 13
#define Col5 14
#define Col6 15
#define Col7 16
#define Col8 17
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

#define Speed_of_Move 5  // How fast the alphabets move.  0<=Speed_of_Move<=10, the bigger, the faster.


