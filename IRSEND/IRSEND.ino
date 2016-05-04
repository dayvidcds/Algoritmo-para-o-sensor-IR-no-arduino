const int IRledPin = 3;
 
void setup(){                
   pinMode(IRledPin, OUTPUT);       
   Serial.begin(9600);
 }
 
 void loop(){
   delay(1000);
   Serial.println("Sending IR signal");
   SendNikonCode();
   delay(60*1000);
 }

 void pulseIR(long microsecs){
    cli();
    while(microsecs > 0){
    digitalWrite(IRledPin, HIGH);  
    delayMicroseconds(10);
    digitalWrite(IRledPin, LOW);
    delayMicroseconds(10);
    microsecs -= 26;
   }
   sei();
 }
 
 void SendNikonCode() {
   //aqui fica os bagulhos que foi recebido pelo IRreceptor
 } 
