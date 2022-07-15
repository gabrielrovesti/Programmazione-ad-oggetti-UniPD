#include "ResultModule.h"

ResultModule::ResultModule(QWidget *parent, const QMultiMap<QString, QString> &results) : QWidget(parent), results(results) {
    layout = new QGridLayout(this);
    layout->setSpacing(10);
    layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);

    int i=0;
    for(auto it=results.begin(); it!=results.end(); it++, i++) {
        QLabel *text=new QLabel(it.key(), this);
        text->setFixedSize(150, 30);
        text->setWordWrap(true);

        QLabel *value=new QLabel(it.value(), this);
        value->setFixedWidth(300);
        value->setMinimumHeight(30);
        value->setAlignment(Qt::AlignRight);

        layout->addWidget(text, i, 0);
        layout->addWidget(value, i, 1);
    }
}
