/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
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

#include "SubtitleWriter.h"
#include "SettingsManager.h"
#include "VideoReceiver.h"
#include "VideoManager.h"
#include "QGCApplication.h"
#include "QGCCorePlugin.h"
#include <QDateTime>

QGC_LOGGING_CATEGORY(SubtitleWriterLog, "SubtitleWriterLog")


const char* _groupKey =         "ValuesWidget";
const char* _largeValuesKey =   "large";
const char* _smallValuesKey =   "small";

SubtitleWriter::SubtitleWriter(QObject* parent)
    : QObject(parent)
{
    _timer.setSingleShot(false);
    connect(qgcApp()->toolbox()->videoManager()->videoReceiver(), &VideoReceiver::recordedVideoStarted, this, &SubtitleWriter::_startCapturingState );
    connect(qgcApp()->toolbox()->videoManager()->videoReceiver(), &VideoReceiver::recordingChanged, this, &SubtitleWriter::_updateWritingState );
    connect(&_timer, &QTimer::timeout, this, &SubtitleWriter::_captureState);

    QSettings settings;
    settings.beginGroup(_groupKey);
    
    QStringList largeDefaults, smallDefaults;
    qgcApp()->toolbox()->corePlugin()->valuesWidgetDefaultSettings(largeDefaults, smallDefaults);
    
    _largeValues = settings.value(_largeValuesKey, largeDefaults).toStringList().replaceInStrings("Vehicle.", "");
    _smallValues = settings.value(_smallValuesKey, smallDefaults).toStringList().replaceInStrings("Vehicle.", "");




}

SubtitleWriter::~SubtitleWriter()
{

}

void SubtitleWriter::_updateWritingState() {
    if(!qgcApp()->toolbox()->videoManager()->videoReceiver()->recording()) {
        qCDebug(SubtitleWriterLog) << "Stopping writing";
        _timer.stop();
    }
}

void SubtitleWriter::_startCapturingState() {
        _timer.start(500);
        _startTime = QDateTime::currentDateTime();
}

void SubtitleWriter::_captureState() {


    auto *vehicle = qgcApp()->toolbox()->multiVehicleManager()->activeVehicle();
    if (vehicle) {
        for ( const auto& i : _largeValues  ) {   
            qCDebug(SubtitleWriterLog) << i << vehicle->getFact(i)->cookedValue();
        }
    }
}