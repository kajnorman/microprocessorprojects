//States are defined as close to the naming used in the FSM
#define ALL_OFF 0 
#define LED1_ON 1 
#define LED1_and_LED2_ON 2

int light_state ;
int led1 = 12;
int led2 = 11;
int but1 = 7;
int but2 = 6;
int but3 = 5;

void setup()
{
  Serial.begin(9600);
  pinMode(led2, OUTPUT); //Yellow Led
  pinMode(led1, OUTPUT); //Green Led
  pinMode(but1, INPUT_PULLUP); //But1
  pinMode(but2, INPUT_PULLUP); //But2
  pinMode(but3, INPUT_PULLUP); //But3
  light_state = ALL_OFF;
  Serial.println("All LEDS are off.");
}

void loop()
{
  switch (light_state) //Change states and handle output
  { 
    case ALL_OFF:
    {
      if (digitalRead(but1) == LOW)
        {
          digitalWrite(led1, HIGH);
          Serial.println("LED1 on.");
          light_state = LED1_ON;
        }
      break;
    }   
    case LED1_ON:
    {
      if (digitalRead(but2) == LOW)
        {
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          Serial.println("LED1 and Led2 are on.");
          light_state = LED1_and_LED2_ON;
        }
      break;
    }
    case LED1_and_LED2_ON:
      if (digitalRead(but3) == LOW)
        {
          digitalWrite(led2, LOW);
          digitalWrite(led1, LOW);
          Serial.println("All LEDS are off.");
          light_state = ALL_OFF;
        }
      break;
    default:
      break;
  }
}

