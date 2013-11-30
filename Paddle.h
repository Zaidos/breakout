#include <math.h>
using namespace std;


class Paddle
{
	private:
		float width;
		float speed;
		float posY;
		float posX;
		float height;
	public:
		Paddle( float h = 5.0f, float w = 50.0f, float s = 15.0f, float x = 550.0f, float y = 550.0f )
		{
			height = h;
			width = w;
			speed = s;
			posX = x;
			posY = y;
		}
		void ResetPaddle()
		{
		    posX = 550.0f;
		    posY = 550.0f;
		}
		void PaddleCollision(Ball &ball)
		{
		    if( ball.GetY() + ball.GetHeight() >= ( posY - height ) )
		    {
				if( (ball.GetX() > (posX - width - 1)) && 
					(ball.GetX() < (posX + width + 1)))
				{
					ball.SetVerticalDirection(ball.GetVerticalDirection() * -1);
					if(ball.GetX() < posX)//if it his on left side of paddle.
					{
					//ball.SetHorizontalDirection(fabs(ball.GetOriginalHorizontal())*-1);
					ball.SetHorizontalDirection(fabs(ball.GetHorizontalDirection())*-1);
					//ball.SetHorizontalDirection(ball.GetHorizontalDirection()+(ball.GetX() - posX)/100);
					//if(fabs(ball.GetX() - posX)<15)ball.SetHorizontalDirection(ball.GetHorizontalDirection()/2);
					}
					else//if it hits on right side of paddle
					{
					//ball.SetHorizontalDirection(fabs(ball.GetOriginalHorizontal()));
					ball.SetHorizontalDirection(fabs(ball.GetHorizontalDirection()));
					//ball.SetHorizontalDirection(ball.GetHorizontalDirection()+(ball.GetX() - posX)/100);
					//if(fabs(ball.GetX() - posX)<15)ball.SetHorizontalDirection(ball.GetHorizontalDirection()/2);
					}

				}
		    }
		}
		float GetWidth()
		{	
			return width;
		}
		float GetHeight()
		{	
			return height;
		}
		void SetHeight(float h)
		{	
			height = h;
		}
		void SetWidth(float w)
		{	
			width = w;
		}
		float GetY()
		{
			return posY;
		}
		float GetX()
		{
			return posX;
		}
		float SetY(float y)
		{
			posY = y;
		}
		float SetX(float x)
		{
			posX = x;
		}
		float GetSpeed()
		{
			return speed;
		}
		float SetSpeed(float s)
		{
			speed = s;
		}
};
