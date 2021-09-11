//####################### Library #######################
/* Sources:
 *   Morse codes table: https://morsedecoder.com/fr/
 *   Codes of the Morse tenses: https://www.codebug.org.uk/learn/step/541/morse-code-timing-rules/
 */

char asciiTable[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
  'À', 'Â', 'Æ', 'Ç', 'È', 'Ë', 'É', 'Ê', 'Ï', 'Ô', 'Ü', 'Ù', 
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
  ' ', '!', ',', '?', '.', '\'' , '/', '(', ')', '&', ':', ';', '=', '+', '-', '_', '"', '$', '@', '¿', '¡'
};
String morseTable[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
  ".--.-", ".--.-", ".-.-", "-.-..", ".-..-", "..-..", "..-.." ,"-..-.", "-..--", "---.", "..--", "..--", 
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", 
  "/", "-.-.--", "--..--","..--..", ".-.-.-", ".----.", "-..-.", "-.--.", "-.--.-", ".-...", "---...", "-.-.-.", "-...-", ".-.-.", "-....-", "..--.-", ".-..-.", "...-..-", ".--.-.", "..-.-", "--...-"
};
int duration = 200;

// Modifies the duration of one 'time'. (default: 200ms)
void setTimeDuration(int _duration) {
  duration = _duration;
}

/* Convert a text in morse code.
 * If one character is not present in 'asciiTable':
 *   If convertUnrecognizedUharacters=false: it will be ignored.
 *   Else: it will be replace with '#'.
 */
String stringToMorse(String text) { stringToMorse(text, true); }
String stringToMorse(String text, boolean convertUnrecognizedUharacters) {
  String output = "";
  char newText[text.length()+1];
  text.toUpperCase();
  text.toCharArray(newText, text.length()+1);
  boolean found;
  
  for (char letter : newText) {
    found = false;
    
    for (int i=0; i<sizeof(asciiTable); i++) {
      if (letter == asciiTable[i]) {
        output += morseTable[i]+" ";
        break;
      }
    }
    if (!found && convertUnrecognizedUharacters) output += "#";
  }
  return output.endsWith(" ") ? output.substring(output.length()-1) : output;
}

/* Convert a morse code in text.
 * If one character is not present in 'asciiTable':
 *   If convertUnrecognizedUharacters=false: it will be ignored.
 *   Else: it will be replace with '#'.
 */
String morseToString(String morseText) { morseToString(morseText, true); }
String morseToString(String morseText, boolean convertUnrecognizedUharacters) {
  String output = "";
  String newText[] = {};
  int index = morseText.indexOf(' ');
  int textSize = morseText.length();
  boolean found;
  
  while (index != -1) {
    index = morseText.indexOf(' ');
    newText[sizeof(newText)] = morseText.substring(index);
    morseText = morseText.substring(index+1, textSize);
  }

  for (String morse : newText) {
    found = false;
    
    for (int i=0; i<sizeof(morseTable)/sizeof(morseTable[0]); i++) {
      if (morse == morseTable[i]) {
        output += asciiTable[i];
        found = true;
        break;
      }
    }
    if (!found && convertUnrecognizedUharacters) output += "#";
  }
  return output;
}

/* Cut and run a morse code on a given pin (Led, Speaker, etc) according to the codes of the Morse tenses.
 * The '#' character is considered an unrecognized character. (add when converting to Morse code)
 * If the program encounters a character other than '.', '-', '_', ' ', '/', '#', it will stop.
 */
void runMorse(String morseText) { runMorse(morseText, 13); }
void runMorse(String morseText, int outputPin) {
  char text[morseText.length()+1];
  morseText.toCharArray(text, morseText.length()+1);

  for (char morse : text) {
    if (morse == '.') led(outputPin, duration);
    else if (morse == '-' || morse == '_') led(outputPin, duration*3);
    else if (morse == ' ') delay(duration*3);
    else if (morse == '/') delay(duration*7);
    else if (morse == '#') continue;
    else return;
  }
  for (int i=0; i<5; i++) led(outputPin, 100, true);
}

// Please don't use this method, it just for the program.
void led(int outputPin, int wait) { led(outputPin, wait, false); }
void led(int outputPin, int wait, boolean all) {
  digitalWrite(outputPin, HIGH);
  delay(wait);
  digitalWrite(outputPin, LOW);
  if (all) delay(wait);
  else delay(duration);
}
//####################### Library #######################
