def result_shiftLeft(arr):
    temp = [0 for i in range(len(arr))]
    for i in range(len(arr) - 1):
        temp[i] = arr[i + 1]
    temp[-1] = arr[0]
    return temp

def jumlah_isi_array(arr):
    res = 0
    for i in range(len(arr)):
        res += arr[i]
    return res

N = int(input("Jumlah proses : "))
t_lim = int(input("Waktu kuantum : "))
entry_time = [-1 for i in range(N)]
dura = [-1 for j in range(N)]
for i in range(N):
    while entry_time[i] < 0 or dura[i] < 0:
        entry_time[i] = int(input("Entry time proses P%d : " %i))
        dura[i] = int(input("Durasi proses P%d : " %i))

total_waktu = jumlah_isi_array(dura)
arr_pro = ["P%d" % i for i in range(N)]
pro_prog = [0 for i in range(N)]
temp_dura = []
temp_arr_pro = []
temp_pro_prog = []
temp_entry_time = []
indeks = 0

for i in range(total_waktu):
    if indeks == 1:
        temp_pro_prog[0] = i
    elif indeks > 0:
        temp_pro_prog[0] += 1

    if entry_time[indeks] == i:
        temp_dura.append(dura[indeks])
        temp_entry_time.append(entry_time[indeks])
        temp_arr_pro.append(arr_pro[indeks])
        temp_pro_prog.append(pro_prog[indeks])
        if indeks + 1 != N:
            indeks += 1
        else:
            indeks = 2

        print("t = %d" % i, end=" ")
        for j in range(len(temp_pro_prog)):
            if temp_pro_prog[j] < temp_dura[j] and i >= temp_entry_time[j]:
                print("|%s|" % temp_arr_pro[j], end="")
        print()

    elif temp_pro_prog[0] % t_lim == 0 and temp_pro_prog[0] > 0:
        temp_arr_pro = result_shiftLeft(temp_arr_pro)
        temp_pro_prog = result_shiftLeft(temp_pro_prog)
        temp_dura = result_shiftLeft(temp_dura)
        temp_entry_time = result_shiftLeft(temp_entry_time)
        print("t = %d" % i, end=" ")
        for j in range(len(temp_pro_prog)):
            if temp_pro_prog[j] < temp_dura[j] and i >= temp_entry_time[j]:
                print("|%s|" % temp_arr_pro[j], end="")
        print()
    elif temp_pro_prog[0] == temp_dura[0]:
        temp_arr_pro.pop(0)
        temp_pro_prog.pop(0)
        temp_dura.pop(0)
        temp_entry_time.pop(0)

        print("t = %d" % i, end=" ")
        for j in range(len(temp_pro_prog)):
            if temp_pro_prog[j] < temp_dura[j] and i >= temp_entry_time[j]:
                print("|%s|" % temp_arr_pro[j], end="")
        print()

print("t = %d" % total_waktu)