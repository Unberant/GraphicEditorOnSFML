# GraphicEditorOnSFML
- I used the SFML graphics library, so I'm adding a working project, but you need to install an additional library to run.  
Instruction: https://www.sfml-dev.org/tutorials/2.5/
- In performing the work used a Composite and Decorator, to describe the logic and interface, and part of the Prototype pater to describe cloning
- To create elementary components (Circle, Rectangle), you need to connect two libraries  
```javascript
#include "GroupPattern.h"  
#include "ShapeLibrary.h"  
iComponent * circle = new eCircleShape (eCoordinates (5,20), 25, Color :: Red);  
iComponent * rectangle = new eRectangleShape (e2Dimension (55,40), eCoordinates (10,350), Color :: Red);  
```
___There are different types of constructions___  
- To combine components into a group, you need to create it as follows:  
```javascript
iComponent * group = new eGroupCreator (); 
```
___You also can change the contour's colour___   
- Add component(s) to the group:  
```javascript
group-> addToGroup (circle);  
group-> addToGroup (rectangle);
group -> removeFromGroup (circle); // for remove from group
```
- To copy items:  
```javascript
Group1 = group-> clone ();  
Rectangle1 = rectangle-> clone ();  
```
- Move items (if methood is used on group, all items will be moved)
```javascript
group-> moveTo (300, -21);  
```
___all elements in the group will be moved 300 coordinates to the right, 21 - up___  
- To get a description of objects you need to use Interface ::  
```javascript
std :: vector <iComponent *> vector = Interface :: mergeShapes (3, group1, group3, group4); // - Merge objects into a vector  
Interface :: printDescription (vector); // - output description of objects in vector  
Interface :: printDescription (group1); //- output of the object description  
Interface :: DrawShapes (vector)  // - drawing objects in vector, 
				 // it should be noted that SFML does not support interrupting the console with graphics and program continuation,
			 	 // ie if you use this method, it is the logical conclusion of the program  
```
