#include "avl_tree.h"

AVL_Tree::AVL_Tree()
{

}


void AVL_Tree::update(AVL_Tree* t) {
    if (!t) return;
    t->h = std::max(height(t->left), height(t->right)) + 1;
}


int AVL_Tree::bfactor(AVL_Tree* t) {
    if (!t) return 0;
    update(t);
    return height(t->right) - height(t->left);
}



int AVL_Tree::height(AVL_Tree* t) {
    return (t ? t->h : 0);
}


void AVL_Tree::rotright(AVL_Tree* &t) {
    if (!t) return;
    AVL_Tree* q = t->left;
    if (!q) return;
    t->left = q->right;
    q->right = t;
    update(t);
    update(q);
    t = q;
}

void AVL_Tree::rotleft(AVL_Tree* &t) {
    if (!t) return;
    AVL_Tree* q = t->right;
    if (!q) return;
    t->right = q->left;
    q->left = t;
    update(t);
    update(q);
    t = q;
}


void AVL_Tree::balance(AVL_Tree* &t) {
    if (!t) return;
    update(t);
    if (bfactor(t) == -2) {
        if (bfactor(t->left) > 0) {
            rotleft(t->left);
        }
        rotright(t);
    } else if (bfactor(t) == 2) {
        if (bfactor(t->right) < 0) {
            rotright(t->right);
        }
        rotleft(t);
    }
}


void AVL_Tree::insert(AVL_Tree* &root, int key) {
    if (!root) {
        root = new AVL_Tree;
        root->key = key;
        update(root);
        return;
    }
    if (key <= root->key) {
        insert(root->left, key);
    } else {
        insert(root->right, key);
    }
    balance(root);
}


double AVL_Tree::recalc_coords(AVL_Tree *t, double width, double height) {
    if (!t) return 0;
    double left_size = recalc_coords(t->left, width, height + 100);
    t->x = width + left_size;
    t->y = height;
    return left_size + recalc_coords(t->right, width + left_size + 30, height + 100) + 30;
}

void AVL_Tree::draw(AVL_Tree* t, QGraphicsItemGroup* group, double shift) {
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
    node->setBrush(QBrush(Qt::red));
    group->addToGroup(node);
    group->addToGroup(text);

    draw(t->left, group, shift);
    draw(t->right, group, shift);
}
