#include <iostream>
#include <random>

int det(int matrix[3][3]){
    return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
           matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
           matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}

bool simulateRand3x3Play(){
    int board[3][3] {};
    // a b c
    // d e f
    // g h i
    // det = a*(e*i-f*h) - b*(d*i-f*g) + c*(d*h - e*g)

    int pieceCount[2] {0, 0};
    int maxPieceCount[2] {4, 5};
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);


    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            int randInd = dis(gen);

            if(pieceCount[randInd] < maxPieceCount[randInd]){
                board[i][j] = randInd;
                pieceCount[randInd]++;
            }else{
                int newInd {!randInd};
                board[i][j] = newInd;
                pieceCount[newInd]++;
            }

        }
    }

    /*
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            std::cout << board[i][j] << ", ";
        }
        std::cout << "\n";
    }
    */

    bool outcome { det(board) == 1 };
    return outcome; // true for player 1 false for player 0
}

int main(){
    int playerOneWins {};
    int numOfRounds {1000000};

    std::cout << "simulating " << numOfRounds << " games.\n";
    for(int i = 0; i < numOfRounds; ++i){
        playerOneWins += simulateRand3x3Play();
    }

    float playerOneWinPerc {static_cast<float>(playerOneWins)/static_cast<float>(numOfRounds)};
    std::cout << "player1 won " << playerOneWins << " times. Which is " << playerOneWinPerc*100 << "% of the time\n";
    std::cout << "player0 won " << numOfRounds-playerOneWins << " times. Which is " << (1-playerOneWinPerc)*100 << "% of the time\n";
    return 0;
}
