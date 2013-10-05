#include "QtGui"
#include "dialog.h"
#include "QDebug"
#include "iostream"
#include "QtAlgorithms"
#include "QtCore"

Dialog::Dialog( QWidget *parent , Qt::WindowFlags f )
    :QDialog( parent , f  )
{
    setupUi( this );

    init = 0;
}

void Dialog::on_loadFilterPushButton_clicked()
{
    filterList.clear();
    //extract the lines
    QStringList tmp = filterTextEdit->toPlainText().split( '\n' );
    QMessageBox::about( this ,  "FilterList loaded" ,
                        tr("<h1><center>Total Lines:</center></h1><p><h2><center>%1</center></h2>").arg( tmp.size() ) );
    //find the legal lines
    QStringList tmp2;
    for( int i = 0 ; i < tmp.size() ; ++i )
    {
        if( config.indexIn( tmp.at(i) , 0 ) != -1 )
        {
            if( config.captureCount() == 1 )
                tmp2.append( config.cap(0) );
            else
                tmp2.append( config.cap(2) );
        }
    }

    //duplicate remove
    for( int i = 0 ; i < tmp2.size() ; ++i )
    {
        if( !filterList.contains( tmp2.at(i) ) )
            filterList.insert( tmp2.at(i) );
    }

    QMessageBox::about( this ,  "FilterList loaded" , tr("<h1><center>Leagal String</center></h1><p><h2><center>%1</center></h2>").arg( tmp2.size() ) );
    qDebug() << tr( "filterList's size is : %1" ).arg( filterList.size() );

}

int Dialog::get_score_seqs( std::string str1 , std::string str2 )
{
    int score = 0;
    if(str1.size() != str2.size())
    {
        //cerr<<str1<<endl;
        //cerr<<str2<<endl;
        //cerr<<"Different length"<<endl;
        //PRINTFUNCTION("Different length!\n");
        return -1;
    }
    for(int i = 0; i < (int)str1.size(); i++)
    {
        char tmp[10];
        char chr1 = str1[i];
        char chr2 = str2[i];
        if(chr1 == 'U')
        {
            chr1 = '-';
        }
        if(chr2 == 'U')
        {
            chr2 = '-';
        }
        sprintf(tmp, "%c_%c", chr1, chr2);
        if(pair2score.count(tmp) == 0)
        {
            //cerr<<tmp<<endl;
            //cerr<<str1<<endl;
            //cerr<<str2<<endl;
            //cerr<<"Contains unrecognizable character"<<endl;
            //PRINTFUNCTION("Contains unrecognizable character\n");
            return -1;
        }
        score += pair2score[tmp];
    }
    return score;
}

int cmp( struct Blosum62 left , struct Blosum62 right )
{
    return left.score > right.score ? 1 : 0 ;
}
void Dialog::on_thousandPushButton_clicked()
{
    on_samplePushButton_clicked(0);
    on_encodePushButton_clicked();
    on_transferPushButton_clicked(0);
    if( encodeMethod == "one-hot" )
    {
        QRegExp filter ;
        filter.setPattern( "\\d*\\.\\d*" );
        QRegExp filter1;
        filter1.setPattern("(\\d*)(%)");
        QStringList cal;

        //generate A,B,C,D
        QFile operate( "output" );
        int A , B , C , D;
        int tmp;

        //output
        QFile outfile( "sumup" );
        if( !outfile.open( QIODevice::WriteOnly | QIODevice::Text) )
        {
            qDebug() << "sumup open error";
            return;
        }
        QTextStream out( &outfile );

        for( int i = 0 ; i < 1000 ; ++i )
        {
            on_samplePushButton_clicked(0);
            on_encodePushButton_clicked();
            on_transferPushButton_clicked(0);
            QProcess test;
            //system("D:\\libsvm-3.14\\tools\\easy.py train.encode test.encode" );
            //test.start( "D:\\libsvm-3.14\\windows\\svm-predict.exe test.encode.scale train.encode.model output");
            //test.waitForFinished();
            on_findBestPushButton_clicked();
            test.start( "C:\\Users\\lvqicong\\SVM\\libsvm-3.14\\windows\\svm-predict.exe test.encode.scale train.encode.model output" );
    //        test.start( "D:\\libsvm-3.14\\windows\\svm-predict.exe test.encode.scale train.encode.model output" );
            test.waitForFinished();
            QTextStream in( &test );
            QString buff = in.readAll();
    //        qDebug() << buff ;
            filter.indexIn( buff );
            QString buff1 = filter.cap( 0 );
            if( buff1.size() == 0 )
            {
                filter1.indexIn( buff );
                buff1 = filter1.cap( 1 );
            }
            cal.push_back( buff1 );
            //output rate
            out << buff1 << "\t" ;

            if( !operate.open( QIODevice::ReadOnly | QIODevice::Text) )
            {
                qDebug() << "test.encode.output open error";
                return;
            }
            QTextStream result( &operate );
            A = B = C = D = 0;
            for( int i = 0 ; i < positiveTest.size() ; ++i )
            {
                result >> tmp;
                //真的被分成真的
                if( tmp == 1 )
                    A++;
                else
                    B++;
            }
            for( int i = 0 ; i < humanTest.size() ; ++i )
            {
                result >> tmp;
                if( tmp == -1 )
                    D++;
                else
                    C++;
            }
            operate.close();

            //output A,B,C,D
            out << A << "\t" << B << "\t" << C << "\t" << D << endl;

            /*
            if( buff1.toDouble() < 35.0 )
                break;
            */
        }


        /*
        for( int i = 0 ; i < cal.size() ; ++i )
        {
            out << cal.at(i) << endl;
        }
        outfile.close();
        */
    }
    else if( encodeMethod == "attribute" )
    {
        double snAvg = 0;
        double spAvg = 0;
        double lowerBound = lowerDoubleSpinBox->value();
        double upperBound = upperDoubleSpinBox->value();

        QFile avgFile;
        avgFile.setFileName( "avg" );
        if( !avgFile.open( QIODevice::WriteOnly | QIODevice::Text ) )
        {
            qDebug() << "avgFile open error";
            return ;
        }
        QTextStream avg( &avgFile );

        int positive;
        int negative;
        int result;
        float sn;
        float sp;
        int A , B , C , D ;
        blosum62 = ( struct Blosum62 * )malloc( train.size() * sizeof( struct Blosum62 ) );

        for( double nowRate = lowerBound ; nowRate <= upperBound ; nowRate += 0.01 )
        {
            QFile outfile;
            outfile.setFileName( tr("sumup_%1").arg( nowRate ) );
            QFile recordFile;
            recordFile.setFileName( tr("record_%1").arg( nowRate ) );
            if( !recordFile.open( QIODevice::WriteOnly | QIODevice::Text) )
            {
                qDebug() << "record open error";
                return;
            }
            if( !outfile.open( QIODevice::WriteOnly | QIODevice::Text) )
            {
                qDebug() << "sumup open error";
                return;
            }
            QTextStream out( &outfile );
            QTextStream record( &recordFile );
            snAvg = spAvg = 0;
            for( int times = 0 ; times < 100 ; ++times )
            {
                on_samplePushButton_clicked(0);
                on_encodePushButton_clicked();
                on_transferPushButton_clicked(0);
                A = B = C = D = 0;
                for( int i = 0 ; i < test.size() ; ++i )
                {
                    for( int j = 0 ; j < train.size() ; ++j )
                    {
                        blosum62[j].score = get_score_seqs( test.at(i).toStdString() , train.at(j).toStdString() );
                        blosum62[j].tag = ( j < positiveTrain.size() ? 1 : 0 ) ;
                        if( blosum62[j].tag )
    //                        blosum62[j].score *= 1.1;
                            blosum62[j].score *= nowRate;
    //                    qDebug() << "blosum62[j].score : " << blosum62[j].score << " blosum62[j].tag : " << blosum62[j].tag;
                    }
                    qSort( blosum62 , blosum62 + train.size() , cmp );
                    for( int j = 0 ;j < train.size() ; ++j )
                    {
    //                    qDebug() << blosum62[j].score << blosum62[j].tag ;
                    }
                    positive = 0;
                    negative = 0;
                    for( int j = 0 ; j < 3 ; ++j )
                    {
                        record << "( " << blosum62[j].score << " , " << blosum62[j].tag << "),";
                        if( blosum62[j].tag == 1 )
    //                        positive +=  sample1SpinBox->value() / sample2SpinBox->value() + 2 ;
    //                        positive += 3;
                            positive ++;
                        else
                            negative ++;
                    }
    //                qDebug() << "positive : " << positive << " negative : " << negative ;
                    result = ( positive > negative ? 1 : 0 );
                    record << endl << result << ' ';
                    if( i < positiveTest.size() )
                    {
                        record << 1 << endl;
                    }
                    else
                    {
                        record << 0 << endl;
                    }

                    if( result == 1 )
                    {
                        if( i < positiveTest.size() )
                            A++;
                        else
                            C++;
                    }
                    else
                    {
                        if( i < positiveTest.size() )
                            B++;
                        else
                            D++;
                    }

                }
                sn = float(A)/( A + B );
                sp = float(D)/( C + D );
                snAvg += sn;
                spAvg += sp;
                out << sn << "\t" << sp << "\t" <<A << "\t" << B << "\t" << C << "\t" << D << "\n";
            }
            avg << snAvg << '\t' << spAvg << endl;
            outfile.close();
            recordFile.close();
        }
        avgFile.close();
        free(blosum62);
    }

}

void Dialog::on_samplePushButton_clicked( int show )
{
    humanTrain.clear();
    positiveTrain.clear();
    humanTest.clear();
    positiveTest.clear();
    if( positiveTrainLookUp != NULL )
        delete positiveTrainLookUp;
    humanTrainLookUp.clear();


    int positiveNum = sample2SpinBox->value();
    int humanNum = sample1SpinBox->value();
    qsrand( QTime::currentTime().msec() );
    int index;
    int i = 0;
    QFile file( "human.train" );

    //sample the humanFiltered
    if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qDebug() << "human.train open error!";
        return ;
    }
    QTextStream out1( &file );
    while( i < humanNum )
    {
        index = qrand() % humanFiltered.size() ;
        if( !humanTrainLookUp.contains( index ) )
        {
            humanTrain.append( humanFiltered.at( index ) );
            humanTrainLookUp.insert( index );
            ++i;
        }
    }
    for( i = 0 ; i < humanTrain.size() ; ++i )
    {
        out1 << humanTrain.at( i ) << endl;
    }
    file.close();
    if( show )
        QMessageBox::about( this ,  "humanTrain Sampled" , tr("<h1><center>HumanTrain Sampled :</center></h1><p><h2><center>%1</center></h2>").arg( humanTrain.size() ) );

    //sample the positive
    file.setFileName( "positive.train" );
    if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qDebug() << "positive.train open error!";
        return;
    }
    QTextStream out2( &file );
    QSet<int> marker;
    positiveTrainLookUp = new int[ positive.size() ];
    for( i = 0 ; i < positive.size() ; ++i )
    {
        positiveTrainLookUp[i] = 0;
    }
    i = 0;
    while( i < positiveNum )
    {
        index = qrand() % positive.size() ;
        if( !marker.contains( index ) )
        {
            positiveTrain.append( positive.at( index ) );
            marker.insert( index );
            positiveTrainLookUp[index] = 1;
            ++i;
        }
    }
    for( i = 0 ; i < positiveTrain.size() ; ++i )
    {
        out2 << positiveTrain.at( i ) << endl;
    }
    file.close();

    if( show )
        QMessageBox::about( this ,  "PositiveTrain Sampled" , tr("<h1><center>PositiveTrain Sampled :</center></h1><p><h2><center>%1</center></h2>").arg( positiveTrain.size() ) );


    //sample humantest
    file.setFileName( "human.test" );
    if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qDebug() << "human.test open error!";
        return ;
    }

    //
    int humanNum_tmp = humanNum;
//    humanNum = positive.size() - positiveTrain.size();
    humanNum = 100;
    //

    QTextStream out3( &file );
    i = 0;
    while( i < humanNum )
    {
        index = qrand() % humanFiltered.size() ;
        if( !humanTrainLookUp.contains( index ) && seventyfilter( humanFiltered.at(index) ) )
        {
            humanTest.append( humanFiltered.at( index ) );
            humanTrainLookUp.insert( index );
            ++i;
        }
    }
    for( i = 0 ; i < humanTest.size() ; ++i )
    {
        out3 << humanTest.at( i ) << endl;
    }
    file.close();
    if( show )
        QMessageBox::about( this ,  "HumanTest Sampled" , tr("<h1><center>HumanTest Sampled :</center></h1><p><h2><center>%1</center></h2>").arg( humanTest.size() ) );

    humanNum = humanNum_tmp;

    //generate positivetest
    file.setFileName( "positive.test" );
    if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qDebug() << "positive.test Open Erroe!";
        return;
    }
    QTextStream out4( &file );
    for( i = 0 ; i < positive.size() ; ++i )
    {
        if( positiveTrainLookUp[i] != 1 )
            positiveTest.append( positive.at( i ) );
    }
    for( i = 0 ; i < positiveTest.size() ; ++i )
    {
        out4 << positiveTest.at( i ) << endl;
    }
    file.close();
    if( show )
        QMessageBox::about( this ,  "PositiveTest Sampled" , tr("<h1><center>PositiveTest Sampled :</center></h1><p><h2><center>%1</center></h2>").arg( positiveTest.size() ) );

}

int Dialog::seventyfilter( QString tmp )
{
    int count = 0 ;
    int i , j ;
    for( i = 0 ; i < humanTrain.size() ; ++i)
    {
        //qDebug() << humanTrain.size();
        count = 0;
        for( j = 0 ; j < humanTrain.at(i).size() ; ++j )
        {
            if( tmp.at(j) == humanTrain.at(i).at(j) )
                count++;
            if( count >= humanTrain.size() * 0.7 )
            {
                //qDebug() << tmp << humanTrain.at(i);
                break;
            }
        }
        if( j < humanTrain.at(i).size() )
            break;
    }
    if( i < humanTrain.size() )
        return 0;
    return 1;
}

void Dialog::on_loadfilePushButton_clicked()
{
    humanFiltered.clear();
    humanFilteredLookUp.clear();
    positive.clear();
    positiveLookUp.clear();

    //read all human protein
    QString fileName = QFileDialog::getOpenFileName( this , tr("Open uniprot-human.fasta") , "./" , tr("fasta files( *.fasta )") );
    qDebug() << "uniprot-human.fasta's name is : " << fileName;
    QFile file( fileName );
    if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        qDebug() << "file1 open error !";
        return ;
    }

    QTextStream in( &file );
    QString buff,tmp ;
    QStringList splitTmp;


    buff.clear();
    while( !in.atEnd() )
    {
        tmp = in.readLine();
//        qDebug() << tmp;
        if( tmp.indexOf( '>' ) != -1 )
        {
//            qDebug() << buff ;
            int pos = 0 ;
            splitTmp.clear();
            while( ( pos = config.indexIn( buff , pos ) ) != -1 )
            {
                pos++;
                if( config.captureCount() == 1 )
                    splitTmp += config.cap(0);
                else
                    splitTmp += config.cap(2);
            }
            for( int i = 0 ; i < splitTmp.size() ; ++i )
            {
//                qDebug() << splitTmp.at(i) ;
                if( !filterList.contains( splitTmp.at(i) ) && !humanFilteredLookUp.contains( splitTmp.at(i) ) )
                {
                    humanFilteredLookUp.insert( splitTmp.at(i) );
                    humanFiltered.append( splitTmp.at(i) );
                }
            }
            buff.clear();
            continue;
        }
        buff += tmp;
    }
    //deal with the last buff
    int pos = 0 ;
    splitTmp.clear();
    while( ( pos = config.indexIn( buff , pos ) ) != -1 )
    {
        pos++;
        if( config.captureCount() == 1 )
            splitTmp += config.cap(0);
        else
            splitTmp += config.cap(2);
    }
    for( int i = 0 ; i < splitTmp.size() ; ++i )
    {
        if( !filterList.contains( splitTmp.at(i) ) && !humanFilteredLookUp.contains( splitTmp.at(i) ) )
        {
            humanFilteredLookUp.insert( splitTmp.at(i) );
            humanFiltered.append( splitTmp.at(i) );
        }
    }
    buff.clear();
    qDebug() << "humanFilteredLookUp's size is : " << humanFilteredLookUp.size() ;
    qDebug() << "humanFiltered's size is : " << humanFiltered.size() ;
    QMessageBox::about( this ,  "Human protein loaded" , tr("<h1><center>Leagal String</center></h1><p><h2><center>%1</center></h2>").arg( humanFiltered.size() ) );
    file.close();


    //output the filtered human protein
    file.setFileName( "humamFiltered.data" );
    if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qDebug() << "file2 open error !";
        return ;
    }
    QTextStream out1( &file );
    for( int i = 0 ; i < humanFiltered.size() ; ++i )
    {
        out1 << humanFiltered.at(i) << endl;
    }
    file.close();

    //read the positive ptp

    fileName = QFileDialog::getOpenFileName( this , tr("Open PTP positive") , "./" , tr("data files( *.* )") );
    qDebug() << "PTP positive's filename : " << fileName;
    file.setFileName( fileName );
    if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        qDebug() << "file3 open error !";
        return ;
    }
    QTextStream in1( &file );

    while( !in1.atEnd() )
    {
        tmp = in1.readLine();
        //为了避免Y偏移现象，需要对不同的模式设置不同的起始地址。
        if( config.indexIn( tmp , 0 ) != -1 )
        {
            if( config.captureCount() == 1 )
                buff = config.cap(0);
            else
                buff = config.cap(2);
        }
        if( !positiveLookUp.contains( buff ) )
        {
                positive.append( buff );
                positiveLookUp.insert( buff );
        }
    }
    qDebug() << "positiveLookUp's size is : " << positiveLookUp.size() ;
    qDebug() << "positive's size is : " << positive.size() ;
    seventyfilter();
    QMessageBox::about( this ,  "PTP positive loaded" , tr("<h1><center>Leagal String</center></h1><p><h2><center>%1</center></h2>").arg( positive.size() ) );

    file.close();
    file.setFileName( "positive.data" );
    if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qDebug() << "file4 open error!";
        return;
    }
    QTextStream out2( &file );
    for( int i = 0 ; i < positive.size() ; ++i )
    {
        out2 << positive.at(i) << endl;
    }
    file.close();
}

void Dialog::seventyfilter()
{
    QStringList tmp;
    int count , i , j , k;
    for( i = 0 ; i < positive.size() ; i++ )
    {
        for( j = 0 ; j < tmp.size() ; ++j )
        {
            count = 0 ;
            for( k = 0 ; k < tmp.at(j).size() ; ++k )
            {
                if( positive.at(i).at(k) == tmp.at(j).at(k) )
                    count ++;
                if( count >= ( tmp.at(j).size() * 0.7 ) )
                {
                    qDebug() << tmp.at(j) << "\t" << positive.at(i);
                    break;
                }
            }
            if( k < tmp.at(j).size() )
                break;
        }
        if( j == tmp.size() )
            tmp.push_back( positive.at(i) );
    }
    qDebug() << positive.size();
    positive.clear();
    positive = tmp;
    qDebug() << tmp.size();
    qDebug() << positive.size();
}

void Dialog::on_transferPushButton_clicked(int show)
{
    test.clear();
    train.clear();
    QFile file( "train.encode" );
    if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qDebug( "train.encode Open Error!");
        return;
    }
    QTextStream out1( &file );
    for( int i = 0 ; i < positiveTrainEncode.size() ; ++i )
    {
        out1 << "+1";

        train.push_back(positiveTrainEncode.at(i));

        for( int j = 0 ; j < positiveTrainEncode.at(i).size() ; ++j )
        {
            out1 << " " << j + 1 << ":" << positiveTrainEncode.at(i).at(j) ;
        }
        out1 << endl;
    }
    for( int i = 0 ; i < humanTrainEncode.size() ; ++i )
    {
        out1 << "-1";

        train.push_back( humanTrainEncode.at(i) );

        for( int j = 0 ; j < humanTrainEncode.at(i).size() ; ++j )
        {
            out1 << " " << j+1 << ":" << humanTrainEncode.at(i).at(j);
        }
        out1 << endl;
    }
    file.close();
    file.setFileName( "test.encode" );
    if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qDebug() << "test.encode Open Error!";
        return ;
    }
    QTextStream out2( &file );
    for( int i = 0 ; i < positiveTestEncode.size() ; ++i )
    {
        out2 << "+1";
        test.push_back( positiveTestEncode.at(i) );
        for( int j = 0 ; j < positiveTestEncode.at(i).size() ; ++j )
        {
            out2 << " " << j + 1 << ":" << positiveTestEncode.at(i).at(j) ;
        }
        out2 << endl;
    }
    for( int i = 0 ; i < humanTestEncode.size() ; ++i )
    {
        out2 << "-1";
        test.push_back( humanTestEncode.at(i) );
        for( int j = 0 ; j < humanTestEncode.at(i).size() ; ++j )
        {
            out2 << " " << j+1 << ":" << humanTestEncode.at(i).at(j);
        }
        out2 << endl;
    }
    file.close();
    if( show )
        QMessageBox::about( this ,  "Transfer Finish" , tr("<h1>Transfer Finish</h1><p>output as file \"train.encode\" and \"test.encode\"") );

}

void Dialog::on_clearConfigPushButton_clicked()
{
    regexpLineEdit->setText("");
}

void Dialog::on_findBestPushButton_clicked()
{
    float gBegin;
    float gEnd;
    float interval;
    gBegin = 0.05;
    gEnd = 1.01;
    interval = 0.01;
    float nBegin;
    float nEnd;
    nBegin = 0.01;
    nEnd = 1.01;
    QProcess train;
    QRegExp filter1 ;
    filter1.setPattern( "(\\d*\\.\\d*)(%)" );
    QRegExp filter2;
    filter2.setPattern("(\\d*)(%)");
    QString tmp;
    QString buff;

    float bestG = 0;
    float bestRate = 0;
    float bestN = 0;

//    system( "D:\\libsvm-3.14\\windows\\svm-scale.exe train.encode > train.encode.scale" );
//    system( "D:\\libsvm-3.14\\windows\\svm-scale.exe test.encode > test.encode.scale" );

    system( "C:\\Users\\lvqicong\\SVM\\libsvm-3.14\\windows\\svm-scale.exe train.encode > train.encode.scale" );
    system( "C:\\Users\\lvqicong\\SVM\\libsvm-3.14\\windows\\svm-scale.exe test.encode > test.encode.scale" );

    for( nBegin = 0.01 ; nBegin < nEnd ; nBegin += interval )
    {
        for( gBegin = 0.01 ; gBegin < gEnd ; gBegin += interval )
        {
//            train.start( tr("D:\\libsvm-3.14\\windows\\svm-train.exe -s 2 -g %1 -n %2 -v 5 train.encode.scale").arg( gBegin ).arg( nBegin ) , QIODevice::ReadOnly );
            train.start( tr("C:\\Users\\lvqicong\\SVM\\libsvm-3.14\\windows\\svm-train.exe -s 2 -g %1 -n %2 -v 5 train.encode.scale").arg( gBegin ).arg(nBegin) , QIODevice::ReadOnly );

            train.waitForFinished();
            QTextStream in( &train );
            tmp = in.readAll();
            qDebug() << tmp;
            filter1.indexIn( tmp );
            buff = filter1.cap( 1 );
            if( buff.size() == 0 )
            {
                filter2.indexIn( tmp );
                buff = filter2.cap( 1 );
            }
            if( buff.toFloat() > bestRate )
            {
                bestRate = buff.toFloat();
                bestG = gBegin;
                bestN = nBegin;
                qDebug() << "bestRage = " << bestRate << "bestG = " << bestG << "bestN = " << bestN;
            }
            qDebug() << "rate : " << buff << " g : " << gBegin << "n = " << nBegin ;
        }
    }
    //train.start( tr("D:\\libsvm-3.14\\windows\\svm-train.exe -s 2 -g %1 train.encode.scale train.encode.model").arg( bestG ).arg( bestN ) , QIODevice::ReadOnly );
    train.start( tr("C:\\Users\\lvqicong\\SVM\\libsvm-3.14\\windows\\svm-train.exe -s 2 -g %1 -n %2 train.encode.scale train.encode.model").arg( bestG ).arg( bestN ) , QIODevice::ReadOnly );
    train.waitForFinished();

}

void Dialog::on_loadConfigPushButton_clicked()
{
    config.setPattern( regexpLineEdit->text() );
    QMessageBox::about( this ,  "LoadPattern" , tr("<h1>RegExp\'s Pattern is:</h1><p>%1").arg(regexpLineEdit->text()) );
}

void Dialog::on_encodePushButton_clicked()
{
    positiveTestEncode.clear();
    positiveTrainEncode.clear();
    humanTestEncode.clear();
    humanTrainEncode.clear();
    encodeMethod = encodeComboBox->currentText();
    if( encodeMethod == "attribute" )
        attributeEncode();
    else if( encodeMethod == "one-hot" )
        one_hotEncode();
}
int scores[576] = {4, -1, -2, -2, 0, -1, -1, 0, -2, -1, -1, -1, -1, -2, -1, 1, 0, -3, -2, 0, -2, -1, 0, -4,
                   -1, 5, 0, -2, -3, 1, 0, -2, 0, -3, -2, 2, -1, -3, -2, -1, -1, -3, -2, -3, -1, 0, -1, -4,
                   -2, 0, 6, 1, -3, 0, 0, 0, 1, -3, -3, 0, -2, -3, -2, 1, 0, -4, -2, -3, 3, 0, -1, -4,
                   -2, -2, 1, 6, -3, 0, 2, -1, -1, -3, -4, -1, -3, -3, -1, 0, -1, -4, -3, -3, 4, 1, -1, -4,
                   0, -3, -3, -3, 9, -3, -4, -3, -3, -1, -1, -3, -1, -2, -3, -1, -1, -2, -2, -1, -3, -3, -2, -4,
                   -1, 1, 0, 0, -3, 5, 2, -2, 0, -3, -2, 1, 0, -3, -1, 0, -1, -2, -1, -2, 0, 3, -1, -4,
                   -1, 0, 0, 2, -4, 2, 5, -2, 0, -3, -3, 1, -2, -3, -1, 0, -1, -3, -2, -2, 1, 4, -1, -4,
                   0, -2, 0, -1, -3, -2, -2, 6, -2, -4, -4, -2, -3, -3, -2, 0, -2, -2, -3, -3, -1, -2, -1, -4,
                   -2, 0, 1, -1, -3, 0, 0, -2, 8, -3, -3, -1, -2, -1, -2, -1, -2, -2, 2, -3, 0, 0, -1, -4,
                   -1, -3, -3, -3, -1, -3, -3, -4, -3, 4, 2, -3, 1, 0, -3, -2, -1, -3, -1, 3, -3, -3, -1, -4,
                   -1, -2, -3, -4, -1, -2, -3, -4, -3, 2, 4, -2, 2, 0, -3, -2, -1, -2, -1, 1, -4, -3, -1, -4,
                   -1, 2, 0, -1, -3, 1, 1, -2, -1, -3, -2, 5, -1, -3, -1, 0, -1, -3, -2, -2, 0, 1, -1, -4,
                   -1, -1, -2, -3, -1, 0, -2, -3, -2, 1, 2, -1, 5, 0, -2, -1, -1, -1, -1, 1, -3, -1, -1, -4,
                   -2, -3, -3, -3, -2, -3, -3, -3, -1, 0, 0, -3, 0, 6, -4, -2, -2, 1, 3, -1, -3, -3, -1, -4,
                   -1, -2, -2, -1, -3, -1, -1, -2, -2, -3, -3, -1, -2, -4, 7, -1, -1, -4, -3, -2, -2, -1, -2, -4,
                   1, -1, 1, 0, -1, 0, 0, 0, -1, -2, -2, 0, -1, -2, -1, 4, 1, -3, -2, -2, 0, 0, 0, -4,
                   0, -1, 0, -1, -1, -1, -1, -2, -2, -1, -1, -1, -1, -2, -1, 1, 5, -2, -2, 0, -1, -1, 0, -4,
                   -3, -3, -4, -4, -2, -2, -3, -2, -2, -3, -2, -3, -1, 1, -4, -3, -2, 11, 2, -3, -4, -3, -2, -4,
                   -2, -2, -2, -3, -2, -1, -2, -3, 2, -1, -1, -2, -1, 3, -3, -2, -2, 2, 7, -1, -3, -2, -1, -4,
                   0, -3, -3, -3, -1, -2, -2, -3, -3, 3, 1, -2, 1, -1, -2, -2, 0, -3, -1, 4, -3, -2, -1, -4,
                   -2, -1, 3, 4, -3, 0, 1, -1, 0, -3, -4, 0, -3, -3, -2, 0, -1, -4, -3, -3, 4, 1, -1, -4,
                   -1, 0, 0, 1, -3, 3, 4, -2, 0, -3, -3, 1, -1, -3, -1, 0, -1, -3, -2, -2, 1, 4, -1, -4,
                   0, -1, -1, -1, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, 0, 0, -2, -1, -1, -1, -1, -1, -4,
                   -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, 1
                  };
char acids[24] = {'A', 'R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H', 'I', 'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V', 'B', 'Z', 'X', '-'};
void Dialog::attributeEncode()
{
    if( !init )
    {
        for(int i = 0; i < 25; i++)
        {
            for(int j = 0; j < 25; j++)
            {
                char tmp[10];
                sprintf(tmp, "%c_%c", acids[i], acids[j]);
                pair2score[tmp] = scores[i * 24 + j];
            }
        }
        init = 1;
    }
    positiveTestEncode = positiveTest;
    positiveTrainEncode = positiveTrain;
    humanTrainEncode = humanTrain;
    humanTestEncode = humanTest;
}

void Dialog::one_hotEncode()
{
    for( int i = 0 ; i < positiveTest.size() ; ++i )
    {
        one_hotReplace( positiveTest[i] , positiveTestEncode );
    }
    for( int i = 0 ; i < positiveTrain.size() ; ++i )
    {
        one_hotReplace( positiveTrain[i] , positiveTrainEncode );
    }
    for( int i = 0 ; i < humanTest.size() ; ++i )
    {
        one_hotReplace( humanTest[i] , humanTestEncode );
    }
    for( int i = 0 ; i < humanTrain.size() ; ++i )
    {
        one_hotReplace( humanTrain[i] , humanTrainEncode );
    }

}

void Dialog::one_hotReplace(QString tmp , QStringList &final )
{
    QString out;
    for( int i = 0 ; i < tmp.size() ; ++i )
    {
        if( tmp.at(i)==  'A' )
            out.append( "00000000000000000001");
        else if( tmp.at(i) == 'C' )
            out.append( "00000000000000000010");
        else if( tmp.at(i) == 'D' )
            out.append( "00000000000000000100");
        else if( tmp.at(i) == 'E' )
            out.append( "00000000000000001000");
        else if( tmp.at(i) == 'F' )
            out.append( "00000000000000010000");
        else if( tmp.at(i) == 'H' )
            out.append( "00000000000000100000");
        else if( tmp.at(i) == 'I' )
            out.append( "00000000000001000000");
        else if( tmp.at(i) == 'G' )
            out.append( "00000000000010000000");
        else if( tmp.at(i) == 'K' )
            out.append( "00000000000100000000");
        else if( tmp.at(i) == 'L' )
            out.append( "00000000001000000000");
        else if( tmp.at(i) == 'M' )
            out.append( "00000000010000000000");
        else if( tmp.at(i) == 'N' )
            out.append( "00000000100000000000");
        else if( tmp.at(i) == 'P' )
            out.append( "00000001000000000000");
        else if( tmp.at(i) == 'Q' )
            out.append( "00000010000000000000");
        else if( tmp.at(i) == 'R' )
            out.append( "00000100000000000000");
        else if( tmp.at(i) == 'S' )
            out.append( "00001000000000000000");
        else if( tmp.at(i) == 'T' )
            out.append( "00010000000000000000");
        else if( tmp.at(i) == 'V' )
            out.append( "00100000000000000000");
        else if( tmp.at(i) == 'W' )
            out.append( "01000000000000000000");
        else if( tmp.at(i) == 'Y' )
            out.append( "10000000000000000000");
    }
    final.append( out );
}
