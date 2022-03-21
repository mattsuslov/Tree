#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QGraphicsItemGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    group = new QGraphicsItemGroup;

    update_scene();
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_zoomMinusBtn_clicked()
{
    scale -= 0.1;
    group->setScale(scale);
    scene->update();
}

void MainWindow::on_zoomPlusBtn_clicked()
{
    scale += 0.1;
    group->setScale(scale);
    scene->update();
}


void MainWindow::update_scene() {
    scene->clear();
    group = new QGraphicsItemGroup;
    switch (mode) {
    case 0:
        AVL_Tree::draw(avl, group,  AVL_Tree::recalc_coords(avl, 0, 0) / 2);
        group->setScale(scale);
        scene->addItem(group);
        break;
    case 1:
        RB_Tree::draw(rb_tree, group, RB_Tree::recalc_coords(rb_tree, 0, 0) / 2);
        group->setScale(scale);
        scene->addItem(group);
        break;
    case 2:
        Splay::draw(splay, group,  Splay::recalc_coords(splay, 0, 0) / 2);
        group->setScale(scale);
        scene->addItem(group);
        break;
    case 3:
        Treap::draw(treap, group,  Treap::recalc_coords(treap, 0, 0) / 2);
        group->setScale(scale);
        scene->addItem(group);
        break;
    default:
        break;

    }
}


void MainWindow::on_SplayChsBtn_clicked()
{
    mode = 2;
    update_scene();
}


void MainWindow::on_TreapChsBtn_clicked()
{
    mode = 3;
    update_scene();
}


void MainWindow::on_AVLChsBtn_clicked()
{
    mode = 0;
    update_scene();
}


void MainWindow::on_RBChsBtn_clicked()
{
    mode = 1;
    update_scene();
}

void MainWindow::on_delBtn_clicked()
{
    int key = ui->key_to_del->text().toInt();
    switch (mode) {
    case 0:

        break;
    case 1:

        break;
    case 2:
        Splay::remove(splay, key);
        break;
    case 3:
        Treap::remove(treap, key);
        break;
    default:
        break;

    }

    update_scene();
}

void MainWindow::on_insBtn_clicked()
{
    int cnt = ui->cnt_to_ins->text().toInt();
    int lhs = ui->lhsSpin->text().toInt();
    int rhs = ui->rhsSpin->text().toInt();
    switch (mode) {
    case 0:
        for (int i = 0; i < cnt; ++i) {
            AVL_Tree::insert(avl, rand() % (rhs - lhs + 1) + lhs);
        }
        break;
    case 1:
        for (int i = 0; i < cnt; ++i) {
            RB_Tree::insert(rb_tree, rand() % (rhs - lhs + 1) + lhs);
        }
        break;
    case 2:
        for (int i = 0; i < cnt; ++i) {
            Splay::insert(splay, rand() % (rhs - lhs + 1) + lhs);
        }
        break;
    case 3:
        for (int i = 0; i < cnt; ++i) {
            Treap::insert(treap, rand() % (rhs - lhs + 1) + lhs);
        }
        break;
    default:
        break;

    }

    update_scene();
}
