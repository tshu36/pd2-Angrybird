#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>
#include <QCursor>
#include <iostream>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <block.h>
#include <flyingpig.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void creat_a_world();
    void restart();
    QPushButton *exit_but, *restart_but;
    QLabel *score;

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void reset();
    void end_the_game();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    int powerx=5, powery=3, firstx, firsty, lasty, lastx, clicko=0, pigs, birdplace, birdies, how_many=0, last_bird=4;
    bool launch[4], dead[2], birdstop[4], end, bird_exist[4], pig_exist[2], bird_spical[4],special_use[4];
    Bird *birdie[4];
    flyingpig *pig[2];
    int final_score;
    //block *test;
};

#endif // MAINWINDOW_H
