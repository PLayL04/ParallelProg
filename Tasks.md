# Задания

### Лабораторная работа №1
>Среди студентов СибФУ проведен опрос с целью определения процента студентов, знающих формулировку правила Буравчика. В результате собраны данные о количестве знатоков на каждом факультете по группам. Известно, что всего в СибФУ обучается 10000 студентов. Требуется создать многопоточное приложение для определения процента знающих правило Буравчика студентов. Потоки должны осуществлять поиск количества знатоков по факультету. Искомый процент определяет главный поток.

### Лабораторная работа №2
>Вычислить определенный интегралл по отрезку $[a,b]$, используя метод трапеций. Производить вычисление с некоторым шагом, интервал разделить между несколькими потоками. Входные данные: числа $a$ и $b$, функция $f(x)$ определяется с помощью программной функции.

### Лабораторная работа №3
>Выполнить предыдущую задачу. Записать в общую очередь промежуточные результаты вычислений потоков, с указанием идентификатора потока или индивидуального номера потока, присваиваемого потоку пользователем. Защитить операции с общей очередью посредством двоичного семафора. Вывести общую очередь, после завершения основных вычислений.

### Лабораторная работа №4
>Выполнить предыдущую задачу. К входным данным задачи добавляется целое положительное число К. Ограничить количество одновременно работающих над задачей потоков до К, с помощью семафоров (не двоичных).

### Лабораторная работа №5
>_Задача о тараканьих бегах._ Задано N участников тараканьих бегов. Каждый участник ведет статистику своих побед и поражений, а также является счастливым обладателем личного таракана, в свою очередь каждый таракан имеет личный показатель максимально-развиваемой им скорости. Поле для тараканьего забега состоит из М дорожек, следовательно, в одном тараканьем забеге может участвовать не более М выбранных из N тараканов. Участники, не попавшие в забег, тренируют своих тараканов, повышая их максимально-развиваемую скорость. Каждый таракан проходит гонку с некоторой скоростью, не превышающей их максимально-развиваемой скорости. По результатам каждого забега выделяются участники, занявшие 1, 2, 3 места и не занявшие призовых мест. Промоделировать К тараканьих забегов. N, М, К задаются пользователем.

### Лабораторная работа №6
>Выполнить предыдущую задачу, используя для защиты критических секций и синхронизации условные переменные.