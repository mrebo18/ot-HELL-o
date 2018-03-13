//Sharne made a thing! Yay :>

Sharne created the heuristic. It is a sum of the pieces on the board after a move, with additional weight given to pieces in the corners or on the edges. She implemented the doMove function that was compatible with the heuristic, which was eventually replaced with minimax.

Malia implemented the initialization of the othello bot. She also created the minimax. The minimax algorithm allows the bot to look at the possible moves and look forward a certain depth to determine the best move. She added mobility to the heuristic (minimize the opponent's mobility).

To improve the AI, we implemented a heuristic and created minimax. We also added a mobility weight to our heuristic, by negatively weighting the number of moves the opponent can make. We tweaked with the numbers on the heuristic, and due to the heavy weight of certain moves, we multiplied the initial number of pieces on the board by 5. Also, alpha-beta pruning was attempted, although the result was invalid moves.