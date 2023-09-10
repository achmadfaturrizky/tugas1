#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

// ANSI escape sequences for text color
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

void printHeader(const char *title)
{
    printf("\033[1;36m"); // Mengubah warna teks menjadi cyan
    printf("====================================\n");
    printf("   %s\n", title);
    printf("====================================\n");
    printf("\033[0m"); // Mengembalikan warna teks ke default
}

// Fungsi untuk format angka dengan pemisah ribuan
void formatWithThousandSeparator(char *buffer, double number)
{
    char temp[256];
    snprintf(temp, sizeof(temp), "%.0lf", number); // Mengonversi angka ke string tanpa desimal
    int length = strlen(temp);
    int commaCount = (length - 1) / 3;

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

int main()
{
    double totalPurchase, discount = 0.0, additionalDiscount = 0.0;
    int transactionCount = 0;
    int month = 0, year = 0;
    int prevMonth = 0, prevYear = 0;

    setlocale(LC_NUMERIC, "en_US.UTF-8"); // Set locale untuk pemisah ribuan (gunakan tanda .)

    while (true)
    {
        printf("===========================\n");
        printf("Program Kalkulator Diskon\n");
        printf("===========================\n");

        char formattedTotalPurchase[256];
        printf("Masukkan total belanja (Rp.): ");
        if (scanf("%s", formattedTotalPurchase) != 1)
        {
            printf(RED "Error: Masukkan angka yang valid.\n" RESET);
            while (getchar() != '\n')
                ; // Membersihkan buffer input
            continue;
        }

        // Menghilangkan pemisah ribuan (tanda .) dari input pengguna
        int len = strlen(formattedTotalPurchase);
        for (int i = 0; i < len; i++)
        {
            if (formattedTotalPurchase[i] == '.')
            {
                for (int j = i; j < len; j++)
                {
                    formattedTotalPurchase[j] = formattedTotalPurchase[j + 1];
                }
                len--;
                i--;
            }
        }

        // Mengonversi input yang telah diformat ke dalam bentuk angka
        if (sscanf(formattedTotalPurchase, "%lf", &totalPurchase) != 1 || totalPurchase < 0)
        {
            printf(RED "Error: Masukkan total belanja yang valid (angka positif).\n" RESET);
            continue;
        }

        printf("Masukkan bulan (1-12): ");
        if (scanf("%d", &month) != 1 || month < 1 || month > 12)
        {
            printf(RED "Error: Masukkan bulan yang valid (1-12).\n" RESET);
            while (getchar() != '\n')
                ; // Membersihkan buffer input
            continue;
        }

        printf("Masukkan tahun (YYYY): ");
        if (scanf("%d", &year) != 1 || year < 1000)
        {
            printf(RED "Error: Masukkan tahun yang valid (YYYY).\n" RESET);
            while (getchar() != '\n')
                ; // Membersihkan buffer input
            continue;
        }

        if (transactionCount == 0 || (month == prevMonth && year == prevYear))
        {
            switch ((int)totalPurchase)
            {
            case 0 ... 199999:
                discount = 0.0;
                break;
            case 200000 ... 549000:
                discount = 0.1;
                break;
            case 550000 ... 1000000:
                discount = 0.2;
                break;
            default:
                discount = 0.3;
                break;
            }
        }
        else
        {
            discount = 0.0;
            transactionCount = 0; // Reset jumlah transaksi jika bulan dan tahun berbeda
        }

        transactionCount++;

        if (transactionCount == 4)
        {
            additionalDiscount = 0.2; // Diskon tambahan 20% setelah 4 transaksi
            transactionCount = 0;     // Reset jumlah transaksi setelah mendapatkan diskon tambahan
        }
        else
        {
            additionalDiscount = 0.0; // Tidak ada diskon tambahan jika belum mencapai 4 transaksi
        }

        prevMonth = month;
        prevYear = year;

        double discountAmount = totalPurchase * discount;
        double additionalDiscountAmount = totalPurchase * additionalDiscount;
        double priceAfterDiscount = totalPurchase - discountAmount - additionalDiscountAmount;

        char formattedPrice[256];
        formatWithThousandSeparator(formattedPrice, priceAfterDiscount);

        // Menampilkan informasi diskon
        printf("\nDiskon: " GREEN "%.0lf%%" RESET "\n", discount * 100);
        printf("Diskon Tambahan: " GREEN "%.0lf%%" RESET "\n", additionalDiscount * 100);
        printf("Harga yang harus dibayar setelah diskon: " GREEN "Rp. %s\n" RESET, formattedPrice);

        char input[5];
        printf("\nIngin menginput lagi? (ya/tidak): ");
        scanf("%s", input);

        if (strcmp(input, "tidak") == 0)
        {
            break;
        }
    }

    // Menambahkan ASCII art
    printf("\n\n");
    printHeader("By:");
    printf("Achmad Fatur Rizky\n");
    printf("NIM: 2702372025\n");

    return 0;
}
