#ifndef RB_TREE_H
#define RB_TREE_H


#include <QGraphicsScene>
#include <queue>
#include <vector>
#include <QGraphicsTextItem>
#include <QGraphicsItemGroup>
#include <QGraphicsScene>

class RB_Tree
{
public:
    RB_Tree();

    static void insert(RB_Tree* &root, int key);
    static void draw(RB_Tree* t, QGraphicsItemGroup* group, double shift);
    static double recalc_coords(RB_Tree* t, double width, double height);
    static int find_height(RB_Tree* t);

    int key, color = 0;

    RB_Tree *left = nullptr, *right = nullptr, *par = nullptr;

    int x, y;


private:

    static int get_color(RB_Tree* t);

    static void rotleft(RB_Tree* &t);
    static void rotright(RB_Tree* &t);
    static void swap_color(RB_Tree* t);
    static void balance(RB_Tree* t, RB_Tree* &root);

};

#endif // RB_TREE_H
