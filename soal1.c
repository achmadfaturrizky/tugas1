#include <stdio.h>
#include <locale.h>
#include <string.h>

// Fungsi untuk format angka dengan pemisah ribuan
void formatWithThousandSeparator(char *buffer, double number)
{
    char temp[256];
    snprintf(temp, sizeof(temp), "%.0lf", number); // Mengonversi angka ke string tanpa desimal
    int length = strlen(temp);

    int newIndex = 0;
    for (int i = 0; i < length; i++)
    {
        if (i > 0 && (length - i) % 3 == 0)
        {
            buffer[newIndex++] = '.';
        }
        buffer[newIndex++] = temp[i];
    }
    buffer[newIndex] = '\0';
}

void printHeader(const char *title)
{
    printf("\033[1;36m"); // Mengubah warna teks menjadi cyan
    printf("====================================\n");
    printf("   %s\n", title);
    printf("====================================\n");
    printf("\033[0m"); // Mengembalikan warna teks ke default
}

void printError(const char *message)
{
    printf("\033[1;31m"); // Mengubah warna teks menjadi merah
    printf("Error: %s\n", message);
    printf("\033[0m"); // Mengembalikan warna teks ke default
}

void printResult(double km, double m, double cm)
{
    char formattedKm[256], formattedM[256], formattedCm[256];
    formatWithThousandSeparator(formattedKm, km);
    formatWithThousandSeparator(formattedM, m);
    formatWithThousandSeparator(formattedCm, cm);

    printf("\033[1;32m"); // Mengubah warna teks menjadi hijau
    printf("Hasil konversi:\n");
    printf("Kilometer: %s Km\n", formattedKm);
    printf("Meter: %s M\n", formattedM);
    printf("Sentimeter: %s Cm\n", formattedCm);
    printf("\033[0m"); // Mengembalikan warna teks ke default
}

int main()
{
    double distanceKm;

    while (1)
    {
        printHeader("Konversi Jarak Kilometer");

        printf("Masukkan jarak dalam kilometer (0 untuk keluar): ");
        if (scanf("%lf", &distanceKm) == 1)
        {
            if (distanceKm == 0)
            {
                break; // Keluar dari loop jika input 0
            }
            else if (distanceKm < 0)
            {
                printError("Masukkan nilai yang valid (harus lebih dari atau sama dengan 0).");
            }
            else
            {
                // Mengonversi kilometer ke meter dan sentimeter
                double distanceM = distanceKm * 1000; // 1 km = 1000 m
                double distanceCm = distanceM * 100;  // 1 m = 100 cm

                // Menampilkan hasil konversi
                printResult(distanceKm, distanceM, distanceCm);
            }
        }
        else
        {
            // Menampilkan pesan kesalahan jika input bukan angka
            printError("Masukkan angka yang valid.");
        }

        // Membersihkan buffer stdin
        while (getchar() != '\n')
            ;
    }

    // Menambahkan ASCII art
    printf("\n\n");
    printHeader("By:");
    printf("Achmad Fatur Rizky\n");
    printf("NIM: 2702372025\n");

    return 0;
}
