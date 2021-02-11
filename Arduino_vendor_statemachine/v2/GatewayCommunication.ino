/*
packet:
  +---+-------+---------+-----+----+
  |':'|command|parameter|value|’\r’|
  +---+-------+---------+-----+----+
  
  Start of packet :  ‘:’  0x3A ( colon (8 bits))
  End of packet :  ‘\r’  0x0D  (carriage return (8 bits))
  
  commands:
  ‘@’: 0x40 Ping  (is sent with no parameter and no value (8 bits))  
Is answered with ‘@’ : 0x40 (8 bits)
  ‘R’: 0x52  Read parameter  ( is sent with no value (8 bits))     
          Is answered with one byte 0xNN a number in the range 0-255 (8 bits))  
  ‘W’: 0x57  Write parameter

  Parameter: the “name” for the value to be set
  ‘N’ : number of nickels(8 bits)
  ‘D’ : number of dimes (8 bits)
  ‘I’ : number of items (8 bits)

  Value: the number of elements (N, D or I) to set for a certain parameter
  0xNN : number of elements, a number in the range from 0-255 (8 bits)

  Notes: 
      •  Using the UART-format 8 bits are sent at a time. 
      • One startbit is used
      • The baudrate is 9600
      • No parity is used
      • A Slave/Master principle is used.
      o The Gateway is the master
      o The Vendor state machine is the slave
*/




#define stdby  0
#define processing 10
#define awaitcommand 30
#define awaitparameter 40
#define awaitvalue 50
#define awaitend 60

char Command, Parameter, Value;

int ComState = stdby;


void  GatewaycommunicatingStatemachine(void)
{
  int x ;
  if ((x = Serial.read ()) == -1)  return ; 
   switch (ComState) {
     case stdby: 
              if (x ==':') ComState = awaitcommand;
              break;
     case awaitcommand: 
              if (x=='R'  || x =='W')    //  what about @
                  {
                    ComState = awaitparameter;
                    Command = x;
                  }
              else 
                  {
                    ComState = stdby;
                  }
              break;
     case awaitparameter: 
              if (x=='D'  || x =='N'|| x =='I')    
                  {
                    Parameter = x;
                    if (Command=='W')   
                        {
                          ComState = awaitvalue;
                        }
                    else //Command == R   --- Read
                        {
                          ComState = awaitend;
                        }
                  }
              else 
                  {
                    ComState = stdby;
                  }
              break;
     case awaitvalue:
              Serial.println("Value acceptrd\n");   //debug
              Serial.println(x);   //debug
              Value = x;
              ComState = awaitend;   ////
              break; 
     case awaitend:
              if (x =='\r')
              {
                ComState = stdby;
                ProcesPacket();
              }
              break;
   }  
   Serial.print("\nComstate");
   Serial.println(ComState);
}

void ProcesPacket(void)
{
              Serial.println("Processing packet \nCommand :");   //debug
              Serial.println(Command);                           //debug


if (Command == 'R')
    {
              Serial.println("Reading Value \n");               //debug
              Serial.println(Value);                            //debug
      switch (Parameter){
        case 'N' : 
           Serial.write(Nickels);
           break;
        case 'D' : 
           Serial.write(Dimes);
           break;
        case 'I' : 
           Serial.write(Items);
           break;
      }
    } 
if (Command == 'W')
    {
              Serial.println("Writing Value \n");          //debug
              Serial.println(Value);                       //debug

      
      switch (Parameter){
        case 'N' : 
            Nickels = Value;
            break;
        case 'D' : 
            Dimes = Value;
           break;
        case 'I' : 
           Items = Value;
           break;
      }
    }
}
