#include <iostream>
#include <list>

/*************************************************************/
std::list<int> parse_scores(std::string& src) {
    std::list<int> scores;
    int s, pos;
    
    do {
        pos = src.find(",");

        if (pos > 0) {
            s = std::stoi(src.substr(0, pos));
            src = src.substr(pos + 1);
        } else {
            s = std::stoi(src);
        }

        scores.push_back(s);
    } while (pos > 0);

    return scores;
}

void remove_extreme_scores(std::list<int>& scores) {
    int min = 100;
    int max = 0;

    for (auto s : scores) {
        if (s < min) {
            min = s;
        } else if (s > max) {
            max = s;
        }
    }

    scores.remove(min);
    scores.remove(max);
}

void remove_extreme_scores_the_right_way(std::list<int>& scores) {
    std::list<int>::iterator min_pos, max_pos;
    int min = 101;
    int max = -1;

    for (auto it = scores.begin(); it != scores.end(); it++) {
        if ((*it) < min) {
            min = (*it);
            min_pos = it;
        } else if ((*it) > max) {
            max = (*it);
            max_pos = it;
        }
    }

    scores.erase(min_pos);
    scores.erase(max_pos);
}

float compute_average(std::list<int>& scores) {
    float total = 0.0F;

    for (int s : scores) {
        total += s;
    }

    return total / scores.size();
}

float compute_competition_average(std::list<int>& scores) {
    float total = 0.0F;
    int min = 100;
    int max = 0;

    for (int s : scores) {
        total += s;
        
        if (s < min) {
            min = s;
        } else if (s > max) {
            max = s;
        }
    }

    return (total - min - max) / (scores.size() - 2.0F);
}

/*************************************************************/
int main(int argc, char* argv[]) {
    std::string src;

    std::getline(std::cin, src);
    std::list<int> scores = parse_scores(src);
    remove_extreme_scores(scores);
    float avg = compute_average(scores);

    printf("%.2f\n", avg);

    return 0;
}
