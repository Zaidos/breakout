#include <iostream>
//#include "Ball.h"
using namespace std;

        class Brick
        {
            private:
                float width;
                float height;
                float posX;
                float posY;
		bool alive;
            public:
                Brick():width(40.0f),height(15.0f){}
                void Initialize(float x, float y)
                {
                    posX = x;
                    posY = y;
		    alive = true;
                }
                float GetWidth(){ return width; }
                float GetHeight(){ return height; }
		float GetX(){ return posX; }
		float GetY(){ return posY; }
		void brickCollision(Ball &ball)
		{
	                //bottom of brick w/ top of ball.
	                if((ball.GetY() - ball.GetHeight() == posY + height)
	                        &&(ball.GetX()/*+ball.GetWidth()*/>(posX))
	                            && (ball.GetX()/*-ball.GetWidth()*/ < (posX + width)))
	                            {
	                                ball.SetVerticalDirection(ball.GetVerticalDirection() *-1);
	                                alive = false;
	                            }
	                //top of brick w/ bottom of ball
	                if((ball.GetY() + ball.GetHeight() == posY)
	                        &&(ball.GetX()/*+ball.GetWidth()*/>(posX))
	                            && (ball.GetX()/*-ball.GetWidth()*/ < (posX + width)))
	                            {
	                                ball.SetVerticalDirection(ball.GetVerticalDirection() *-1);
	                                alive = false;
	                            }
	                //left of ball with right of brick
	                if((ball.GetX() - ball.GetWidth() == posX + width)
	                        &&((ball.GetY() + ball.GetHeight())>(posY))
	                            && (ball.GetY() < (posY + height)))
	                            {
	                                ball.SetHorizontalDirection(ball.GetHorizontalDirection() *-1);
	                                alive = false;
	                            }
	                //right of ball left of brick
	                if((ball.GetX() + ball.GetWidth() == posX)
	                        &&((ball.GetY() + ball.GetHeight()) > (posY))
	                            && (ball.GetY() < (posY + height)))
	                            {
	                                ball.SetHorizontalDirection(ball.GetHorizontalDirection() *-1);
	                                alive = false;
	                            }
		}
		bool isAlive(){ return alive; }
		void kill(){ alive = false; }



        };


class Bricks
{
    private:
	float posX;
	float posY;
	int TotalBricks;
    public:
	Brick bricks[4][18];

	Bricks(float x=300, float y=140)
	{
	    TotalBricks = 72;
	    posX = x;
	    posY = y;
	    int b = 0;
	    for(int j = 0; j< 4;j++)
	    {
		x=posX;
		for(int i = 0; i < 18; i++)
		{
		    bricks[j][i].Initialize(x+i*30,y+j*10);
		    x++;
		}
		y++;
	    }

	    
	}
	Brick* GetBricks()
	{
	    Brick *thing;
	    thing = new Brick;
	    thing = &bricks[0][0];
	    return thing;
	}

};
