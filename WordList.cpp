#include "WordList.h"
#include <cmath>


WordList::WordList(std::istream& stream){

    std::string word;

    while (std::getline(stream, word)){

        bool valid = true;
        for (char c : word){

            if (c < 'a' || c > 'z'){

                valid = false;
                break;
            }

        }

        if (valid && (word.empty() == false)) {

            mWords.push_back(word);

        }

    }

}


Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {

    Heap heap(maxcount);

    size_t target_length = points.size();

    for (const std::string& word : mWords) {

        if (word.length() != target_length){

            continue;

        }

        float total_score = 0.0f;
        for (size_t i = 0; i < target_length; ++i){

            char c = word[i];
            const Point& key_point = QWERTY[c - 'a'];
            const Point& touch_point = points[i];

            float dx = key_point.x - touch_point.x;
            float dy = key_point.y - touch_point.y;

            float d2 = (dx * dx) + (dy * dy);

            float s = 1.0f / (10.0f * d2 + 1.0f);
            total_score += s;

        }

        float avg = total_score / target_length;

        if (avg < cutoff) {

            continue;

        }

        if (heap.count() < heap.capacity()){

            heap.push(word, avg);
        } else {

            if (avg > heap.top().score) {

                heap.pushpop(word, avg);

            }
        }

    }
    return heap;


}
