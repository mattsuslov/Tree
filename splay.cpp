#include "splay.h"


Splay::Splay()
{

}


Splay*& get_p(Splay* & root, Splay* t) {
    if (t->par->par == nullptr) return root;
    if (t->par->par->left == t->par) return t->par->par->left;
    return t->par->par->right;
}


void Splay::splay_node(Splay* &root, Splay* t) {
    if (!t || !root) return;
    while (t != root) {
        if (t->par == root) {
            if (root->left == t) {
                rotright(root);
            } else {
                rotleft(root);
            }
        } else {
            if (t->par->par->left == t->par) {
                if (t->par->left == t) { // zigzig
                    rotright(get_p(root, t->par));
                    rotright(get_p(root, t));
                } else { //zigzag
                    rotleft(get_p(root, t));
                    rotright(get_p(root, t));
                }
            } else {
                if (t->par->right == t) { // zigzig
                    rotleft(get_p(root, t->par));
                    rotleft(get_p(root, t));
                } else { //zigzag
                    rotright(get_p(root, t));
                    rotleft(get_p(root, t));
                }
            }
        }
    }
}


Splay* Splay::find(Splay* t, int x) {
    if (t->key == x) return t;
    if (x <= t->key) {
        return find(t->left, x);
    } else {
        return find(t->right, x);
    }
}


void Splay::rotleft(Splay* &t) {
    if (!t) return;
    Splay* q = t->right;
    if (!q) return;
    q->par = t->par;
    t->par = q;
    t->right = q->left;
    if (q->left) q->left->par = t;
    q->left = t;
    t = q;
}


void Splay::rotright(Splay* &t) {
    if (!t) return;
    Splay* q = t->left;
    if (!q) return;
    q->par = t->par;
    t->par = q;
    t->left = q->right;
    if (q->right) q->right->par = t;
    q->right = t;
    t = q;
}


void Splay::insert(Splay* &root, int key) {
    if (!root) {
        root = new Splay;
        root->key = key;
        root->par = nullptr;
        return;
    }
    Splay* par = nullptr, *ptr = root;
    while (ptr != nullptr) {
        par = ptr;
        if (key <= ptr->key) {
            ptr = ptr->left;
        } else {
            ptr = ptr->right;
        }
    }

    Splay* t = new Splay;
    t->par = par;
    t->key = key;
    if (key <= par->key) {
        par->left = t;
    } else {
        par->right = t;
    }
    splay_node(root, t);
}


void Splay::draw(Splay* t, QGraphicsItemGroup* group, double shift) {
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


double Splay::recalc_coords(Splay* t, double width, double height) {
    if (!t) return 0;
    double left_size = recalc_coords(t->left, width, height + 100);
    t->x = width + left_size;
    t->y = height;
    return left_size + recalc_coords(t->right, width + left_size + 30, height + 100) + 30;
}


void Splay::remove(Splay* &root, int key) {
    Splay* t = find(root, key);
    if (t == nullptr) return;
    splay_node(root, t);
    t = root;
    root = merge(root->left, root->right);
    delete t;
}


Splay* Splay::merge(Splay* L, Splay* R) {
    if (L == nullptr) return R;
    if (R == nullptr) return L;
    Splay* Lmax = L;
    while (Lmax->right != nullptr) Lmax = Lmax->right;
    splay_node(L, Lmax);
    L->right = R;
    L->right->par = L;
    return L;
}


