#include <iostream>
#include <cstdio>
#include <cmath>

// Teste de commit

using namespace std;

void smfdate(int jdate, char* gdate) {
    static const int month_len[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int day_of_year = ((jdate >> 4) & 0x0000000F) +
                      ((jdate >> 8) & 0x0000000F) * 10 +
                      ((jdate >> 12) & 0x0000000F) * 100;
    int century = (jdate >> 24) * 100 + 1900;
    int year = century + ((jdate >> 16) & 0x0000000F) + (((jdate >> 20) & 0x0000000F) * 10);
    bool leap = ((year & 3) == 0 && ((year % 25) != 0 || (year & 15) == 0));
    int day_of_month = day_of_year;
    int month;
    for (month = 0; month < 12; month ++) {
        int mlen = month_len[month];
        if (leap && month == 1)
            mlen ++;
        if (day_of_month <= mlen)
            break;
        day_of_month -= mlen;
    }
    snprintf(gdate, 11, "%d-%02d-%02d", year, month + 1, day_of_month);
}

void smftime(int stime, char* ctime) {
    div_t dv1{}, dv2{}, dv3{};
    dv1 = div(stime, 360000);
    // int hours = dv1.quot;
    dv2 = div(dv1.rem, 6000);
    // int minutes = dv2.quot;
    dv3 = div(dv2.rem, 100);
    // int seconds = dv3.quot;
    // int hundreds = dv3.rem;
    // snprintf(ctime, 12, "%02d:%02d:%02d.%02d", hours, minutes, seconds, hundreds);
    snprintf(ctime, 12, "%02d:%02d:%02d.%02d", dv1.quot, dv2.quot, dv3.quot, dv3.rem);
}

int main() {
    int jdate = 0x0116060F;
    char gdate[11] = {0};
    smfdate(jdate, gdate);
    printf("%s\n", gdate);

    int stime = 0x005D7740;
    char ctime[12] = {0};
    smftime(stime, ctime);
    printf("%s\n", ctime);
}
