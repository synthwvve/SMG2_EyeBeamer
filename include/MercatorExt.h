#pragma once
#include "syati.h"

namespace MR {
    void convertMercatorPlaneToSphereTransAndRotate(TVec3f* pPos, TPos3f* pRotation, const TVec3f& rPos, bool applyInverse);
    void convertMercatorPlaneToSphereTransAndRotate(TVec3f* pPos, TVec3f* pRotation, const TVec3f& rPos, bool applyInverse);
}