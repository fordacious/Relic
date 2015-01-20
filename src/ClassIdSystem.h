extern int id_count;

template <class T>
int getId() {
    static int id = id_count++;
    return id;
}