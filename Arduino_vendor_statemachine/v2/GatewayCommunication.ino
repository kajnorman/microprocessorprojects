
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
