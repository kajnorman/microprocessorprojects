/*
 * Author knn@eaaa.dk
 * 
 * Taken from 
 * 
 * https://www.swarthmore.edu/NatSci/mzucker1/e15_f2014/E15CForMicrocontroller.pdf
Implement a vending machine (for 15¢ object) with
two inputs “n” and “d,” and two output “C” and “R.”
• n is true if a nickel is inserted, d is true for a dime.
• C is true if change (5¢) is required,
 R is true if we are to release the item.
• The machine starts in state S0 and at each iteration:
• If we are in state S0 (0 money) we:
    • remain if no money has been put into the machine, (n=0, d=0)
    • go to S5 (5¢) if nickel has been entered, but no dime (n=1, d=0),
    • go to S10 (10¢) if a dime has been entered
• If we are in S5 we:
    • remain in S5 if no money has been put into the machine,
    • go to S10 if a nickel has been entered,
    • go to S15 (15¢) if a dime has been entered.
• If we are in S10 we:
    • remain in S10 if no money has been put into the machine,
    • go to S15 if a nickel has been entered,
    • go to S20 (20¢) if a dime has been entered. 
•If we are in S15 we:
    •go to S0 (starting state),
    • set R=1 to release an item from the vending machine.
     (Other states have R=0, though this was not explicitly shown.)
•If we are in S20 we:
    • go to S15,
    • but we also set C=1 to indicate that we must release change (5¢) back
    to the customer.
     (Other states set C=0, though this was not explicitly shown.) 
*/
#define S0 1
#define S5 2
#define S10 3
#define S15 5
#define S20 33 

int n=0, d=0, R, C, myState=S0; 

unsigned char Nickels=10,Dimes=10,Items=70;


// the setup function runs once when you press reset or power the board
void setup() {
 //***************************************************************************************
 // Variable declarations and initializations go here, as well as configuration of GPIO's
 //*************************************************************************************** 
  pinMode(2, INPUT_PULLUP);//nickel
  pinMode(3, INPUT_PULLUP);//dime
  pinMode(12, OUTPUT);//Release Item
  pinMode(13, OUTPUT);//Release change (a nickel)
  Serial.begin(9600);
  Serial.println ("vending machine protocol 1.0") ;
}

// the loop function runs over and over again forever
void loop() {
 //*******************************************************************************
 // Determine values of “n” and “d”.
 //*******************************************************************************
 Determine_n_d(); 
 
 //*******************************************************************************
 // Code for state transitions goes here.
 //*******************************************************************************
 switch (myState) {
     case S0: if (n) myState = S5;
              else 
              if (d) myState = S10;
              break;
     case S5: if (n) myState = S10;
              else 
              if (d) myState = S15;
              break;
     case S10: if (n) myState = S15;
               else 
               if (d) myState = S20;
               break;
     case S15: myState = S0;
               break;
     case S20: myState = S15;
               break;
     // The default state should never occur,
     // but if it does, we go to state 1
     default: myState=S0; // This should never happen!
}
 //*******************************************************************************
 // Code for state outputs goes here. 
 //*******************************************************************************
     switch (myState) {
     case S0:
     case S5:
     case S10: R=0; C=0; break;
     case S15: R=1; C=0;digitalWrite(12,1);delay(500);digitalWrite(12,0); break;
     case S20: R=0; C=1;digitalWrite(13,1);delay(500);digitalWrite(13,0);break;
     default: R=0; C=0; // This should never happen!
}


  GatewaycommunicatingStatemachine();
 //*******************************************************************************
 // Code for status if needed 
 //*******************************************************************************
 
   /*Serial.print("myState ");
   Serial.println(myState);
   Serial.print("d ");
   Serial.println(d);
   Serial.print("n ");
   Serial.println(n); */
}






void Determine_n_d(void)
 {   //The Devil is in the detail  !!!   :-)
  static int previousread2=1, previousread3=1;
  static int currentread2=1, currentread3=1; 

     previousread2 = currentread2;
     previousread3 = currentread3; 
     currentread3 = digitalRead(3);
     currentread2 = digitalRead(2);
     
     if  ((previousread2==1) && (currentread2==0))
        n=1;
     else 
        n=0;
     if  ((previousread3==1) && (currentread3==0))
        d=1;
     else 
        d=0;
 }
