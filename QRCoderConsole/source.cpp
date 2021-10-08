#include "QREncoder.h"

int main(int argc, char** argv)
{
    if(argc == 2)
    {
        QREncoder::encode(argv[1]).print();
    }
    else if(argc == 3)
    {
        QREncoder::ErrorCorrectionLevel level = QREncoder::LevelQ;
        if (*argv[2] == 'L')
            level = QREncoder::LevelL;
        else if (*argv[2] == 'M')
            level = QREncoder::LevelM;
        else if (*argv[2] == 'Q')
            level = QREncoder::LevelQ;
        else if (*argv[2] == 'H')
            level = QREncoder::LevelH;

        QREncoder::encode(argv[1], level).print();	    
    }
    else if(argc == 4)
    {
        QREncoder::encode(argv[3]).print(argv[1], argv[2]);
    }
    else if(argc == 5)
    {
        QREncoder::ErrorCorrectionLevel level = QREncoder::LevelQ;
        if (*argv[4] == 'L')
            level = QREncoder::LevelL;
        else if(*argv[4] == 'M')
            level = QREncoder::LevelM;
        else if (*argv[4] == 'Q')
            level = QREncoder::LevelQ;
        else if (*argv[4] == 'H')
            level = QREncoder::LevelH;

        QREncoder::encode(argv[3], level).print(argv[1], argv[2]);
    }
    else
    {
        printf("Unsupported %d args\n", argc);
        printf("usage: %s [<fore> <background>] <text> [Level(L|M|Q|H)]\n", argv[0]);
    }
    return 0;
}
