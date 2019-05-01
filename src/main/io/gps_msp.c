/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "platform.h"

#if defined(USE_GPS) && defined(USE_GPS_PROTO_MSP)

#include "build/build_config.h"
#include "build/debug.h"

#include "common/axis.h"
#include "common/gps_conversion.h"
#include "common/maths.h"
#include "common/utils.h"

#include "drivers/serial.h"
#include "drivers/time.h"

#include "fc/config.h"
#include "fc/runtime_config.h"

#include "sensors/sensors.h"

#include "io/gps.h"
#include "io/gps_private.h"

void gpsNewFrameMSP(void)
{

    //gpsSol.fixType = GPS_FIX_2D;
    gpsSol.fixType = GPS_FIX_3D;
    //gpsSol.fixType = GPS_NO_FIX;

    gpsSol.numSat = 6;

    gpsSol.llh.lon = -15349744;
    gpsSol.llh.lat = 509102311;
    gpsSol.llh.alt = 0;

    gpsSol.groundSpeed = 0;
    gpsSol.groundCourse = 0;

    gpsSol.velNED[X] = 0;
    gpsSol.velNED[Y] = 0;
    gpsSol.velNED[Z] = 0;

    gpsSol.flags.validVelNE = 1;
    gpsSol.flags.validVelD = 1;
    gpsSol.flags.validEPE = 1;
    gpsSol.flags.validTime = 1;

    gpsSol.hdop = 2;
    gpsSol.eph = 100;
    gpsSol.epv = 100;

    gpsSol.time.year = 2000;
    gpsSol.time.month = 1;
    gpsSol.time.day = 1;
    gpsSol.time.hours = 0;
    gpsSol.time.minutes = 0;
    gpsSol.time.seconds = 0;

}

void gpsRestartMSP(void)
{

}

void gpsHandleMSP(void)
{

    if (gpsDataMps.flags.hasNewData) {
        gpsSol.fixType = gpsDataMps.fixType;
        gpsSol.numSat = gpsDataMps.numSat;
        gpsSol.llh.lat = gpsDataMps.llh.lat;
        gpsSol.llh.lon = gpsDataMps.llh.lon;
        gpsSol.llh.alt = gpsDataMps.llh.alt;
        gpsSol.groundSpeed = gpsDataMps.groundSpeed;
        gpsSol.flags.hasNewData = false;
        gpsProcessNewSolutionData();
    }

}

#endif
