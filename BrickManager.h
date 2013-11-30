/*Edgar Buenrostro*/
#include <iostream>
//#include "Score.h"
using namespace std;


class BrickManager
{
    private:
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        class Brick
        {
            public:
                float width;
        float height;
        float posX;
        float posY;
        float color[3];/*rgb array*/
                Brick *next;
                Brick ():next(0){}
                Brick (float c[], float x, float y, float w, float h, Brick *link=NULL): 
            width(70.0f), height(30.0f), posX(x), posY(y), next(link)
          {
          for(int i = 0; i<3; i++)
          color[i] = c[i];
        }
        float* GetColor(){ return color; }
                bool brickCollision(Ball &ball, bool &collided, bool &corner,bool &flat, float original[])
                {
          /*ret is a boolean meant to communicate with the BrickManager that this
           * brick has been struck. If so, the manager will delete it from the heap.
           * collided is a similar boolean, but it is meant to prevent duplicate trajectory
           * reversals. Meaning if our square ball hits two bricks at once, it'll delete both
           * of them, but only do a trajectory reversal once. Otherwise it'll go through the
           * bricks
           * Also, corners...:( */
        bool ret = false;
        int numcollisions = 0;
                        //bottom of brick w/ top of ball.
                        if((ball.GetY()  - ball.GetHeight() == posY + height)
                                &&(ball.GetX() + ball.GetWidth() >= (posX))
                                    && (ball.GetX() - ball.GetWidth() <= (posX + width)))
                                    {
          if(!collided)
                                        ball.SetVerticalDirection(ball.GetVerticalDirection() *-1);
          else if(corner)
          {
              ball.SetVerticalDirection(original[1]*-1);
              ball.SetHorizontalDirection(original[0]);
          }

                                        ret = true;
          numcollisions++;
                                    }
                        //top of brick w/ bottom of ball
                        if(((ball.GetY() + ball.GetHeight()) == posY)
                                &&(ball.GetX() + ball.GetWidth() >= (posX))
                                    && (ball.GetX() - ball.GetWidth() <= (posX + width)))
                                    {
          if(!collided)
                                        ball.SetVerticalDirection(ball.GetVerticalDirection() *-1);
          else if(corner)
          {
              ball.SetVerticalDirection(original[1]*-1);
              ball.SetHorizontalDirection(original[0]);
          }
                                        ret = true;
          numcollisions++;
                                    }
                        //left of ball with right of brick
                        if((ball.GetX() - ball.GetWidth() == posX + width)
                                &&((ball.GetY() + ball.GetHeight()) >= (posY))
                                    && (ball.GetY() - ball.GetHeight() <= (posY + height)))
                                    {
          if(!collided)
                                        ball.SetHorizontalDirection(ball.GetHorizontalDirection() *-1);
          else if(corner)
          {
              ball.SetHorizontalDirection(original[0]*-1);
              ball.SetVerticalDirection(original[1]);
          }
                                        ret = true;
          numcollisions++;
                                    }
                        //right of ball left of brick
                        if((ball.GetX() + ball.GetWidth() == posX)
                                &&((ball.GetY() + ball.GetHeight()) >= (posY))
                                    && (ball.GetY() - ball.GetHeight() <= (posY + height)))
                                    {
          if(!collided)
                                        ball.SetHorizontalDirection(ball.GetHorizontalDirection() *-1);
          else if(corner)
          {
              ball.SetHorizontalDirection(original[0]*-1);
              ball.SetVerticalDirection(original[1]);
          }
                                        ret = true;
          numcollisions++;
                                    }

      corner = (numcollisions == 2)? true:false;
      if(corner&&!flat)
      {
          if(ball.GetY() - ball.GetHeight() == posY + height)
          {
        //Bottom
        if(ball.GetX() - ball.GetWidth() == posX + width)
        {
            //Right
            ball.SetHorizontalDirection(fabs(ball.GetHorizontalDirection()));
            ball.SetVerticalDirection(fabs(ball.GetVerticalDirection()));
        }
        else if(ball.GetX() + ball.GetWidth() == posX)
        {
            //Left
            ball.SetHorizontalDirection(fabs(ball.GetHorizontalDirection())*-1);
            ball.SetVerticalDirection(fabs(ball.GetVerticalDirection()));
        }
          }
          else if(ball.GetY() + ball.GetHeight() == posY)
          {
        //Top
        if(ball.GetX() - ball.GetWidth() == posX + width)
        {
            //Right
            ball.SetHorizontalDirection(fabs(ball.GetHorizontalDirection()));
            ball.SetVerticalDirection(fabs(ball.GetVerticalDirection())*-1);
        }
        else if(ball.GetX() + ball.GetWidth() == posX)
        {
            //left
            ball.SetHorizontalDirection(fabs(ball.GetHorizontalDirection())*-1);
            ball.SetVerticalDirection(fabs(ball.GetVerticalDirection())*-1);
        }
          }
      }
      flat = (!corner)? true:false;
          

      return ret;
                }

        };
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        typedef Brick* BrickPointer;
  float posX;
  float posY;
  float BrickWidth;
  float BrickHeight;
  int level;
        BrickPointer myTop;
    public:
        BrickManager()
  { 
      /*These coordinates correspond to the start of our brick grid,
       * so we know where to start our brick creation*/
      posX = 190;//230; //Use 100 for corner testing
      posY = 120;//Use 150 for corner testing
      BrickWidth = 70;//Use 70 for corner testing
      BrickHeight = 30;//Use 30 for corner testing
      level = 0;
      myTop = NULL;
  }
  
      /*In the future this might take parameters to indicate WHICH level
       * is desired and the list will be created with the appropriate brick
       * attributes to match the desired level design*/
  void InitializeLevel()
  {
  //    level++;
            float x;
            float y=posY;
      float lightblue[3] = {0.0, 0.5, 0.5};
      float darkblue[3] = {0.1, 0.0, 0.5};

      if(myTop != NULL){ myTop = NULL; }

            for(int j = 0; j< 2;j++)
            {
                float x=posX;
                for(int i = 0; i < 11; i++)
                {
        if((j+i)%2==0)
        myTop=new Brick(lightblue,x+i*BrickWidth,y+j*BrickHeight,BrickWidth,BrickHeight,myTop);
        else
        myTop=new Brick(darkblue,x+i*BrickWidth,y+j*BrickHeight,BrickWidth,BrickHeight,myTop);
                }
            }

  }

  /*Traverse through the linked list and deletes them brick objects that 
   * have been struck. This will create weird checkerboard patterns*/
  void CheckCollisions(Ball &ball, Score &score)
  {
      bool collided = false;
      bool corner = false;
      bool flat = false;
      BrickPointer temp, ptr=myTop;
      if(myTop == NULL)
      {
      ball.ResetBall();
      InitializeLevel();
      }
      float original[2] = {ball.GetHorizontalDirection(), ball.GetVerticalDirection()};
      while(ptr!=NULL && !collided)
      {
      if(ptr->brickCollision(ball,collided,corner,flat,original))
      {
        score.setScore(1);
        collided = true;//prevents duplicate trajectory reversals.
        if(ptr == myTop) 
        { 
          myTop = ptr->next;
          break; 
        }
        else
        {
          temp->next = ptr->next;
          temp = ptr;
          ptr=ptr->next;
          delete temp;
        }
      }
      else
      {
        temp = ptr;
        ptr = ptr->next;
      }
      }
  }

  /*I'll have to take this draw out of this class to keep it portable. 
   * We might have to make a component that is simply in charge of drawing
   * and we can transfer it there at that time.*/
  void Draw()
  {
      BrickPointer ptr = myTop;
      int i=0;
      while(ptr!=NULL)
      {
    /*
                    if(i%2==0)glColor3f(0.0f,0.5f,0.5f); 
        else
      glColor3f(0.1f,0.0f,0.5f);//for checkerboard I'll change this.
      */
        glColor3f(ptr->GetColor()[0],ptr->GetColor()[1],ptr->GetColor()[2]);
                    glVertex2f(ptr->posX, ptr->posY);//top left
                    glVertex2f(ptr->posX + ptr->width, ptr->posY);//top right
                    glVertex2f(ptr->posX + ptr->width, ptr->posY + ptr->height);//bottom right
                    glVertex2f(ptr->posX, ptr->posY + ptr->height);//bottom left
        ptr=ptr->next;
       i++; 
      }
  }
};


