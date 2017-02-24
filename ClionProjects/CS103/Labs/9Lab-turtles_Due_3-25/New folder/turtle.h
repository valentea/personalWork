#include "draw.h"
class Turtle
{
	private:
		double xCord,yCord,angleInDegrees;
		Color color;
		bool printLine=true;
	public:
		Turtle();
		Turtle(double,double,double);
		void move(double distance);
		void turn(double degrees);
		void setColor(Color colorSet);
		void on();
		void off();
};

