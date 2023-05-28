#include <iostream>
#include <vector>

/*************************************************************/
std::vector<int> elevator_layers(std::string& src) {
    std::vector<int> layers;
    int layer, pos;
    
    do {
        pos = src.find(",");

        if (pos > 0) {
            layer = std::stoi(src.substr(0, pos));
            src = src.substr(pos + 1);
        } else {
            layer = std::stoi(src);
        }

        if (layer < 0) {
            layer += 1;
        }

        layers.push_back(layer);
    } while (pos > 0);

    return layers;
}

std::vector<int> elevator_moves(std::vector<int>& layers) {
    std::vector<int> moves;

    for (int idx = 1; idx < layers.size(); idx++) {
        moves.push_back(layers[idx] - layers[idx - 1]);
    }

    return moves;
}

float compute_cost(std::vector<int>& moves, float upcost, float downcost) {
    float cost = 0.0F;

    for (int move : moves) {
        if (move < 0) {
            cost -= move * downcost;
        } else {
            cost += move * upcost;
        }
    }

    return cost;
}

/*************************************************************/
int main(int argc, char* argv[]) {
    std::string src;

    std::getline(std::cin, src);
    std::vector<int> layers = elevator_layers(src);
    std::vector<int> moves = elevator_moves(layers);
    float cost = compute_cost(moves, 1.0F, 0.3F);

    printf("%.1f\n", cost);

    return 0;
}
