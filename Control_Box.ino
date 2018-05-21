#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

const int TEMPS=750;
int affichageFait;// déclaration de la variable
int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;
int val6 = 0;
int val7 = 0;
int val8 = 0;
int volume = 20;

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(13,OUTPUT); // led interne et buzzer
  // Serial.begin(9600);
  affichageFait=0;//initialisation de la variable
  // ############################# programme dfp
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(volume);  //Set volume value. From 0 to 30
  // myDFPlayer.play(1);  //Play the first mp3
}

void loop() {
  // ############################# programme dfp
  static unsigned long timer = millis();
  
  if (millis() - timer > 3000) {
    timer = millis();
    //myDFPlayer.next();  //Play next mp3 every 3 second.
  }
  
  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
  // ############################# mon programme
  if (affichageFait==0)
  {
    delay(TEMPS);
    Serial.println("Et on demare!");//envoi d'un autre message
    affichageFait=1;
  }
  val3 = digitalRead(3);
  val4 = digitalRead(4);
  val5 = digitalRead(5);
  val6 = digitalRead(6);
  val7 = digitalRead(7);
  val8 = digitalRead(8);
  //Serial.print(val6);
  //Serial.println(val7);
  //delay(TEMPS);
  
  if (val8)
  {
    if(val3)
    {
      delay(200);
      volume = volume + 5;
      if (volume > 30)
      {
        volume = 0;
      }
      myDFPlayer.volume(volume);  //Set volume value. From 0 to 30
      Serial.println("juste 3");
    }
    if(val4)
    {
      myDFPlayer.play(9);
      Serial.println("juste 4");
    }
    if(val5)
    {
      myDFPlayer.play(8);
      Serial.println("juste 5");
    }
    if(val6)
    {
      myDFPlayer.play(7);
      Serial.println("juste 6");
    }
    if(val7)
    {
      myDFPlayer.play(6);
      Serial.println("juste 7");
    }
  }
  else
  {
    if(val3)
    {
      myDFPlayer.play(5);
      Serial.println("8+3");
    }
    if(val4)
    {
      myDFPlayer.play(4);
      Serial.println("8+4");
    }
    if(val5)
    {
      myDFPlayer.play(3);
      Serial.println("8+5");
    }
    if(val6)
    {
      myDFPlayer.play(2);
      Serial.println("8+6");
    }
    if(val7)
    {
      myDFPlayer.play(1);
      Serial.println("8+7");
    }
  }

}

int myBuzzer(int nb, int msec, int port){
  for (int i=1;i<=nb;i=i+1)
  {
    digitalWrite(port, HIGH);
    delay(msec);
    digitalWrite(port, LOW);
    delay(msec);
    Serial.println(i);
  }
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
