# ConsoleTester
A simple console-based tester for closed questions with one or more correct answers.

## Installation instructions

### Windows

 1. Download at least the `.msi` file.
 2. Open it and proceed with the installation.
 3. Done.
 
### Other systems

 1. Download the source code.
 2. Compile it yourself.
 3. Hope it works, because it's tested only on Windows.

## Usage

* You can modify the questions.txt file in your installation folder or make your own.
  * Make sure it follows the syntax. 
  * If you make your own, remember to use the l command upon opening the programme.
* Open up the programme. It will open a console with instructions.
  * Special:
    * ! - Quit the programme.
    * l - Change location - load questions from another location.
    * s - Toggle correct answer showing - By default, correct answers are not shown after answering.
  * Questioning modes
    * f - Full mode     - programme will randomise the order and use each question once. Results outputted at the end.
    * e - Endless mode  - programme will randomise the order and use each question once, then repeat it. '!' ends it. '%' outputs results.
    * r - Random mode   - programme will randomise which question it shows, then repeat it. '!' ends it. '%' outputs results.
* You answer by inputting a space-separated letter sequence of answers you deem to be correct. Just the sequence and Enter/Return, e.g. " A d".
   
## How are you calculating the percentages when there are multiple correct answers?

I am using a special(TM) method. Your score for a question is the worst of the two assignment percentages you made in the answer - to the verstractor set and distractor set. You don't need to understand it. 

**It just works.**

  
