#include <stdio.h>

/*
Nama : Surya Dharma
NIM  : 13220027
*/

/* Program belum selesai */

/*
int jumlah_isi_array(int arr[], N)
{
    int i, res = 0;
    for (i = 0; i < N; i ++)
        {
            res += arr[i];
        }
    return res;
}
*/

void main()
{
    int i, N, t_kuantum;
    printf("Jumlah proses : ");
    scanf("%d", &N);
    printf("Waktu kuantum : ");
    scanf("%d", &t_kuantum);

    int entry_time[N], dura[N];
    for (i = 0;i < N; i++){
        entry_time[i] = -1;
        dura[i] = -1;
    }
    for (i = 0;i < N; i++){
            printf("Entry time proses P%d :", i);
            scanf("%d", entry_time[0]);
            printf("Waktu eksekusi proses P%d :", i);
            scanf("%d", dura[0]);
        while (entry_time[i] < 0 || dura[i] < 0){
            printf("Entry time proses P%d :", i);
            scanf("%d", entry_time[0]);
            printf("Waktu eksekusi proses P%d :", i);
            scanf("%d", dura[0]);
        }
    }
}
