#include <SFML/Graphics.hpp>
#include <iostream>

#include "GroupPattern.h"
#include "ShapeLibrary.h"

using namespace sf;
int main()
{
	iComponent* cir1 = new eCircleShape(eCoordinates(5,20),25,Color::Red); // creating Circle object with Pattern 
	iComponent* rec2 = new eRectangleShape(e2Dimension(55,40),eCoordinates(10,350),Color::Yellow);
	iComponent* rec3 = new eRectangleShape(350, 50, 45, 75);// creating Rectangle object with Pattern 
	iComponent* cir4 = new eCircleShape(eCoordinates(320, 300), 60,Color::Blue); // etc
	iComponent* cir5 = new eCircleShape(eCoordinates(500, 558), 70, Color::Green);
	iComponent* rec6 = new eRectangleShape(e2Dimension(30,40), eCoordinates(101, 620),Color::Black);
	iComponent* group1 = new eGroupCreator(Color::Blue); // creating group to which objects of the shape type will be added
	iComponent* group2 = new eGroupCreator(Color::Magenta); // parameter  is a outline color
	iComponent* group3 = new eGroupCreator(Color::Yellow); // etc
	iComponent* group4 = new eGroupCreator();

	group2->addToGroup(cir1); 
	group2->addToGroup(rec2);
	group1->addToGroup(group2);
	group1->addToGroup(rec6);

	group3->addToGroup(rec3);
	group3->addToGroup(cir4);
	group3->addToGroup(cir5);
	group3->addToGroup(rec6);
	group3->removeFromGroup(cir4);

	group4 = group3->clone(); // clone group3 to group4
	group4->moveTo(300, -21); // right 80 points, up 10 points


	std::vector<iComponent*> vec1 = Interface::mergeShapes(3, group1,group3, group4); // merge unlimited objects in one vector 

	Interface::printDescription(vec1); // print object descriptions
	Interface::DrawShapes(vec1);// draw objects with SFML Library
	
	//Interface::DrawShapes(grop3);
	//Interface::DrawShapes(grop1);
	//Interface::DrawShapes(grop4);

	return 0;
}