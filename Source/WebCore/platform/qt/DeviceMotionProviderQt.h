/*
 * Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef DeviceMotionProviderQt_h
#define DeviceMotionProviderQt_h

#include "DeviceMotionData.h"
#include <QAccelerometerFilter>
#include <wtf/RefPtr.h>

#if !HAVE(QT5)
using QTM_NAMESPACE::QAccelerometer;
using QTM_NAMESPACE::QAccelerometerFilter;
using QTM_NAMESPACE::QAccelerometerReading;
#endif

namespace WebCore {

class DeviceMotionController;
class DeviceOrientationProviderQt;

class DeviceMotionProviderQt : public QAccelerometerFilter {
public:
    DeviceMotionProviderQt();
    virtual ~DeviceMotionProviderQt();

    void setController(DeviceMotionController*);

    bool filter(QAccelerometerReading*);

    void start();
    void stop();
    DeviceMotionData* currentDeviceMotion() const { return m_motion.get(); }

private:
    RefPtr<DeviceMotionData> m_motion;
    QAccelerometer m_acceleration;
    DeviceOrientationProviderQt* m_deviceOrientation;
    DeviceMotionController* m_controller;
};

} // namespace WebCore

#endif // DeviceMotionProviderQt_h
