#ifndef TREAP_H
#define TREAP_H

#include <random>
#include <QGraphicsScene>
#include <QGraphicsTextItem>


class Treap
{
public:
    Treap();
    static void insert(Treap* &t, int key);
    static void remove(Treap* &t, int key);
    static Treap* find(Treap* &t, int key);
    static double recalc_coords(Treap *t, double width, double height);
    static void draw(Treap* t, QGraphicsItemGroup* group, double shift);

    int key;
    int prior;

    Treap *left = nullptr, *right = nullptr;

    double x, y;
    int h = 0;

private:
    static void split(Treap* ver, int key, Treap* &L, Treap* &R);
    static Treap* merge(Treap* L, Treap* R);
    static Treap* node(int key);
    static int get_height(Treap* t);



    void update();
};

#endif // TREAP_H
