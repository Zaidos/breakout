#include <time.h>

using namespace std;

class Ball
{
  private:
    float posX;
    float posY;
    float width;
    float height;
    float speed;
    float horizontalDirection;
    float verticalDirection;

  public:
    Ball(float x = 550, float y = 500, float s = 1.0f, float h = 5.0, float w = 5.0)
    {
      posX = x;
      posY = y;
      speed = s;
      height = 5.0;
      width = 5.0;
      srand((unsigned)time(0));
      int i = ((rand()%2)==0)? -1: 1;
      horizontalDirection = 0.25f*i;
      verticalDirection = -0.25f;
    }

    void ResetBall()
    {
        posX = 550;
        posY = 500;
        int i = ((rand()%2)==0)? -1: 1;
        horizontalDirection = 0.25f*i;
        verticalDirection = -0.25f;
        speed = 1.0f;
    }

    float GetWidth()
    {
      return width;
    }

    float GetHeight()
    {
      return height;
    }

    void SetWidth(float w)
    {
      width = w;
    }

    void SetHeight(float h)
    {
      height = h;
    }

    float GetX()
    {
      return posX;
    }
    float GetY()
    {
      return posY;
    }

    void SetX(float x)
    {
      posX = x;
    }
    void SetY(float y)
    {
      posY = y;
    }

    void SetSpeed(float s)
    {
      speed = s;
    }
    float GetSpeed()
    {
      return speed;
    }

    float GetHorizontalDirection()
    {
        return horizontalDirection;
    }
    float GetVerticalDirection()
    {
        return verticalDirection;
    }

    void SetHorizontalDirection(float h)
    {
        horizontalDirection = h;
    }
    void SetVerticalDirection(float v)
    {
        verticalDirection = v;
    }
    float GetOriginalHorizontal()
    {
        return 1.0f;
    }
    float GetOriginalVertical()
    {
        return 1.0f;
    }

};

