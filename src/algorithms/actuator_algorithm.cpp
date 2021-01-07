//The possible actuation scenarios are planned in this file

//Feel free to make changes(Add more scenarios. Discuss before deleting/modifying scenarios)


//Actuation in response to the placement of the cube on the iBoard

/* Scenario 1 : 
- User places a cube on the iBoard1
- Check if the cube in the bottom layer is already up
  - if cube already moved up, move it down
  - if not actuated, stay the same
*/


/* Scenario 2 : 
- User A places a cube on the iBoard1
- Check for placment of cubes in iBoard2
  - if cube placed already, reduce the actuation distance of the bottom cube relative to the default actuation distance
  - if no cube, stick to default actuation distance
*/

/* Scenario 3:
- User A places a cube on iBoard1
- A default waiting duration(timer) is set for placement
- It is reset with everyplacement
- When the timer runs out after a placement, it is assumed that the user is done with placement
- The iBoard2 is actuated in a synchronous motion(up and down) until the user places a cube on any of the immobile cubes
*/

//Actuation for playing games
/*
- Pattern to  be recognised :
  - to activate play mode:
    X-o
    X-X
    X-o
      - No other cubes should be placed on the iBoard
    - Change LED to green
    - Sync actuation on iBoard2
    - Check for iBoard2 to accept
      - if user places a cube on an immobile cube, 
        - stop actuation
        - change to play mode
  - to deactivate play mode:
    X-X
    X-X
      - No other cubes should be placed on the iBoard
    - Change LED to red
    - Sync actuation on iBoard2
    - Check for iBoard2 to accept
      - if user places a cube on an immobile cube, 
        - stop actuation
        - change to default mode
- Play mode:
  - Scenario 1 and 2 used during the play
  - Different LED colour used for each user
  - Patter recognition:
    - Pattern 1:
      X-X-X-X
    - Pattern 2:
      X-o-o-o
      o-X-o-o
      o-o-X-o
      o-o-o-X
    - Pattern 3:
      X-o-o-o
      X-o-o-o
      X-o-o-o
      X-o-o-o
  - If pattern recognised
    - sync actuation of the 'X' blocks indicating winner
    - check if the user removes a placed cube or places a cube on a immobile cube
      - if placed/removed
        - stop actuation
  - If a cube on iBoard1 is lifted
    - the respective cube should move down in iBoard2 to keep the game going
*/

//LED colour change for activated cubes for certain default emojis
/* Scenario 4: Heart
- Pattern to  be recognised :
X-o-X
X-X-X
o-X-o
- Change LED to Red
*/

/* Scenario 5: Smile
- Pattern to  be recognised :
o-X-X-o
o-o-o-o
X-o-o-X
o-X-X-o
- Change LED to Green/Yellow
*/

/* Scenario 6: Sad face
- Pattern to  be recognised :
o-X-X-o
o-o-o-o
o-X-X-o
X-o-o-X
- Change LED to Red
*/
