#ifndef DIALOG_H
#define DIALOG_H

#include "QDialog.h"
#include "ui_dialog.h"
#include "map"
#include "string"

struct Blosum62
{
    int score;
    int tag;
    int nowScore;
};

typedef struct InData
{
    QString seq;
    QString pos;
}indata;

class Dialog : public QDialog , public Ui::Dialog
{
    Q_OBJECT;
public:
    Dialog(QWidget *parent = 0   , Qt::WindowFlags f = 0 );

private slots:
    void on_loadFilterPushButton_clicked();
    void on_samplePushButton_clicked( int show = 1 );
    void on_transferPushButton_clicked( int show = 1 );
    void on_loadConfigPushButton_clicked();
    void on_clearConfigPushButton_clicked();
    void on_encodePushButton_clicked();
    void on_loadfilePushButton_clicked();
    void on_thousandPushButton_clicked();
    void on_findBestPushButton_clicked();
    void on_predictPushButton_clicked();

private:

    void attributeEncode();
    void one_hotEncode();
    void one_hotReplace(QString tmp , QStringList &final);
    void seventyfilter();
    int seventyfilter( QString tmp );
    int get_score_seqs(std::string str1 , std::string str2 );
//    int cmp( struct Blosum62 left , struct Blosum62 right );


private:
    QRegExp config;

    QSet< QString > humanFilteredLookUp;
    QStringList humanFiltered;

    QSet< QString > filterList;

    QSet< QString > positiveLookUp;
    QStringList positive;

    QStringList humanTrain;
    QSet< int > humanTrainLookUp;
    QStringList positiveTrain;
    int *positiveTrainLookUp;

    QStringList humanTest;
    QStringList positiveTest;

    QString encodeMethod;
    QStringList positiveTestEncode;
    QStringList positiveTrainEncode;
    QStringList humanTrainEncode;
    QStringList humanTestEncode;

    std::map< std::string, int> pair2score;
    bool init ;
    QStringList train;
    QStringList test;

    struct Blosum62 ** blosum62;

    struct Blosum62 *testBlosum62;
    QMultiMap< QString , indata > testData;

};


#endif // DIALOG_H
