char asciiTable[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 
  'V', 'W', 'X', 'Y', 'Z', ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', ',', '?', '.', '\'' 
};
String morseTable[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", 
  ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "/", ".----", "..---", 
  "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----", "-.-.--", "--..--","..--..", 
  ".-.-.-", ".----."
};
#define duration 200

String stringToMorse(String text) {
  char newText[text.length()+1];
  text.toUpperCase();
  text.toCharArray(newText, text.length()+1);
  String output = "";
  
  for (char letter : newText) {
    for (int i=0; i<sizeof(asciiTable); i++) {
      if (letter == asciiTable[i]) {
        output += morseTable[i]+" ";
        break;
      }
    }
  }
  return output;
}

void runMorse(String morseStr) { runMorse(morseStr, 13); }
void runMorse(String morseStr, int outputPin) {
  char text[morseStr.length()+1];
  morseStr.replace("_", "-");
  morseStr.toCharArray(text, morseStr.length()+1);

  for (char morse : text) {
    if (morse == '.') led(outputPin, duration);
    else if (morse == '-') led(outputPin, duration*3);
    else if (morse == ' ') delay(duration*5);
    else if (morse == '/') delay(duration*7);
    else break;
  }
  for (int i=0; i<5; i++) led(outputPin, 100, true);
}

void led(int outputPin, int wait) { led(outputPin, wait, false); }
void led(int outputPin, int wait, boolean all) {
  digitalWrite(outputPin, HIGH);
  delay(wait);
  digitalWrite(outputPin, LOW);
  if (all) delay(wait);
  else delay(duration*3);
}
