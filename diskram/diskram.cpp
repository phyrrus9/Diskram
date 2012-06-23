#include <fstream>
using namespace std;
namespace diskram
{
    fstream ramdisk;
    void init__(void)
    {
        ramdisk.open("./.ramdisk", ios::binary | ios::in | ios::out | ios::trunc);
    }
    inline void ramexit(int code)
    {
        system("rm ./.ramdisk");
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
                message[i] = '\251';
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
            for (int i = 0; i < size; i++)
            {
                if (message[i] == '\251') //ensure that nothing gets read that shouldnt be there
                                          //by that I mean empty (unused) data that would just be
                                          //the character /251 or ©
                    message[i] = '\0';    //change it into the null terminator (for cout and stuff)
            }
        }
        int getsize(void)
        {
            return size;
        }
    };
}