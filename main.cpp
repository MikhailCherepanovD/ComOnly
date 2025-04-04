#include <QCoreApplication>
#include "ScannerConnecter.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ScannerConnecter::ptr_t sc =   ScannerConnecter::get();
    return a.exec();
}
