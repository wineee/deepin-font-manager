/*
 *
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:
*
* Maintainer:
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "fonticontext.h"

#include <DStyle>

DWIDGET_USE_NAMESPACE
using DTK_GUI_NAMESPACE::DSvgRenderer;

/*************************************************************************
 <Function>      FontIconText
 <Description>   构造函数-构造字体图标对象
 <Author>
 <Input>
    <param1>     picPath         Description:图像路径
    <param2>     parent          Description:父对象
 <Return>        FontIconText    Description:返回一个构造字体图标对象
 <Note>          null
*************************************************************************/
FontIconText::FontIconText(const QString &picPath, QWidget *parent)
    : QWidget(parent)
    , m_picPath(picPath)
    , render(new DSvgRenderer(this))
    , m_isTtf(false)
{
    render->load(picPath);
    QSize defaultSize = render->defaultSize();
    setFixedSize(defaultSize.width(), defaultSize.height());
}

/*************************************************************************
 <Function>      setFontName
 <Description>   设置字体名
 <Author>
 <Input>
    <param1>     familyName      Description:字体的familyName属性
    <param2>     styleName       Description:字体的styleName属性
 <Return>        null            Description:null
 <Note>          null
*************************************************************************/
void FontIconText::setFontName(const QString &familyName, const QString &styleName)
{
    m_font = font();
    m_font.setFamily(familyName);

    if (styleName.contains("Italic")) {
        m_font.setItalic(true);
    }

    if (styleName.contains("Regular")) {
        m_font.setWeight(QFont::Normal);
    } else if (styleName.contains("Bold")) {
        m_font.setWeight(QFont::Bold);
    } else if (styleName.contains("Light")) {
        m_font.setWeight(QFont::Light);
    } else if (styleName.contains("Thin")) {
        m_font.setWeight(QFont::Thin);
    } else if (styleName.contains("ExtraLight")) {
        m_font.setWeight(QFont::ExtraLight);
    } else if (styleName.contains("ExtraBold")) {
        m_font.setWeight(QFont::ExtraBold);
    } else if (styleName.contains("Medium")) {
        m_font.setWeight(QFont::Medium);
    } else if (styleName.contains("DemiBold")) {
        m_font.setWeight(QFont::DemiBold);
    } else if (styleName.contains("Black")) {
        m_font.setWeight(QFont::Black);
    }
}

/*************************************************************************
 <Function>      paintEvent
 <Description>   重写绘图事件
 <Author>        null
 <Input>
    <param1>     event           Description:事件对象
 <Return>        null            Description:null
 <Note>          null
*************************************************************************/
void FontIconText::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    //first draw image

    const auto ratio = devicePixelRatioF();
    QSize defaultSize = render->defaultSize() * ratio;
    QRect picRect = rect();
    QIcon m_fontIcon;
    if (m_isTtf == true) {
        //then draw text
        m_fontIcon = QIcon("/usr/share/icons/bloom/mimetypes/256/font-ttf.svg");// QIcon::fromTheme("deepin-font-manager");
    } else {
        m_fontIcon = QIcon("/usr/share/icons/bloom/mimetypes/256/font-x-generic.svg");// QIcon::fromTheme("deepin-font-manager");
    }
    QPixmap p = m_fontIcon.pixmap(defaultSize);
    painter.drawPixmap(picRect, p);

}

/*************************************************************************
 <Function>      setContent
 <Description>   设置是否为ttf字体属性
 <Author>
 <Input>
    <param1>     isTtf           Description:是否为ttf字体属性参数
 <Return>        null            Description:null
 <Note>          null
*************************************************************************/
void FontIconText::setContent(bool isTtf)
{
    m_isTtf = isTtf;
}
