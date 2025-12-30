#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

// Константа Пи
#define PI 3.14159265358979323846

double f(double x);
double derivative(double x);
void tablica(double a, double b, int n);
void poisk_min_max(double a, double b, int n,
    double* min_x, double* min_y,
    double* max_x, double* max_y);
double poisk_x_po_y(double Y, double a, double b,
    double tochnost, double shag);

int main() {
    setlocale(LC_ALL, "RUS");

    printf("Программа анализа функции f(x)\n");
    printf("f(x) = {\n");
    printf("  tan(x),                   x < -?/6\n");
    printf("  (x? - 9)/(x + 3),        -?/6 ? x < 2\n");
    printf("  ?(x?/?(n?+1)), n=0..11,  x ? 2\n");
    printf("}\n");

    int vibor;

    do {
        printf("\n       ГЛАВНОЕ МЕНЮ     \n");
        printf("1. Значение функции в точке\n");
        printf("2. Таблица значений на интервале\n");
        printf("3. Минимум/максимум на отрезке\n");
        printf("4. Найти x по заданному Y\n");
        printf("5. Производная в точке\n");
        printf("0. Выход\n");
        printf("Выберите пункт (0-5): ");
        scanf("%d", &vibor);

        switch (vibor) {

        case 1: {
            double x;
            printf("x = ");
            scanf("%lf", &x);

            double result = f(x);

            if (result != result) {
                printf("f(%.3f) не вычисляется\n", x);
            }
            else {
                printf("f(%.3f) = %.6f\n", x, result);
            }
            break;
        }

        case 2: {
            double a, b;
            int n;

            printf("a = ");
            scanf("%lf", &a);
            printf("b = ");
            scanf("%lf", &b);
            printf("n = ");
            scanf("%d", &n);

            if (n <= 0) {
                printf("Ошибка: n > 0\n");
            }
            else {
                tablica(a, b, n);
            }
            break;
        }

        case 3: {
            double a, b;
            int n;
            double min_x, min_y, max_x, max_y;

            printf("a = ");
            scanf("%lf", &a);
            printf("b = ");
            scanf("%lf", &b);
            printf("n = ");
            scanf("%d", &n);

            if (n <= 0) {
                printf("Ошибка: n > 0\n");
            }
            else {
                poisk_min_max(a, b, n, &min_x, &min_y, &max_x, &max_y);

                printf("Минимум: f(%.4f) = %.6f\n", min_x, min_y);
                printf("Максимум: f(%.4f) = %.6f\n", max_x, max_y);
            }
            break;
        }

        case 4: {
            double Y, a, b, tochnost, shag;

            printf("Y = ");
            scanf("%lf", &Y);
            printf("a = ");
            scanf("%lf", &a);
            printf("b = ");
            scanf("%lf", &b);
            printf("tochnost = ");
            scanf("%lf", &tochnost);
            printf("shag = ");
            scanf("%lf", &shag);

            double result = poisk_x_po_y(Y, a, b, tochnost, shag);

            if (result != result) {
                printf("Решений не найдено\n");
            }
            break;
        }

        case 5: {
            double x;

            printf("x = ");
            scanf("%lf", &x);

            double proizv = derivative(x);

            if (proizv != proizv) {
                printf("Не могу вычислить производную\n");
            }
            else {
                printf("f'(%.3f) ? %.6f\n", x, proizv);
            }
            break;
        }

        case 0:
            printf("Выход из программы\n");
            break;

        default:
            printf("Ошибка! Введите число от 0 до 5\n");
            break;
        }

    } while (vibor != 0);

    return 0;
}

// ОСНОВНАЯ ФУНКЦИЯ f(x)
double f(double x) {
    double result;

    if (x < -PI / 6.0) {
        if (fabs(x) < 0.000001) {
            return 0.0 / 0.0;
        }
        if (fabs(cos(x)) < 0.000001) {
            return 0.0 / 0.0;
        }
        result = tan(x) / x;
    }
    else if (x >= -PI / 6.0 && x < 2.0) {
        if (fabs(x + 3.0) < 0.000001) {
            return 0.0 / 0.0;
        }
        result = (x * x - 9.0) / (x + 3.0);
    }
    else {
        result = 0.0;
        for (int n = 0; n <= 11; n++) {
            double chislitel = pow(x, n);
            double znamenatel = sqrt((pow(n, 3)) + 1.0);
            result += chislitel / znamenatel;
        }
    }

    return result;
}

// ПРОИЗВОДНАЯ (численный метод)
double derivative(double x) {
    double h = 0.000001;

    double f1 = f(x - h);
    double f2 = f(x + h);

    if (f1 != f1 || f2 != f2) {
        return 0.0 / 0.0;
    }

    return (f2 - f1) / (2.0 * h);
}

// ТАБЛИЦА ЗНАЧЕНИЙ
void tablica(double a, double b, int n) {
    printf("\n   ТАБЛИЦА ЗНАЧЕНИЙ   \n");
    printf("   x        f(x)\n");
    printf("-------------------\n");

    double shag = (b - a) / n;

    for (int i = 0; i <= n; i++) {
        double x = a + i * shag;
        double y = f(x);

        if (y != y) {
            printf("%8.3f   не вычисляется\n", x);
        }
        else {
            printf("%8.3f   %10.6f\n", x, y);
        }
    }
}

// ПОИСК МИНИМУМА И МАКСИМУМА
void poisk_min_max(double a, double b, int n,
    double* min_x, double* min_y,
    double* max_x, double* max_y) {
    double shag = (b - a) / n;

    *min_x = a;
    *max_x = a;
    *min_y = f(a);
    *max_y = f(a);

    if (*min_y != *min_y) {
        for (int i = 1; i <= n; i++) {
            double x = a + i * shag;
            double y = f(x);
            if (y == y) {
                *min_x = *max_x = x;
                *min_y = *max_y = y;
                break;
            }
        }
    }

    for (int i = 0; i <= n; i++) {
        double x = a + i * shag;
        double y = f(x);

        if (y == y) {
            if (y < *min_y) {
                *min_y = y;
                *min_x = x;
            }
            if (y > *max_y) {
                *max_y = y;
                *max_x = x;
            }
        }
    }
}
// ПОИСК X ПО ЗАДАННОМУ Y
double poisk_x_po_y(double Y, double a, double b,
    double tochnost, double shag) {
    printf("Ищем x: f(x) ? %.3f на [%.2f, %.2f]\n", Y, a, b);

    int naydeno = 0;
    double first_solution = 0.0 / 0.0;

    for (double x = a; x <= b; x += shag) {
        double fx = f(x);

        if (fx == fx) {
            if (fabs(fx - Y) < tochnost) {
                naydeno++;
                printf("Найдено: x ? %.4f, f(x) = %.6f\n", x, fx);
                if (naydeno == 1) {
                    first_solution = x;
                }
            }
        }
    }

    printf("Всего найдено решений: %d\n", naydeno);
    return first_solution;
}