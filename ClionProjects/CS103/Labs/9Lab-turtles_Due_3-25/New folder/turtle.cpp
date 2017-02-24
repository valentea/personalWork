#include "Turtle.h"
#include <cmath>

Turtle::Turtle()
{
	xCord=0;
	yCord=0;
	angleInDegrees=0;
	color.green=0;
	color.red=0;
	color.blue=0;
}

Turtle::Turtle(double x, double y, double a)
{
	xCord=x;
	yCord=y;
	angleInDegrees=a;
	color.green=0;
	color.red=0;
	color.blue=0;
}

void Turtle::move(double distance) {
	double angleInRadians=(angleInDegrees/180)*M_PI;
	double xCordAfterTravel=distance*cos(angleInRadians);
	double yCordAfterTravel=distance*sin(angleInRadians);
	draw::setcolor(color.red,color.green,color.blue);

	if(printLine==true) {
		draw::settransparency(0);
	}else {
		draw::settransparency(1);
	}

	draw::line(xCord,yCord,xCord+xCordAfterTravel,yCord+yCordAfterTravel);
	xCord+=xCordAfterTravel;
	yCord+=yCordAfterTravel;
}

void Turtle::turn(double degrees) {
	angleInDegrees+=degrees;
}

void Turtle::setColor(Color colorSet) {
	color.red=colorSet.red;
	color.green=colorSet.green;
	color.blue=colorSet.blue;
}

void Turtle::on() {
	printLine=true;
}

void Turtle::off() {
	printLine=false;
}