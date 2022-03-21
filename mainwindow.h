#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <treap.h>
#include <avl_tree.h>
#include <rb_tree.h>
#include <splay.h>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_zoomMinusBtn_clicked();

    void on_zoomPlusBtn_clicked();

    void on_SplayChsBtn_clicked();

    void on_TreapChsBtn_clicked();

    void on_AVLChsBtn_clicked();

    void on_RBChsBtn_clicked();

    void on_delBtn_clicked();

    void on_insBtn_clicked();

private:
    Ui::MainWindow *ui;
    double scale = 1;
    int mode = 3;
    QGraphicsScene* scene;
    QGraphicsItemGroup* group;
    Treap* treap = nullptr;
    AVL_Tree* avl = nullptr;
    RB_Tree* rb_tree = nullptr;
    Splay* splay = nullptr;


    void update_scene();

};
#endif // MAINWINDOW_H
