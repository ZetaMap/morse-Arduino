# morse-Arduino
A small program which allows to convert a text into Morse code and conversely. And which can run it on a given pin.<br>
You just need to copy/paste this program at the start of your script.<br>

### Sources

* Morse codes table: https://morsedecoder.com/fr/
* Codes of the Morse tenses: https://www.codebug.org.uk/learn/step/541/morse-code-timing-rules/

### Content

* Constants and Variables:
  * **characterTable**: The list of all the characters recognized by the program 
  * **morseTable**: The list of Morse codes associated with recognized characters
  * **DURATION**: The duration of one time (by default: 200ms)

* Methods:
  * **setTimeDuration**
    * Parameters: **duration**
    * Description: Modifies the duration of one 'time'. (default: 200ms)

  * **textToMorse**
    * Parameters: **text**, **convertUnrecognizedCharacters (optional)**[default: true]
    * Description: Convert a text in morse code. <br>
        If one character is not present in 'characterTable': <br>
        If convertUnrecognizedCharacters=false: it will be ignored. <br>
        Else: it will be replace with '#'. <br>
        
  * **morseToText**
    * Parameters: **morseText**, **convertUnrecognizedCode (optional)**[default: true]
    * Description: Convert a morse code in text. <br>
      If one morse code is not present in 'morseTable': <br>
      If convertUnrecognizedCode=false: it will be ignored. <br>
      Else: it will be replace with '#'. <br>
      If the program encounters a character other than '.', '-', '_', ' ', '/', and '#', it will print an error and return the text already converted. <br>
      
  * **runMorse**
    * Parameters: **morseText**, **outputPin (optional)**[default: LED_BUILTIN], **frequency (optional)**[default: -1]
      
