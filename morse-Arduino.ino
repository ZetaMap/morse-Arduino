//####################### Library #######################
/* Sources:
 *   Morse codes table: https://morsedecoder.com/fr/
 *   Codes of the Morse tenses: https://www.codebug.org.uk/learn/step/541/morse-code-timing-rules/
 *   
 * Create by ZetaMap.
 * Github project: https://github.com/ZetaMap/morse-Arduino
 * My github: https://github.com/ZetaMap
 */

static char characterTable[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
  'À', 'Â', 'Æ', 'Ç', 'È', 'Ë', 'É', 'Ê', 'Ï', 'Ô', 'Ü', 'Ù', 
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
  ' ', '!', ',', '?', '.', '\'' , '/', '(', ')', '&', ':', ';', '=', '+', '-', '_', '"', '$', '@', '¿', '¡'
};
static String morseTable[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
  ".--.-", ".--.-", ".-.-", "-.-..", ".-..-", "..-..", "..-.." ,"-..-.", "-..--", "---.", "..--", "..--", 
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", 
  "/", "-.-.--", "--..--","..--..", ".-.-.-", ".----.", "-..-.", "-.--.", "-.--.-", ".-...", "---...", "-.-.-.", "-...-", ".-.-.", "-....-", "..--.-", ".-..-.", "...-..-", ".--.-.", "..-.-", "--...-"
};
int DURATION = 200;

/* Modifies the duration of one 'time'. (default: 200ms)*/
void setTimeDURATION(const int duration) {
  DURATION = duration;
}

/* Convert a text in morse code. 
 * If one character is not present in 'characterTable':
 *   If convertUnrecognizedCharacters=false: it will be ignored.
 *   Else: it will be replace with '#'.
 */
String stringToMorse(String text) { return stringToMorse(text, true); }
String stringToMorse(String text, const boolean convertUnrecognizedCharacters) {
  String output = "";
  char character;
  boolean found;
  text.toUpperCase();
  
  for (int i=0; i<text.length(); i++) {
    character = text[i];
    found = false;
    
    for (int ii=0; ii<69; ii++) {
      if (character == characterTable[ii]) {
        output += morseTable[ii]+" ";
        found = true;
        break;
      }
    }
    if (!found && convertUnrecognizedCharacters) output += "#";
  }
  return output.endsWith(" ") ? output.substring(0, output.length()-1) : output;
}

/* Convert a morse code in text.
 * If one morse code is not present in 'morseTable':
 *   If convertUnrecognizedMorseCode=false: it will be ignored.
 *   Else: it will be replace with '#'.
 * If the program encounters a character other than '.', '-', '_', ' ', '/', and '#', it will print an error and return the text already converted.
 */
String morseToString(String morseText) { return morseToString(morseText, true); }
String morseToString(String morseText, const boolean convertUnrecognizedMorseCode) {
  morseText += " ";
  String output = "";
  String morse = "";
  char character;
  boolean found;
  
  for (int i=0; i<morseText.length(); i++) {
    character = morseText[i];

    if (character == '.'|| character == '-'|| character == '_') {
      morse += character;
      
    } else if (character == '/') {
      output += " ";
      
    } else if (character == ' ') {
      found = false;

      for (int ii=0; ii<69; ii++) {
        if (morse == morseTable[ii]) {
          output += characterTable[ii];
          found = true;
          break;
        }
      }
      
      if (!found && convertUnrecognizedMorseCode) output += "#";
      morse = "";
      
    } else if (character != '#') {
      Serial.println("Error: unknown morse character '"+String(character)+"'");
      break;
    }
  }
  return output;
}

/* Cut and run a morse code on a given pin (bip, Speaker, etc) according to the codes of the Morse tenses.
 * The '#' character is considered an unrecognized character. (add when converting to Morse code)
 * If the program encounters a character other than '.', '-', '_', ' ', '/', and '#', it will print an error and stop.
 */
void runMorse(const String morseText) { runMorse(morseText, LED_BUILTIN); }
void runMorse(const String morseText, const int outputPin) {
  char morse;

  for (int i=0; i<morseText.length(); i++) {
    morse = morseText[i];
    
    if (morse == '.') bip(outputPin, DURATION);
    else if (morse == '-' || morse == '_') bip(outputPin, DURATION*3);
    else if (morse == ' ') delay(DURATION*3);
    else if (morse == '/') delay(DURATION*7);
    else if (morse == '#') continue;
    else {
      Serial.println("Error while printing character: "+morse);
      return;
    }
  }
  
  delay(DURATION*3);
  for (int i=0; i<5; i++) bip(outputPin, (int) DURATION/2, true);
}

// Please don't use this method, it just for the program.
void bip(int outputPin, int wait) { bip(outputPin, wait, false); }
void bip(int outputPin, int wait, boolean all) {
  digitalWrite(outputPin, HIGH);
  delay(wait);
  digitalWrite(outputPin, LOW);
  if (all) delay(wait);
  else delay(DURATION);
}
//####################### Library #######################
