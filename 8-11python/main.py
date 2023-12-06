from random import randint #выбираем рандомное число
def radix_sort(mass): #поразрядная
    mas = [str(x) for x in mass]
    max_razr = max(x for x in [len(y) for y in mas])
    for i in range(max_razr):
        temp = [[] for _ in range(10)]
        for j in mas:
            temp[(int(j) // 10 ** i) % 10].append(j)
        mas = [cur for temp_temp in temp for cur in temp_temp]

    mas = [int(x) for x in mas]
    return mas
def radix_modif(mass):
    mas_otr = []
    mas_neotr = []
    for x in mass:
        if x >= 0:
            mas_neotr.append(str(x))
        else:
            mas_otr.append(str(x)[1:])
    mas_neotr = radix_sort(mas_neotr)
    if mas_otr != []:
        mas_otr = [x for x in radix_sort(mas_otr)[::-1]]
    mas = [int('-' + str(x)) for x in mas_otr] + mas_neotr
    return mas
##################################################
def heapswap(mas,i,cur_heap_size): #пирамидальная

    l = i*2+1
    r = l+1
    maxx = i

    if l < cur_heap_size and mas[i] < mas[l]: # существование правого левого элемента и поиск наибольшего в узле
        maxx = l
    if r < cur_heap_size and mas[maxx] < mas[r]:
        maxx = r

    if maxx != i:
        mas[i],mas[maxx] = mas[maxx], mas[i]
        heapswap(mas, maxx,  cur_heap_size)
def heap_sort(mas):
    cur_heap_size = len(mas)
    # первая куча
    for i in range(cur_heap_size, -1, -1):
        heapswap(mas,i, cur_heap_size)
    #оставшиеся кучи после того как мы отсеисаем отсортированные верхушки
    for i in range(cur_heap_size - 1, 0, -1):
        mas[i], mas[0] = mas[0], mas[i]
        heapswap(mas,0,i)
##########################################################
def merge_sort(mas):
    if (0 <= len(mas) <= 1):
        return mas
    left = merge_sort(mas[:len(mas)//2])
    right = merge_sort(mas[len(mas)//2:])
    l = r = 0
    out = []
    while l < len(left) and r < len(right):
        if left[l] <= right[r]:
            out.append(left[l])
            l += 1
        else:
            out.append(right[r])
            r += 1
    while l < len(left):
        out.append(left[l])
        l += 1
    while r < len(right):
        out.append(right[r])
        r += 1
    return out
########################################
def q_sort(mas):
    if len(mas) == 0:
        return mas
    t_rasb = mas.pop(randint(0, len(mas)-1))
    left = [x for x in mas if x < t_rasb]
    right = [x for x in mas if x >= t_rasb]
    return q_sort(left) + [t_rasb] + q_sort(right)
##############################


mas = [randint(-1000, 1000) for i in range(10)]
print(mas)

#mas_sorted = radix_modif(mas)
#mas_sorted = heap_sort(mas)
#mas_sorted = merge_sort(mas)
mas_sorted = q_sort(mas)

print(mas_sorted)
#print(mas)

