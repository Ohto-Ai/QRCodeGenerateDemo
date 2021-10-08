

#include "QREncoder.h"

int main(int argc, char** argv)
{
    if(argc == 2)
    {
        QREncoder::encode(argv[1]).print();
        return 0;
    }
    else if(argc == 4)
    {
        QREncoder::encode(argv[3]).print(argv[1], argv[2]);
        return 0;
    }
    printf("Unsupport %d args\n", argc);
    printf("usage: %s [<fore> <background>] <text>\n", argv[0]);
    return 0;
}
