/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include "boxdatareader.h"

BoxDataReader::BoxDataReader(QIODevice *device) :
    QTextStream(device)
{
}

void BoxDataReader::readFile(QIODevice *device)
{
    QTextStream::setDevice(device);
}

QBoxSet *BoxDataReader::readBox()
{
    //! [1]
    QString line = readLine();
    if (line.startsWith("#"))
        return 0;
    //! [1]

    //! [2]
    QStringList strList = line.split(" ", QString::SkipEmptyParts);
    //! [2]

    //! [3]
    sortedList.clear();
    for (int i = 1; i < strList.count(); i++)
        sortedList.append(strList.at(i).toDouble());

    qSort(sortedList.begin(), sortedList.end());
    //! [3]

    int count = sortedList.count();

    //! [4]
    QBoxSet *box = new QBoxSet(strList.first());
    box->setValue(QBoxSet::LowerExtreme, sortedList.first());
    box->setValue(QBoxSet::UpperExtreme, sortedList.last());
    box->setValue(QBoxSet::Median, findMedian(0, count));
    box->setValue(QBoxSet::LowerQuartile, findMedian(0, count / 2));
    box->setValue(QBoxSet::UpperQuartile, findMedian(count / 2 + (count % 2), count));
    //! [4]

    return box;
}

qreal BoxDataReader::findMedian(int begin, int end)
{
    //! [5]
    int count = end - begin;
    if (count % 2) {
        return sortedList.at(count / 2 + begin);
    } else {
        qreal right = sortedList.at(count / 2 + begin);
        qreal left = sortedList.at(count / 2 - 1 + begin);
        return (right + left) / 2.0;
    }
    //! [5]
}
