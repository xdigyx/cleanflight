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
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <platform.h>
#include "build/debug.h"

#include "common/axis.h"


// FIXME shouldn't need PG's for this
#include "config/parameter_group.h"
#include "config/parameter_group_ids.h"

#include "fc/rate_profile.h"

#include "modules/pid_module.h"

modulePid_t *modulePid;

void pidSetController(pidControllerType_e type)
{
    modulePid->vTable->setController(type);
}

void pidResetITerm(void)
{
    modulePid->vTable->resetITerm();
}

void pidController(
        const pidProfile_t *pidProfile,
        const struct controlRateConfig_s *controlRateConfig,
        uint16_t max_angle_inclination,
        const rollAndPitchTrims_t *angleTrim,
        const uint16_t midrc
) {
    modulePid->pid_controller(pidProfile, controlRateConfig, max_angle_inclination, angleTrim, midrc);
}

void module_pidSetInstance(modulePid_t *instance)
{
    modulePid = instance;
}
