#include "dialog.h"
#include "QApplication"

int main( int argc , char * argv[] )
{
    QApplication app( argc , argv );

    Dialog *test = new Dialog( 0 ,0 );

    test->show();

    return app.exec();

}
