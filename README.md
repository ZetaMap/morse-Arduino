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
    * Parameters: **text**, **convertUnrecognizedCharacters** (optional)
    * Description: Convert a text in morse code. <br>
        If one character is not present in 'characterTable': <br>
          \tIf convertUnrecognizedCharacters=false: it will be ignored. <br>
          \tElse: it will be replace with '#'. <br>
