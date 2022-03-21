#ifndef AVL_TREE_H
#define AVL_TREE_H


#include <algorithm>
#include <vector>
#include <queue>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

class AVL_Tree
{
public:
    AVL_Tree();

    static void insert(AVL_Tree* &root, int key);
    static void draw(AVL_Tree* t, QGraphicsItemGroup* group, double shift);
    static double recalc_coords(AVL_Tree* t, double width, double height);

    int key;
    int h;

    AVL_Tree *left = nullptr, *right = nullptr;


    int x, y;

private:

    static int height(AVL_Tree* t);
    static int bfactor(AVL_Tree* t);
    static void update(AVL_Tree* t);

    static void rotleft(AVL_Tree* &t);
    static void rotright(AVL_Tree* &t);
    static void balance(AVL_Tree* &t);
};

#endif // AVL_TREE_H
