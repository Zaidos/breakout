/* BREAKOUT: LIVES CLASS, COMPONENT D
 * Written by: Allison Escobar
 * CMPS 335: Software Engineering
 * Spring 2010
*/

// Lives class.
class Lives
{
    private:
  int lives;

    public:
  // Constructor.
  Lives() 
  { lives = 0;}

  // Sets the current number of lives to lives + numLives.
  // If numLives is negative, the number of lives decreases.
  void setLives( int numLives ) 
      { lives += numLives; }
  
  // Returns the current number of lives.
  int getLives() 
  { return lives; }

  // Resets the number of lives to 0.
  void resetLives()
  { lives = 0; }
};

