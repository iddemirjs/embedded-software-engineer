String interval = "-1";
String startPoint = "-1";

#define LED0 9
#define LED1 10
#define LED2 11
#define LED3 12
#define LED4 13

void setup() {
  Serial.begin(9600);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

int binario[5]; // onde fica o numero em binário

// function to convert decimal to binary
void decParaBin(int n)
{
  int k = 0;
  while(k<5){
    binario[k]=0;
    k++;
  }
  // contador para o array binario
  int i = 0;
  while (n > 0) {
 
        // colocando o número binario no array
        binario[i] = n % 2;
        n = n / 2;
        i++;
    }
}
 
void loop() {
  if(Serial.available() == 0 && interval == "-1") {
     Serial.print("Enter timeInterval:");
  }
  while (Serial.available() == 0 && interval == "-1") { // Serial Porta girdi değerinin olup olmadığını kontrol et
  }
  if(Serial.available() != 0 && interval == "-1" ){
    interval = Serial.readString();
    interval.trim();
    Serial.println(interval);// Serial Porttaki girdi değerini oku ve string e ata.   
  }

  if(Serial.available() == 0 && startPoint == "-1") {
     Serial.print("Enter increment:");
  }
  while(Serial.available() == 0 && startPoint == "-1") {
  }
  if (Serial.available() != 0 && startPoint == "-1"){
    startPoint = Serial.readString(); 
    startPoint.trim();
    Serial.println(startPoint);
  }
  
  Serial.println("startpoint:"+startPoint);
  if(startPoint != "-1" && interval != "-1"){
    int intervalInt = interval.toInt();
    int startPointInt = startPoint.toInt();
    if(intervalInt < 1 || intervalInt > 10000){
      interval = "-1";
      Serial.println("Unexpected interval input");
    }
    if(startPointInt < 1 || startPointInt > 30){
      startPoint = "-1";
      Serial.println("Unexpected increment input");
    }
    if(startPoint != "-1" && interval != "-1"){
      int currentNumber = 0;
      while(true){
        decParaBin(currentNumber);
        Serial.print("decimal:");
        Serial.println(currentNumber);
        Serial.print("binary start : ");
        Serial.print( binario[4]);
        Serial.print( binario[3]);
        Serial.print( binario[2]);
        Serial.print( binario[1]);
        Serial.println( binario[0]);
        digitalWrite(LED0, binario[0]);
        digitalWrite(LED1, binario[1]);
        digitalWrite(LED2, binario[2]);
        digitalWrite(LED3, binario[3]);
        digitalWrite(LED4, binario[4]);   
        delay(intervalInt);
        currentNumber = (currentNumber + startPointInt) % 32;
      }
    }
    //decParaBin(startPoint.toInt());
    //Serial.print("binary start : ");
    //Serial.print( binario[4]);
    //Serial.print( binario[3]);
    //Serial.print( binario[2]);
    //Serial.print( binario[1]);
    //Serial.println( binario[0]);
    //delay(intervalInt);
  }
  

}
