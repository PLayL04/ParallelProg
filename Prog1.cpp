#include <iostream>
#include <vector>
#include <pthread.h>

const int TOTAL_STUDENTS = 10000;
int total_knowers = 0;

struct FacultyData {
    std::vector<int> groups;
    int knowers;
};

void* calculateKnowers(void* arg) {
    FacultyData* data = (FacultyData*)arg;
    data->knowers = 0;
    for (int knowers_in_group : data->groups) {
        data->knowers += knowers_in_group;
    }
    total_knowers += data->knowers;
    pthread_exit(NULL);
}

int main() {
    setlocale(LC_ALL, "Russiаn");
    
    std::vector<FacultyData> faculties = {
        { {10, 15, 20, 5}, 0 },
        { {25, 30, 10}, 0 },
        { {5, 10, 15, 20, 25}, 0 }
    };

    std::vector<pthread_t> threads(faculties.size());
    for (size_t i = 0; i < faculties.size(); ++i) {
        pthread_create(&threads[i], NULL, calculateKnowers, (void*)&faculties[i]);
    }

    for (size_t i = 0; i < threads.size(); ++i) {
        pthread_join(threads[i], NULL);
    }

    double percentage = (static_cast<double>(total_knowers) / TOTAL_STUDENTS) * 100.0;
    std::cout << "Общее количество знатоков правила Буравчика: " << total_knowers << std::endl;
    std::cout << "Процент знатоков: " << percentage << "%" << std::endl;

    return 0;
}