#include <iostream>
#include <pthread.h>
#include <semaphore.h>

const double a = -3.0;
const double b = 2.0;
const int n = 1000000;
const int num_threads = 10;
const int K = 4;

double integral_result = 0.0;
sem_t sem_thread_limit;
sem_t sem_result_mutex;

double f(double x) {
    return 3 * x * x + 1;
}

struct ThreadData {
    int thread_id;
    double local_a;
    double local_b;
    int local_n;
    double local_result;
};

void* compute_integral(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    double h = (data->local_b - data->local_a) / data->local_n;
    double sum = 0.0;

    for (int i = 1; i < data->local_n; i++) {
        double x = data->local_a + i * h;
        sum += f(x);
    }

    sum += (f(data->local_a) + f(data->local_b)) / 2.0;
    data->local_result = sum * h;

    sem_wait(&sem_result_mutex);
    integral_result += data->local_result;
    sem_post(&sem_result_mutex);

    sem_post(&sem_thread_limit);

    return nullptr;
}

int main() {
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    sem_init(&sem_thread_limit, 0, K);
    sem_init(&sem_result_mutex, 0, 1);

    double segment_length = (b - a) / num_threads;

    for (int i = 0; i < num_threads; i++) {
        sem_wait(&sem_thread_limit);

        thread_data[i].thread_id = i;
        thread_data[i].local_a = a + i * segment_length;
        thread_data[i].local_b = a + (i + 1) * segment_length;
        thread_data[i].local_n = n / num_threads;
        thread_data[i].local_result = 0.0;

        pthread_create(&threads[i], nullptr, compute_integral, &thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], nullptr);
    }

    sem_destroy(&sem_thread_limit);
    sem_destroy(&sem_result_mutex);

    std::cout << "Интеграл функции 3x^2 + 1 на отрезке [" << a << ", " << b << "] равен: " << integral_result << std::endl;

    return 0;
}