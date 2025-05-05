#include <iostream>
#include <pthread.h>

const double a = -3.0;
const double b = 2.0;
const int n = 1000000;
const int num_threads = 8;

double integral_result = 0.0;
pthread_mutex_t mutex;

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

    pthread_mutex_lock(&mutex);
    integral_result += data->local_result;
    pthread_mutex_unlock(&mutex);

    return nullptr;
}

int main() {
    setlocale(LC_ALL, "Russian");

    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    pthread_mutex_init(&mutex, nullptr);

    double segment_length = (b - a) / num_threads;

    for (int i = 0; i < num_threads; i++) {
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

    pthread_mutex_destroy(&mutex);

    std::cout << "Интеграл функции 3x^2 + 1 на отрезке [" << a << ", " << b << "] равен: " << integral_result << std::endl;

    return 0;
}