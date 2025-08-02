#ifndef LEFTLIST_H
#define LEFTLIST_H

#include <QWidget>
#include<QListWidgetItem>

namespace Ui {
class LeftList;
}

class LeftList : public QWidget
{
    Q_OBJECT

public:
    explicit LeftList(QWidget *parent = nullptr);
    ~LeftList();

private:

    void setListT1();

    void setListT2();

signals:
    void LeftListClicked_1(int cur,int index);
    void LeftListClicked_2(int cur,int index);
    void LeftListClicked_3(int cur,int index);
private:

    Ui::LeftList *ui;
};

#endif // LEFTLIST_H
