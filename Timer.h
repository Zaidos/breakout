/* BREAKOUT: TIMER CLASS, COMPONENT D
 * Written by: Allison Escobar
 * CMPS 335: Software Engineering
 * Spring 2010
*/

#include <ctime>
using namespace std;

class Timer
{
    private:
  double gameTimeElapsed;
  double roundTimeElapsed;
  time_t startRoundTime;
  time_t endRoundTime;

    public:
  // Constructor.
  Timer()
  {
      gameTimeElapsed = 0.0;
      roundTimeElapsed = 0.0;
  }

  /* Return the amount of time elapsed (seconds) since the beginning of 
   * the game.*/
  double getGameTimeElapsed()
  {
      gameTimeElapsed = (clock() / CLOCKS_PER_SEC);
      return gameTimeElapsed;
  }

  /* Return the amount of time elapsed (seconds) since the beginning of 
   * a round.*/
  double getRoundTimeElapsed()
  {
      /* THE NEXT 2 LINES SHOULD BE CALLED BY A TIMER CLASS OBJECT IN
       * THE MAIN PROGRAM AT THE BEGINNING AND END OF A ROUND.*/
      //time(&startRoundTimer);
      //time(&endRoundTimer);
      
      /* Sets roundTimeElapsed to the difference between the beginning
       * and end times of a round.*/
      roundTimeElapsed = difftime(endRoundTime, startRoundTime);
      
      return roundTimeElapsed;
  }

  /* Extend the round time by substracting secondsExtended from the
   * round time elapsed.*/
  void extendRoundTime(double secondsExtended)
  {
       roundTimeElapsed -= secondsExtended;
  }

  /* THE NEXT TWO FUNCTIONS WERE WRITTEN FOR C++ IMPLEMENTATION OF AND TESTING FOR THE TIMERS.
   * WHEN displayTimer IS CALLED FROM A TIMER CLASS OBJECT AND 60 IS PASSED AS A PARAMETER,
   * A TIMER DISPLAYS AND COUNTS DOWN TO 0.*/
  void timer()
  {
      clock_t clockTicks;
      clockTicks = clock() +  CLOCKS_PER_SEC;
      while (clock() < clockTicks) {}
  }
};
