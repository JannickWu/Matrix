#include "avr/pgmspace.h"
#include "math.h"
#include "String.h"
#include "matrix_constants.h"


// common-anode 8*8 matrix
//In the second method, the matrix can display 2 numbers at the same time. The first number uses col1 to col3 and the other one uses col6 to col8.  The col4 and col5 are used to display the decimal point.





// In the second method, the 8*8 matrix will display t numbers and each number is 5 rows* 3 cols.
extern const char Number[10][5][3];


extern const Alphabet_node Alphabet_table[27];

//In the third method, the alphabet will use 8 rows * 8 cols.



void setup() {
  // put your setup code here, to run once:
  pinMode(SER_ROW, OUTPUT);
  pinMode(SER_COL, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK_ROW, OUTPUT);
  pinMode(CLK_COL, OUTPUT);
  Serial.begin(9600);

}
void loop() {

  //----------------------------------------------------------------
  //    Test_method1();


  //----------------------------------------------------------------
        Test_method2();

  //----------------------------------------------------------------
  //  Display_words(0.57);
  //  Display_words(" very good");
//  Test_method3();

}



// the lowest score is 0 and the highest score is 5.0.
void Test_method1()
{
  for (int i = floor(Min_Score); i <= floor(Max_Score * 10); i++) //Because the loop can only use int, so we need to call function floor() to convert double to integer.
  {
    for (int j = 0; j < Time_Delay; j++) //time-delay
      Light_LEDs(i / 10.0);
  }
}


//Display the score using the first method.
//double Score  is the average score given by the students
void Light_LEDs(double Score)
{
  if (Min_Score <= Score && Score <= Max_Score)
  {
    int number = floor(Score / Max_Score * Number_of_LEDs);     // how many LEDs should be light
    int Rows = number / Number_of_Rows;
    int Cols = number % Number_of_Cols;

    //The LEDs of these rows are all light.
    //For example: if the number is 35. than integer rows=35/8=4. So, the first 4 rows are light.
    digitalWrite(LATCH, LOW);
    shiftOut(SER_ROW, CLK_ROW, MSBFIRST, B11111111 << Rows);
    shiftOut(SER_COL, CLK_COL, MSBFIRST, B11111111);
    digitalWrite(LATCH, HIGH);

    digitalWrite(LATCH, LOW);
    shiftOut(SER_ROW, CLK_ROW, MSBFIRST, ~(B00000001 << Rows));
    shiftOut(SER_COL, CLK_COL, MSBFIRST, ~(B11111111 << Cols));
    digitalWrite(LATCH, HIGH);

  }
  else
  {
    Serial.println("Invalid score!!!");
  }
}


void Test_method2()
{
  for (int i = floor(Min_Score); i <= floor(Max_Score * 10); i++)
  {
    Display_numbers(i / 10.0);
  }
}

//Display the score using the second method.
//double Score : the average score given by the students

void Display_numbers(double Score)
{

  if (Min_Score <= Score && Score <= Max_Score )
  {

    //If we want to display 2.7, we need to split the 2 numbers
    int mid = floor(Score * 10);    //2.7*10=27
    int First_Number = mid / 10;    //First_Number=2
    int Second_Number = mid % 10;   //Second_Number=7


    for (int i = 0; i < Time_Delay; i++)
    {
      Light_First_Number(Number[First_Number]);
      Light_Second_Number(Number[Second_Number]);
    }
  }
  else
  {
    Serial.println("Invalid score!!!");
  }
}


void Light_First_Number(const char Number[5][3])
{
  for (int Col = 1; Col < 4; Col++) // the cols of the 1st number are col1, col2, col3
  {
    digitalWrite(LATCH, LOW);
    shiftOut(SER_COL, CLK_COL, MSBFIRST, 1 << (Col - 1));

    int row_data = 0;
    for (int Row = 1; Row < 6; Row++)
    {
      row_data = (row_data << 1) + pgm_read_byte_near(&Number[Row - 1][Col - 1]);
    }
    row_data <<= 3;
    shiftOut(SER_ROW, CLK_ROW, LSBFIRST, ~row_data);
    digitalWrite(LATCH, HIGH);
  }

  digitalWrite(LATCH, LOW);
  shiftOut(SER_COL, CLK_COL, MSBFIRST, B00001000);
  shiftOut(SER_ROW, CLK_ROW, MSBFIRST, B11101111);
  digitalWrite(LATCH, HIGH);

}

void Light_Second_Number(const char Number[5][3])
{
  for (int Col = 5; Col < 8; Col++) // the cols of the 1st number are col1, col2, col3
  {
    digitalWrite(LATCH, LOW);
    shiftOut(SER_COL, CLK_COL, MSBFIRST, 1 << (Col - 1));

    int row_data = 0;
    for (int Row = 1; Row < 6; Row++)
    {
      row_data = (row_data << 1) + pgm_read_byte_near(&Number[Row - 1][Col - 5]);
    }
    row_data <<= 3;
    shiftOut(SER_ROW, CLK_ROW, LSBFIRST, ~row_data);
    digitalWrite(LATCH, HIGH);
  }

}

void Test_method3()
{
  for (int i = Min_Score; i <= Max_Score; i++)
  {
    Display_words(0.1 + i);
  }
}

//Display the score using the second method.
//double Score : the average score given by the students

void Display_words(double Score)
{
  if (Min_Score <= Score && Score <= Max_Score)
  {
    String words;
    if (Score >= Boundary_of_Very_Good * Max_Score)
    {
      words = " Very good";
    }
    else
    {
      if (Score >= Boundary_of_Good * Max_Score)
      {
        words = " Good";
      }
      else
      {
        if (Score >= Boundary_of_Normal * Max_Score)
        {
          words = " Normal";
        }
        else
        {
          if (Score >= Boundary_of_Bad * Max_Score)
          {
            words = " Bad";
          }
          else
          {
            words = " Really bad";
          }
        }
      }
    }

    //modify the code and you can display any words.
    //words="any words"
    char words_buffer[8][8 * 20];
    words.toUpperCase();

    //use the alphabet unit to make a sentence and storage the sentence into words_buffer
    for (int i = 0; i < words.length(); i++)
    {
      char current_alphabet = words.charAt(i);
      int alphabet_index = get_index(current_alphabet);
      for (int row = 0; row < Number_of_Rows; row++)
      {
        for (int col = 0; col < Number_of_Cols; col++)
        {
          words_buffer[row][i * Number_of_Cols + col] = pgm_read_byte_near(&Alphabet_table[alphabet_index].matrix[row][col]);
        }
      }
    }

    //display this sentence
    for (int j = 0; j <= Number_of_Cols * (words.length() - 1); j++)
    {
      for (int Time = 0; Time < 1000 / Speed_of_Move; Time++)
      {
        for (int Col = 1; Col <= 8; Col++)
        {
          digitalWrite(LATCH, LOW);
          shiftOut(SER_COL, CLK_COL, MSBFIRST, 1 << (Col - 1));
          int row_data = 0;
          for (int Row = 1; Row <= 8; Row++)
          {
            row_data = (row_data << 1) + int(words_buffer[Row - 1][j + Col - 1]);
          }
          shiftOut(SER_ROW, CLK_ROW, LSBFIRST, ~row_data);
          digitalWrite(LATCH, HIGH);
        }
      }
    }
  }
  else
  {
    Serial.println("Invalid score!!!");
  }
}


void Display_words(String words)
{

  char words_buffer[8][8 * 20];
  words.toUpperCase();

  //use the alphabet unit to make a sentence and storage the sentence into words_buffer
  //For example : GOOD='G'+'O'+'O'+'D'
  for (int i = 0; i < words.length(); i++)
  {
    char current_alphabet = words.charAt(i);
    int alphabet_index = get_index(current_alphabet);
    for (int row = 0; row < Number_of_Rows; row++)
    {
      for (int col = 0; col < Number_of_Cols; col++)
      {
        words_buffer[row][i * Number_of_Cols + col] = pgm_read_byte_near(&Alphabet_table[alphabet_index].matrix[row][col]);
      }
    }
  }

  //display this sentence
  //keep the sentence still and move the 8*8 matrix slowly.
  for (int j = 0; j <= Number_of_Cols * (words.length() - 1); j++)
  {
    for (int Time = 0; Time < 1000 / Speed_of_Move; Time++)
    {
      for (int Col = 1; Col <= 8; Col++)
      {
        digitalWrite(LATCH, LOW);
        shiftOut(SER_COL, CLK_COL, MSBFIRST, 1 << (Col - 1));
        int row_data = 0;
        for (int Row = 1; Row <= 8; Row++)
        {
          row_data = (row_data << 1) + int(words_buffer[Row - 1][j + Col - 1]);
        }
        shiftOut(SER_ROW, CLK_ROW, LSBFIRST, ~row_data);
        digitalWrite(LATCH, HIGH);
      }
    }
  }

}

int get_index(char alphabet)
{
  for (int i = 0; i < sizeof(Alphabet_table) / sizeof(Alphabet_table[0]); i++)
  {
    if (pgm_read_byte_near(&Alphabet_table[i].alphabet) == alphabet)
    {
      return i;
    }
  }
  return -1;
}
