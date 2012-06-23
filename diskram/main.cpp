#include <fstream>
#include <iostream>
using namespace std;
fstream ramdisk;
void init__(void)
{
    ramdisk.open("./ramdisk", ios::binary | ios::in | ios::out | ios::trunc);
}
inline void _exit(int code)
{
    system("rm ./ramdisk");
    exit(code);
}
class drm
{
    int size, offset;
public:
    drm(int len)
    {
        size = len;
        ramdisk.seekp(0L, ios::end);
        offset = ramdisk.tellp();
        char *message = new char[len];
        for (int i = 0; i < len; i++)
            message[i] = '0';
        ramdisk.write(message, strlen(message));
    }
    void set(char * message)
    {
        ramdisk.seekp(offset, ios::beg);
        ramdisk.write(message, strlen(message));
    }
    void get(char message[])
    {
        ramdisk.seekg(offset, ios::beg);
        //cout << "Seek to 0x" << offset << endl;
        ramdisk.read(message, size);
        cout << message;
    }
    int getsize(void)
    {
        return size;
    }
};

int main()
{
    init__();
    char message[] = "hello world!";
    drm *d;
    d = new drm(strlen(message));
    d->set(message);
    char *message2 = new char[d->getsize()];
    d->get(message);
    drm *array[50];
    for (int i = 0; i < 50; i++)
        array[i] = new drm(20);
    cout << message2;
    _exit(EXIT_SUCCESS);
}