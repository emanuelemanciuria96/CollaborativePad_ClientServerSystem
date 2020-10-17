//
// Created by Windows on 16/10/2020.
//

#ifndef CLIENT_CUSTOMSTYLE_H
#define CLIENT_CUSTOMSTYLE_H


#include <QtWidgets/QProxyStyle>

class CustomStyle : public QProxyStyle{
    Q_OBJECT
public:
    CustomStyle(){};

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                       QPainter *painter, const QWidget *widget) const override{
        /* do not draw focus rectangles - this permits modern styling */
        if (element == QStyle::PE_FrameFocusRect)
            return;

        QProxyStyle::drawPrimitive(element, option, painter, widget);
    };
};


#endif //CLIENT_CUSTOMSTYLE_H
