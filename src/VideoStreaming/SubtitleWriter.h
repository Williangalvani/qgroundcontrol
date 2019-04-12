/****************************************************************************
 *
 *   (c) 2009-2018 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


/**
 * @file
 *   @brief QGC Video Receiver
 *   @author Gus Grubba <mavlink@grubba.com>
 */

#pragma once

#include "QGCLoggingCategory.h"
#include <QObject>
#include <QTimer>


Q_DECLARE_LOGGING_CATEGORY(SubtitleWriterLog)

class SubtitleWriter : public QObject
{
    Q_OBJECT
public:

    explicit SubtitleWriter(QObject* parent = nullptr);
    ~SubtitleWriter();

public slots:
    void _updateWritingState();

protected slots:

    void _captureState();
    void _startCapturingState();

protected:
    QTimer _timer;
    QStringList _largeValues;
    QStringList _smallValues;
    QDateTime startTime;
};