#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal.h>
#define PIN 13
#define NUMPIXELS 144  // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);
#define DELAYVAL 0  // Time (in milliseconds) to pause between pixels

String topQuestions[] = {"Make 50:", "Make 100:", "Make 227:", "Make 5:", "Make 
64:","Fin"}; //This is the array for the questions
int maxNumQuestions = 6; 
int NumQuestions = 0;
int score = 0;
int lightSensorPin = 13;
 LiquidCrystal lcd(12, 11, 5, 4, 3, 2);   // set the LCD address to 0x27 for a 16 
 // chars and 2 line display
int Contrast=0;
// this constant won't change:
const int  Up_buttonPin   = 9;    // the pin that the pushbutton is attached to
const int  Down_buttonPin   = 8;
const int complete = 7;
int binPV[] = {128,64,32,16,8,4,2,1}; //array for the decimal widgets of each bit
// in the byte
int quNUM[] = {50,100,227,5,64}; //array for the number the user must make
// Variables will change:
int buttonPushCounter = 0;  
int up_buttonState = 0;         
int up_lastButtonState = 0;
int down_buttonState = 0;        
int down_lastButtonState = 0;    
int corr_buttonState = 0;         
int corr_lastButtonState = 0;
bool bPress = false;
int totalNum = 0;
int i =0;
int x=0;
bool gPress = false;  //Addition button state
bool rPress = false; //Skip button state

int buttonState = 0;  // variable for reading the pushbutton status
int buttonState2 = 0;
int lightNum= 0;
bool btnState= false;
bool btnState2= false;
bool btnState3= false;

void setup()
{

 pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
 Serial.begin(9600);
 analogWrite(6,Contrast);
 lcd.begin(16, 2);

 pinMode( Up_buttonPin , INPUT_PULLUP);
 pinMode( Down_buttonPin , INPUT_PULLUP);
 pinMode( complete , INPUT_PULLUP);

    //Introduction welcome to Bin0Gu3ssr:
    lcd.setCursor(0, 0);          
    lcd.print("Welcome");
    lcd.setCursor(0, 1);
    lcd.print("To Bin0Gu3ssr");
    delay(3000);
    lcd.clear();
    lcd.print("LETS LEARN!");
    delay(3000);
    lcd.clear();
    lcd.print("Starting...");
    lcd.clear();

 lcd.setCursor(2,1);
 lcd.print(totalNum);

  // initialize the LED pin as an output:
  pinMode(lightSensorPin, OUTPUT);

}
void loop()

{
  
 corr_buttonState = digitalRead(complete); //read in the button for checking if the 
// user has matched the number.


  if (x<5) //if not all the questions have been completed
    {
     lcd.setCursor(0, 0);                        //display question
     lcd.print(topQuestions[NumQuestions]);
       
   if (corr_buttonState == LOW)                     //if True button is clcked
        {
           
       checkRight(); //check userNumber matches the number from the question
           
        }
    }else{
      Winner(); //if all questions have been completed run win function.
    }



if (i<9){ 
  checkUp();
  checkDown();
}


if(gPress == true) { //if green button pressed
if(lightNum <= 22){ //if number of lights lit up are less than 8 bits
  for (int i = 0; i < 3; i++) { //increase lights lit up green for three
   
    pixels.setPixelColor(lightNum, pixels.Color(124, 252, 0));
    lightNum = lightNum+1;
     
      }
      delay (1000);
      gPress = false;
}
  } else if(rPress == true) { //if red button pressed
     if(lightNum <= 22){ //if number of lights lit up are less than 8 bits
      for (int i = 0; i < 3; i++) { //increase lights lit up red for three
   
        pixels.setPixelColor(lightNum, pixels.Color(139, 0, 0));
        lightNum = lightNum+1;
     
      }
      delay (1000);
      rPress = false;
  }
 }



 Serial.println(buttonState);




 pixels.show();  // Send the updated pixel colors to the hardware.


  if( bPress){ //show the total number when the button is not pressed.
     bPress = false;

     lcd.setCursor(2,1);


     lcd.print("               ");


     lcd.setCursor(2,1);


     lcd.print(totalNum);

  }




}



void checkUp()


{
 //read the green button press
 up_buttonState = digitalRead(Up_buttonPin);
 // compare the buttonState to its previous state
 if (up_buttonState != up_lastButtonState) {
   // if the state has changed, increment the counter, more to next number in bit
 //array
   if (up_buttonState == LOW) {
       bPress = true;
       gPress =true;
       totalNum  += binPV[i];



     
   
     i++;
     buttonPushCounter++;
   

   } else {


     // if the current state is LOW then the button went from on to off:
     Serial.println("off");
   }
     // Delay a little bit to avoid bouncing
     delay(50);
 }
 // save the current state as the last state, for next time through the loop


  up_lastButtonState = up_buttonState;
  
}


void checkDown()
{
 //read the red button press
 down_buttonState = digitalRead(Down_buttonPin);
 // compare the buttonState to its previous state
 if (down_buttonState != down_lastButtonState) {
   // if the state has changed, move to next item in the bit array don't add 
// anything to total number. 
       
   if (down_buttonState == LOW) {
       bPress = true;
       rPress = true;



       i++;
       buttonPushCounter++;
   
   } else {


     // if the current state is LOW then the button went from on to off:
     Serial.println("off");
   }
   // Delay a little bit to avoid bouncing
   delay(50);
 }
 // save the current state as the last state, for next time through the loop


 down_lastButtonState = down_buttonState;
  
}


void correctAnswer()
{                                   //Function for correct answers
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CORRECT!");
    delay(2000);
    lcd.clear();
       lcd.setCursor(2,1);
     lcd.print(totalNum);
}


void wrongAnswer()
{                                      //Function for Wrong answers
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WRONG!");
    delay(2000);
    lcd.clear();
    lcd.setCursor(2,1);
    lcd.print(totalNum);
}


void checkRight()


{

corr_buttonState = digitalRead(complete);




 // compare the total number to the current number in the qNUM array 
 if (totalNum == quNUM[x]) {
 // if true increase question number, move to next item in the qNUM array
//move to the first item in the bit array, run correct answer. clear LED strip
   NumQuestions++;
   score++;
   totalNum == quNUM[x];
   x++;
   i=0;
   totalNum = 0;
   lightNum =0;
   correctAnswer();
   pixels.clear();

   } else {
// Reset addition arrays reset total number, run wrong answer and clear the leds
      i=0;
      totalNum = 0;
      lightNum =0;
      wrongAnswer();
      pixels.clear();


   }
   // Delay a little bit to avoid bouncing
   delay(50);
 }
//reset function to reset the machine
void(* resetFunc) (void) = 0;
void Winner(){
//Clear lcd screen clear leds, reset Arduino. tell user they have won.
   lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("YOU WIN!");
     delay(1500);
     lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Thank You");
    lcd.setCursor(0, 1);
  lcd.print("For Playing");
   delay(1500);
   lcd.clear();
    delay(500);
   resetFunc();
}
