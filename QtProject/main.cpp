#include "mainwindow.h"
#include "structs_tools.h"
#include <glwidget.h>

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

int main(int argc, char *argv[])
{
    /*
    cmd cmd1(cmd::cmd_t::start, 3, 2, 1);
    cmd cmd2(cmd::cmd_t::dance, 90, 60, 90);
    cmd cmd3(cmd::cmd_t::sing, 90, 60, 90);
    cmd cmd4(cmd::cmd_t::stop, 3, 2, 1);


    // отправка
    QByteArray bytes;
    bytes.append(cmd1.to_bytes());
    bytes.append(cmd2.to_bytes());
    bytes.append(cmd3.to_bytes());
    bytes.append(cmd4.to_bytes());


    //Очереди
    QList<cmd> queue;

    // получение
    ///cmd cmds[4];
    ///int n_cmd = 0;
    int startpos = 0;
    int pos = 0;
    while(pos<bytes.size()){
        if(bytes[pos] == '\n'){
            bool ok;
            cmd c;
            c = cmd::fromBytes(bytes.sliced(startpos, pos-startpos+1), &ok); // новые байты не создаются, sliced - подуказатель.
            if(ok){
               ///cmds[n_cmd]=c;
               ///n_cmd++;
               queue.push_back(c);
               pos++;
               startpos=pos;
            } else{
                qDebug()<<"ОШИБКА";
            }
        }
        pos++;
    }

    // cmd a;
    // memcpy(a, bytes.constData(), sizeof(cmd));

    //cmd p = *reinterpret_cast<cmd*>(bytes.data()); // bytes - элемент очереди.
    */
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QSurfaceFormat format;
    format.setSamples(16);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    //GLWidget glWidget;
    //glWidget.show();

    return a.exec();
}
