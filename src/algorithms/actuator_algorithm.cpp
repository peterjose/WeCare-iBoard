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
