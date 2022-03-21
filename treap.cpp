#include "treap.h"

Treap::Treap()
{
}

int Treap::get_height(Treap* t) {
    return (t ? t->h : 0);
}

void Treap::update() {
    this->h = std::max(get_height(this->right), get_height(this->left)) + 1;
}


void Treap::draw(Treap* t, QGraphicsItemGroup* group, double shift) {
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


void Treap::split(Treap* ver, int key, Treap* &L, Treap* &R) {
    if (ver == nullptr) {
        L = R = nullptr;
        return;
    }
    if (ver->key <= key) {
        split(ver->right, key, ver->right, R);
        L = ver;
    } else if (ver->key > key) {
        split(ver->left, key, L, ver->left);
        R = ver;
    }
    ver->update();
}


Treap* Treap::merge(Treap* L, Treap* R) {
    if (!L) return R;
    if (!R) return L;
    if (L->prior < R->prior) {
        L->right = merge(L->right, R);
        L->update();
        return L;
    } else {
        R->left = merge(L, R->left);
        R->update();
        return R;
    }
}


Treap* Treap::node(int key) {
    Treap* node = new Treap;
    node->key = key;
    node->prior = rand();
    return node;
}


double Treap::recalc_coords(Treap *t, double width, double height) {
    if (!t) return 0;
    double left_size = recalc_coords(t->left, width, height + 100);
    t->x = width + left_size;
    t->y = height;
    return left_size + recalc_coords(t->right, width + left_size + 30, height + 100) + 30;
}


void Treap::insert(Treap* &t, int key) {
    Treap *L, *R;
    split(t, key, L, R);
    t = merge(L, merge(node(key), R));
}

void Treap::remove(Treap* &root, int key) {
    Treap *C;
    Treap *L = nullptr, *R = nullptr;
    split(root, key, L, R);
    split(L, key-1, L, C);
    root = merge(L, R);
}


Treap* Treap::find(Treap* &t, int key) {
    if (!t) return nullptr;
    if (t->key == key) return t;

    if (key < t->key) return find(t->left, key);
    return find(t->right, key);
}


