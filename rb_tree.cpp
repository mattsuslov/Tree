#include "rb_tree.h"

RB_Tree::RB_Tree()
{

}

int RB_Tree::find_height(RB_Tree* t) {
    if (t == nullptr) return 0;
    return find_height(t->left) + 1;
}

int RB_Tree::get_color(RB_Tree* t) {
    return (t ? t->color : 1);
}

void RB_Tree::rotright(RB_Tree* &t) {
    if (!t) return;
    RB_Tree* q = t->left;
    if (!q) return;
    q->par = t->par;
    t->par = q;
    t->left = q->right;
    if (q->right) q->right->par = t;
    q->right = t;
    t = q;
}

void RB_Tree::rotleft(RB_Tree* &t) {
    if (!t) return;
    RB_Tree* q = t->right;
    if (!q) return;
    q->par = t->par;
    t->par = q;
    t->right = q->left;
    if (q->left) q->left->par = t;
    q->left = t;
    t = q;
}


void RB_Tree::swap_color(RB_Tree* t) {
    if (!t) return;
    if (t->left) t->left->color = 1;
    if (t->right) t->right->color = 1;
    t->color = 0;
}


void RB_Tree::balance(RB_Tree* t, RB_Tree*& root) {
    if (t == root) {
        root->color = 1;
        return;
    }
    while (get_color(t) == 0 && get_color(t->par) == 0) {
        RB_Tree *grandpa = t->par->par;
        RB_Tree *dad = t->par;
        if (grandpa->left == dad) {
            RB_Tree *uncle = grandpa->right;
            if (get_color(uncle) == 0) {
                swap_color(grandpa);
                t = grandpa;
            } else {
                if (dad->right == t) {
                    rotleft(grandpa->left);
                }
                grandpa->color = 0;
                grandpa->left->color = 1;
                if (grandpa == root) {
                    rotright(root);
                } else {
                    if (grandpa->par->left == grandpa) {
                        rotright(grandpa->par->left);
                    } else {
                        rotright(grandpa->par->right);
                    }
                }
                break;
            }
        } else {
            RB_Tree *uncle = grandpa->left;
            if (get_color(uncle) == 0) {
                swap_color(grandpa);
                t = grandpa;
            } else {
                if (dad->left == t) {
                    rotright(grandpa->right);
                }
                grandpa->color = 0;
                grandpa->right->color = 1;
                if (grandpa == root) {
                    rotleft(root);
                } else {
                    if (grandpa->par->left == grandpa) {
                        rotleft(grandpa->par->left);
                    } else {
                        rotleft(grandpa->par->right);
                    }
                }
                break;
            }
        }
    }
    root->color = 1;
}


void RB_Tree::insert(RB_Tree* &root, int key) {
    RB_Tree* t = new RB_Tree;
    t->key = key;
    t->color = 0;
    if (!root) {
        root = t;
        root->color = 1;
        return;
    }
    RB_Tree* ptr = root;
    RB_Tree* par = nullptr;
    while (ptr != nullptr) {
        par = ptr;
        if (key <= ptr->key) {
            ptr = ptr->left;
        } else {
            ptr = ptr->right;
        }
    }

    t->par = par;
    if (key <= par->key) {
        par->left = t;
    } else {
        par->right = t;
    }
    balance(t, root);
}


double RB_Tree::recalc_coords(RB_Tree *t, double width, double height) {
    if (!t) return 0;
    double left_size = recalc_coords(t->left, width, height + 100);
    t->x = width + left_size;
    t->y = height;
    return left_size + recalc_coords(t->right, width + left_size + 30, height + 100) + 30;
}

void RB_Tree::draw(RB_Tree* t, QGraphicsItemGroup* group, double shift) {
    if (t == nullptr || group == nullptr) return;
    if (t->left) {
        QGraphicsLineItem* line = new QGraphicsLineItem(t->x - shift, t->y, t->left->x - shift, t->left->y);
        line->setPen(QPen(Qt::green));
        group->addToGroup(line);
    }
    if (t->right) {
        QGraphicsLineItem* line = new QGraphicsLineItem(t->x - shift, t->y, t->right->x - shift, t->right->y);
        line->setPen(QPen(Qt::green));
        group->addToGroup(line);
    }
    QGraphicsEllipseItem* node = new QGraphicsEllipseItem(t->x - 15 - shift, t->y - 15, 30, 30);
    QGraphicsTextItem* text = new QGraphicsTextItem(QString::fromStdString(std::to_string(t->key)));
    text->setPos(t->x - 10 - shift, t->y - 10);
    node->setBrush((t->color ? QBrush(Qt::black) : QBrush(Qt::red)));
    group->addToGroup(node);
    group->addToGroup(text);

    draw(t->left, group, shift);
    draw(t->right, group, shift);
}

