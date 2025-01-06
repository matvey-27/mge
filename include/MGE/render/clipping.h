#pragma once

#include "camera.h"
#include "../math/vec3.hpp"

namespace mge {

    vec3<float> ClipTringle();
    
    vec3<float> SignedDistance(vec3<float> plane, vec3<float>* vertex);
    
}