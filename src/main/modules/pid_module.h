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

#pragma once

typedef enum {
    PID_CONTROLLER_MW23 = 0,
    PID_CONTROLLER_MWREWRITE,
    PID_CONTROLLER_LUX_FLOAT,
    PID_COUNT
} pidControllerType_e;

#define GYRO_I_MAX 256                      // Gyro I limiter
#define YAW_P_LIMIT_MIN 100                 // Maximum value for yaw P limiter
#define YAW_P_LIMIT_MAX 500                 // Maximum value for yaw P limiter

typedef enum {
    PIDROLL,
    PIDPITCH,
    PIDYAW,
    PIDALT,
    PIDPOS,
    PIDPOSR,
    PIDNAVR,
    PIDLEVEL,
    PIDMAG,
    PIDVEL,
    PID_ITEM_COUNT
} pidIndex_e;

typedef struct pidProfile_s {
    uint8_t  P8[PID_ITEM_COUNT];
    uint8_t  I8[PID_ITEM_COUNT];
    uint8_t  D8[PID_ITEM_COUNT];
    uint8_t  pidController;
    uint16_t yaw_p_limit;                   // set P term limit (fixed value was 300)
    uint16_t dterm_lpf;                     // dterm filtering
    uint16_t yaw_lpf;                       // additional yaw filter when yaw axis too noisy
    uint8_t  deltaMethod;
} pidProfile_t;

PG_DECLARE_PROFILE(pidProfile_t, pidProfile);

// pid controller function prototype
typedef void (*pidControllerFuncPtr)(
        const pidProfile_t *pidProfile,
        const controlRateConfig_t *controlRateConfig,
        uint16_t max_angle_inclination,
        const rollAndPitchTrims_t *angleTrim,
        const uint16_t midrc);

typedef struct modulePidVTable_s {
    void (*setController)(pidControllerType_e type);
    void (*resetITerm)(void);
} modulePidVTable_t;

typedef struct modulePid_s {
    const modulePidVTable_t *vTable;

    // each pid controller module may support more than one PID algorithm
    pidControllerFuncPtr pid_controller;
} modulePid_t;

typedef struct modulePidCF_s {
    modulePid_t instance;
} modulePidCF_t;

extern modulePidCF_t modulePidCF;

modulePid_t *moduleInitPidCF(void);


void pidController(
        const pidProfile_t *pidProfile,
        const struct controlRateConfig_s *controlRateConfig,
        uint16_t max_angle_inclination,
        const rollAndPitchTrims_t *angleTrim,
        const uint16_t midrc
);
void pidSetController(pidControllerType_e type);
void pidResetITerm(void);

void module_pidSetInstance(modulePid_t *instance);

