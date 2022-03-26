#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
unsigned long time_now = 0;
String row0Text = "bu bir uzun text baya uzun.";
String row1Text = "bu bir uzun text baya uzun.";
int row0Status = 0;
int row1Status = 0;
int row0Direction = 0;
int row1Direction = 0;
int row0Speed = 500;
int row1Speed = 1000;

String lastCommand = "-1";
String waitingCommand = "";
String commandParameter = "";
int r0X=0;
int r1X=0;
String trCharacters[] = "çığöşİĞÜÖŞÇ";
String trCharactersTo[] = "ciugosIGUOSC";

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
  printMenu();
  
  Serial.print("\nPLEASE ENTER SETTING NUMBER : ");
  lcd.setCursor(r0X,0);
  lcd.print(row0Text);
  lcd.setCursor(r1X,1);
  lcd.print(row1Text);
}

void loop()
{
  if(Serial.available() != 0 && lastCommand == "-1" ){
    lastCommand = Serial.readString();
    lastCommand.trim();
    orderProcess(lastCommand);
    Serial.println();
  } else if(Serial.available() != 0 && lastCommand == "-2"){
    commandParameter = Serial.readString();
    commandParameter.trim();
    putNewParameter(waitingCommand,commandParameter);
    Serial.println();
  }

  time_now = ( millis() ) % 50000;
  if(time_now % row0Speed < 20){
    makeRow0Process();
  }
  if(time_now % row1Speed < 20){
    makeRow1Process();
  }
  
}

void printMenu(){
  Serial.println("0 – PRINT THIS STATUS SCREEN");
  Serial.println("LCD ROW 0 (UP)");
  Serial.println("1 – TEXT :");
  Serial.println(row0Text);
  Serial.print("2 – SCROLLING STATUS :");
  Serial.println((row0Status == 0 ) ? "DISABLE" : "ENABLE");
  Serial.print("3 – SCROLLING DIRECTION :");
  Serial.println((row0Direction == 0 ) ? "LEFT" : "RIGHT");
  Serial.print("4 – SCROLLING SPEED (MS):");
  Serial.println(row0Speed);
  Serial.println("LCD ROW 1 (DOWN)");
  Serial.println("5 – TEXT :");
  Serial.println(row1Text);
  Serial.print("6 – SCROLLING STATUS :");
  Serial.println((row1Status == 0 ) ? "DISABLE" : "ENABLE");
  Serial.print("7 – SCROLLING DIRECTION :");
  Serial.println((row1Direction == 0 ) ? "LEFT" : "RIGHT");
  Serial.print("8 – SCROLLING SPEED (MS):");
  Serial.print(row1Speed);
}

void orderProcess(String cmd){
  Serial.println(cmd);
  if(cmd >= "0" && cmd <= "8"){
   if(cmd == "0"){
     printMenu();
     lastCommand = "-1";
     waitingCommand = "";
     commandParameter = "";
     Serial.print("PLEASE ENTER SETTING NUMBER : ");
   } else if(cmd == "1") {
     Serial.print("PLEASE ENTER TEXT FOR (R1) : ");
     lastCommand = "-2";
     waitingCommand = "1";
   } else if(cmd == "2"){
     Serial.print("PLEASE ENTER 0 TO DISABLE OR 1 TO ENABLE SCROLLING (R1) : ");
     lastCommand = "-2";
     waitingCommand = "2";
   }else if(cmd == "3"){
     Serial.print("PLEASE ENTER 0 FOR LEFT AND 1 FOR RIGHT SCROLLING DIRECTION (R1) : ");
     lastCommand = " 91";
     waitingCommand = "3";
   }else if(cmd == "4"){
     Serial.print("PLEASE ENTER SCROLLING SPEED FOR (R1) (MS) : ");
     lastCommand = "-2";
     waitingCommand = "4";
   }else if(cmd == "5") {
     Serial.print("PLEASE ENTER TEXT FOR (R1) : ");
     lastCommand = "-2";
     waitingCommand = "5";
   } else if(cmd == "6"){
     Serial.print("PLEASE ENTER 0 TO DISABLE OR 1 TO ENABLE SCROLLING (R1) : ");
     lastCommand = "-2";
     waitingCommand = "6";
   }else if(cmd == "7"){
     Serial.print("PLEASE ENTER 0 FOR LEFT AND 1 FOR RIGHT SCROLLING DIRECTION (R1) : ");
     lastCommand = "-2";
     waitingCommand = "7";
   }else if(cmd == "8"){
     Serial.print("PLEASE ENTER SCROLLING SPEED FOR (R1) (MS) : ");
     lastCommand = "-2";
     waitingCommand = "8";
   }
  }
}

void putNewParameter(String processID, String parameter){
  Serial.println(parameter);
  if(processID == "1"){
    row0Text = parameter;
    Serial.println(row0Text);
    convertTRCharacters();
    Serial.println(row0Text);
  }else if(processID == "2"){
    if(parameter == "0"){
      row0Status = 0;
    }else if(parameter == "1"){
      row0Status = 1;
    }
  }else if(processID == "3"){
    if(parameter == "1"){
      row0Direction = 0;
    }else if(parameter == "0"){
      row0Direction = 1;
    }
  }else if(processID == "4"){
    row0Speed = parameter.toInt();
  }else if(processID == "5"){
    row1Text = parameter;
    convertTRCharacters();
  }else if(processID == "6"){
    if(parameter == "0"){
      row1Status = 0;
    }else if(parameter == "1"){
      row1Status = 1;
    }
  }else if(processID == "7"){
    if(parameter == "1"){
      row1Direction = 0;
    }else if(parameter == "0"){
      row1Direction = 1;
    }
  }else if(processID == "8"){
    row1Speed = parameter.toInt();
  }
  lastCommand = "-1";
  waitingCommand = "";
  commandParameter = "";
  Serial.print("PLEASE ENTER SETTING NUMBER : ");
}

void makeRow0Process(){
  lcd.setCursor(0,0);
  lcd.print("                ");
  if  (row0Direction == 0){
    r0X = (++r0X)%16;
  }else{
    r0X = (--r0X)%16;
    r0X = (r0X < 0) ? 16 + r0X : r0X;
  }
  
  if(row0Text.length()<16 && row0Text.length() > 16 - r0X) {
    lcd.setCursor(0,0);
    lcd.print(row0Text.substring(16 - r0X));  
  }else if (row0Text.length() >= 16){
    lcd.setCursor(0,0);
    lcd.print(row0Text.substring(row0Text.length()-r0X, row0Text.length())); 
  }
  lcd.setCursor(r0X,0);
  lcd.print(row0Text);
  
}

void makeRow1Process(){
  lcd.setCursor(0,1);
  lcd.print("                ");
  if  (row1Direction == 0){
    r1X = (++r1X)%16;
  }else{
    r1X = (--r1X)%16;
    r1X = (r1X < 0) ? 16 + r1X : r1X;
  }

  if(row1Text.length()<16 && row1Text.length() > 16 - r1X) {
    lcd.setCursor(0,1);
    lcd.print(row1Text.substring(16 - r1X));  
  }else if (row1Text.length() >= 16){
    lcd.setCursor(0,1);
    lcd.print(row1Text.substring(row1Text.length()-r1X, row1Text.length())); 
  }
  
  lcd.setCursor(r1X,1);
  lcd.print(row1Text);
}

void convertTRCharacters(){
  for(int i = 0;i<=12;i++){
    row0Text.replace(trCharacters[i],trCharactersTo[i]);
    row1Text.replace(trCharacters[i],trCharactersTo[i]);
  }
}
