#include <stdio.h>
#include <stdlib.h>

/*
Nama : Surya Dharma
NIM  : 13220027
*/

/* Asumsi input program selalu bilangan bulat positif,
dan entry time suatu proses selalu lebih kecil dari total durasi semua proses */

typedef struct node
{
    int indeks_proses;
    int cur_time;
    struct node *next;
}Node;

typedef struct Queue
{
    Node *head;
}Queue;

// Prosedur menambahkan node baru ke queue
void enqueue(Queue *queue, int indeks, int waktu_sekarang)
{
    Node *newnode = malloc(sizeof(Node));
    newnode->indeks_proses = indeks;
    newnode->cur_time = waktu_sekarang;
    newnode->next = NULL;

    if(queue->head == NULL){
        queue->head = newnode;
    }
    else{
        Node *temp = queue->head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newnode;
    }
}

// Prosedur menghapus node pada queue
void dequeue(Queue *queue)
{
    if(queue->head != NULL){
        Node *temp = queue->head;
        queue->head = temp->next;
        free(temp);
    }
}

// Prosedur menampilkan isi queue
void printQueue(Queue *queue)
{
    Node *temp = queue->head;
    while(temp != NULL){
        printf("|P%d| ", temp->indeks_proses);
        temp = temp->next;
    }
    printf("\n");
}

// Prosedur circular shift ke kiri dari node-node pada queue
void circularShiftLeft(Queue *queue)
{
    int temp_indeks_proses = queue->head->indeks_proses;
    int temp_cur_time = queue->head->cur_time;
    dequeue(queue);
    enqueue(queue, temp_indeks_proses, temp_cur_time);
}

// Prosedur untuk membebaskan semua node setelah head
void subdestroy_list(Node* cur_node)
{
    if(cur_node != NULL){
        subdestroy_list(cur_node->next);
        free(cur_node);
    }
}

// Prosedur untuk membebaskan semua node selain head dan head itu sendiri
void destroy_list(Node **head)
{
    subdestroy_list(*head);
    *head = NULL;
}

// Prosedur sorting array arr_entry dan arr_dura dari kecil ke besar berdasarkan elemen arr_entry
void sort_arr(int arr_entry[], int arr_dura[], int dim)
{
    int temp_entry, temp_dura;
    for(int i = 0; i < dim; ++i){
        for(int j = 0; j < dim - 1; ++j){
            if(arr_entry[j] > arr_entry[j + 1]){
                temp_entry = arr_entry[j];
                arr_entry[j] = arr_entry[j + 1];
                arr_entry[j + 1] = temp_entry;

                temp_dura = arr_dura[j];
                arr_dura[j] = arr_dura[j + 1];
                arr_dura[j + 1] = temp_dura;
            }
        }
    }
}

int main()
{
    // Deklarasi variabel
    Queue *queue = malloc(sizeof(Queue));
    queue->head = NULL;
    int N, t_kuantum, i, total_time = 0, id_proses = 0;

    // Menerima input jumlah proses dan waktu kuantum
    printf("Jumlah proses : ");
    scanf("%d", &N);
    printf("Waktu kuantum : ");
    scanf("%d", &t_kuantum);

    // Deklarasi array untuk menampung entry time dan lama proses
    int entry_time[N], arr_waktu[N];

    // Menerima input entry time dan durasi setiap proses
    for(i = 0; i < N; ++i){
        printf("Entry time proses: ");
        scanf("%d", &entry_time[i]);
        printf("Lama proses : ");
        scanf("%d", &arr_waktu[i]);

        total_time += arr_waktu[i];
    }
    printf("\n");

    // Sorting proses berdasarkan entry time
    sort_arr(entry_time, arr_waktu, N);

    // Menampilkan proses beserta entry time dan durasinya
    printf("Proses\tEntry time\tDurasi\n");
    for(i = 0; i < N; ++i){
        printf("P%d\t%d\t\t%d\n", i, entry_time[i], arr_waktu[i]);
    }
    printf("\n");

    // Algoritma round robin
    for(i = 0; i < total_time; ++i){
        if(i != 0 && queue->head != NULL){
            // Increment
            queue->head->cur_time++;

            // Pengecekan apakah sudah sama dengan durasi proses
            if(queue->head->cur_time == arr_waktu[queue->head->indeks_proses]){
                dequeue(queue);
                if(entry_time[id_proses] != i){
                    printf("t = %d\t", i);
                    printQueue(queue);
                }
            }
            // Pengecekan apakah sama dengan waktu kuantum
            else if(queue->head->cur_time % t_kuantum == 0){
                circularShiftLeft(queue);
                if(entry_time[id_proses] != i){
                    printf("t = %d\t", i);
                    printQueue(queue);
                }
            }
        }

        // Entry
        if(id_proses < N){
            if(entry_time[id_proses] == i){
                enqueue(queue, id_proses, 0);
                id_proses++;

                printf("t = %d\t", i);
                printQueue(queue);
            }
        }

    }
    printf("t = %d", total_time);

    destroy_list(&(queue->head));
    free(queue);
    return 0;
}
