#include <fstream>
using namespace std;

class Score
{
  private:
    int score;
    int top5Scores[5];
    bool arrayIsEmpty;

    public:
    Score()
    {
      score = 0;
      arrayIsEmpty = true;

      for (int i = 0; i < 5; i++)
        top5Scores[i] = 0;
    }
  
    // Reset the current score to 0.
    void resetScore() { score = 0; }

    // Set the current score to score + scoreValue.
    void setScore(int scoreValue) { score += scoreValue; }

    // Return the currentScore.
    int getScore() { return score; }

    // Record the top 5 scores in an array and output them to a file.
    void getHighScores()
    {
      // Define ifstream object and open file with top 5 scores.
      ifstream scoreInput("top5Scores.txt");
      
      // Read top 5 scores into the highScores array.
      for (int i = 0; i < 5; i++)
        scoreInput >> top5Scores[i];

      /* Retrieve the final score and compare it with the scores in the file array. 
       * Record the top 5 scores at the end of the comparison.*/
      for (int i = 0; i < 5; i++)
      {
        if( score > top5Scores[i] )
        { 
          for( int j = 4; j > i; j-- )
          {
            top5Scores[j] = top5Scores[j-1];
          }
          top5Scores[i] = score;
          break;
        }
      }
      
      // Define ofstream object and open file with top 5 scores.
      ofstream scoreOutput("top5Scores.txt");

      // Write the top 5 scores to the file.
      for (int i = 0; i < 5; i++)
        scoreOutput << top5Scores[i] << "\n";

      // Close the file.
      scoreInput.close();
      scoreOutput.close();
    }
};

