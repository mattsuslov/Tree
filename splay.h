#ifndef SPLAY_H
#define SPLAY_H


#include <QGraphicsScene>
#include <QGraphicsTextItem>


class Splay
{
public:
    Splay();

    static void insert(Splay* &root, int key);
    static void remove(Splay* &root, int key);
    static void draw(Splay* t, QGraphicsItemGroup* group, double shift);
    static double recalc_coords(Splay* t, double width, double height);

    int key;

    Splay *left = nullptr, *right = nullptr, *par = nullptr;

    int x, y;

private:
    static void splay_node(Splay* &root, Splay* t);
    static Splay* merge(Splay* L, Splay* R);
    static Splay* find(Splay* root, int x);

    static void rotleft(Splay* &t);
    static void rotright(Splay* &t);
};

#endif // SPLAY_H
