/*
    Celestron driver

    Copyright (C) 2015 Jasem Mutlaq

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef CELESTRONDRIVER_H
#define CELESTRONDRIVER_H

#include <string>

typedef enum     { GPS_OFF, GPS_ON } CELESTRON_GPS_STATUS;
typedef enum     { SR_1, SR_2, SR_3, SR_4, SR_5, SR_6, SR_7, SR_8, SR_9} CELESTRON_SLEW_RATE;
typedef enum     { RA_AXIS, DEC_AXIS } CELESTRON_AXIS;
typedef enum     { CELESTRON_N, CELESTRON_S, CELESTRON_W, CELESTRON_E} CELESTRON_DIRECTION;
typedef enum     { FW_MODEL, FW_VERSION, FW_GPS, FW_RA, FW_DEC } CELESTRON_FIRMWARE;

typedef struct
{
    std::string Model;
    std::string Version;
    std::string GPSFirmware;
    std::string RAFirmware;
    std::string DEFirmware;
} FirmwareInfo;

/**************************************************************************
 Misc.
**************************************************************************/
void set_celestron_debug(bool enable);
void set_celestron_simulation(bool enable);
void set_celestron_device(const char *name);

/**************************************************************************
 Simulation
**************************************************************************/
void set_sim_gps_status(CELESTRON_GPS_STATUS value);
void set_sim_slew_rate(CELESTRON_SLEW_RATE value);
void set_sim_slewing(bool isSlewing);
void set_sim_ra(double ra);
void set_sim_dec(double dec);

/**************************************************************************
 Diagnostics
**************************************************************************/
bool check_celestron_connection(int fd);

/**************************************************************************
 Get Info
**************************************************************************/
/** Get All firmware information in addition to model and version */
bool get_celestron_firmware(int fd, FirmwareInfo *info);
/** Get version */
bool get_celestron_version(int fd, FirmwareInfo *info);
/** Get Mount model */
bool get_celestron_model(int fd, FirmwareInfo *info);
/** Get GPS Firmware version */
bool get_celestron_gps_firmware(int fd, FirmwareInfo *info);
/** Get RA Firmware version */
bool get_celestron_ra_firmware(int fd, FirmwareInfo *info);
/** Get DEC Firmware version */
bool get_celestron_dec_firmware(int fd, FirmwareInfo *info);
/** Get RA/DEC */
bool get_celestron_coords(int fd, double *ra, double *dec);
/** Get UTC/Date/Time */
bool get_celestron_utc_date_time(int fd, double *utc_hours, int *yy, int *mm, int *dd, int *hh, int *minute, int *ss);

/**************************************************************************
 Motion
**************************************************************************/
bool start_celestron_motion(int fd, CELESTRON_DIRECTION dir, CELESTRON_SLEW_RATE rate);
bool stop_celestron_motion(int fd, CELESTRON_DIRECTION dir);
bool abort_celestron(int fd);
bool slew_celestron(int fd, double ra, double dec);
bool sync_celestron(int fd, double ra, double dec);

/**************************************************************************
 Time & Location
**************************************************************************/
bool set_celestron_location(int fd, double longitude, double latitude);
bool set_celestron_datetime(int fd, struct ln_date *utc, double utc_offset);

/**************************************************************************
 Utility functions
**************************************************************************/
unsigned int get_ra_fraction(double ra);
unsigned int get_de_fraction(double de);
bool is_scope_slewing(int fd);

#endif