#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printMonthCalendar(int year, int month) {
    const char *months[] = {
        "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь",
        "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"
    };
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Проверка високосного года
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29;
    }

    // Установка первого дня месяца
    struct tm firstDay = {0};
    firstDay.tm_mday = 1;
    firstDay.tm_mon = month - 1;
    firstDay.tm_year = year - 1900;
    mktime(&firstDay);

    printf("\n     %s %d\n", months[month - 1], year);
    printf(" Пн Вт Ср Чт Пт Сб Вс\n");

    // Печать начальных отступов
    int startDay = firstDay.tm_wday;
    if (startDay == 0) startDay = 7;
    for (int i = 1; i < startDay; i++) {
        printf("   ");
    }

    // Печать дней месяца
    for (int day = 1; day <= daysInMonth[month - 1]; day++) {
        printf("%3d", day);
        if ((startDay + day - 1) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

int main() {
    int year, month;

    printf("Добро пожаловать в MiNE календарь \n\n");
    printf("Год: ");
    scanf("%d", &year);
    printf("Месяц: ");
    scanf("%d", &month);

    if (month < 1 || month > 12) {
        printf("Ошибка: Неправильный номер месяца.\n");
        return 1;
    }

    printMonthCalendar(year, month);

    printf("\nGood day!\n");

    return 0;
}