#define IRpin_PIN PIND
#define IRpin 2
#define MAXPULSE 65000
#define RESOLUTION 20
  
// we will store up to 100 pulse pairs (this is -a lot-)
uint16_t pulses[100][2]; // pair is high and low pulse
uint8_t currentpulse = 0; // index for pulses we're storing
  
void setup(){
  Serial.begin(9600);
  Serial.println("Ready to decode IR!");
}
  
void loop(){
  uint16_t highpulse, lowpulse;
  highpulse = lowpulse = 0;
  while(IRpin_PIN & _BV(IRpin)){
    highpulse++;
    delayMicroseconds(RESOLUTION);
  
    // If the pulse is too long, we 'timed out' - either nothing
    // was received or the code is finished, so print what
    // we've grabbed so far, and then reset
    if((highpulse >= MAXPULSE) && (currentpulse != 0)){
      printpulses();
      currentpulse=0;
      return;
    }
  }
  pulses[currentpulse][0] = highpulse;
  
  // same as above
  while(!(IRpin_PIN & _BV(IRpin))){
    lowpulse++;
    delayMicroseconds(RESOLUTION);
    if((lowpulse >= MAXPULSE) && (currentpulse != 0)){
      printpulses();
      currentpulse=0;
      return;
    }
  }
  pulses[currentpulse][1] = lowpulse;
  
  // we read one high-low pulse successfully, continue!
  currentpulse++;
}
  
void printpulses(void) {
  Serial.println('\n\r\n\rReceived: \n\rOFF \tON');
  // Gera o codigo da tecla pressionada.
  for (uint8_t i = 0; i < currentpulse; i++) {
  Serial.print("delayMicroseconds(");
  Serial.print(pulses[i][0] * RESOLUTION, DEC);
  Serial.print(");\n");
  Serial.print("pulseIR(");
  Serial.print(pulses[i][1] * RESOLUTION, DEC);
  Serial.print(");\n");
  }
 
}
